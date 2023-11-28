#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#include "planner.h"
#ifndef STD_HEADERS_H
#include "std_headers.h"
#include "dictionary.h"
#include "codes.h"
#endif

using namespace std;

int check(TrainInfoPerStation *l1, TrainInfoPerStation *l2)
{
  int x1;
  int x2;
  int t1 = l1->arrTime;
  int t2 = l2->depTime;
  for (int i = 0; i < 7; i++)
  {
    if (l1->daysOfWeek[i] == true)
    {
      x1 = i;
      break;
    }
  }
  for (int i = 0; i < 7; i++)
  {
    if (l2->daysOfWeek[i] == true)
    {
      x2 = i;
      if (x2 > x1)
      {
        break;
      }
      if (x2 == x1)
      {
        if (t2 >= t1)
        {
          break;
        }
      }
    }
  }

  int t1_hr = t1 / 100;
  int t2_hr = t2 / 100;
  int t1_min = t1 - (t1_hr * 100);
  int t2_min = t2 - (t2_hr * 100);
  if (t1_min > t2_min)
  {
    t2_hr--;
    t2_min += 60;
  }
  t2_hr += 24 * (x2 - x1);
  int diff = (t2_hr - t1_hr) * 60 + (t2_min - t1_min);

  return diff;
}

int distinct(listOfObjects<TrainInfoPerStation *> *list)
{
  int same = 0;
  int len = 1;
  listOfObjects<TrainInfoPerStation *> *temp = list;
  if (temp == nullptr)
  {
    return 0;
  }
  while (temp->next != nullptr)
  {
    if (temp->object->journeyCode == temp->next->object->journeyCode)
    {
      same++;
    }
    len++;
    temp = temp->next;
  }
  return len - same;
}
int length(listOfObjects<TrainInfoPerStation *> *list)
{
  int len = 1;
  listOfObjects<TrainInfoPerStation *> *temp = list;
  while (temp->next != nullptr)
  {
    len++;
    temp = temp->next;
  }
  return len;
}
listOfObjects<TrainInfoPerStation *> *return_tail(listOfObjects<TrainInfoPerStation *> *list)
{
  listOfObjects<TrainInfoPerStation *> *temp = list;
  while (temp->next != nullptr)
  {
    temp = temp->next;
  }
  return temp;
}
listOfObjects<int> *return_tail_int(listOfObjects<int> *list)
{
  listOfObjects<int> *temp = list;
  while (temp->next != nullptr)
  {
    temp = temp->next;
  }
  return temp;
}
int add_path(StationAdjacencyList *adjacency, int curridx, int destidx, listOfObjects<TrainInfoPerStation *> *path_list, listOfObjects<int> *idx_list)
{
  listOfObjects<StationConnectionInfo *> *adjToList = adjacency[curridx].toStations;
  listOfObjects<StationConnectionInfo *> *x = adjacency[curridx].toStations;
  listOfObjects<TrainInfoPerStation *> *r = path_list;
  listOfObjects<TrainInfoPerStation *> *q = r;
  listOfObjects<int> *den = idx_list;
  listOfObjects<int> *ben = den;
  if (r != nullptr)
  {
    r = return_tail(r);
  }
  if (den != nullptr)
  {
    den = return_tail_int(den);
  }
  if (curridx == destidx)
  {

    r->next = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-2, 0, 0, 0));
    den->next = new listOfObjects<int>(-2);
    return -2;
  }
  else if (adjToList == nullptr)
  {

    r->next = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-3, 0, 0, 0));
    den->next = new listOfObjects<int>(-3);
    return -3;
  }

  else
  {
    while (adjToList != nullptr)
    {

      listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
      while (ltrai != nullptr)
      {

        int idx = adjToList->object->adjacentStnIndex;
        q = return_tail(r);
        q->next = new listOfObjects<TrainInfoPerStation *>(ltrai->object);
        ben = return_tail_int(den);
        ben->next = new listOfObjects<int>(idx);

        int dummy = add_path(adjacency, idx, destidx, q, ben);
        listOfObjects<TrainInfoPerStation *> *tempo = return_tail(q);
        listOfObjects<int> *temmpora = return_tail_int(ben);
        if (dummy == -3)
        {
          q->next = nullptr;
          ben->next = nullptr;
        }
        else if (dummy == -2 && adjToList->next != nullptr)
        {
          tempo->next = new listOfObjects<TrainInfoPerStation *>(q->object);
          temmpora->next = new listOfObjects<int>(ben->object);
        }
        ltrai = ltrai->next;
      }
      adjToList = adjToList->next;
    }

    return -4;
  }
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;

  int destStnIdx = stnNameToIndex.get(destStnName)->value;

  listOfObjects<int> *index_list = new listOfObjects<int>(-2);
  listOfObjects<int> *index = index_list;
  listOfObjects<TrainInfoPerStation *> *x = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-2, 1, 2, 3));
  listOfObjects<StationConnectionInfo *> *adjToList = adjacency[srcStnIdx].toStations;
  listOfObjects<TrainInfoPerStation *> *p = x;

  while (adjToList != nullptr)
  {

    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;

    while (ltrai != nullptr)
    {

      int idx = adjToList->object->adjacentStnIndex;
      p = return_tail(p);
      p->next = new listOfObjects<TrainInfoPerStation *>(ltrai->object);
      index = return_tail_int(index);
      index->next = new listOfObjects<int>(idx);
      int fuck = add_path(adjacency, idx, destStnIdx, p, index);

      ltrai = ltrai->next;
    }
    adjToList = adjToList->next;
  }
  listOfObjects<TrainInfoPerStation *> *triuyt = x;
  int count = 0;
  while (triuyt != nullptr)
  {
    if (triuyt->object->journeyCode == -2)
    {
      count++;
    }
    triuyt = triuyt->next;
  }
  if (count <= 1)
  {
    cout << RED << "NO JOURNEYS" << RESET << endl;
  }
  else
  {
    listOfObjects<int> *iarr[10];
    listOfObjects<int> *xiarr[10];
    int isize[10];
    int idiff[10];
    bool ivalid[10];
    for (int i = 0; i < 10; i++)
    {
      xiarr[i] = new listOfObjects<int>(-4);
    }
    for (int i = 0; i < 10; i++)
    {
      isize[i] = 0;
      idiff[i] = 1;
      iarr[i] = new listOfObjects<int>(-3);
    }
    int ii = 0;
    while (index_list != nullptr)
    {
      if (index_list->object != -2)
      {
        if (isize[ii] == 0)
        {
          iarr[ii]->object = index_list->object;
        }
        else
        {
          listOfObjects<int> *r = return_tail_int(iarr[ii]);
          r->next = new listOfObjects<int>(index_list->object);
        }
        isize[ii]++;
        index_list = index_list->next;
      }
      else if (isize[ii] != 0)
      {
        index_list = index_list->next;
        ii++;
      }
      else
      {
        index_list = index_list->next;
      }
    }
    for (int j = 0; j < 10; j++)
    {
      xiarr[j] = iarr[j];
      int ixh = 0;
      while (ixh < isize[j])
      {
        if (ixh + 1 < isize[j])
        {
          if (xiarr[j]->object != xiarr[j]->next->object)
          {
            idiff[j]++;
          }
        }
        xiarr[j] = xiarr[j]->next;
        ixh++;
      }
    }
    listOfObjects<int> *finalarr = new listOfObjects<int>(-5);
    for (int j = 0; j < 10; j++)
    {
      int xih = 0;
      if (idiff[j] - 1 <= maxStopOvers)
      {
        int dum = 0;
        while (xih < isize[j])
        {

          if (dum == 0 && j == 0)
          {

            finalarr->object = iarr[j]->object;
          }
          else
          {
            listOfObjects<int> *r1 = return_tail_int(finalarr);
            r1->next = new listOfObjects<int>(iarr[j]->object);
          }
          iarr[j] = iarr[j]->next;
          xih++;
          dum++;
        }
      }
    }

    listOfObjects<TrainInfoPerStation *> *arr[10];
    listOfObjects<TrainInfoPerStation *> *xarr[10];
    int size[10];
    int diff[10];
    bool valid[10];
    for (int i = 0; i < 10; i++)
    {
      xarr[i] = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-4, 0, 0, 0));
    }
    for (int i = 0; i < 10; i++)
    {
      size[i] = 0;
      valid[i] = true;
      diff[i] = 1;
      arr[i] = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(-3, 0, 0, 0));
    }

    int i = 0;
    while (x != nullptr)
    {
      if (x->object->journeyCode != -2)
      {
        if (size[i] == 0)
        {
          arr[i]->object = x->object;
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *r = return_tail(arr[i]);
          r->next = new listOfObjects<TrainInfoPerStation *>(x->object);
        }
        size[i]++;
        x = x->next;
      }
      else if (size[i] != 0)
      {
        x = x->next;
        i++;
      }
      else
      {
        x = x->next;
      }
    }

    for (int j = 0; j < 10; j++)
    {
      xarr[j] = arr[j];
      int xh = 0;
      while (xh < size[j])
      {
        if (xh + 1 < size[j])
        {
          if (xarr[j]->object->journeyCode != xarr[j]->next->object->journeyCode)
          {
            listOfObjects<int> *temporary = finalarr;
            int findx = 0;
            for (int k = 0; k < j; k++)
            {
              findx = findx + size[k];
            }
            findx = findx + xh;
            diff[j]++;
            int corindx = 0;
            if (findx == 0)
            {
              corindx = temporary->object;
            }
            while (findx > 1)
            {
              temporary = temporary->next;
              findx--;
            }
            if (corindx == 0)
            {
              corindx = temporary->next->object;
            }

            int paridx;
            if (xh == 0)
            {
              paridx = srcStnIdx;
            }
            else
            {
              paridx = temporary->object;
            }

            listOfObjects<StationConnectionInfo *> *slist = adjacency[corindx].fromStations;
            listOfObjects<StationConnectionInfo *> *sellist;
            while (slist != nullptr)
            {
              if (slist->object->adjacentStnIndex == paridx)
              {
                sellist = slist;
              }
              slist = slist->next;
            }
            listOfObjects<TrainInfoPerStation *> *flist = sellist->object->trains;
            TrainInfoPerStation *arrival;
            while (flist != nullptr)
            {
              if (flist->object->journeyCode == xarr[j]->object->journeyCode)
              {
                arrival = flist->object;
              }
              flist = flist->next;
            }
            if (check(arrival, xarr[j]->next->object) > (maxTransitTime * 60))
            {

              valid[j] = false;
            }
          }
        }
        xarr[j] = xarr[j]->next;
        xh++;
      }
    }

    for (int j = 0; j < 10; j++)
    {
      xarr[j] = arr[j];
      int xh = 0;

      if (valid[j] && size[j] != 0)
      {

        if (diff[j] - 1 <= maxStopOvers)
        {
          std::cout << RED << "JOURNEYS :" << RESET << endl
                    << endl;

          while (xh < size[j])
          {

            listOfObjects<int> *temporary = finalarr;
            int findx = 0;
            for (int k = 0; k < j; k++)
            {
              findx = findx + size[k];
            }
            findx = findx + xh;

            int corindx = 0;
            if (findx == 0)
            {
              corindx = temporary->object;
            }
            while (findx > 1)
            {
              temporary = temporary->next;
              findx--;
            }
            if (corindx == 0)
            {
              corindx = temporary->next->object;
            }
            int paridx;
            if (xh == 0)
            {
              paridx = srcStnIdx;
            }
            else
            {
              paridx = temporary->object;
            }
            string parname = stnNameToIndex.getKeyAtIndex(paridx);
            string childname = stnNameToIndex.getKeyAtIndex(corindx);

            if (xh == 0)
            {
              std::cout << BLUE << "AT " << parname << " STATION" << endl
                        << endl;
              string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
              cout << GREEN << "Day(s): " << RESET;
              for (int i = 0; i < 7; i++)
              {
                if (xarr[j]->object->daysOfWeek[i])
                  cout << GREEN << days[i] << " ";
              }

              cout << endl
                   << endl;
              cout << RED << "JourneyCode: " << xarr[j]->object->journeyCode << RESET << "\t";
              cout << RED << "Arr: " << RESET;
              if (xarr[j]->object->arrTime == -1)
              {
                cout << "Starts";
              }
              else
              {
                cout << RED << xarr[j]->object->arrTime << RESET << "\t";
              }
              cout << RED << " Dep: " << RESET;
              if (xarr[j]->object->depTime == -1)
              {
                cout << "Ends";
              }
              else
              {
                cout << RED << xarr[j]->object->depTime << RESET << endl
                     << endl;
              }
            }
            if (xh + 1 < size[j])
            {

              cout << BLUE << "AT " << childname << " STATION" << RESET << endl
                   << endl;

              listOfObjects<StationConnectionInfo *> *slist = adjacency[corindx].fromStations;
              listOfObjects<StationConnectionInfo *> *sellist;
              while (slist != nullptr)
              {
                if (slist->object->adjacentStnIndex == paridx)
                {
                  sellist = slist;
                }
                slist = slist->next;
              }
              listOfObjects<TrainInfoPerStation *> *flist = sellist->object->trains;
              TrainInfoPerStation *arrival;
              while (flist != nullptr)
              {
                if (flist->object->journeyCode == xarr[j]->object->journeyCode)
                {
                  arrival = flist->object;
                }
                flist = flist->next;
              }

              string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

              int x1;
              int x2;
              int t1 = arrival->arrTime;
              int t2 = xarr[j]->next->object->depTime;
              for (int i = 0; i < 7; i++)
              {
                if (arrival->daysOfWeek[i] == true)
                {
                  x1 = i;
                  break;
                }
              }
              for (int i = 0; i < 7; i++)
              {
                if (xarr[j]->next->object->daysOfWeek[i] == true)
                {
                  x2 = i;
                  if (x2 > x1)
                  {
                    break;
                  }
                  if (x2 == x1)
                  {
                    if (t2 >= t1)
                    {
                      break;
                    }
                  }
                }
              }

              cout << RED << "JourneyCode: " << xarr[j]->next->object->journeyCode << RESET << "\t";
              cout << RED << "Arr: " << RESET;
              if (arrival->arrTime == -1)
              {
                cout << "Starts";
              }
              else
              {
                cout << RED << "Day- " << days[x1] << ","
                     << " time- " << arrival->arrTime << RESET << "\t";
              }
              cout << RED << " Dep: " << RESET;
              if (xarr[j]->next->object->depTime == -1)
              {
                cout << "Ends";
              }
              else
              {
                cout << RED << "Day- " << days[x2] << ","
                     << " time- " << xarr[j]->next->object->depTime << RESET << endl
                     << endl;
              }
              if (xarr[j]->object->journeyCode != xarr[j]->next->object->journeyCode)
              {

                cout << GREEN << "Transition time IN MINUTES: " << check(arrival, xarr[j]->next->object) << RESET << endl
                     << endl;
              }
            }
            if (xh == size[j] - 1)
            {
              cout << BLUE << "REACHED " << childname << " STATION" << RESET << endl
                   << endl;

              listOfObjects<StationConnectionInfo *> *slist = adjacency[corindx].fromStations;
              listOfObjects<StationConnectionInfo *> *sellist;
              while (slist != nullptr)
              {
                if (slist->object->adjacentStnIndex == paridx)
                {
                  sellist = slist;
                }
                slist = slist->next;
              }
              listOfObjects<TrainInfoPerStation *> *flist = sellist->object->trains;
              TrainInfoPerStation *arrival;
              while (flist != nullptr)
              {
                if (flist->object->journeyCode == xarr[j]->object->journeyCode)
                {
                  arrival = flist->object;
                }
                flist = flist->next;
              }

              cout << RED << "FROM JourneyCode: " << xarr[j]->object->journeyCode << RESET << "\t";
              cout << RED << "Arrived at: " << RESET;
              if (arrival->arrTime == -1)
              {
                cout << "Starts";
              }
              else
              {
                cout << RED << arrival->arrTime << RESET << "\t";
              }
            }

            xarr[j] = xarr[j]->next;
            xh++;
          }
        }
        std::cout << endl
                  << endl
                  << endl
                  << endl;
      }
    }
  }

  return;
}
#endif
