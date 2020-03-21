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

int MinorityGameAgent::take_action(int public_information) {
    int best_strategy = this->pick_best_strategy();
    
    return this->strategies[best_strategy].pick_action(public_information);
}

int MinorityGameAgent::pick_best_strategy() {
    int best_strategy = 0;
    int max_score = -1001001001;

    // TODO: argmax的なもので置き換える
    for (int i = 0; i < this->scores.size(); ++i) {
        if (this->scores[i] > max_score) {
            best_strategy = i;
            max_score = this->scores[i];
        }
    }

    return best_strategy;
}