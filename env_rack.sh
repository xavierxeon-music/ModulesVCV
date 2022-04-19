#!/bin/bash

VERSION=2.1.0

#####################################################3

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   
(return 0 2>/dev/null) && THIS_SCRIPT_IS_SOURCED=1 || THIS_SCRIPT_IS_SOURCED=0

function _set_rack_dir {

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

function _checkout {
   
   local CURRENT_DIR=$(pwd)

   if [ -f $SCRIPT_DIR/Rack/README.md ]
   then
      return
   fi

   git submodule update --init --recursive

   cd $SCRIPT_DIR/Rack
   local BRANCH_EXIST_TEST=$(git branch -l | grep $VERSION)
   if [ -z "$BRANCH_EXIST_TEST" ]
   then
      echo "new branch"
      git checkout tags/v$VERSION -b $VERSION
   fi

   local BRANCH_CURRENT_TEST=$(git branch --show-current)
   if [ "$BRANCH_CURRENT_TEST" != "$VERSION" ]
   then
      git switch $VERSION 
   
      cd $SCRIPT_DIR/Rack
      make dep -j 16
      make -j 16

      cd $SCRIPT_DIR/Rack/plugins
      ln -s ../../3rdParty/Fundamental Fundamental   
      ln -s ../../3rdParty/ImpromptuModular ImpromptuModular      
      ln -s ../../SchweineSystem SchweineSystem

      cd $SCRIPT_DIR/Fundamental
      make
      make dist
   fi

   cd $CURRENT_DIR
}

function module {
   $SCRIPT_DIR/Tools/module.py $@
}

function travel_sync {
   rsync -azhP --delete /Users/waspe/Documents/Rack2/plugins/SchweineSystem/ travel:/Users/waspe/Documents/Rack2/plugins/SchweineSystem/ 
}

_set_rack_dir
_checkout

