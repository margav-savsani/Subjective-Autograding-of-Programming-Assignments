#!/bin/bash
awk ' { for (i=1;i<=NF;i++)  count_arr[$i]++; } 
END { for( word in count_arr )  print word " " count_arr[word]  } ' ./$1/*| sort -k1	

