#!/bin/bash

javac P5.java

for file in ./microIR_tests/*
do
	java P5 < $file
done
