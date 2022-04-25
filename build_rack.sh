#!/bin/bash

VERSION=2.1.0

#####################################################3

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   
CURRENT_DIR=$(pwd)


RACK_DIR_TEST=$(echo $RACK_DIR)
if [ -z "$RACK_DIR_TEST" ]
then
   
   export RACK_DIR=$SCRIPT_DIR/Rack
   echo "rack environment set"
fi


if [ ! -f $SCRIPT_DIR/Rack/README.md ]
then
   cd $SCRIPT_DIR
   git submodule update --init --recursive
fi


cd $SCRIPT_DIR/Rack
BRANCH_EXIST_TEST=$(git branch -l | grep $VERSION)
if [ -z "$BRANCH_EXIST_TEST" ]
then
   echo "new branch"
   git checkout tags/v$VERSION -b $VERSION
fi

BRANCH_CURRENT_TEST=$(git branch --show-current)
if [ "$BRANCH_CURRENT_TEST" != "$VERSION" ]
then
   git switch $VERSION 
fi

make dep -j 16
make -j 16

cd $SCRIPT_DIR/Rack/plugins
ln -s ../../3rdParty/Fundamental Fundamental   
ln -s ../../3rdParty/ImpromptuModular ImpromptuModular      
ln -s ../../SchweineSystem SchweineSystem

cd $SCRIPT_DIR/3rdParty/Fundamental
git switch v2
make

cd $SCRIPT_DIR/3rdParty/ImpromptuModular
git switch master
make

cd $CURRENT_DIR
