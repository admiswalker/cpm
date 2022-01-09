#!/bin/bash

CALL_DIR=`pwd -P`

export PATH=$CALL_DIR/env_cpm/local/bin:$PATH
export LD_LIBRARY_PATH=$CALL_DIR/env_cpm/local/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$CALL_DIR/env_cpm/local/lib64:$LD_LIBRARY_PATH
export LIBRARY_PATH=$CALL_DIR/env_cpm/local/lib:$LIBRARY_PATH
export LIBRARY_PATH=$CALL_DIR/env_cpm/local/lib64:$LIBRARY_PATH

