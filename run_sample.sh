#!/bin/bash


echo '-- set CPM environment ---'
. cpm_env/local/set_env.sh

echo '-- check compiler version ---'
gcc --version

echo '-- compile ---'
#g++ sample/main.cpp -lcpmex -o exe
g++ sample/main.cpp -lcpmex -lsstd -o exe

echo '-- run exe file ---'
./exe

