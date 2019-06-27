#include <iostream>
#include <thread>

void hello() {
    std::cout << "hello concurrence world!" << std::endl;
}

int main(int argc, char ** agrv) {
    std::thread thread_(hello);
    thread_.join();
    return 0;
}
