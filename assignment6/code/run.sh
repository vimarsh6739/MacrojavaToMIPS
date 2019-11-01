#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/microIR/

javac P6.java

for file in ./microIR/*
do
	java P6 < $file >dump
	echo "Testing $file..."
	java -jar mars.jar <dump
	echo "______________$file done _________________"
	rm -rf dump
done
