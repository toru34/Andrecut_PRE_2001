#ifndef CONFIG_H_
#define CONFIG_H_

#include <random>

extern const int BUY;
extern const int SELL;

extern std::mt19937 mt_engine;
extern std::uniform_real_distribution<double> uniform_real_dist;

#endif