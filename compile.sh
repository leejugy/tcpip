set -e

export CC=arm-linux-gnueabihf-gcc
make -j
echo ===========
echo finish work
echo ===========

printf ".vscode\nclient\nserver" > .gitignore