#!/bin/bash

VERSION=2.1.0

#####################################################3

local SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   

function _set_rack_dir {

   local RACK_DIR_TEST=$(echo $RACK_DIR)
   if [ -z "$RACK_DIR_TEST" ]
   then
      
      export RACK_DIR=$SCRIPT_DIR/Rack
      echo "rack environment ready"
   fi
}

function _checkout {
   
   cd $SCRIPT_DIR/Rack
   local RANCH_EXIST_TEST=$(git branch -l | grep $VERSION)
   if [ -z "$BRANCH_EXIST_TEST" ]
   then
      git checkout tags/v$VERSION -b $VERSION
   fi

   local BRANCH_CURRENT_TEST=$(git branch --show-current)
   if [ "$BRANCH_CURRENT_TEST" != "$VERSION" ]
   then
      git switch $VERSION 
   fi
}

function update_modules {

   if [ ! -f plugin.json ]
   then
      echo 'not a plugin dir'
      return
   fi

   cd res
   FILES=$(ls -1 *.svg)
   cd ..

   for FILE in $FILES
   do
      NAME=${FILE/.svg/}
      $RACK_DIR/helper.py createmodule $NAME res/$NAME.svg tmp/$NAME.cpp
   done
}

_set_rack_dir
_checkout