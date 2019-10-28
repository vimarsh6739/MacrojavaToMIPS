#!/bin/bash

javac P5.java

for file in ./microIR_tests/*
do
	java P5 < $file >dump
	echo "Testing $file"
	java -jar kgi.jar <dump
	echo "-------------------------"
	rm -rf dump
done
