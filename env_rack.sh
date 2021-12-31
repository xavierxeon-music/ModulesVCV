#!/bin/bash

TEST=$(echo $RACK_DIR)
if [ -z "$TEST" ]
then
   export RACK_DIR=$(pwd)/Rack-SDK
   echo "rack environment ready"
fi

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