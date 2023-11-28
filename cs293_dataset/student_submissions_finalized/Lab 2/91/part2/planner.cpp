#include "planner.hpp"

static bool float_eq(float f1, float f2)
{
    return ((f1 - f2) < FLT_EPSILON) && ((f1 - f2) > (-FLT_EPSILON));
}

static bool float_gt(float f1, float f2)
{
    return (f1 > (f2 + FLT_EPSILON));
}

static bool float_lt(float f1, float f2)
{
    return float_gt(f2, f1);
}

static bool float_gte(float f1, float f2)
{
    return (f1 > (f2 - FLT_EPSILON));
}

static bool float_lte(float f1, float f2)
{
    return float_gte(f2, f1);
}

Journey::Journey()
    : st(2400), et(2400)
{
    s1[0] = '\0';
    s2[0] = '\0';
}

Journey::Journey(char const _s1[], float _st, char const _s2[], float _et)
    : st(_st), et(_et)
{
    strcpy(s1, _s1);
    strcpy(s2, _s2);
}

Journey& Journey::operator=(Journey j2)
{
    strcpy(s1, j2.s1);
    strcpy(s2, j2.s2);
    st = j2.st;
    et = j2.et;
    return (*this);
}

bool Journey::operator==(Journey j2)
{
    return ((strcmp(s1, j2.s1) == 0) && float_eq(st, j2.st) && (strcmp(s2, j2.s2) == 0) && float_eq(et, j2.et));
}

FullJourney::FullJourney(char const _s1[], float _st, char const _s_mid[], float _st_mid, char const _s2[], float _et)
    : st(_st), st_mid(_st_mid), et(_et)
{
    strcpy(s1, _s1);
    strcpy(s_mid, _s_mid);
    strcpy(s2, _s2);
}

FullJourney::FullJourney()
    : st(2400), st_mid(2400), et(2400)
{
    s1[0] = '\0';
    s_mid[0] = '\0';
    s2[0] = '\0';
}

FullJourney::FullJourney(Journey* j1, Journey* j2)
{
    if (j1 == nullptr) {
        s1[0] = s_mid[0] = s2[0] = '\0';
        st = st_mid = et = 2400;
    }
    else {
        strcpy(s1, j1->s1);
        st = j1->st;
        if (j2 != nullptr) {
            strcpy(s_mid, j2->s1);
            st_mid = j2->st;
            strcpy(s2, j2->s2);
            et = j2->et;
        }
        else {
            s_mid[0] = '\0';
            st_mid = j1->et;
            strcpy(s2, j1->s2);
            et = j1->et;
        }
    }
}

FullJourney& FullJourney::operator=(FullJourney J2)
{
    strcpy(s1, J2.s1);
    strcpy(s_mid, J2.s_mid);
    strcpy(s2, J2.s2);
    st = J2.st;
    st_mid = J2.st_mid;
    et = J2.et;
    return (*this);
}

bool FullJourney::operator==(FullJourney J2)
{
    return ((strcmp(s1, J2.s1) == 0) && float_eq(st, J2.st) && (strcmp(s_mid, J2.s_mid) == 0) && float_eq(st_mid, J2.st_mid) && (strcmp(s2, J2.s2) == 0) && float_eq(et, J2.et));
}

Station::Station()
{
    name[0] = '\0';
}

Station::Station(char const _name[])
    : n(0)
{
    strcpy(name, _name);
}

void Station::add_journey(Journey j)
{
    bool new_journey = true;
    assert(strcmp(j.s1, name) == 0);
    for (int i = 0; i < n; i++) {
        if (journeys[i] == j) {
            new_journey = false;
            break;
        }
    }
    if (new_journey) {
        journeys[n] = j;
        n += 1;
    }
}

Journey* Station::find_next_direct_journey(float now, char const dest[])
{
    Journey* j = nullptr;
    for (int i = 0; i < n; i++) {
        if ((strcmp(journeys[i].s2, dest) == 0) && float_gt(journeys[i].st, now)) {
            if (j == nullptr || float_lt(journeys[i].st, j-> st)) {
                j = journeys + i;
            }
        }
    }
    return j;
}

bool Planner::add(char const s1_name[], float st, char const s2_name[], float et)
{
    if (!stations.get(s1_name)) {
        stations.put(s1_name, Station(s1_name));
        Station* s1_ptr = stations.get(s1_name);
        s1_ptr->add_journey(Journey(s1_name, st, s2_name, et));
    }
    else {
        Station* s1_ptr = stations.get(s1_name);
        s1_ptr->add_journey(Journey(s1_name, st, s2_name, et));
    }
    if (!stations.get(s2_name)) {
        stations.put(s2_name, Station(s2_name));
    }
}

FullJourney Planner::find_next_journey(char const s1_name[], float now, char const s2_name[])
{
    Station* s1 = stations.get(s1_name);
    Journey* j = s1->find_next_direct_journey(now, s2_name);
    FullJourney J = FullJourney(j, nullptr);
    float min_time;
    
    if (j == nullptr)
        min_time = 2400;
    else
        min_time = j->st;

    for (int i = 0; i < s1->n; i++) {
        Journey j1 = s1->journeys[i];
        if (float_lte(j1.st, now) || float_gt(j1.st, min_time))
            continue;
        Station* s_mid = stations.get(j1.s2);
        for (int j = 0; j < s_mid->n; j++) {
            Journey j2 = s_mid->journeys[j];
            if (float_gt(j2.st, j1.et) && (strcmp(j2.s2, s2_name) == 0)) {
                J = FullJourney(&j1, &j2);
                break;
            }
        }
    }
    return J;
}

void Planner::Query()
{
    while (true) {
        char type[CHAR_ARRAY_SIZE];
        char s1_name[CHAR_ARRAY_SIZE];
        char s2_name[CHAR_ARRAY_SIZE];
        float st, et;
        std::cin >> type;
        if (strcmp(type, "EXIT") == 0)
            break;
        std::cin >> s1_name >> st;
        if (strcmp(type, "ADD") == 0) {
            std::cin >> s2_name >> et;
            add(s1_name, st, s2_name, et);
        }
        else if (strcmp(type, "QUERY_STATION") == 0) {
            Station* s1 = stations.get(s1_name);
            if (s1 == nullptr) {
                std::cout << "ERROR: Station does not exist\n";
                continue;
            }
            else {
                for (int i = 0; i < s1-> n; i++) {
                    Journey j = s1->journeys[i];
                    if (float_gte(j.st, st)) {
                        std::cout << j.st << ' ' << j.s2 << '\n';
                    }
                }
            }
        }
        else if (strcmp(type, "QUERY_JOURNEY") == 0) {
            std::cin >> s2_name;
            Station* s1 = stations.get(s1_name);
            Station* s2 = stations.get(s2_name);
            if (s1 == nullptr || s2 == nullptr) {
                std::cout << "ERROR: Station does not exist\n";
                continue;
            }
            else {
                FullJourney J = find_next_journey(s1_name, st, s2_name);
                if (J == FullJourney()) {
                    std::cout << "ERROR: No journey found\n";
                    continue;
                }
                else {
                    std::cout << J.st << ' ' << J.s_mid << (J.s_mid[0] == '\0'? "" : (" " + std::to_string((int)J.st_mid))) << '\n';
                    continue;
                }
            }
        }
        else {
            std::cout << "ERROR: Invalid Query\n";
        }
    }
}

int main()
{
    Planner p;
    p.Query();
}
