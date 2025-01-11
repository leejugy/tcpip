set -e

export CC=~/gcc_old/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
make -j
echo ===========
echo finish work
echo ===========

printf ".vscode\nclient\nserver" > .gitignore