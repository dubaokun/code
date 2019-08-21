#include <thread>
#include <future>
#include <chrono>
#include <iostream>

int find_the_answer_to_ltuae()
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Async ID = " << std::this_thread::get_id() << std::endl; 
    }

    return 42;
}

void do_other_stuff() {
    std::cout << std::this_thread::get_id() <<" main thread run!" << std::endl;
}

int main()
{
    std::future<int> the_answer=std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout<<"The answer is "<<the_answer.get()<<std::endl;
}
