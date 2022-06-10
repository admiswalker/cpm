#!/bin/bash
SCRIPT_DIR=`cd $(dirname ${BASH_SOURCE:-$0}); pwd`
docker build -t docker_img_cpm_meson_env $SCRIPT_DIR
