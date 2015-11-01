#ifndef GENERAL_H
#define GENERAL_H

#include <cstdint>

#include <chrono>
#include <random>

#if defined(MULTI_THREADING)
#include <thread>

const unsigned int MAXTHREADS = std::thread::hardware_concurrency();
#endif  // endif MULTI_THREADING

// Autre seed possible : std::chrono::system_clock::now().time_since_epoch().count()
static std::mt19937 randEngine(123456789);
//static std::mt19937 randEngine(std::chrono::system_clock::now().time_since_epoch().count());

// Définit le type pour le stockage des compteurs de lapins, plus la taille stockable est importante plus la simulation pourra être prolongée
typedef int64_t rabbits_t;

#endif // GENERAL_H
