#!/bin/bash


URL00=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0.tar.xz-00

URL1=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0.tar.xz-00
URL2=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0.tar.xz-01
fName1=${URL1##*/}       # <architecture>-<libName>-<version>.tar.xz-00
fName2=${URL2##*/}       # <architecture>-<libName>-<version>.tar.xz-01

echo $fName1

#for i in `seq 0 9`
for i in `seq 0 2`
do
    num=`printf "%02d\n" $i`
    URLxx=URL$num
    cmd='echo $'$URLxx
    URL_str=`eval $cmd`
    URL_len=${#URL_str}

    if [ $URL_len == 0 ]; then
	break
    fi
    
    echo $URL_str
    echo $URL_len
done


