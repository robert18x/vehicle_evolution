#!/bin/bash

sudo apt-get update && apt-get upgrade -y && \
sudo apt-get install -y gcc-10 g++-10 make gdb cppcheck clang-tidy clang-format ccache python3 python3-pip \
                        libgl-dev libice-dev pkg-config libstb-dev libfreetype-dev liballegro5-dev libglfw3-dev \
                        freeglut3-dev libglew-dev libsdl2-dev libvulkan-dev libx11-xcb-dev libfontenc-dev libxaw7-dev \
                        libxkbfile-dev libxmu-dev libxmuu-dev libxres-dev libxtst-dev libxvmc-dev libxcb-render-util0-dev \
                        libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev \
                        libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-util-dev xorg-dev
python3 -m pip install conan cmake && pip3 install --upgrade conan cmake
# sudo ln -s ~/.local/bin/cmake /usr/bin/cmake
# libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules