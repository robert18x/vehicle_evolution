#!/bin/bash

sudo apt-get update && apt-get update -y && \
sudo apt-get install docker

sudo docker build -t vehicle_evolution:0.0.1 .
sudo docker run --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" vehicle_evolution:0.0.1
