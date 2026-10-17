#include "dice.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

// Usage: DICE dice(seed); call roll_one_dice(...) or roll_play_order(...).
// The engine is seeded once in the constructor. Do not reseed per roll.
int DICE::roll_one_dice(double upper_bound, const std::vector<int>& unavailable) {
    // N = floor(upper_bound), with 1 <= N <= 100000.
    // Reject non-finite values/bounds outside this range.
    // Ignore duplicate exclusions and exclusions outside 1..N.
    // Uniformly select one remaining integer. Reject an empty pool.
    // Use standard <random> facilities; do not use rand() % N.
    if (!std::isfinite(upper_bound))
        throw std::invalid_argument("non-finite upper bound");
    const double floored = std::floor(upper_bound);
    if (floored < 1.0 || floored > 100000.0)
        throw std::invalid_argument("upper bound out of range");
    const int n = static_cast<int>(floored);

    std::vector<char> taken(static_cast<std::size_t>(n) + 1, 0);
    int excluded = 0;
    for (int value : unavailable) {
        if (value < 1 || value > n) continue;
        char& slot = taken[static_cast<std::size_t>(value)];
        if (slot) continue;
        slot = 1;
        ++excluded;
    }
    const int remaining = n - excluded;
    if (remaining <= 0)
        throw std::invalid_argument("empty candidate pool");

    std::uniform_int_distribution<int> dist(0, remaining - 1);
    int pick = dist(engine_);
    for (int value = 1; value <= n; ++value) {
        if (taken[static_cast<std::size_t>(value)]) continue;
        if (pick == 0) return value;
        --pick;
    }
    throw std::logic_error("roll_one_dice failed to select a candidate");
}

std::vector<PlayerRoll> DICE::roll_play_order(int num_players) {
    // Accept 1..1000 players; otherwise throw invalid_argument.
    // Call roll_one_dice once per player, excluding earlier selected values.
    // Use max(100, num_players) as the shared upper bound.
    // Return results in strictly decreasing order of roll value.
    if (num_players < 1 || num_players > 1000)
        throw std::invalid_argument("num_players out of range");

    const int upper = std::max(100, num_players);
    std::vector<int> used;
    used.reserve(static_cast<std::size_t>(num_players));
    std::vector<PlayerRoll> order;
    order.reserve(static_cast<std::size_t>(num_players));
    for (int player = 1; player <= num_players; ++player) {
        const int value = roll_one_dice(static_cast<double>(upper), used);
        used.push_back(value);
        order.push_back(PlayerRoll{player, value});
    }
    std::sort(order.begin(), order.end(),
              [](const PlayerRoll& a, const PlayerRoll& b) {
                  return a.value > b.value;
              });
    return order;
}
