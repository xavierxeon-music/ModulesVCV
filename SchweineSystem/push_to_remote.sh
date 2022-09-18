#!/bin/bash

make
make install

cd /Applications
open -W "VCV Rack 2 Pro.app" &

cd ~/Documents/Rack2/plugins/SchweineSystem
if [ ! -f .fsync ]
then
   echo 'no sync info'
   return 
fi

REMOTE=$(cat .fsync)
rsync -azhP --delete --exclude .fsync * $REMOTE

