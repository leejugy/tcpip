set -e

make -j
echo ===========
echo finish work
echo ===========

printf ".vscode\nclient\nserver" > .gitignore