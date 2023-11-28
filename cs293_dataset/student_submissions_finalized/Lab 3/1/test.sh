#! /bin/bash

for i in {0..9}
do
	./automated < testcases/input${i}.txt > my_out.txt
	diff my_out.txt testcases/output${i}.txt
done
