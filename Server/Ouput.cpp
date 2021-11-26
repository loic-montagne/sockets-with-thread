/*
#include <iostream>
#include "Semaphore.h"
#include "Output.h"

Output* Output::singleton_ = nullptr;

Output* Output::GetInstance()
{
    if (singleton_ == nullptr) {
        singleton_ = new Output();
    }
    return singleton_;
}

Output::Output() : sem_std_out(1)
{
}

template <typename... T> void Output::print(T... args)
{
    sem_std_out.wait();
    ((std::cout << args), ...);
    std::cout.flush();
    sem_std_out.notify();
}

void Output::print_error(const char* error_message)
{
    sem_std_out.wait();
    perror(error_message);
    sem_std_out.notify();
}
*/