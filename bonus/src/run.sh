#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/minijava/

javac P7.java

echo "TESTING PUBLIC TESTCASES:::"
for file in ../minijava/*
do
	#echo "Expected output ::->"
	javac -d ../bin $file  
	java -cp ../bin $(basename -- ${file%.*}) > output1.out
	cat $file | java P7 > Test.ll
	#echo "LLVM output ::->"
	clang -w -o Test Test.ll 
	./Test > output2.out
	cmp -l output1.out output2.out && echo "Testing $(basename -- $file) -> Testcase passed" || echo "Testing $(basename -- $file) -> Outputs dont match"
	
	echo "-------------------------"
	#rm -rf Test Test.ll output1.out output2.out
done

echo "CHECKING EXTRA TESTCASES::::"

for file in ../minijava-extra/*
do
	#echo "Testing $(basename -- $file)"
	#echo "Expected output ::->"
	javac -d ../bin $file
	java -cp ../bin $(basename -- ${file%.*}) > output1.out
	cat $file | java P7 > Test.ll
	#echo "LLVM output ::->"
	clang -w -o Test Test.ll 
	./Test > output2.out
	cmp -l output1.out output2.out && echo "Testing $(basename -- $file ) -> Testcase passed" || echo "Testing $(basename -- $file ) -> Outputs dont match"
	echo "-------------------------"
	#rm Test Test.ll output1.out output2.out
done

echo "CHECKING PRIVATE TESTCASES::::"

for file in ../private/*
do
	echo 
	#echo "Expected output ::->"
	javac -d ../bin $file
	java -cp ../bin $(basename -- ${file%.*}) > output1.out
	cat $file | java P7 > Test.ll
	#echo "LLVM output ::->"
	clang -w -o Test Test.ll 
	./Test > output2.out
	cmp -l output1.out output2.out && echo "Testing $(basename -- $file ) -> Testcase passed" || echo "Testing $(basename -- $file ) -> Outputs dont match"
	echo "-------------------------"
	#rm Test Test.ll output1.out output2.out
done

echo "CHECKING HIDDEN TESTCASES::::"

for file in ../hidden/*
do

	#echo "Expected output ::->"
	javac -d ../bin $file
	java -cp ../bin $(basename -- ${file%.*}) > output1.out
	cat $file | java P7 > Test.ll
	#echo "LLVM output ::->"
	clang -w -o Test Test.ll 
	./Test > output2.out
	cmp -l output1.out output2.out && echo "Testing $(basename -- $file ) -> Testcase passed" || echo "Testing $(basename -- $file ) -> Outputs dont match"
	echo "-------------------------"
	#rm Test Test.ll output1.out output2.out
done

echo "Testing Done"
