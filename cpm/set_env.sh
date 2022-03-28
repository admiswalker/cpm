#!/bin/bash

CALL_DIR=`pwd -P`

export PATH=$CALL_DIR/cpm_env/local/bin:$PATH
export LD_LIBRARY_PATH=$CALL_DIR/cpm_env/local/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$CALL_DIR/cpm_env/local/lib64:$LD_LIBRARY_PATH
export LIBRARY_PATH=$CALL_DIR/cpm_env/local/lib:$LIBRARY_PATH
export LIBRARY_PATH=$CALL_DIR/cpm_env/local/lib64:$LIBRARY_PATH

export LD_RUN_PATH=$CALL_DIR/cpm_env/local/lib:$LD_RUN_PATH
export C_INCLUDE_PATH=$CALL_DIR/cpm_env/local/include:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=$CALL_DIR/cpm_env/local/include:$CPLUS_INCLUDE_PATH
export MAN_PATH=$CALL_DIR/cpm_env/local/share/man:$MAN_PATH
export OPENSSL_ROOT_DIR=$CALL_DIR/cpm_env/local/bin

