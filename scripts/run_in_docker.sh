#!/bin/bash

XAUTHORITY_DEFAULT_FILE="$HOME/.Xauthority"
XAUTHORITY_FILE=$XAUTHORITY

if [ -z "$XAUTHORITY_FILE" ] ; then
    XAUTHORITY_FILE=$XAUTHORITY_DEFAULT_FILE
fi

NCORES=`grep -c ^processor /proc/cpuinfo`
BUILD_THREADS=$(($NCORES + 2))

sudo apt-get update && sudo apt-get upgrade -y
sudo apt-get install -y docker

sudo docker build --build-arg BUILD_THREADS=$BUILD_THREADS -t vehicle_evolution:0.1 .
sudo docker run --net=host --env="DISPLAY" --volume="$XAUTHORITY_FILE:/root/.Xauthority" vehicle_evolution:0.1
