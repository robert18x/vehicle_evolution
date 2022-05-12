#!/bin/bash

XAUTHORITY_DEFAULT_FILE="$HOME/.Xauthority"
XAUTHORITY_FILE=$XAUTHORITY

if [ -z "$XAUTHORITY_FILE" ] ; then
    XAUTHORITY_FILE=$XAUTHORITY_DEFAULT_FILE
fi

NCORES=`grep -c ^processor /proc/cpuinfo`
BUILD_THREADS=$(($NCORES + 2))

docker -v >/dev/null 2>&1
if [[ $? != 0 ]]; then
    sudo apt-get update && sudo apt-get install -y ca-certificates curl gnupg lsb-release
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    sudo apt-get update && sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin
fi

sudo docker build --build-arg BUILD_THREADS=$BUILD_THREADS -t vehicle_evolution:0.1 .
sudo docker run --net=host --env="DISPLAY" --volume="$XAUTHORITY_FILE:/root/.Xauthority" vehicle_evolution:0.1
