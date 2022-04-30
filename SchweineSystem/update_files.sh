#!/bin/bash

function store {
   for FILE_NAME in $(find . -type f -name "*.$1")
   do 
      echo $FILE_NAME >> SchweineSystem.files
   done
}

if [ -f SchweineSystem.files ]
then
   rm SchweineSystem.files
fi

store h
store hpp
store cpp
