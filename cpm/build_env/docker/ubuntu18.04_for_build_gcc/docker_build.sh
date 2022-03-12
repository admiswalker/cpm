#!/bin/sh
SCRIPT_DIR=`cd $(dirname ${0}) && pwd`
docker build -t docker_img_cpm_gen $SCRIPT_DIR
