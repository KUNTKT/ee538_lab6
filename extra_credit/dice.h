#ifndef LAB6_DICE_H
#define LAB6_DICE_H

#include <cstdint>
#include <random>
#include <vector>

struct PlayerRoll { int player_id; int value; };

class DICE {
    std::mt19937 engine_;
public:
    explicit DICE(std::uint32_t seed) : engine_(seed) {}
    // null candidate set is represented by an empty vector.
    // Reject invalid bounds or an exhausted candidate pool with invalid_argument.
    int roll_one_dice(double upper_bound, const std::vector<int>& unavailable);
    // Return each player exactly once, sorted by decreasing distinct roll value.
    // Player IDs are 1..num_players. Use upper bound max(100, num_players).
    std::vector<PlayerRoll> roll_play_order(int num_players);
};
#endif
