#!/bin/bash

SDK_VERSION=2.0.4

brew install git wget cmake autoconf automake libtool jq python zstd

wget https://vcvrack.com/downloads/Rack-SDK-${SDK_VERSION}-mac.zip
unzip Rack-SDK-${SDK_VERSION}-mac.zip
rm Rack-SDK-${SDK_VERSION}-mac.zip