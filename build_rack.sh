#!/bin/bash

VERSION=2.1.2

#####################################################3

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   
CURRENT_DIR=$(pwd)
(return 0 2>/dev/null) && THIS_SCRIPT_IS_SOURCED=1 || THIS_SCRIPT_IS_SOURCED=0

if [ 1 == $THIS_SCRIPT_IS_SOURCED ]
then
   echo "you must not source this script"
   return
fi


OS_TEST=$(uname)
if [ "$OS_TEST" == " Darwin" ]
then
   echo 'install brew packages'
   brew install git wget cmake autoconf automake libtool jq python zstd
else
   echo 'install apt packages'
   sudo apt install unzip git gdb curl cmake libx11-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev zlib1g-dev libasound2-dev libgtk2.0-dev libgtk-3-dev libjack-jackd2-dev jq zstd libpulse-dev
fi


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
ln -s ../../3rdParty/BogaudioModules BogaudioModules      
ln -s ../../SchweineSystem SchweineSystem

cd $SCRIPT_DIR/3rdParty/Fundamental
git switch v2
make

cd $SCRIPT_DIR/3rdParty/ImpromptuModular
git switch master
make

cd $SCRIPT_DIR/3rdParty/BogaudioModules
git switch master
make

cd $CURRENT_DIR
