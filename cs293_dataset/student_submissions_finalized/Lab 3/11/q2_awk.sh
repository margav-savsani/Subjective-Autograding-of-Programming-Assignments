#!/bin/bash
awk ' {for(n=0;n<10;n++) ord[sprintf("%c",n+48)]=n } 
{for(n=97;n<123;n++) ord[sprintf("%c",n)]=n-87} 
{ sum=0; base=8+2*(NR%3) ; temp=1; for (i=NF; i>=1 ; i--)  { sum += ord[$i]*temp ; temp*=base ;  } }
 {print sum}' sampleq2_input.txt

