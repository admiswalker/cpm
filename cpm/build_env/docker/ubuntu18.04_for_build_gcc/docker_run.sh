#!/bin/sh
ALL_ARG=$@                            # cpm/packages/amd64/m4/1.4.15/install_src.sh --env CACHE_DIR --env BUILD_DIR --env INST_PATH
SHELL_PATH=$1                         # cpm/packages/amd64/m4/1.4.15/install_src.sh
DOCKER_OPTIONS=${ALL_ARG#$SHELL_PATH} #                                             --env CACHE_DIR --env BUILD_DIR --env INST_PATH
docker run --rm -it --name run_cpm -v $PWD:/home -w /home -p 8000:8000 $DOCKER_OPTIONS docker_img_cpm_gen:latest sh $SHELL_PATH
