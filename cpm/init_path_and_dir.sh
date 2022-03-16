#!/bin/bash

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.
BUILD_DIR=$CALL_DIR/$BUILD_DIR; mkdir -p $BUILD_DIR # When using Docker, the absolute path is determined at run time.
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.
INed_PATH=$CALL_DIR/$INed_PATH; mkdir -p $INed_PATH # When using Docker, the absolute path is determined at run time.
