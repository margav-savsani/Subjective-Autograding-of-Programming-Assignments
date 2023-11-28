#include "graph.h"

void Graph::printSources()
{
    bool firstDone = 0;
    for (int i = 0; i < numNodes; i++)
    {
        if (sources[i])
        {
            if (!firstDone)
            {
                firstDone = 1;
                output << "Source nodes: " << i + 1;
            }
            else
            {
                output << " " << i + 1;
            }
        }
    }
    output << endl << endl;
}

void Graph::printRelated(){
    bool firstDone = 0;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (relatedMatrix[i][j]) {
                if (!firstDone)
                {
                    firstDone = 1;
                    output << "Source node pairs: (" << i+1 << "," << j+1 << ")";
                }
                else
                {
                    output << " (" << i+1 << "," << j+1 << ")";
                }
            }
        }
    }
    output << endl << endl;
}

void Graph::similarityB()
{
    for(int n1=0; n1<numNodes; n1++){
        for(int n2=0; n2<numNodes; n2++){
            if (sources[n1]==0 && sources[n2]==0){
                int x1 = 1;
                for(int m1=0; m1<numNodes; m1++){
                    if (edgeMatrix[m1][n1]){
                        int x2 = 0;
                        for(int m2=0; m2<numNodes; m2++){
                            if (edgeMatrix[m2][n2]){
                                if (relatedMatrix[m1][m2]){
                                    x2 = 1;
                                }
                            }
                        }
                        if (x2 == 0){
                            x1 = 0;
                            break;
                        }
                    }
                }
                for(int m1=0; m1<numNodes; m1++){
                    if (edgeMatrix[m1][n1]){
                        int x2 = 0;
                        for(int m2=0; m2<numNodes; m2++){
                            if (edgeMatrix[m2][n2]){
                                if (relatedMatrix[m2][m1]){
                                    x2 = 1;
                                }
                            }
                        }
                        if (x2 == 0){
                            x1 = 0;
                            break;
                        }
                    }
                }
                if (x1 == 1){
                    relatedMatrix[n1][n2] = 1;
                    similarityB();
                }
            }
        }
    }

    
    

    // for (int i = 0; i < numNodes - 1; i++)
    //     for (int j = i + 1; j < numNodes; j++)
    //     {
    //         if (sources[i]==0 && sources[j]==0){
    //             // for(int m1=0; m1<numNodes; m1++){
    //             //     for(int m2=0; m2<numNodes; m2++){
    //             //         if (relatedMatrix[m1][m2]){

    //             //         }
    //             //     }
    //             // }
    //         }

            
    //     }
}

void Graph::similarityC(){
    for(int n1=0; n1<numNodes; n1++){
        for(int n2=0; n2<numNodes; n2++){
            if (edgeMatrix[n2][n1]){
                bool x = 0;
                for(int k=0; k<numNodes ; k++){
                    if (k == n2)
                        continue;
                    if (edgeMatrix[k][n1]){
                        x = 1;
                        break;
                    }
                }
                if (x == 0){
                    relatedMatrix[n1][n2] = 1;
                }
            }
        }
    }
}

void Graph::collapse(){
    int array[numNodes][numNodes];

    for(int i=0; i<numNodes; i++){
        array[i][0] = i+1;
        array[i][1] = i;
    }

    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if (relatedMatrix[i][j]){
                relatedMatrix[j][i] = 1;
                if (i > j){
                    int temp = j;
                    j = i;
                    i = temp;
                }
                // array[i]
            }
        }
    }
}

void Graph::printCollapse(){

}


// ------------------------------------------------------------------------------------

// if (sources[i] && sources[j])
            //     relatedMatrix[i][j] = 1;
            // else
            // if (edgeMatrix[j][i])
            // {
                // bool invalid = 0;
                // for (int k = 0; k < numNodes; k++)
                // {
                //     if (edgeMatrix[k][i])
                //         if (k != j)
                //         {
                //             invalid = 1;
                //             break;
                //         }
                // }
                // if (!invalid)
                // {
                //     relatedMatrix[i][j] = 1;
                // }
            // }