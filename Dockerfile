FROM ubuntu:20.04

LABEL version="0.1"

ARG DEBIAN_FRONTEND=noninteractive
ARG BUILD_THREADS=2

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y gcc-10 g++-10 make ccache python3 python3-pip libgl-dev pkg-config libx11-dev libx11-xcb-dev \
        libfontenc-dev libice-dev libsm-dev libxau-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev \
        libxdmcp-dev libxext-dev libxfixes-dev libxft-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev \
        libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev \
        libxxf86vm-dev xtrans-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev \
        libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev \
        libxcb-xinerama0-dev xkb-data libxcb-dri3-dev uuid-dev libxcb-util-dev xorg-dev libglu1-mesa-dev
RUN python3 -m pip install conan cmake && pip3 install --upgrade conan cmake

ENV CC=/usr/bin/gcc-10
ENV CXX=/usr/bin/g++-10

RUN mkdir -p /home/vehicle_evolution_build && mkdir -p /home/vehicle_evolution

WORKDIR /home/vehicle_evolution_build

COPY . .

RUN mkdir -p build

WORKDIR /home/vehicle_evolution_build/build/

RUN cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . -- -j $BUILD_THREADS

RUN cp /home/vehicle_evolution_build/build/src/vehicle_evolution /home/vehicle_evolution/vehicle_evolution

WORKDIR /home/vehicle_evolution

ENTRYPOINT ["./vehicle_evolution"]
