#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
// #include "planner.h"
#endif

using namespace std;
  
class pathNode{
  public:
  int stn;
  int stops;//till now useless
  listOfObjects< TrainInfoPerStation *> *list;
  int transitTime[7];//useless
  int len;//useless

};

class info{
  public:
  int stat;
  int transitT;
  TrainInfoPerStation *train;
  int dayArr=-1;
  int dayDep=-1;
};

void addToPath(listOfObjects<listOfObjects<info *>*> *&final, listOfObjects<info *> *tx, int &fin, int transitTime, int stopOvers){
  //check validity and add
  listOfObjects<listOfObjects<info *>*> *f = final;
  listOfObjects<info *> *p = tx;

  //counting stopovers
  int count=0;
  while(p->next){
    if(p->object->train->journeyCode != p->next->object->train->journeyCode)
      count++;
    p = p->next;
  }
  if(count>stopOvers+1){
    return;
  }

  //checking transitTime
  p=tx;
  bool flag = false;
  int bb=0;
  while(p->next)
  {
   
      flag = false;
      if(bb==0)
      {//calculation only for 1st 2 stations
        bb++;
        for(int i=0; i<7; i++){
          for(int j=i; j<7; j++){
            if(p->next->object->train->daysOfWeek[j] && p->object->train->daysOfWeek[i])
            {
           
                if(p->object->train->depTime < p->object->train->arrTime){
                  for(int k=i+1; k<7; k++){
                    if(p->object->train->daysOfWeek[k]){
                      p->object->dayDep = i;
                      p->object->dayArr = k;
                      break;
                    }
                  }
                }
                else{
                  p->object->dayDep = i;
                  p->object->dayArr = i;
                }
                
                if(p->next->object->train->depTime < p->next->object->train->arrTime){
                  for(int k=j+1; k<7; k++){
                    if(p->next->object->train->daysOfWeek[k]){
                      p->next->object->dayDep = j;
                      p->next->object->dayArr = k;
                      break;
                    }
                  }
                }
                else{
                  p->next->object->dayArr = j;
                  p->next->object->dayDep = j;
                }
     
                if(p->object->train->journeyCode!=p->next->object->train->journeyCode){
                  int time = (p->next->object->dayDep - p->object->dayArr)*2400 + p->next->object->train->depTime - p->object->train->arrTime;
                  p->next->object->transitT = time;
                  if(time<=transitTime && time>=0){
                    flag = true;
                    break;
                  }
                }
                else{
                  p->next->object->transitT = 0;
                  flag = true;
                  break;
                }
              
            }
          }
          if(flag) break;
        }


      }//now daydep and dayarr of 2nd station is set
      else{
        for(int i=p->object->dayArr; i<7; i++){

          if(p->next->object->train->daysOfWeek[i]){
            if( p->next->object->train->depTime < p->object->train->arrTime && i==p->object->dayArr ){
              continue;
            }

            if(p->next->object->train->depTime < p->next->object->train->arrTime){
              for(int k=i+1; k<7; k++){
                if(p->next->object->train->daysOfWeek[k]){
                  p->next->object->dayArr = k;
                  p->next->object->dayDep = i;
                  break;
                }
              }
            }
            else{
              p->next->object->dayArr = i;
              p->next->object->dayDep = i;
            }
            
            if(p->object->train->journeyCode!=p->next->object->train->journeyCode){
              int time = (p->next->object->dayArr - p->object->dayDep)*2400 + p->next->object->train->depTime - p->object->train->arrTime;
              if(time>=0 && time<= transitTime){
                //update
                // p->object->dayDep = i;
                p->next->object->transitT = time;
                flag = true;
                break;
              }
            }
            else{
              p->next->object->transitT = 0;
              flag = true;
              break;
            }
            
            
          }

        }
      }

      if(flag == false) return;

    p = p->next;
  }

  //check if sucha path already exist
  bool same = false;
  bool sure = false; //sure if notsame
  f = final;
  listOfObjects<info *> *temp = f->object;
  if(fin!=0){
    while(f){
      p = tx;
      temp = f->object;
      sure = false;
      while(temp && p){
        if(temp->object->train->journeyCode == p->object->train->journeyCode)
        {
          same = true;
          //since no need to check further
        }
        else{
          same = false;
          sure = true;
        }
        temp = temp->next;
        p = p->next;
      }
      
      if(p!=NULL || temp!=NULL){
        //means not same
        sure = true;
      }
      if(sure==false) return;
      f = f->next;
    }
    // if(!same) {return;}
  }
  
  //if both test passed then add it to final path list

  if(fin==0){
    p = tx;
    final = new listOfObjects<listOfObjects< info *>*>( new listOfObjects< info *>(p->object) );
    listOfObjects<info *> *temp = final->object;
    p = p->next;
    while(p){
      temp->next = new listOfObjects<info *>(p->object);
      temp = temp->next;
      p = p->next;
    }
    f = final;
    fin++;
    
  }
  else{
    // p = tx;
    f = final;
    while(f->next){
      f = f->next;
      // cout<<f->object->object->journeyCode<<" in pathadd "<<endl;
    }
    p = tx;
    f->next = new listOfObjects<listOfObjects< info *>*>( new listOfObjects< info *>(p->object) );
    listOfObjects< info *> *temp = f->next->object;
    p = p->next;
    while(p){
      temp->next = new listOfObjects< info *>(p->object);
      temp = temp->next;
      p = p->next;
    }
    f = f->next;
    fin++;
  }

  return;

}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  bool isVisited[DICT_SIZE]; 
  StationAdjacencyList src = adjacency[stnNameToIndex.get(srcStnName)->value];
  StationAdjacencyList dest = adjacency[stnNameToIndex.get(destStnName)->value];  
  
  pathNode *p = new pathNode();
  p->stn = stnNameToIndex.get(srcStnName)->value;
  p->stops = 0;
  p->list = stationInfo[stnNameToIndex.get(srcStnName)->value];
  for(int i=0; i<7; i++){
    p->transitTime[i]=0;
  }
  p->len = 0;

  info *init = new info();
  init->transitT = 0 ;
  init->stat = p->stn;
  init->train = p->list->object;

  listOfObjects<listOfObjects<info *> *> *storepath;
  listOfObjects<listOfObjects<info *> *> *finalpath = new listOfObjects<listOfObjects< info *>*>( new listOfObjects<info*>(init) );
  int final = 0; 
  listOfObjects<listOfObjects<info *> *> *fp = finalpath;
  listOfObjects<pathNode *> *path = new listOfObjects<pathNode *>(p);
  listOfObjects<pathNode *> *stack = new listOfObjects<pathNode *>(p);

  isVisited[stnNameToIndex.get(srcStnName)->value]= true;

  listOfObjects<pathNode *> *lastPath = path;
  bool moveon = false;

  while(stack){
    
    listOfObjects<pathNode *> *tempStack = stack;
    while(tempStack->next){
      tempStack = tempStack->next;
    }

    pathNode *station = (tempStack->object);
    
    if(!isVisited[station->stn]){
      //if visited then dont create another pathnode in lastNode

      pathNode *pnode = new pathNode();
      pnode->stn = station->stn;
      pnode->stops = station->stops ;
      pnode->list = station->list;
      for(int i=0; i<7; i++){
        pnode->transitTime[i] = station->transitTime[i];
      }
      pnode->len = station->len;

      lastPath->next = new listOfObjects<pathNode *>(pnode);
      lastPath->next->prev = lastPath;
      lastPath = lastPath->next;
      
      isVisited[station->stn] = true;

    }
    else if(station->stn != lastPath->object->stn){

      pathNode *pnode = new pathNode();
      pnode->stn = station->stn;
      pnode->stops = station->stops ;
      pnode->list = station->list;
      for(int i=0; i<7; i++){
        pnode->transitTime[i] = station->transitTime[i];
      }
      pnode->len = station->len;

      lastPath->next = new listOfObjects<pathNode *>(pnode);
      lastPath->next->prev = lastPath;
      lastPath = lastPath->next;

    }
    if(station->stn == stnNameToIndex.get(destStnName)->value && lastPath->object->stn != stnNameToIndex.get(destStnName)->value ){
      pathNode *pnode = new pathNode();
      pnode->stn = station->stn;
      pnode->stops = station->stops ;
      pnode->list = station->list;
      for(int i=0; i<7; i++){
        pnode->transitTime[i] = station->transitTime[i];
      }
      pnode->len = station->len;

      lastPath->next = new listOfObjects<pathNode *>(pnode);
      lastPath->next->prev = lastPath;
      lastPath = lastPath->next;
      
      isVisited[station->stn] = true;
    }

    if (station->stn == stnNameToIndex.get(destStnName)->value){
      // cout<<"inside print\n";
      listOfObjects<pathNode *> *tempPath = path->next;
      listOfObjects<TrainInfoPerStation *> *x = path->next->object->list;
      // listOfObjects<TrainInfoPerStation *> *lp = patthh;
      listOfObjects<listOfObjects<info *> *> *pop = storepath;
      listOfObjects<listOfObjects<info *> *> *pop2 = storepath;
      int popstart = 0;

      int i=popstart;
      int len=popstart;
      while(x){
        if(popstart==0){
          info *inf = new info();
          inf->stat = path->next->object->stn;
          inf->transitT = 0;
          inf->train = x->object;

          storepath = new listOfObjects<listOfObjects< info *>*>( new listOfObjects< info *>(inf) );
          popstart++;
          pop = storepath;
        }
        else{
          info *inf = new info();
          inf->stat = path->next->object->stn;
          inf->transitT = 0;
          inf->train = x->object;

          pop->next = new listOfObjects<listOfObjects< info *>*>( new listOfObjects< info *>(inf) );
          pop = pop->next;
          popstart++;
        }
        x = x->next;
      }
      len=popstart;
      i=len;
      while(tempPath->next){

        pop = storepath;
        listOfObjects<info *> *tx = pop->object;
        listOfObjects<TrainInfoPerStation *> *y = tempPath->next->object->list;
        int yi=0;

        while(y){

          pop = storepath;
          if(yi==0){
            while(i-- && pop){
              tx = pop->object;
              while(tx->next){
                tx = tx->next;
              }
                info *inf = new info();
                inf->stat = tempPath->next->object->stn;
                inf->transitT = 0;
                inf->train = y->object;
                tx->next = new listOfObjects<info *>(inf);
 
              pop = pop->next;
              
            }
            yi++;
          }
          else{
            yi++;
            i=len;
            pop2 = storepath;
            pop = storepath;
            while(pop && pop->next){
              pop = pop->next;
            }
            while(i-- ){
              listOfObjects<info *> *ty = pop2->object;
              //i will fill the elements of ty int tx
              pop->next = new listOfObjects<listOfObjects< info *>*>( new listOfObjects< info *>(pop2->object->object) );
              len++; popstart++;
              tx = pop->next->object;
              ty = ty->next;
              while(ty && ty->next){

                  tx->next = new listOfObjects<info *>(ty->object);
                  tx = tx->next;

                ty = ty->next;
              }

                info *inf = new info();
                inf->stat = tempPath->next->object->stn;
                inf->transitT = 0;
                inf->train = y->object;
                tx->next = new listOfObjects< info *>(inf);
              

              pop = pop->next;
              pop2 = pop2->next;
            }
          }
          y = y->next;
          // cout<<"  yi times "<<yi<<endl;
        }
        tempPath = tempPath->next;
      }  
      //storepath has all the paths now...
      pop = storepath;
      
      while (pop)
      {
        listOfObjects<info *> *tx = pop->object;

        addToPath(finalpath, tx, final, maxTransitTime, maxStopOvers);
        
        // tx = pop->object;
        // while(tx){
        //   cout<<tx->object->train->journeyCode<<" ";
        //   tx = tx->next;
        // }
        // cout<<endl;
        pop = pop->next;
      }
      
      moveon = true;

    }
    else{
      moveon = false;
    }
  
    listOfObjects<StationConnectionInfo*> *neigh = adjacency[station->stn].toStations;
    // cout<<station->stn<<endl;
    
    neigh = adjacency[station->stn].toStations;

    int nim=0;

    while(neigh && !moveon ){
      if(!isVisited[neigh->object->adjacentStnIndex]){

        pathNode *pp = new pathNode();
        pp->stn = neigh->object->adjacentStnIndex;
        pp->stops = station->stops+1;
        pp->list = neigh->object->trains;
        pp->len =0;

          if(stack==NULL){
            stack = new listOfObjects<pathNode *>(pp);
            tempStack = stack;
          }
          else{
            listOfObjects<pathNode *> *tempStack = stack;
            while(tempStack->next)
              tempStack = tempStack->next;
            tempStack->next = new listOfObjects<pathNode *>(pp);
            tempStack->next->prev = tempStack;
          }
          // currTrains = neigh->object->trains;
          nim++;
        // }

      }
      neigh = neigh->next;
      
    }
    
    if( nim==0){

      tempStack = stack;
      while(stack && tempStack->next){
        tempStack = tempStack->next;
      }

      if(stnNameToIndex.getKeyAtIndex(tempStack->object->stn)==srcStnName) 
        break;
      
      lastPath = lastPath->prev;
      if(lastPath)lastPath->next = NULL;

      isVisited[tempStack->object->stn] = true; 

      if( tempStack && tempStack->prev){
        tempStack = tempStack->prev;
        tempStack->next = NULL;
      }
      else{
        stack = NULL;
        tempStack = NULL;
      }

    }

  }

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  if(finalpath==NULL || finalpath==fp) cout<< RED << "NO POSSIBLE JOURNEYS FOUND" << RESET <<endl;
  else{
    listOfObjects<listOfObjects<info*>*>*kpk = finalpath;
    cout << RED << "NOTE: " << RESET << "Day 0 means SUN, 1 means MON, 2 means TUE, 3 means WED, 4 means THURS, 5 means FRI, 6 means SAT" << endl;
    while(kpk)
    {
      cout << "Journey: " << endl;
      listOfObjects<info *> *tt = kpk->object;
      cout << BLUE << " Station: " << srcStnName << RESET << endl;
      // if(kpk-)
      while(tt){
      
        cout << BLUE << " JourneyCode: " << tt->object->train->journeyCode << RESET << "\t" ;
        if(tt->object->train->arrTime == -1)
          cout << RED  << "Arrival: " <<tt->object->dayArr<<","<< "Starts"<< "\t " << "Departure: " <<tt->object->dayDep<<"," <<tt->object->train->depTime  << RESET << endl;
        else
          cout << RED << "Arrival: " <<tt->object->dayArr<<","<< tt->object->train->arrTime<< " \t "  << "Departure: " <<tt->object->dayDep<<"," <<tt->object->train->depTime << RESET << endl;

        if(stnNameToIndex.getKeyAtIndex(tt->object->stat) == destStnName)
          cout <<GREEN << " Station: " << destStnName << "\t" << RESET << endl  ;
        else
          cout <<GREEN << " Station: " << stnNameToIndex.getKeyAtIndex(tt->object->stat) << " \t " << RESET ;
        if(tt->next && tt->next->object->transitT != 0)
          cout<< GREEN<< "TransitTime: " << tt->next->object->transitT << RESET << endl  ;
        else
          cout<<endl;
        
        tt = tt->next;
      }
      cout<<endl;
      kpk = kpk->next;
    }
  }
  return;
}

#endif
