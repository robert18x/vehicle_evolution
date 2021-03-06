#!/bin/bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y gcc-10 g++-10 make gdb cppcheck clang-tidy clang-format ccache python3 python3-pip libgl-dev pkg-config libx11-dev \
    libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxau-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxdmcp-dev \
    libxext-dev libxfixes-dev libxft-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev \
    libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev xtrans-dev libxcb-render0-dev libxcb-render-util0-dev \
    libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev \
    libxcb-xinerama0-dev xkb-data libxcb-dri3-dev uuid-dev libxcb-util-dev xorg-dev libglu1-mesa-dev doxygen
python3 -m pip install conan cmake && pip3 install --upgrade conan cmake
