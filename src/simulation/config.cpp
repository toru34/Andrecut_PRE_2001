#include "config.h"

const int BUY = 1;
const int SELL = -1;

std::mt19937 mt_engine(34);
std::uniform_real_distribution<double> uniform_real_dist(0, 1);