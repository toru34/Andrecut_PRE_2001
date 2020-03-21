#include "minority_game_agent.h"

MinorityGameAgent::MinorityGameAgent(int n_public_information_patterns, int n_strategies) {
    // Initalise strategies
    for (int i = 0; i < n_strategies; ++i) {
        this->strategies.emplace_back(MinorityGameStrategy(n_public_information_patterns));
    }

    // Initalise strategies' scores
    for (int i = 0; i < n_strategies; ++i) {
        this->scores.emplace_back(0.0);
    }
}