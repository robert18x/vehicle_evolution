FROM ubuntu:20.04

LABEL version="0.1"

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get update -y && \
    apt-get install -y gcc-10 g++-10 make gdb cppcheck clang-tidy clang-format ccache python3 python3-pip libgl-dev && \
    python3 -m pip install conan cmake && pip3 install --upgrade conan cmake

ENV CC=/usr/bin/gcc-10
ENV CXX=/usr/bin/g++-10

RUN mkdir -p /home/vehicle_evolution

WORKDIR /home/vehicle_evolution

COPY . .

RUN mkdir -p build

WORKDIR /home/vehicle_evolution/build

RUN cmake .. && \
    cmake --build . --

ENTRYPOINT [""]
