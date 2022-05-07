#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   
(return 0 2>/dev/null) && THIS_SCRIPT_IS_SOURCED=1 || THIS_SCRIPT_IS_SOURCED=0

function _init_module {

   if [ 0 == $THIS_SCRIPT_IS_SOURCED ]
   then
      echo "you need to source this script"
      return
   fi

   local RACK_DIR_TEST=$(echo $RACK_DIR)
   if [ -z "$RACK_DIR_TEST" ]
   then
      
      export RACK_DIR=$SCRIPT_DIR/Rack
      echo "export RACK_DIR=$SCRIPT_DIR/Rack" >> ~/.profile
      echo "rack environment ready"
   fi
}

function module {
   $SCRIPT_DIR/Tools/module.py $@
}

_init_module

