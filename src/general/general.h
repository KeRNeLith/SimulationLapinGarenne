#ifndef GENERAL_H
#define GENERAL_H

//#include <chrono>
#include <random>
#include <thread>

// Autre seed possible : std::chrono::system_clock::now().time_since_epoch().count()
static std::mt19937 randEngine(123456789);
//static std::mt19937 randEngine(std::chrono::system_clock::now().time_since_epoch().count());

const unsigned int maxNbThread = std::thread::hardware_concurrency();

#endif // GENERAL_H
