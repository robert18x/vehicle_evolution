FROM ubuntu:20.04

LABEL version="0.1"

ARG DEBIAN_FRONTEND=noninteractive

RUN mkdir -p /home/vehicle_evolution

WORKDIR /home/vehicle_evolution

COPY . .

RUN ./prepare_environment.sh

RUN mkdir -p build

WORKDIR /home/user/app/build

RUN cmake .. && \
    cmake --build . --


    