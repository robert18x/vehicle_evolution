apt-get update && apt-get update -y
apt-get install -y gcc-10 g++-10 makefile gdb cppcheck clang-tidy clang-format ccache python3 python3-pip
pip3 install conan cmake && pip3 install --upgrade conan cmake
# sudo ln -s ~/.local/bin/cmake /usr/bin/cmake