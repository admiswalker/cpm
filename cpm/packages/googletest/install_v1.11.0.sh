#!/bin/bash

wget https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
unzip -n release-1.11.0.zip
cd ./googletest-release-1.11.0;

mkdir -p build; cd build; cmake ..; make

mv lib/ ../../
cd ../googletest; mv include/ ../../
