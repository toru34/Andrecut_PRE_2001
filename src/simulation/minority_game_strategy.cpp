#include "minority_game_strategy.h"

MinorityGameStrategy::MinorityGameStrategy(int n_public_information_patterns) {
    for (int i = 0; i < n_public_information_patterns; ++i) {
        this->actions.emplace_back(uniform_real_dist(mt_engine) < 0.5 ? BUY : SELL);
    }
}

int MinorityGameStrategy::pick_action(int p) {
    return this->actions[p];
}