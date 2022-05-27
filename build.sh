#!/bin/bash

source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1
echo "Creating "bin" directory for executables..."
mkdir bin
echo "Created "bin" directory for executables" 
make -f makefile
mv usm* buf* ~/HELLO/bin
echo "Executables are now in "bin" directory"
echo "Enter cd bin"
