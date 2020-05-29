g++ -std=c++11 -static-libgcc -static-libstdc++  simulator.cpp  test_main.cpp -o simulator_withThread -pthread
echo "compile done..."
./simulator_withThread
