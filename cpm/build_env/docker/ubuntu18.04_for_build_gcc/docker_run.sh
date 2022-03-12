#!/bin/sh

# Case1. get call path of docker
#   ALL_ARG: pwd ./
#       CMD: pwd
#   CMD_ARG:      pwd
#
# Case2. run shell script on docker
#   ALL_ARG: sh cpm/packages/amd64/m4/1.4.15/install_src.sh --env CACHE_DIR --env BUILD_DIR --env INST_PATH
#       CMD: sh cpm/packages/amd64/m4/1.4.15/install_src.sh
#   CMD_ARG:    cpm/packages/amd64/m4/1.4.15/install_src.sh
#                                                           --env CACHE_DIR --env BUILD_DIR --env INST_PATH

ALL_ARG=$@
CMD=$1
DOCKER_OPTIONS=${ALL_ARG#$CMD}
docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 $DOCKER_OPTIONS docker_img_cpm_gen:latest $CMD
