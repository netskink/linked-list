#!/bin/bash

# configure this script to exit on first error
set -e

# simple script to demo makefile targets

# clean everything
echo "***"
echo Demo clean target
make clean

# build just the test code
echo "***"
echo Demo building of test_list program.  This builds the code for the test program 
echo but does not run it.
make test_list

# build everything and run the sample and the test code
echo "***"
echo Demo building both the demo program and the test program
echo and then runs both.
make test
