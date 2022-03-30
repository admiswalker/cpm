#!/bin/bash

CPM_CALL_DIR=`pwd -P`
CPM_CACHE_DIR=$CPM_CALL_DIR/$CPM_CACHE_DIR # When using Docker, the absolute path is determined at run time.
CPM_BUILD_DIR=$CPM_CALL_DIR/$CPM_BUILD_DIR # When using Docker, the absolute path is determined at run time.
CPM_DLIB_PATH=$CPM_CALL_DIR/$CPM_DLIB_PATH # When using Docker, the absolute path is determined at run time.
CPM_INST_WDIR=$CPM_CALL_DIR/$CPM_INST_WDIR # When using Docker, the absolute path is determined at run time.
CPM_INST_PATH=$CPM_CALL_DIR/$CPM_INST_PATH # When using Docker, the absolute path is determined at run time.

CPM_OWN_DIR=`dirname $0`
CPM_OWN_DIR=$CPM_CALL_DIR/$CPM_OWN_DIR
