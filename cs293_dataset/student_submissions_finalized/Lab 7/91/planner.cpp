#ifndef PLANNER_CPP
#define PLANNER_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

// Edit version 1: Added COMMENT_START_CHAR to allow reading admin and
// user inputs from file with comments.    The part of a line including
// and after COMMENT_START_CHAR is ignored for interpreting the line.
#define COMMENT_START_CHAR '$'
// End edit version 1

using namespace std;

// Edit version 1: Adding some more color to the welcome message
void Planner::displayWelcomeMessage()
{
    std::cout << BLUE << "*********************************************************" << RESET << '\n';
    std::cout << RED << "Welcome to the CS293 Travel Planner (Autumn 2022 version)" << RESET << '\n';
    std::cout << BLUE << "*********************************************************" << RESET << '\n';
    std::cout << '\n';
}
// End edit version 1

bool Planner::displayMenuAndAct()
{
    int userCode;

    std::cout << "Enter user code (0 to exit): ";
    std::cin >> userCode;
    int userLevel = getUserLevel(userCode);

    if (userLevel == EXIT_LEVEL) {
        std::cout << "Thank you for using the journey planner.\n";
        std::cout << "Bye!\n";
        return false;
    }

    if (userLevel == ADMIN_LEVEL) {
        return doAdminJob();
    }
    else if (userLevel == USER_LEVEL) {
        return doUserJob();
    }
    else {
        std::cout << "Invalid user code\n";
        return true;
    }
}

inline int Planner::getUserLevel(int userCode)
{
    return ((userCode == MAGIC_CODE) ? ADMIN_LEVEL : \
        (userCode == EXIT_CODE) ? EXIT_LEVEL : \
        (userCode > 0) ? USER_LEVEL : INVALID_LEVEL);
}

bool Planner::doAdminJob()
{
    bool readFrmFile = false;
    std::string inpFileName = "";
    std::fstream inpFile;

    do {
        if (!readFrmFile) {
            // Edit version 1: Added some extra std::couts for clarity
            std::cout << "****************************\n";
            // End edit version 1
            std::cout << "Please choose an admin job:\n";
            std::cout << "    0. Exit admin user\n";
            std::cout << "    1. Enter/delete station name\n";
            std::cout << "    2. Enter/delete journey code\n";
            std::cout << "    3. Read commands from file\n";
            std::cout << "    4. Exit reading commands from file\n";

            // Edit version 1: Added option to print trie of station names"Input: " to the output std::string
            // Also added printing of the std::string "Input: " before the
            // user types in an input
            std::cout << "    5. Print trie of station names\n";
            // Lab 7 specific
            std::cout << "    6. Enter journey information\n";
            // End lab 7 specific
            std::cout << '\n' << "Input: ";
            // End edit version 1

        }

        int option = getInt(readFrmFile, &inpFile);

        if (!readFrmFile && (option == ADMIN_READ_FROM_FILE)) {
            logFile << "Executing \"Read commands from file\" \n";

            std::cout << "    Input file name: ";
            std::cin >> inpFileName;

            inpFile.open(inpFileName, ios::in);
            if (!inpFile.is_open()) {
                std::cout << "Failed to open file " << inpFileName << " for reading\n";
                logFile << "Failed\n";
                inpFileName = "";
            }
            else {
                logFile << "Success\n";
                readFrmFile = true;
            }
            continue;
        }
        else if (readFrmFile && (option == ADMIN_READ_FROM_FILE)) {
            logFile << "Executing \"Read commands from file\" \n";
            logFile << "Ignoring ...\n";

            // Edit version 1: Made the error message a bit explanatory
            std::cerr << "\"Read from file\" command encountered while already reading from file. Ignoring ...\n";
            // End edit version 1
            continue;
        }
        else if (readFrmFile && (option == ADMIN_EXIT_READ_FROM_FILE)) {
            logFile << "Executing \"Exit reading commands from file\" \n";

            // Edit version 1: Made the message a bit more explanatory
            std::cout << "Finished reading and executing commands from file\n";
            // End edit version 1
            inpFile.close();
            if (!inpFile.is_open()) {
                logFile << "Success\n";
            }
            else {
                logFile << "Failed.\n";
            }
            readFrmFile = false;
            inpFileName = "";
            continue;
        }
        else if (!readFrmFile && (option == ADMIN_EXIT_READ_FROM_FILE)) {
            logFile << "Executing \"Exit reading commands from file\" \n";
            logFile << "Ignoring ...\n";

            std::cerr << "\"Exit read from file\" command while not reading from file. Ignoring ...\n";
            continue;
        }
        else {
            // option is neither ADMIN_READ_FROM_FILE nor ADMIN_EXIT_READ_FROM_FILE

            switch (option) {
                case ADMIN_EXIT:
                    logFile << "Executing \"Exit admin user\"\n";

                    std::cout << "Thank you for being an admin!\n";
                    std::cout << "Bye!!!\n";
                    if (readFrmFile) {
                        readFrmFile = false;
                        inpFileName = "";
                        if (inpFile.is_open()) {
                            inpFile.close();
                        }
                    }
                    return true;

                case ADMIN_ENTER_DELETE_STN_NAME:
                    logFile << "Executing \"Enter/delete station name\"\n";

                    if (!readFrmFile) {
                        // Edit version 1: Added some extra std::couts for clarity
                        std::cout << "****************************\n";
                        // End edit version 1
                        std::cout << "Entering/deleting station name. \n";
                        std::cout << " Choose a sub-option:\n";
                        std::cout << "    11. Enter new station name\n";
                        std::cout << "    12. Delete station name\n";
                        // Edit version 1: Added "Input: " to the output std::string
                        std::cout << '\n' << "Input: ";
                        // End edit version 1
                    }

                    option = getInt(readFrmFile, &inpFile);
                    if ((option != ADMIN_ENTER_STN_NAME) &&
                            (option != ADMIN_DELETE_STN_NAME)) {
                        logFile << "Invalid sub-option\n";
                        if (!readFrmFile) {
                            std::cout << "Invalid sub-option (" << option << ")! Please try again.\n";
                        }
                        continue;
                    }
                    else if (option == ADMIN_ENTER_STN_NAME) {
                        logFile << "Executing \"Enter station name\"\n";

                        if (!readFrmFile) {
                            std::cout << "Enter complete station name: ";
                        }
                        std::string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
                        if (addStationName(srcStnName)) {
                            logFile << "Success\n";
                        }
                        else {
                            logFile << "Failed.\n";
                        }
                        continue;
                    }
                    else { // option = ADMIN_DELETE_STN_NAME)
                        logFile << "Executing \"Delete station name\"\n";
                        if (!readFrmFile) {
                            std::cout << "Enter complete station name: ";
                        }
                        std::string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
                        if (delStationName(srcStnName)) {
                            logFile << "Success\n";
                        }
                        else {
                            logFile << "Failed.\n";
                        }
                        continue;
                    }

                case ADMIN_ENTER_DELETE_JOURNEY_CODE:
                    logFile << "Executing \"Enter/delete journey code\"\n";

                    if (!readFrmFile) {
                        // Edit version 1: Added some extra std::couts for clarity
                        std::cout << "****************************\n";
                        // End edit version 1
                        std::cout << '\n' << "Entering/deleting journey code. ";
                        std::cout << " Choose a sub-option:\n";
                        std::cout << "    21. Enter a new journey code\n";
                        std::cout << "    22. Delete a journey code\n";
                        // Edit version 1: Added "Input: " to the output std::string
                        std::cout << '\n' << "Input: ";
                        // End edit version 1
                    }

                    option = getInt(readFrmFile, &inpFile);
                    if ((option != ADMIN_ENTER_JOURNEY_CODE) &&
                            (option != ADMIN_DELETE_JOURNEY_CODE)) {
                        logFile << "Invalid sub-option\n";
                        if (!readFrmFile) {
                            std::cout << "Invalid sub-option (" << option << ")! Please try again.\n";
                            continue;
                        }
                        // Edit version 1: Closing an if branch.    This was incorrectly
                        // closed in the original version
                    }
                    // End edit version 1

                    else if (option == ADMIN_ENTER_JOURNEY_CODE) {
                        logFile << "Executing \"Enter journey code\"\n";

                        if (!readFrmFile) {
                            std::cout << "Enter journey code: ";
                        }
                        int journeyCode = getInt(readFrmFile, &inpFile);
                        if (!readFrmFile) {
                            std::cout << "Enter complete source station name: ";
                        }
                        std::string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
                        if (!readFrmFile) {
                            std::cout << "Enter complete destination station name: ";
                        }
                        std::string destStnName = getStringWithSpaces(readFrmFile, &inpFile);
                        if (addJourneyCode(srcStnName, destStnName, journeyCode)) {
                            logFile << "Success\n";
                        }
                        else {
                            logFile << "Failed.\n";
                        }
                        continue;
                    }
                    else { // option = ADMIN_DELETE_JOURNEY_CODE)
                        logFile << "Executing \"Delete journey code\"\n";
                        if (!readFrmFile) {
                            std::cout << "Enter journey code: ";
                        }
                        int journeyCode = getInt(readFrmFile, &inpFile);
                        if (!readFrmFile) {
                            std::cout << "Enter complete source station name: ";
                        }
                        std::string srcStnName = getStringWithSpaces(readFrmFile, &inpFile);
                        if (!readFrmFile) {
                            std::cout << "Enter complete destination station name: ";
                        }
                        std::string destStnName = getStringWithSpaces(readFrmFile, &inpFile);

                        if (delJourneyCode(srcStnName, destStnName, journeyCode)) {
                            logFile << "Success\n";
                        }
                        else {
                            logFile << "Failed.\n";
                        }
                        continue;
                    }

                    break;

            case ADMIN_PRINT_TRIE:
                stnNamesTrie->printTrie();
                continue;

            // Lab 7 specific
            case ADMIN_ENTER_JOURNEY_INFO:
                int stnIndex;
                listOfObjects<TrainInfoPerStation *> *newTrainInfo;
                TrainInfoPerStation *stnTrainInfo;
                int depTime, arrTime, dayCount;
                int len, numStops, journeyCode;
                Entry<int> *stnEntry;
                int daysOfWeek;

                if (!readFrmFile) {
                    std::cout << "Enter journey code (train no.): ";
                }
                journeyCode = getInt(readFrmFile, &inpFile);

                if (!readFrmFile) {
                    std::cout << "Enter count of stops (including src and dest): ";
                }
                numStops = getInt(readFrmFile, &inpFile);

                if (!readFrmFile) {
                    std::cout << "Enter binary std::string of length 7 to denote days of week when train leaves source station: ";
                }
                daysOfWeek = getInt(readFrmFile, &inpFile);
                // len = daysOfWeek.length();
                // if (len != 7) {
                //     logFile << "Incorrect format for specifying days of week when train leaves source station\n";
                //     std::cout << "Incorrect format for specifying days of week when train leaves source station\n";
                //     break;
                // }

                for (int i=0; i < numStops; i++) {
                    if (!readFrmFile) {
                        std::cout << "Enter full station name: ";
                    }
                    std::string stnName = getStringWithSpaces(readFrmFile, &inpFile);
                    stnEntry = stnNameToIndex.get(stnName);
                    if (stnEntry == nullptr) {
                        logFile << "Couldn't find station " << stnName << " in stnNameToIndex dictionary.\n";
                        std::cerr << "Couldn't find station " << stnName << " in stnNameToIndex dictionary.\n";
                        continue;
                    }
                    else {
                        stnIndex = stnEntry->value;
                    }

                    if (!readFrmFile) {
                        std::cout << "Enter day count, arrival and departure times (-1 if not applicable): ";
                    }
                    dayCount = getInt(readFrmFile, &inpFile);
                    if ((i == 0) && (dayCount != 1)) {
                        std::cerr << "Source station must have day count 1; setting it to 1\n";
                        dayCount = 1;
                    }

                    arrTime = getInt(readFrmFile, &inpFile);
                    if ((i == 0) && (arrTime != -1)) {
                        std::cerr << "Source station must have arrival time -1; setting it to -1\n";
                        arrTime = -1;
                    }

                    depTime = getInt(readFrmFile, &inpFile);
                    if ((i == numStops-1) && (depTime != -1)) {
                        std::cerr << "Final destination station must have departure time -1; setting it to -1\n";
                        depTime = -1;
                    }

                    // Now fill in the train information per station
                    stnTrainInfo = new TrainInfoPerStation(journeyCode, (unsigned short) i, arrTime, depTime);
                    if (stnTrainInfo == nullptr) {
                        logFile << "Memory allocation failure\n";
                        std::cerr << "Memory allocation failure.\n";
                        continue;
                    }
                    for (int j = 0; j < 7; j++) {
                        if (daysOfWeek % 10 == 1) stnTrainInfo->setDayOfWeek((j+(dayCount-1))%7);
                        else if (daysOfWeek % 10 == 0) stnTrainInfo->resetDayOfWeek(j+(dayCount-1)%7);
                        else {
                            logFile << "Incorrect days of week input\n";
                            std::cerr << "Incorrect days of week input\n";
                            continue;
                        }

                    }
                    newTrainInfo = new listOfObjects<TrainInfoPerStation *> (stnTrainInfo);
                    if (newTrainInfo == nullptr) {
                        logFile << "Memory allocation failure.\n";
                        std::cerr << "Memory allocation failure.\n";
                        continue;
                    }

                    if (stationInfo[stnIndex] == nullptr) {
                        stationInfo[stnIndex] = newTrainInfo;
                    }
                    else {
                        newTrainInfo->next = stationInfo[stnIndex];
                        if (newTrainInfo->next != nullptr) {
                            newTrainInfo->next->prev = newTrainInfo;
                        }
                        stationInfo[stnIndex] = newTrainInfo;
                    }
                }
                continue;
                // End lab 7 specific
            default:
                logFile << "Invalid admin user option (" << option << ")\n";
                std::cerr << "Invalid admin user option (" << option << ")\n";
                continue;
            }
        }
    } while (true);
}

bool Planner::doUserJob() {
    int option;
    std::string srcStnName, destStnName;

    // Edit version 1: Commenting the following declarations
    // They are no longer needed.
    // std::string srcPrefix, dstPrefix, tempPrefix;
    // End edit version 1

    std::string reviewstring, keywordString;
    int journeyCode, reviewId;
    bool delReviewStatus;
    char filterChoice;
    int *hMatrix;
    listOfObjects<JourneyCodeReview> *listOfJCodeReviews, *currJCodeReview;
    listOfObjects<std::string> *currReview;
    int matchStartIndex;

    // Edit version 1: Adding code to enable reading commands from a file
    std::string filterWord;
    std::string srcPartWords, destPartWords;
    listOfObjects<std::string> *listOfWords, *completions;
    bool readFrmFile = false;

    std::string inpFileName = "";
    std::fstream inpFile;
    // End edit version 1

    do {

        // Edit version 1: Added some extra std::couts for clarity
        // Also added condition to check if reading from file
        if (!readFrmFile) {
            std::cout << "****************************\n";
            // End edit version 1

            std::cout << "Please choose a user job:\n";
            std::cout << "    100. Exit user\n";
            std::cout << "    110. Enter/delete review\n";
            std::cout << "    120. Find journeys\n";

            // Edit version 1: Added the following two user commands
            std::cout << "    130. Read commands from a file\n";
            std::cout << "    140. Exit reading commands from a file\n";
            // Lab 7 specific
            std::cout << "    150. Find all journeys from station\n";
            // End lab 7 specific
            // End edit version 1

            // Edit version 1: Added "Input: " to the output std::string
            std::cout << '\n' << "Input: ";
            // End edit version 1
        }

        // Edit version 1: Read either from std::cin or from inpFile
        // Code to read and process commands from inpFile or
        // to stop reading commands from inpFile, and revert to
        // reading commands from std::cin
        //
        // std::cin >> option;
        option = getInt(readFrmFile, &inpFile);

        if (!readFrmFile && (option == USER_READ_FROM_FILE)) {
            logFile << "Executing \"Read commands from file\" \n";

            std::cout << "    Input file name: ";
            std::cin >> inpFileName;

            inpFile.open(inpFileName, ios::in);
            if (!inpFile.is_open()) {
    std::cout << "Failed to open file " << inpFileName << " for reading\n";
    logFile << "Failed\n";
    inpFileName = "";
            }
            else {
    logFile << "Success\n";
    readFrmFile = true;
            }
            continue;
        }
        else if (readFrmFile && (option == USER_READ_FROM_FILE)) {
            logFile << "Executing \"Read commands from file\" \n";
            logFile << "Ignoring ...\n";

            std::cerr << "\"Read from file\" command encountered while reading from file. Ignoring ...\n";
            continue;
        }
        else if (readFrmFile && (option == USER_EXIT_READ_FROM_FILE)) {
            logFile << "Executing \"Exit reading commands from file\" \n";

            // Edit version 1: Made the message a bit more explanatory
            std::cout << "Finished reading and executing commands from file\n";
            // End edit version 1
            inpFile.close();
            if (!inpFile.is_open()) {
    logFile << "Success\n";
            }
            else {
    logFile << "Failed.\n";
            }
            readFrmFile = false;
            inpFileName = "";
            continue;
        }
        else if (!readFrmFile && (option == USER_EXIT_READ_FROM_FILE)) {
            logFile << "Executing \"Exit reading commands from file\" \n";
            logFile << "Ignoring ...\n";

            std::cerr << "\"Exit read from file\" command while not reading from file. Ignoring ...\n";
            continue;
        }
        else {
            // End edit version 1

            switch (option) {
                case USER_EXIT:
                    logFile << "Executing \"Exit normal user\"\n";

                    std::cout << "Thank you for being a user!\n";
                    std::cout << "Bye!!!\n";
                    return true;

                case USER_ENTER_DELETE_REVIEW:
                    logFile << "Executing \"Enter/delete review\"\n";

                    // Edit version 1: Added some extra std::couts for clarity
                    // Also added a check on the flag readFrmFile
                    if (!readFrmFile) {
                        std::cout << "****************************\n";
                        // End edit version 1

                        std::cout << "Entering/deleting station name. \n";
                        std::cout << " Choose a sub-option:\n";
                        std::cout << "    111. Enter new review\n";
                        std::cout << "    112. Delete review\n";
                        // Edit version 1: Added "Input: " to the output std::string
                        std::cout << '\n' << "Input: ";
                        // End edit version 1

                        // Edit version 1: Closing the if (!readFrmFile) brace
                    }
                    // End edit version 1

                    // Edit version 1: Changing "std::cin >> option" to a function call
                    // that either reads from std::cin or from an input file, as specified
                    // std::cin >> option;
                    option = getInt(readFrmFile, &inpFile);
                    // End edit version 1

                    if ((option != USER_ENTER_REVIEW) && (option != USER_DELETE_REVIEW)) {
                        logFile << "Invalid sub-option\n";
                        std::cout << "Invalid sub-option (" << option << ")! Please try again.\n";
                        continue;
                    }
                    else { // option == USER_ENTER_REVIEW or option == USER_DELETE_REVIEW
                        if (option == USER_ENTER_REVIEW) {
                            logFile << "Executing \"Enter review\"\n";

                            // Edit version 1: Adding a check on readFrmFile flag
                            if (!readFrmFile) {
                                std::cout << "Enter prefix of any word in source station name: ";
                            }
                            // End edit version 1

                            // Edit version 1: Changing "std::cin >> srcPrefix" followed by
                            // "srcStnName = chooseFromCompletions(srcPrefix)" to the following sequence
                            // of statements.    Note that this allows inputs to be read
                            // either from std::cin or from an input file, as specified.
                            // The following code also lets the user search for a set of completions
                            // from a space separated list of prefixes of individual words that
                            // appear in a station name.    E.g. giving "PU CANT" will return
                            // "PUNE CANTONMENT".

                            srcPartWords = getStringWithSpaces(readFrmFile, &inpFile);
                            listOfWords = findAllWords(srcPartWords);
                            if (listOfWords != nullptr) {
                                completions = stnNamesTrie->completions(listOfWords->object);
                                listOfWords = listOfWords->next;
                                trimByMatchingSubWords(completions, listOfWords);
                                srcStnName = chooseFromCompletions(completions);
                            }
                            // End edit version 1

                            if (srcStnName != "") {
                                logFile << "Chosen source station: " << srcStnName << '\n';

                                // Edit version 1: Adding a check on readFrmFile flag
                                if (!readFrmFile) {
                        std::cout << "Chosen source station: " << srcStnName << '\n';
                                }
                                // End edit version 1
                            }
                            else {
                                logFile << "Failure in choosing source station.\n";
                                std::cout << "Failure in choosing source station.\n";
                                continue;
                            }

                            // Edit version 1: Adding a check on readFrmFile flag
                            if (!readFrmFile) {
                                std::cout << "Enter prefix of any word in destination station name: ";
                            }
                            // End edit version 1

                            // Edit version 1: Changing "std::cin >> dstPrefix" followed by
                            // "destStnName = chooseFromCompletions(destPrefix)" to the following sequence
                            // of statements.    Note that this allows inputs to be read
                            // either from std::cin or from an input file, as specified.
                            // The following code also lets the user search for a set of completions
                            // from a space separated list of prefixes of individual words that
                            // appear in a station name.    E.g. giving "PU CANT" will return
                            // "PUNE CANTONMENT".

                            destPartWords = getStringWithSpaces(readFrmFile, &inpFile);
                            listOfWords = findAllWords(destPartWords);
                            if (listOfWords != nullptr) {
                                completions = stnNamesTrie->completions(listOfWords->object);
                                listOfWords = listOfWords->next;
                                trimByMatchingSubWords(completions, listOfWords);
                                destStnName = chooseFromCompletions(completions);
                            }
                            // End edit version 1

                            if (destStnName != "") {
                                logFile << "Chosen destination station: " << destStnName << '\n';

                                // Edit version 1: Adding a check on readFrmFile flag
                                if (!readFrmFile) {
                        std::cout << "Chosen destination station: " << destStnName << '\n';
                                }
                                // End edit version 1
                            }
                            else {
                                logFile << "Failure in choosing destination station.\n";
                                std::cout << "Failure in choosing destinatoin station.\n";
                                continue;
                            }

                            // Edit version 1: Adding a check on readFrmFile flag
                            if (!readFrmFile) {
                                std::cout << "Enter journey code: ";
                            }
                            // End edit version 1

                            // Edit version 1: Changing "std::cin >> journeyCode" to a function call
                            // that either reads from std::cin or from an input file, as specified
                            // std::cin >> journeyCode;
                            journeyCode = getInt(readFrmFile, &inpFile);
                            // End edit version 1

                            if (!checkValidJourneyCode(srcStnName, destStnName, journeyCode)) {
                                logFile << "Journey Code doesn't match source and destination pair\n";
                                std::cout << "Journey code doesn't match source and destination pair\n";
                                std::cout << "Ignoring command\n";
                                continue;
                            }
                            else {
                                logFile << "Journey code matches source and destination pair\n";

                                // Edit version 1: Adding a check on readFrmFile flag
                                if (!readFrmFile) {
                        std::cout << "Enter short review without any line break:\n";
                                }
                                // End edit version 1

                                // Edit version 1: Changed "std::cin >> reviewstring" to a call to
                                // getStringWithSpaces.    This allows reading from std::cin as well as
                                // from inpFile, as specified.
                                // std::cin >> reviewstring;
                                // if (getline(std::cin >> std::ws, reviewstring)) {
                                reviewstring = getStringWithSpaces(readFrmFile, &inpFile);
                                if (reviewstring != "") {
                        // End edit version 1

                        logFile << "Read review: " << reviewstring << '\n';
                                }
                                else {
                        logFile << "Failure in reading reviewstring\n";
                        std::cout << "Failure in reading reviewstring.\n";
                        continue;
                                }

                                reviewId = addReview(journeyCode, srcStnName, destStnName, reviewstring);
                                if (reviewId > 0) {
                        logFile << "Successfully added review " << reviewId << '\n';

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Added review with review id " << reviewId << '\n';
                        }
                        // End edit version 1
                                }
                                else {
                        logFile << "Failure in adding review\n";
                        std::cout << "Failure in adding review\n";
                                }
                                continue;
                            }
                        }
                        else { // option = USER_DELETE_REVIEW)
                            logFile << "Executing \"Delete review\"\n";

                            // Edit version 1: Adding a check on readFrmFile flag
                            if (!readFrmFile) {
                                std::cout << "Enter review id: \n";
                            }
                            // End edit version 1

                            // Edit version 1: Changing "std::cin >> reviewId" to a function call
                            // that either reads from std::cin or from an input file, as specified
                            // std::cin >> reviewId;
                            reviewId = getInt(readFrmFile, &inpFile);
                            // End edit version 1

                            if (reviewId > 0) {
                                delReviewStatus = delReview(reviewId);
                                if (delReviewStatus) {
                        logFile << "Successfully deleted review " << reviewId << '\n';

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Successfully deleted review " << reviewId << '\n';
                        }
                        // End edit version 1
                                }
                                else {
                        logFile << "Failed to delete review.\n";
                        std::cout << "Failed to delete review.\n";
                                }
                            }
                            else {
                                logFile << "Invalid review id " << reviewId << '\n';
                                std::cout << "Invalid review id " << reviewId <<    '\n';
                            }
                            continue;
                        }
                    }
                    break;
                case USER_FIND_JOURNEYS:
                  {
                    logFile << "Executing \"Find journeys\"\n";

                    // Edit version 1: Adding a check on readFrmFile flag
                    if (!readFrmFile) {
                        std::cout << "Enter prefix of any word in source station name: ";
                    }
                    // End edit version 1

                    // Edit version 1: Changing "std::cin >> srcPrefix" followed by
                    // "srcStnName = chooseFromCompletions(srcPrefix)" to the following sequence
                    // of statements.    Note that this allows inputs to be read
                    // either from std::cin or from an input file, as specified.
                    // The following code also lets the user search for a set of completions
                    // from a space separated list of prefixes of individual words that
                    // appear in a station name.    E.g. giving "PU CANT" will return
                    // "PUNE CANTONMENT".

                    srcPartWords = getStringWithSpaces(readFrmFile, &inpFile);
                    listOfWords = findAllWords(srcPartWords);
                    if (listOfWords != nullptr) {
                        completions = stnNamesTrie->completions(listOfWords->object);
                        listOfWords = listOfWords->next;
                        trimByMatchingSubWords(completions, listOfWords);
                        srcStnName = chooseFromCompletions(completions);
                    }
                    // End edit version 1

                    if (srcStnName != "") {
                        logFile << "Chosen source station: " << srcStnName << '\n';

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Chosen source station: " << srcStnName << '\n';
                        }
                        // End edit version 1

                    }
                    else {
                        logFile << "Failure in choosing source station.\n";
                        std::cout << "Failure in choosing source station.\n";
                        continue;
                    }

                    // Edit version 1: Adding a check on readFrmFile flag
                    if (!readFrmFile) {
                        std::cout << "Enter prefix of any word in destination station name: ";
                    }
                    // End edit version 1

                    // Edit version 1: Changing "std::cin >> dstPrefix" followed by
                    // "destStnName = chooseFromCompletions(destPrefix)" to the following sequence
                    // of statements.    Note that this allows inputs to be read
                    // either from std::cin or from an input file, as specified.
                    // The following code also lets the user search for a set of completions
                    // from a space separated list of prefixes of individual words that
                    // appear in a station name.    E.g. giving "PU CANT" will return
                    // "PUNE CANTONMENT".

                    destPartWords = getStringWithSpaces(readFrmFile, &inpFile);
                    listOfWords = findAllWords(destPartWords);
                    if (listOfWords != nullptr) {
                        completions = stnNamesTrie->completions(listOfWords->object);
                        listOfWords = listOfWords->next;
                        trimByMatchingSubWords(completions, listOfWords);
                        destStnName = chooseFromCompletions(completions);
                    }
                    // End edit version 1

                    if (destStnName != "") {
                        logFile << "Chosen destination station: " << destStnName << '\n';

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Chosen destination station: " << destStnName << '\n';
                        }
                        // End edit version 1
                    }
                    else {
                        logFile << "Failure in choosing destination station.\n";
                        std::cout << "Failure in choosing destinatoin station.\n";
                        continue;
                    }

                    // Edit version 1: Adding a check on readFrmFile flag
                    if (!readFrmFile) {
                        std::cout << "Do you want to filter reviews by keyword? (y/n) ";
                    }
                    // End edit version 1

                    // Edit version 1: Changing "std::cin >> filterChoice" to a function call
                    // that either from std::cin or from an input file, as specified
                    // std::cin >> filterChoice;
                    filterWord = getStringWithoutSpaces(readFrmFile, &inpFile);
                    filterChoice = filterWord[0];
                    // End edit version 1

                    if (filterChoice == 'y') {

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Enter keyword (no line breaks): ";
                        }
                        // End edit version 1

                        // Edit version 1: Changing "std::cin >> keywordString" to a function call
                        // that either from std::cin or from an input file, as specified
                        // std::cin >> keywordString;
                        keywordString = getStringWithSpaces(readFrmFile, &inpFile);
                        // End edit version 1

                        logFile << "Filtering reviews by keyword " << keywordString << '\n';
                        hMatrix = computeHMatrixForKMP(keywordString);
                    }
                    else if (filterChoice == 'n') {
                        logFile << "Not filtering reviews by keyword\n";

                        // Edit version 1: Adding a check on readFrmFile flag
                        if (!readFrmFile) {
                            std::cout << "Not filtering reviews by keyword\n";
                        }
                        // End edit version 1
                        keywordString = "";
                    }

                    listOfJCodeReviews = findJCodeReviews(srcStnName, destStnName);
                    if (listOfJCodeReviews == nullptr) {
                        logFile << "Couldn't find list of journey codes and reviews.\n";
                        std::cout << "Couldn't find list of journey codes and reviews.\n";
                        // Edit version 1: Added a newline at the end of the next print statement
                        std::cout << "Ignoring command\n";
                        // End edit version 1
                        continue;
                    }
                    else {
                        currJCodeReview = listOfJCodeReviews;
                        while (currJCodeReview != nullptr) {
                            currReview = (currJCodeReview->object).reviews;

                            // Edit version 1: Added a condition to print a message if there are no reviews yet
                            if (currReview == nullptr) {
                                logFile << "JCode: " << (currJCodeReview->object).jCode << " from " << srcStnName;
                                logFile << " to " << destStnName << " has no reviews so far\n";
                                std::cout << "JCode: " << (currJCodeReview->object).jCode << " from " << srcStnName;
                                std::cout << " to " << destStnName << " has no reviews so far\n";
                                currJCodeReview = currJCodeReview->next;
                                continue;
                            }

                            // Also added printing of the journey code before the loop for printing reviews
                            std::cout << '\n' << "===================\n";
                            std::cout << "Journey Code " << (currJCodeReview->object).jCode << " reviews" << ((keywordString == "") ? "" : " matching keyword ") << GREEN << keywordString << RESET << ":\n";
                            std::cout << "Source: " << srcStnName << ",     Destination: " << destStnName << "\n\n";

                            // End edit version 1

                            while (currReview != nullptr) {
                                logFile << "JCode: " << (currJCodeReview->object).jCode << ", Rev: " << currReview->object << '\n';

                                if (keywordString != "") {
                        matchStartIndex = KMPMatch(currReview->object, hMatrix, keywordString);
                        if (matchStartIndex != -1) {
                            logFile << "Found keyword " << keywordString << '\n';
                            // Edit version 1: Commenting the following statements.    They have been
                            // move before the loop iterating over reviews.
                            // std::cout << "===================\n";
                            // std::cout << "Journey Code: " << (currJCodeReview->object).jCode << '\n';
                            // End edit version 1
                            printWithHighlight(currReview->object, matchStartIndex, keywordString.length());
                            // Edit version 1: Commenting the printing of the double line boundary. This has now
                            // bee moved to after the loop finishes iterating over reviews.
                            //std::cout << '\n' << "===================\n";
                            std::cout << '\n';
                            // End edit version 1
                        }
                        else {
                            logFile << "Didn't find keyword " << keywordString << '\n';
                        }
                                }
                                else {
                        logFile << "No keyword match required. Printing review.\n";
                        // Edit version 1: Commenting the following statements.    They have been
                        // move before the loop iterating over reviews.
                        // std::cout << "===================\n";
                        // std::cout << "Journey Code: " << (currJCodeReview->object).jCode << '\n';
                        // End edit version 1
                        std::cout << currReview->object << '\n';
                        // Edit version 1: Commenting the following statement.    It has been moved
                        // after the loop iterating over reviews
                        // std::cout << "===================\n";
                        // End edit version 1
                                }

                                currReview = currReview->next;
                            }
                            // Edit version 1: Moved printing of the separator line after the loop
                            // for printing reviews.
                            std::cout << "===================\n" << '\n';
                            // End edit version 1

                            currJCodeReview = currJCodeReview->next;
                        }
                    }
                    break;

                            // Lab 7 specific
                            case USER_FIND_ALL_JOURNEYS_INFO:

                    listOfObjects<std::string> *listOfWords, *completions;

                    if (!readFrmFile) {
                        std::cout << "Enter prefix of any word in station name: ";
                    }
                    std::string srcPartWords = getStringWithSpaces(readFrmFile, &inpFile);
                    std::string srcStnName;
                    listOfWords = findAllWords(srcPartWords);
                    if (listOfWords != nullptr) {
                        completions = stnNamesTrie->completions(listOfWords->object);
                        listOfWords = listOfWords->next;
                        trimByMatchingSubWords(completions, listOfWords);
                        srcStnName = chooseFromCompletions(completions);
                    }

                    if (srcStnName != "") {
                        logFile << "Chosen station: " << srcStnName << '\n';

                        if (!readFrmFile) {
                            std::cout << "Chosen station: " << srcStnName << '\n';
                        }
                    }
                    else {
                        logFile << "Failure in choosing source station.\n";
                        std::cout << "Failure in choosing source station.\n";
                        continue;
                    }

                    Entry<int>* stnEntry = stnNameToIndex.get(srcStnName);
                    if (stnEntry == nullptr) {
                        logFile << "Couldn't find station " << srcStnName << " in stnNameToIndex dictionary.\n";
                        std::cerr << "Couldn't find station " << srcStnName << " in stnNameToIndex dictionary.\n";
                        continue;
                    }

                    printStationInfo(stationInfo[stnEntry->value]);

                    continue;
                    // End lab 7 specific
                  }
                default:
                    logFile << "Invalid user option " << option << '\n';
                    std::cout << "Invalid user option (" << option << "). Please try again.\n";
                    continue;
            }
            // Edit version 1: Closing the brace for the else branch -- when the command
            // read in has to do nothing with reading or stopping reading commands from
            // an input file
        }
        // End edit version 1
    } while (true);
}

// Edit version 1:
// The following implementations of getInt and getStringWithSpaces
// allow reading commands/inputs along with comments
// on the same line, and then selecting the command/input for
// processing, while ignoring the comments.
// This is particularly useful when reading commands/inputs from
// a file, where you might want to add a comment after a
// command/input indicating what the command/input was meant for.
//
// Comments start with the character COMMENT_START_CHAR defined at the
// top of this file.
inline int Planner::getInt(bool readFromFile, std::fstream *file) {
    std::string line;
    if (!readFromFile) {
        getline(std::cin >> std::ws, line);
    }
    else {
        getline(*file >> std::ws, line);
    }

    int len = line.length();
    bool doResize = false;
    int newSize = len;

    for (int i = 0; i < len; i++) {
        if (line.at(i) == COMMENT_START_CHAR) {
            doResize = true;
            newSize = i;
            // Remove preceding whitespaces
            for (int j = i-1; j >= 0; j--) {
    if (isspace(line.at(j))) {
        newSize--;
    }
    else break;
            }
            break;
        }
    }

    if (doResize) {
        line.resize(newSize);
    }

    istringstream inpStream(line);
    int value;
    inpStream >> value;

    return value;
}

inline std::string Planner::getStringWithSpaces(bool readFromFile, std::fstream *file) {
    std::string line;
    if (!readFromFile) {
        getline(std::cin >> std::ws, line);
    }
    else {
        getline(*file >> std::ws, line);
    }

    int len = line.length();
    bool doResize = false;
    int newSize = len;

    for (int i = 0; i < len; i++) {
        if (line.at(i) == COMMENT_START_CHAR) {
            doResize = true;
            newSize = i;
            // Remove preceding whitespaces
            for (int j = i-1; j >= 0; j--) {
    if (isspace(line.at(j))) {
        newSize--;
    }
    else break;
            }
            break;
        }
    }

    if (doResize) {
        line.resize(newSize);
    }

    istringstream inpStream(line);
    std::string value;
    getline(inpStream >> std::ws, value);
    return value;
}

inline std::string Planner::getStringWithoutSpaces(bool readFromFile, std::fstream *file) {
    std::string line;
    if (!readFromFile) {
        getline(std::cin >> std::ws, line);
    }
    else {
        getline(*file >> std::ws, line);
    }

    int len = line.length();
    bool doResize = false;
    int newSize = len;

    for (int i = 0; i < len; i++) {
        if (line.at(i) == COMMENT_START_CHAR) {
            doResize = true;
            newSize = i;
            // Remove preceding whitespaces
            for (int j = i-1; j >= 0; j--) {
    if (isspace(line.at(j))) {
        newSize--;
    }
    else break;
            }
            break;
        }
    }

    if (doResize) {
        line.resize(newSize);
    }

    istringstream inpStream(line);
    std::string value;
    inpStream >> value;
    return value;
}
// End edit version 1

listOfObjects<std::string> * Planner::findAllWords(std::string text) {
    char *arrayOfChars = new char[text.length() + 1];
    if (arrayOfChars == nullptr) {
        logFile << "Memory allocation failure.\n";
        std::cout << "Memory allocation failure. Aborting command.\n";
        return nullptr;
    }

    strcpy(arrayOfChars, text.c_str());

    listOfObjects<std::string> *allWords = nullptr;
    const char delim[] = " ";

    char *nextWord = strtok(arrayOfChars, delim);;
    while (nextWord != nullptr) {
        listOfObjects<std::string> *tempWord = new listOfObjects<std::string> ("");

        if (tempWord == nullptr) {
            logFile << "Memory allocation error.\n";
            std::cout << "Memory allocation error. Aborting\n";
            delete[] arrayOfChars;
            while (allWords != nullptr) {
    listOfObjects<std::string> *toDelete = allWords;
    allWords = allWords->next;
    delete toDelete;
            }
            return nullptr;
        }
        else {
            tempWord->object = nextWord;
            tempWord->next = allWords;
            allWords = tempWord;
        }

        nextWord = strtok(NULL, delim);
    }

    return allWords;
}

void Planner::clearJCRMatrixEntry(int row, int col) {

    listOfObjects<JourneyCodeReview> *currJCR = jCRMatrix[row][col];

    // Can be improved
    while (currJCR != nullptr) {
        listOfObjects<JourneyCodeReview> *toDeleteJCR = currJCR;
        currJCR = currJCR->next;
        listOfObjects<std::string> *currReview = (toDeleteJCR->object).reviews;
        while (currReview != nullptr) {
            listOfObjects<std::string> *toDeleteReview = currReview;
            currReview = currReview->next;
            delete toDeleteReview;
        }
        delete toDeleteJCR;
    }

    // Edit version 2: As pointed out by a student
    jCRMatrix[row][col] = nullptr;

    return;
}

bool Planner::addStationName(std::string stnName) {
    // First check if station name already exists

    Entry<int> *stnIndexEntry = stnNameToIndex.get(stnName);
    if (stnIndexEntry != nullptr) {
        logFile << "Station name " << stnName << " already exists with index " << stnIndexEntry->value << '\n';
        std::cout << "Station name " << stnName << " already exists.\n";
        return true;
    }

    // stnName doesn't exist in the system
    // Enter it in stnNameToIndex

    int freeIndex = stnNameToIndex.findFreeIndex(stnName);
    if (freeIndex == -1) {
        logFile << "Failed to find free index in stnNameToIndex dictionary.\n";
        std::cout << "Failed to find free index in stnNameToIndex dictionary\n";
        return false;
    }

    Entry<int> newEntry(-1);
    newEntry.key = stnName;
    newEntry.value = freeIndex;
    if (!stnNameToIndex.put(newEntry)) {
        logFile << "Failed to insert in stnNameToIndex dictionary.\n";
        std::cout << "Failed to insert in stnNameToIndex dictionary\n";
        return false;
    }

    // Now find the words in stnName as separate std::strings, and
    // insert them in the stnNamesTrie.
    listOfObjects<std::string> *allWords = findAllWords(stnName);
    if (allWords == nullptr) {
        logFile << "Failed to add station name \"" << stnName << "\"\n";
        return false;
    }
    else {
        // Do trie insertion for each word in allWords
        listOfObjects<std::string> *currWord = allWords;
        bool successFlag = true;

        while (currWord != nullptr) {
            if (!stnNamesTrie->insert(currWord->object, freeIndex)) {
    logFile << "Failed to insert \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie\n";
    std::cout << "Failed to insert \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie\n";
    successFlag = false;
    break;
            }
            else {
    logFile << "Successfully inserted \"" << currWord->object << "\" (for station name \"" << stnNameToIndex.getKeyAtIndex(freeIndex) << "\") in trie\n";
    // Edit version 1: Commenting the following extraneous output
    // std::cout << "Successfully inserted " << currWord->object << '\n';
    // End edit version 1
    currWord = currWord->next;
            }
        }

        // Now free up the temporary data structures
        // Can be improved
        while (allWords != nullptr) {
            listOfObjects<std::string> *toDelete = allWords;
            allWords = allWords->next;
            delete toDelete;
        }

        // Finally increment numStations
        numStations ++;

        return true;
    }
}

bool Planner::delStationName(std::string stnName) {
    // First check if station name exists in system

    Entry<int> *stnIndexEntry = stnNameToIndex.get(stnName);
    if (stnIndexEntry == nullptr) {
        logFile << "Station name " << stnName << " doesn't exist\n";
        std::cout << "Station name " << stnName << " doesn't exist.\n";
        return true;
    }

    int stnIndex = stnIndexEntry->value;

    // stnName exists in the system and must be deleted.

    // First find the words in stnName as separate std::strings and remove the
    // corresponding trie entries, as appropriate (read problem statement).

    listOfObjects<std::string> *allWords = findAllWords(stnName);
    if (allWords == nullptr) {
        logFile << "Failed to delete station name\n";
        return false;
    }
    else {
        // Do trie deletion for each word in allWords
        listOfObjects<std::string> *currWord = allWords;
        bool successFlag = true;

        while (currWord != nullptr) {
            if (!stnNamesTrie->del(currWord->object, stnName)) {
    logFile << "Failed to delete \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie\n";
    std::cout << "Failed to delete \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie\n";
    successFlag = false;
    break;
            }
            else {
    logFile << "Successfully deleted \"" << currWord->object << "\" (for station name \"" << stnName << "\") in trie\n";
    std::cout << "Successfully deleted\n";
    currWord = currWord->next;
            }
        }

        // Now remove stnName from stnNameToIndex
        if (!stnNameToIndex.remove(stnName)) {
            logFile << "Couldn't remove " << stnName << " from stnNameToIndex dictionary\n";
            std::cout << "Couldn't remove " << stnName << " from stnNameToIndex dictionary\n";
            return false;
        }

        // Free up the temporary data structures
        // Can be improved
        while (allWords != nullptr) {
            listOfObjects<std::string> *toDelete = allWords;
            allWords = allWords->next;
            delete toDelete;
        }

        // Finally free up the corresponding entries in the jCRMatrix;
        for (int i = 0; i < DICT_SIZE; i++) {
            if (i != stnIndex) {
    clearJCRMatrixEntry(stnIndex, i);
            }
            clearJCRMatrixEntry(i, stnIndex);
        }

        // And to end it all, decrement numStations
        numStations --;

        return true;
    }
}

bool Planner::checkValidJourneyCode(std::string srcStnName, std::string destStnName, int jCode) {

    Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
    Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);
    int srcStnIndex, destStnIndex;

    if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    srcStnIndex = srcStnIndexEntry->value;
    destStnIndex = destStnIndexEntry->value;
    listOfObjects<JourneyCodeReview> *currJCRev = jCRMatrix[srcStnIndex][destStnIndex];
    while (currJCRev != nullptr) {
        if ((currJCRev->object).jCode == jCode) {
            return true;
        }
        else {
            currJCRev = currJCRev->next;
        }
    }
    return false;
}

bool Planner::addJourneyCode(std::string srcStnName, std::string destStnName, int jCode) {

    if (checkValidJourneyCode(srcStnName, destStnName, jCode)) {
        logFile << "Journey code already exists in system for given src, dest\n";
        std::cout << "Journey code already exists in system for given src, dest\n";
        return true;
    }

    // Journey code doesn't exist in system and must be added

    Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
    Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

    int srcStnIndex, destStnIndex;

    if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    srcStnIndex = srcStnIndexEntry->value;
    destStnIndex = destStnIndexEntry->value;

    JourneyCodeReview newJCRev;
    newJCRev.jCode = jCode;
    newJCRev.reviews = nullptr;

    listOfObjects<JourneyCodeReview> *newJCRevEntry = new listOfObjects<JourneyCodeReview> (newJCRev);
    if (newJCRevEntry == nullptr) {
        logFile << "Memory allocation failure.\n";
        std::cout << "Memory allocation failure\n";
        return false;
    }
    else {
        newJCRevEntry->next = jCRMatrix[srcStnIndex][destStnIndex];
        jCRMatrix[srcStnIndex][destStnIndex] = newJCRevEntry;

        // Finally increment numJourneyCodes
        numJCodeSrcDestn ++;
        return true;
    }
}

bool Planner::delJourneyCode(std::string srcStnName, std::string destStnName, int jCode) {

    if (!checkValidJourneyCode(srcStnName, destStnName, jCode)) {
        logFile << "Journey code does not exist in system for given src, dest\n";
        std::cout << "Journey code does not exist in system for given src, dest\n";
        return true;
    }

    // Journey code exists in system for given src, dest pair and must be deleted

    Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
    Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

    int srcStnIndex, destStnIndex;

    if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        return false;
    }

    srcStnIndex = srcStnIndexEntry->value;
    destStnIndex = destStnIndexEntry->value;

    listOfObjects<JourneyCodeReview> *currJCRevEntry = jCRMatrix[srcStnIndex][destStnIndex];
    listOfObjects<JourneyCodeReview> *prevJCRevEntry = nullptr;

    while (currJCRevEntry != nullptr) {
        if ((currJCRevEntry->object).jCode == jCode) {
            // Delete all reviews for this src, dest, jCode combination
            // Can be improved
            listOfObjects<std::string> *currRev = (currJCRevEntry->object).reviews;
            while (currRev != nullptr) {
    listOfObjects<std::string> *toDeleteRev = currRev;
    currRev = currRev->next;
    delete toDeleteRev;
            }

            if (prevJCRevEntry == nullptr) {
    jCRMatrix[srcStnIndex][destStnIndex] = currJCRevEntry->next;
            }
            else {
    prevJCRevEntry->next = currJCRevEntry->next;
            }
            listOfObjects<JourneyCodeReview> *toDeleteJCRevEntry = currJCRevEntry;
            currJCRevEntry = currJCRevEntry->next;
            numJCodeSrcDestn --;
            delete toDeleteJCRevEntry;
        }
        else {
            prevJCRevEntry = currJCRevEntry;
            currJCRevEntry = currJCRevEntry->next;
        }
    }
    return true;
}

int Planner::addReview(int jCode, std::string srcStnName, std::string destStnName, std::string review) {
    Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
    Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

    int srcStnIndex, destStnIndex;

    if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";

        // Edit version 2: returning -1 instead of false
        return -1;
        // End edit version 2
    }

    if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        // Edit version 2: returning -1 instead of false
        return -1;
        // End edit version 2
    }

    srcStnIndex = srcStnIndexEntry->value;
    destStnIndex = destStnIndexEntry->value;

    listOfObjects<JourneyCodeReview> *currJCRevEntry = jCRMatrix[srcStnIndex][destStnIndex];
    while (currJCRevEntry != nullptr) {
        if ((currJCRevEntry->object).jCode == jCode) {
            listOfObjects<std::string> *currRev = (currJCRevEntry->object).reviews;
            lastReviewId++;
            std::string revWithId = "[" + to_string(lastReviewId) + "]: " +    review;
            listOfObjects<std::string> *newRev = new listOfObjects<std::string> (revWithId);
            if (newRev == nullptr) {
    logFile << "Memory allocation failure.\n";
    std::cout << "Memory allocation failure\n";

    // Edit version 2: returning -1 instead of false
    return -1;
    // End edit version 2
            }
            newRev->next = currRev;
            (currJCRevEntry->object).reviews = newRev;

            // Edit version 2: Returning lastReviewId instead of true
            // return true;
            return lastReviewId;
            // End edit version 2
        }
        else {
            currJCRevEntry = currJCRevEntry->next;
        }
    }

    // Couldn't find the required journey code
    // This is an error condition
    logFile << "Couldn't find journey code " << jCode << " for source " << srcStnName << " and destination " << destStnName << '\n';
    std::cout << "Couldn't find journey code " << jCode << " for source " << srcStnName << " and destination " << destStnName << '\n';

    // Edit version 2: returning -1 instead of false
    return -1;
    // End edit version 2
}

bool Planner::delReview(int reviewId) {
    return false;
}

listOfObjects<JourneyCodeReview> * Planner::findJCodeReviews(std::string srcStnName, std::string destStnName) {
    Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
    Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

    int srcStnIndex, destStnIndex;

    if ((srcStnIndexEntry == nullptr) || (srcStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << srcStnName << " in stnNameToIndex dictionary\n";
        return nullptr;
    }

    if ((destStnIndexEntry == nullptr) || (destStnIndexEntry->value == -1)) {
        logFile << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        std::cout << "Couldn't find " << destStnName << " in stnNameToIndex dictionary\n";
        return nullptr;
    }

    srcStnIndex = srcStnIndexEntry->value;
    destStnIndex = destStnIndexEntry->value;

    return (jCRMatrix[srcStnIndex][destStnIndex]);
}

inline void Planner::printWithHighlight(std::string text, int startHLight, int lenHLight) {

    int endHLight = startHLight + lenHLight - 1;

    if (!((startHLight >= 0) && (startHLight < text.length()) &&
    (lenHLight > 0) && (endHLight < text.length()))) {
        logFile << "Incorrect arguments for printWithHighlight\n";
        std::cout << "Incorrect arguments for printing with highlighting. Going ahead with normal print\n";
        std::cout << text;
    }

    std::string prefix = (startHLight > 0) ? text.substr(0, startHLight) : "";
    std::string hLight = text.substr(startHLight, lenHLight);
    std::string suffix = (endHLight < text.length()-1) ? text.substr(endHLight+1, text.length()-endHLight-1) : "";

    std::cout << prefix;
    std::cout << GREEN << hLight << RESET;
    std::cout << suffix;
}

std::string Planner::chooseFromCompletions(listOfObjects<std::string> *completions) {
    if (completions != nullptr) {
        if (completions->next == nullptr) {
            return (completions->object);
        }
        else {
            // Multiple completions possible
            std::cout << "Enter choice number: \n";
            int choiceCount = 0;
            listOfObjects<std::string> *currCompletion = completions;
            while (currCompletion != nullptr) {
                std::cout << choiceCount << ": " << currCompletion->object << '\n';
                currCompletion = currCompletion->next;
                choiceCount++;
            }
            std::cout << '\n';
            int choice;
            do {
                std::cin >> choice;
                if (!(choice >= 0) and (choice < choiceCount)) {
                    std::cout << "Invalid choice.    Please try again.\n";
                    continue;
                }
                else {
                    break;
                }
            } while (true);

            choiceCount = 0;
            while (completions != nullptr) {
                if (choiceCount == choice) {
                    return completions->object;
                }
                choiceCount++;
                completions = completions->next;
            }

            // Execution should never reach here
            return "";
        }
    }
    else {
        std::cout << "No completions possible\n";
        return "";
    }
}

// Edit version 1: Adding one more helper function
void Planner::trimByMatchingSubWords(listOfObjects<std::string> * &completions, listOfObjects<std::string> *listOfSubWords) {
    listOfObjects<std::string> *currCompletion, *prevCompletion, *currSubWord;
    listOfObjects<std::string> *toDeleteCompletion;

    currSubWord = listOfSubWords;
    while (currSubWord != nullptr) {
        currCompletion = completions;
        prevCompletion = nullptr;
        while (currCompletion != nullptr) {
            if ((currCompletion->object).find(currSubWord->object) == std::string::npos) {
                // This completion doesn't match the subword, so remove it
                toDeleteCompletion = currCompletion;
                if (prevCompletion == nullptr) {
                    completions = currCompletion->next;
                }
                else {
                    prevCompletion->next = currCompletion->next;
                }
                currCompletion = currCompletion->next;
                delete toDeleteCompletion;
            }
            else {
                // This completion matches the subword, so retain it for now
                prevCompletion = currCompletion;
                currCompletion = currCompletion->next;
            }
        }
        currSubWord = currSubWord->next;
    }

    // By this time, completions has only the list of completions that match all subwords
}

// Lab 7 specific
void Planner::printStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    listOfObjects<TrainInfoPerStation *> *currList;
    TrainInfoPerStation *currInfo;

    Quicksort(stnInfoList)

    currList = stnInfoList;
    while (stnInfoList != nullptr) {
        currInfo = stnInfoList->object;
        if (currInfo != nullptr) {
            std::cout << "Journey code: " << currInfo->journeyCode << '\n';
            std::cout << "Days of week: ";
            for (int i = 0; i < 7; i++) {
                if (currInfo->daysOfWeek[i])
                    std::cout << i + 1 << " ";
            }
            std::cout << '\n';
            std::cout << "Arrival time: " << currInfo->arrTime << '\n';
            std::cout << "Departure time: " << currInfo->depTime << '\n';
            std::cout << "\n\n";
        }
    }
}

// End lab 7 specific
#endif
