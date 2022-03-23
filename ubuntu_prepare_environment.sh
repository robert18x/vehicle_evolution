#!/bin/bash

sudo apt-get update && apt-get update -y && \
sudo apt-get install -y gcc-10 g++-10 make gdb cppcheck clang-tidy clang-format ccache python3 python3-pip
python3 -m pip install conan cmake && pip3 install --upgrade conan cmake
# sudo ln -s ~/.local/bin/cmake /usr/bin/cmake