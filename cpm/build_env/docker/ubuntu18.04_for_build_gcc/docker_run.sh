#!/bin/sh
ALL_ARG=$@
CALL_DIR=`pwd -P`
#RELATIVE_PATH=.${1#$CALL_DIR}
#DOCKER_OPTIONS=${ALL_ARG#$CALL_DIR*.sh}
RELATIVE_PATH=$1
echo RELATIVE_PATH
echo $RELATIVE_PATH
DOCKER_OPTIONS=${ALL_ARG#$RELATIVE_PATH}
echo DOCKER_OPTIONS
echo $DOCKER_OPTIONS
docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 $DOCKER_OPTIONS docker_img_cpm_gen:latest sh $RELATIVE_PATH
#docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 --env CACHE_DIR docker_img_cpm_gen:latest sh $RELATIVE_PATH
#docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 -e CACHE_DIR -e BUILD_DIR -e INST_PATH docker_img_cpm_gen:latest sh $RELATIVE_PATH

#docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 --env CACHE_DIR=./env_cpm/cache/src/amd64-m4-1.4.15 docker_img_cpm_gen:latest sh $RELATIVE_PATH

# --env CACHE_DIR=./env_cpm/cache/src/amd64-m4-1.4.15 BUILD_DIR=./env_cpm/build/amd64-m4-1.4.15 INST_PATH=./env_cpm/local_archive 
#CACHE_DIR=/mnt/sd/documents/projects/cpm/env_cpm/cache/src/amd64-m4-1.4.15
#BUILD_DIR=/mnt/sd/documents/projects/cpm/env_cpm/build/amd64-m4-1.4.15
#INST_PATH=/mnt/sd/documents/projects/cpm/env_cpm/local_archive
