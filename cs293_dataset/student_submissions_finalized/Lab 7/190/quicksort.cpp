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








void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

    // ^^^^^^^^^^^^^^^^^^^^^^^MY CODE IS HERE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    if(start >= finish) return;
    if (start < finish)
    {
        int q = Partition_with_BST_insert(start, finish);
        QuicksortWithBSTInsert(start, q);
        QuicksortWithBSTInsert(q+1, finish);
    }




// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}





