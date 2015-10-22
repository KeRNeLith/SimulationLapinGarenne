#ifndef GENERAL_H
#define GENERAL_H

//#include <chrono>
#include <random>

// Autre seed possible : std::chrono::system_clock::now().time_since_epoch().count()
static std::mt19937 randEngine(123456789);
//static std::mt19937 randEngine(std::chrono::system_clock::now().time_since_epoch().count());

#endif // GENERAL_H
