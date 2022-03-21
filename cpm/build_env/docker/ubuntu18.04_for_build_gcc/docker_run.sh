#!/bin/sh

# Example of run shell script on docker
#          ALL_ARG: cpm/packages/amd64/m4/1.4.15/install_src.sh --env CACHE_DIR --env BUILD_DIR --env INST_PATH
#              CMD: cpm/packages/amd64/m4/1.4.15/install_src.sh
#   DOCKER_OPTIONS:                                             --env CACHE_DIR --env BUILD_DIR --env INST_PATH

ALL_ARG=$@
CMD=$1
DOCKER_OPTIONS=${ALL_ARG#$CMD}
SCRIPT_DIR=`cd $(dirname ${0}) && pwd`
DOCKER_BASE_PATH=`cat $SCRIPT_DIR/docker_base_path.txt | tr -d '\r' | tr -d '\n'`
docker run --rm -it --name run_cpm -v $PWD:$DOCKER_BASE_PATH -w $DOCKER_BASE_PATH -p 8000:8000 $DOCKER_OPTIONS docker_img_cpm_gen:latest $CMD
