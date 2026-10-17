#include "dice.h"
#include <stdexcept>

// Usage: DICE dice(seed); call roll_one_dice(...) or roll_play_order(...).
// The engine is seeded once in the constructor. Do not reseed per roll.
int DICE::roll_one_dice(double upper_bound, const std::vector<int>& unavailable) {
    // TODO: N = floor(upper_bound), with 1 <= N <= 100000.
    // Reject non-finite values/bounds outside this range.
    // Ignore duplicate exclusions and exclusions outside 1..N.
    // Uniformly select one remaining integer. Reject an empty pool.
    // Use standard <random> facilities; do not use rand() % N.
    (void)upper_bound; (void)unavailable;
    throw std::logic_error("TODO: roll_one_dice");
}

std::vector<PlayerRoll> DICE::roll_play_order(int num_players) {
    // TODO: accept 1..1000 players; otherwise throw invalid_argument.
    // Call roll_one_dice once per player, excluding earlier selected values.
    // Use max(100, num_players) as the shared upper bound.
    // Return results in strictly decreasing order of roll value.
    (void)num_players;
    throw std::logic_error("TODO: roll_play_order");
}
