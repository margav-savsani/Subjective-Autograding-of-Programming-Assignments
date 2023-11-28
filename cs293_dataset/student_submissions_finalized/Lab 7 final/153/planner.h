#ifndef PLANNER_H
#define PLANNER_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

class Planner {
 private:
  int numStations;
  int numJCodeSrcDestn;
  int lastReviewId;
  fstream logFile;

  //static variables for quicksort implementation
  static int recursionLevel, stat_start, stat_end, stat_len, K, stat_len_head;
  static listOfObjects<TrainInfoPerStation*>** stat_headArr;

  // Lab 7 specific
  listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE];
  // End lab 7 specific

  Dictionary<int> stnNameToIndex;
  listOfObjects<JourneyCodeReview> *jCRMatrix[DICT_SIZE][DICT_SIZE];
  Trie *stnNamesTrie;

  inline int getUserLevel(int userCode);
  int getInt(bool readFrmFile, fstream *file);
  string getStringWithSpaces(bool readFrmFile, fstream *file);
  // Edit version 1: Adding the following useful function
  string getStringWithoutSpaces(bool readFrmFile, fstream *file);
  // End edit version 1
  bool doAdminJob();
  bool doUserJob();
  listOfObjects<string> *findAllWords(string text);
  void clearJCRMatrixEntry(int row, int col);
  
  bool addStationName(string stnName);
  bool delStationName(string stnName);
  bool addJourneyCode(string srcStnName, string destStnName, int journeyCode);
  bool delJourneyCode(string srcStnName, string destStnName, int journeyCode);
  bool checkValidJourneyCode(string srcStnName, string destStnName, int journeyCode);
  int addReview(int journeyCode, string srcStnName, string destStnName, string reviewString);
  bool delReview(int reviewId);
  listOfObjects<JourneyCodeReview> *findJCodeReviews(string srcStnName, string dstStnName);
  inline void printWithHighlight(string text, int startHLight, int lenHLight);

  // Edit version 1: Changed signature of function chooseFromCompletions.
  //  Also added one more helper function, trimByMatchingSubWords
  string chooseFromCompletions(listOfObjects<string> *completions);
  void trimByMatchingSubWords(listOfObjects<string> * &completions, listOfObjects<string> *listOfSubWords);
  // End edit version 1
  
  int *computeHMatrixForKMP(string keywordString);
  int KMPMatch(string text, int *hMatrix, string pattern);
  
 public:
  Planner(string logFileName) {
    static int recursionLevel, stat_start, stat_end, stat_len, K, stat_len_head;
    static listOfObjects<TrainInfoPerStation*>** stat_headArr;
    recursionLevel=-1;stat_start=stat_len=stat_len_head=-1;stat_headArr=nullptr;
    stat_end=0;

    numStations = 0;
    numJCodeSrcDestn = 0;
    lastReviewId = -1;
    logFile.open(logFileName, ios::out);
    if (!logFile.is_open()) {
      cout << "Critical error: Failed to open log file \"" << logFileName << "\"" << endl;
      exit(-1);
    }

    for (int i = 0; i < DICT_SIZE; i++) {

      // Lab 7 specific
      stationInfo[i] = nullptr;
      // End lab 7 specific

      for (int j = 0; j < DICT_SIZE; j++) {
	jCRMatrix[i][j] = nullptr;
      }
    }
    stnNamesTrie = new Trie(&stnNameToIndex);
  }

  ~Planner() {
    if (logFile.is_open()) {
      logFile.close();
    }
  }
  void displayWelcomeMessage();
  bool displayMenuAndAct();
  // Lab 7 specific
  void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList);
  void QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end);
  listOfObjects<TrainInfoPerStation*>* partition(listOfObjects<TrainInfoPerStation*> *stnInfoList, int& partition_index);
  TrainInfoPerStation* chooseRandomPivot(listOfObjects<TrainInfoPerStation*> *stnInfoList);
  void printStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList);
  // End lab 7 specific
};


#endif
