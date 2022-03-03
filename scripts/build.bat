@echo off

cd ..
mkdir build
cd build

cmake ../
cmake --build .

pause