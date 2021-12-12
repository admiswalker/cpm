#!/bin/bash

wget https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/tags/v1.0.0.zip
unzip -n v1.0.0.zip
cd ./SubStandardLibrary-SSTD--1.0.0/sstd;
make -j;
mv include/ ../../
mv lib/ ../../
