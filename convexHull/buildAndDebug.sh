mkdir -p build &&
cd build && 
cmake .. &&
cmake --build . &&
gdb ./runTests
