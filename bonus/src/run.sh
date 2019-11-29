#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/minijava/

javac P7.java

for file in ../minijava/*
do
	cat $file | java P7 > Test.ll
	echo "Testing $(basename -- $file)"
	clang -o Test Test.ll && ./Test
	echo "-------------------------"
	rm -rf Test Test.ll
done

#Uncomment to run extra tests

#echo "Checking extra testcases"

#for file in ../minijava-extra/*
#do
#	cat $file | P7 > Test.ll
#	echo "Testing $(basename -- $file)"
#	clang -o Test Test.ll && ./Test
#	echo "-------------------------"
#	rm Test Test.ll
#done

echo "Testing Done"
