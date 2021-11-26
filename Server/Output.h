/*
#include <iostream>
#include "Semaphore.h"

#ifndef OUTPUT_H
#define OUTPUT_H

class Output
{
private:
	static Output* singleton_;
	CSemaphore sem_std_out;
	Output();
	

public:
	template <typename... T> void print(T...);
    void print_error(const char*);

    Output(Output& other) = delete;
    void operator=(const Output&) = delete;

    static Output* GetInstance();
};

#endif
*/