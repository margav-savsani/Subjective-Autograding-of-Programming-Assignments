#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "graph.h"
#endif

void Graph::CheckGAD()
{
     int count = 0;
     int n;
   int size = n - 1;
   for (int i = 0; i < n; i++) {
      if (count == size) {
         return 1;
      }
      if (arr[i].ptr == NULL) {
         count++;
         for (int j = 0; j < n; j++) {
            while (arr[j].ptr != NULL) {
               if ((arr[j].ptr)->d == (arr[i].ptr)->d) {
                  (arr[j].ptr)->d = -1;
               }
               arr[i].ptr = (arr[i].ptr)->next;
            }
         }
      }
   }
   return 0;
}

#endif