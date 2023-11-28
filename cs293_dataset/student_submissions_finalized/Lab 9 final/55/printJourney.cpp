#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


using namespace std;

struct IndxJC {
  int stnIndex;
  int JCode;
  IndxJC(int ind, int jc){
    stnIndex = ind;
    JCode = jc;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // //EDIT
  // cout<<"Entered the function"<<endl;
  // //END EDIT
  
  // insert your code here
  int srcIndx = stnNameToIndex.get(srcStnName)->value;
  int destnIndx = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation*> *result=nullptr;

  listOfObjects<TrainInfoPerStation*> *srcToStnInfo = nullptr;
  listOfObjects<TrainInfoPerStation*> *destFromStnInfo = nullptr;

  listOfObjects<StationConnectionInfo *> *toStations = adjacency[srcIndx].toStations;
  listOfObjects<StationConnectionInfo *> *fromStations = adjacency[destnIndx].fromStations;

  listOfObjects<TrainInfoPerStation *> *srcStationInfo = stationInfo[srcIndx];

  // //EDIT
  // cout<<"Just outside loop 1\n";
  // //END EDIT

  while(toStations!=nullptr){
    // //EDIT
    // cout<<"In loop 1\n";
    // //END EDIT

    //EDIT
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    // listOfObjects<TrainInfoPerStation *> *trains = srcFromStations->object->trains;
    //END EDIT
    
    while(trains!=nullptr){
      if(srcToStnInfo==nullptr){
        srcToStnInfo = new listOfObjects<TrainInfoPerStation*>(trains->object);
      }
      else{
        srcToStnInfo->next = new listOfObjects<TrainInfoPerStation*>(trains->object);
        srcToStnInfo->next->prev = srcToStnInfo;
        srcToStnInfo = srcToStnInfo->next;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  while(true){
    if(srcToStnInfo==nullptr){
      break;
    }
    if(srcToStnInfo->prev==nullptr){
      break;
    }
    srcToStnInfo = srcToStnInfo->prev;
  }

  // //EDIT
  // printStationInfo(srcToStnInfo);
  // // return;
  // //END EDIT

  // //EDIT
  // cout<<"Just outside loop 2\n";
  // //END EDIT
  while(fromStations!=nullptr){
    // //EDIT
    // cout<<"In loop 2\n";
    // //END EDIT
    listOfObjects<TrainInfoPerStation *> *trains = fromStations->object->trains;
    while(trains!=nullptr){
      if(destFromStnInfo==nullptr){
        destFromStnInfo = new listOfObjects<TrainInfoPerStation*>(trains->object);
      }
      else{
        destFromStnInfo->next = new listOfObjects<TrainInfoPerStation*>(trains->object);
        destFromStnInfo->next->prev = destFromStnInfo;
        destFromStnInfo = destFromStnInfo->next;
      }
      trains = trains->next;
    }
    fromStations = fromStations->next;
  }
  while(true){
    if(destFromStnInfo==nullptr){
      break;
    }
    if(destFromStnInfo->prev==nullptr){
      break;
    }
    destFromStnInfo = destFromStnInfo->prev;
  }

  // //EDIT
  // printStationInfo(destFromStnInfo);
  // // return;
  // //END EDIT

  // //EDIT
  // cout<<"Just outside loop 3\n";
  // //END EDIT
  while(srcToStnInfo!=nullptr){
    int checkIfIntersect = srcToStnInfo->object->journeyCode;
    // srcToStnInfo.erase(srcToStnInfo.begin());
    listOfObjects<TrainInfoPerStation*> * tempdestFromStnInfo = destFromStnInfo;
    while(tempdestFromStnInfo!=nullptr){
      if(checkIfIntersect == tempdestFromStnInfo->object->journeyCode){
        // //EDIT
        // cout<<"Trying to add\n";
        // //END EDIT
        if(result==nullptr){
          result = new listOfObjects<TrainInfoPerStation*>(srcToStnInfo->object);
          result->prev = nullptr;
          // //EDIT
          // cout<<"Added to result\n";
          // //EDIT
        }
        else{
          result->next = new listOfObjects<TrainInfoPerStation*>(srcToStnInfo->object);
          // //EDIT
          // cout<<"Added to result\n";
          // //END EDIT
          result->next->prev = result;
          result = result->next;
        }
      }
      tempdestFromStnInfo = tempdestFromStnInfo->next;
    }
    srcToStnInfo = srcToStnInfo->next;
  }


  while(true){
    // //EDIT
    // cout<<"Inside restoring result while loop\n";
    // //END EDIT
    if(result==nullptr){
      break;
    }
    if(result->prev==nullptr){
      break;
    }
    result = result->prev;
  }

  // //EDIT
  // printStationInfo(result);
  // return;
  // //END EDIT

  if (result == nullptr){
    cout<<"No Direct Journey Available"<<endl;
    return;
  }

  listOfObjects<IndxJC*> *Q=nullptr,*Qlast=nullptr;
  
  listOfObjects<TrainInfoPerStation*> *resultCopy = result;
  while(resultCopy!=nullptr){
    IndxJC *entry = new IndxJC(srcIndx,resultCopy->object->journeyCode);
    if(Q==nullptr){
      Q = new listOfObjects<IndxJC*>(entry);
      // //EDIT
      //     cout<<"Added "<<Q->object->stnIndex<<" stnIndex to the Queue of Jcode: "<<Q->object->JCode<<endl;
      // //END EDIT
    }
    else{
      Q->next = new listOfObjects<IndxJC*>(entry);
      // //EDIT
      //     cout<<"Added "<<Q->next->object->stnIndex<<" stnIndex to the Queue of Jcode: "<<Q->next->object->JCode<<endl;
      // //END EDIT
      Q->next->prev = Q;
      Q = Q->next;
    }
    resultCopy = resultCopy->next;
  }

  Qlast = Q;

  while(true){
    if(Q==nullptr){
      break;
    }
    if(Q->prev==nullptr){
      break;
    }
    Q = Q->prev;
  }

  while(Q!=nullptr){

    // //EDIT
    // cout<<"Q is not yet empty\n";
    // //END EDIT
    IndxJC *front = Q->object;
    
    // Q = Q->next;


    if(front->stnIndex == destnIndx){
      Q = Q->next;
      
      // //EDIT
      //   cout<<"Popped1 "<<front->stnIndex<<" stnIndex from the Queue of Jcode: "<<front->JCode<<endl;
      // //END EDIT
      // //EDIT
      //   if(Q==nullptr){
      //     cout<<"Q is nullptr\n";
      //   }
      // //END EDIT
      continue;
    }

    StationAdjacencyList *lst = new StationAdjacencyList(adjacency[front->stnIndex]);

    bool flag = false;

    for(listOfObjects<StationConnectionInfo*> *to = lst->toStations;to!=nullptr;to=to->next){
      for(listOfObjects<TrainInfoPerStation*> *t = to->object->trains;t!=nullptr;t=t->next){
        // //EDIT
        // cout<<t->object->journeyCode<<endl;
        // //END EDIT
        if(t->object->journeyCode == front->JCode){
          IndxJC *entry = new IndxJC(to->object->adjacentStnIndex,front->JCode);
          
          // listOfObjects<IndxJC*> *QCopy = Q;
          Qlast->next = new listOfObjects<IndxJC*>(entry);

          // //EDIT
          // cout<<"Added "<<Qlast->next->object->stnIndex<<" stnIndex to the Queue of Jcode: "<<Qlast->next->object->JCode<<endl;
          // //END EDIT

          Qlast->next->prev = Qlast;
          Qlast = Qlast->next;
          flag = true;
          
          break;
        }
      }
      if(flag==true){
        break;
      }
    }
    
    if(flag==true){
      Q = Q->next;
      
      // //EDIT
      //   cout<<"Popped1 "<<front->stnIndex<<" stnIndex from the Queue of Jcode: "<<front->JCode<<endl;
      // //END EDIT
      // //EDIT
      //     if(Q==nullptr){
      //       cout<<"Q is nullptr\n";
      //     }
      // //END EDIT
      continue;
    }
    // //EDIT
    // else{
    //   cout<<"Going to pop from result\n";
    // }
    // //END EDIT

    // listOfObjects<TrainInfoPerStation*> *tempresult = result;
    // //EDIT
    // if(tempresult==nullptr){
    //   cout<<"tempresult is null\n";
    // }
    // //END EDIT
    // while(tempresult!=nullptr){
    //   // //EDIT
    //   // cout<<"I am here\n";
    //   // //END EDIT
    //   if(tempresult->object->journeyCode == front->JCode){
    //     if(tempresult->prev==nullptr){
    //       result = tempresult->next;
    //       tempresult = tempresult->next;
    //       //EDIT
    //       cout<<"Popped1 "<<tempresult->object->journeyCode<<" from result\n";
    //       printStationInfo(result);
    //       //END EDIT
    //       break;
    //       // delete tempresult;
    //     }
    //     else if(tempresult->next==nullptr){
    //       tempresult->prev->next=nullptr;
    //       //EDIT
    //       cout<<"Popped2 "<<tempresult->object->journeyCode<<" from result\n";
    //       printStationInfo(tempresult->prev);
    //       printStationInfo(result);
    //       //END EDIT
    //       break;
    //       // delete tempresult;
    //     }
    //     else{
    //       tempresult->prev->next=tempresult->next;
    //       tempresult->next->prev=tempresult->prev;
    //       //EDIT
    //       cout<<"Popped3 "<<tempresult->object->journeyCode<<" from result\n";
    //       printStationInfo(tempresult->prev);
    //       printStationInfo(result);
    //       //END EDIT
    //       break;
    //       // delete tempresult;
    //     }
    //   }
    //   tempresult = tempresult->next;
    // }
    
    while(result!=nullptr){
      // //EDIT
      // cout<<"I am here\n";
      // //END EDIT
      if(result->object->journeyCode == front->JCode){
        if(result->prev==nullptr){
          // //EDIT
          // cout<<"Popped1 "<<result->object->journeyCode<<" from result\n";
          // printStationInfo(result);
          // //END EDIT
          result = result->next;
          if(result!=nullptr){
            result->prev = nullptr;
          }
          break;
          // delete tempresult;
        }
        else if(result->next==nullptr){
          result->prev->next=nullptr;
          // //EDIT
          // cout<<"Popped2 "<<result->object->journeyCode<<" from result\n";
          // printStationInfo(result);
          // //END EDIT
          result = result->prev;
          break;
          // delete tempresult;
        }
        else{
          result->prev->next=result->next;
          result->next->prev=result->prev;
          // //EDIT
          // cout<<"Popped3 "<<result->object->journeyCode<<" from result\n";
          // printStationInfo(result);
          // //END EDIT
          result = result->prev;
          break;
          // delete tempresult;
        }
      }
      result = result->next;
    }

    while(true){
      if(result==nullptr){
        break;
      }
      if(result->prev==nullptr){
        break;
      }
      result = result->prev;
    }

    Q = Q->next;
    // //EDIT
    //     cout<<"Popped2 "<<front->stnIndex<<" stnIndex from the Queue of Jcode: "<<front->JCode<<endl;
    // //END EDIT
  }

  if (result == nullptr){
    cout<<"No Direct Journey Available"<<endl;
    return;
  }


  listOfObjects<TrainInfoPerStation *> *resCopy= result;
  listOfObjects<TrainInfoPerStation *> *finalResult=nullptr;

  // //EDIT
  // cout<<"Printing resCopy\n";
  // printStationInfo(resCopy);
  // cout<<"Printing Source Staion Info\n";
  // printStationInfo(srcStationInfo);
  // //END EDIT

  while(resCopy!=nullptr){
    int resJCode = resCopy->object->journeyCode;
    TrainInfoPerStation* srcInfo = nullptr;

    listOfObjects<TrainInfoPerStation*> *srcStationInfoCopy = srcStationInfo;
    while(srcStationInfoCopy!=nullptr){
      if(srcStationInfoCopy->object->journeyCode==resJCode){
        srcInfo = srcStationInfoCopy->object;
        // //EDIT
        // cout<<"Will put "<<srcInfo->journeyCode<<" in finalResult\n";
        // //END EDIT
        break;
      }
      srcStationInfoCopy=srcStationInfoCopy->next;
    }

    if(finalResult == nullptr){
      finalResult = new listOfObjects<TrainInfoPerStation*>(srcInfo);
      // //EDIT
      // cout<<"Have put "<<finalResult->object->journeyCode<<" in final result\n";
      // //END EDIT
    }
    else{
      finalResult->next = new listOfObjects<TrainInfoPerStation*>(srcInfo);
      finalResult->next->prev = finalResult;
      finalResult = finalResult->next;
      // //EDIT
      // cout<<"Have put "<<finalResult->object->journeyCode<<" in final result\n";
      // //END EDIT
    }
    resCopy = resCopy->next;
  }

  while(true){
    if(finalResult==nullptr){
      break;
    }
    if(finalResult->prev==nullptr){
      break;
    }
    finalResult = finalResult->prev;
  }

  // //EDIT
  // cout<<"Printing Final Result\n";
  // //END EDIT
  printStationInfo(finalResult);


  
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
