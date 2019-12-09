#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/minijava/

javac P7.java

echo "~~~~~~~~~~~~~~~~~~~~~BEGIN TESTING~~~~~~~~~~~~~~~~~~~~~~~~"

for file in ../minijava_tests/*
do
	javac -d ../bin $file  
	java -cp ../bin $(basename -- ${file%.*}) > expected.out
	cat $file | java P7 > Test.ll
	clang -w -o Test Test.ll 
	./Test > generated.out
	cmp -l expected.out generated.out && echo "Testing $(basename -- $file):Pass" || echo "Testing $(basename -- $file):FAIL"
done

rm -rf Test Test.ll expected.out generated.out
echo "~~~~~~~~~~~~~~~~~~~~~~~END TESTING~~~~~~~~~~~~~~~~~~~~~~~~"
