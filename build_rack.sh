#!/bin/bash

VERSION=2.1.0

#####################################################3

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"   
CURRENT_DIR=$(pwd)
(return 0 2>/dev/null) && THIS_SCRIPT_IS_SOURCED=1 || THIS_SCRIPT_IS_SOURCED=0

if [ 1 == $THIS_SCRIPT_IS_SOURCED ]
then
   echo "you must not source this script"
   return
fi

RACK_DIR_TEST=$(echo $RACK_DIR)
if [ -z "$RACK_DIR_TEST" ]
then
   
   export RACK_DIR=$SCRIPT_DIR/Rack
   echo "rack environment set"
fi

OS_TEST=$(uname)
if [ ! -f $SCRIPT_DIR/Rack/README.md ]
then
   cd $SCRIPT_DIR
   git submodule update --init --recursive

   if [ "$OS_TEST" == "Darwin" ]
   then
      echo 'install brew packages'
      brew install git wget cmake autoconf automake libtool jq python zstd pkg-config
   else
      echo 'install apt packages'
      sudo apt install unzip git gdb curl cmake libx11-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev zlib1g-dev libasound2-dev libgtk2.0-dev libgtk-3-dev libjack-jackd2-dev jq zstd libpulse-dev
   fi
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

if [ "$OS_TEST" == "Darwin" ]
then
   MAXCORES=$(sysctl -n hw.ncpu)
else
   MAXCORES=$(nproc)
fi

arch -x86_64 make dep -j $MAXCORES || exit
arch -x86_64 make -j $MAXCORES || exit

ln -s $SCRIPT_DIR/3rdParty/Fundamental $SCRIPT_DIR/Rack/plugins/Fundamental   
ln -s $SCRIPT_DIR/3rdParty/ImpromptuModular $SCRIPT_DIR/Rack/plugins/ImpromptuModular      
ln -s $SCRIPT_DIR/3rdParty/BogaudioModules $SCRIPT_DIR/Rack/plugins/BogaudioModules      
ln -s $SCRIPT_DIR/SchweineSystem $SCRIPT_DIR/Rack/plugins/SchweineSystem

cd $SCRIPT_DIR/3rdParty/Fundamental
git switch v2
arch -x86_64 make -j $MAXCORES || exit

cd $SCRIPT_DIR/3rdParty/ImpromptuModular
git switch master
arch -x86_64 make -j $MAXCORES || exit

cd $SCRIPT_DIR/3rdParty/BogaudioModules
git switch master
arch -x86_64 make -j $MAXCORES || exit

cd $CURRENT_DIR
