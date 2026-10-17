// Supplied optional-extra-credit driver. Compile with dice.cpp.
#include "dice.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    std::uint32_t seed = 0;
    int q = 0;
    if (!(std::cin >> seed >> q) || q < 0) return 1;
    DICE dice(seed);
    try {
        for (int i = 0; i < q; ++i) {
            std::string command;
            if (!(std::cin >> command)) return 1;
            try {
                if (command == "roll") {
                    double upper = 0;
                    int k = 0;
                    if (!(std::cin >> upper >> k) || k < 0 || k > 100000) return 1;
                    std::vector<int> unavailable(static_cast<std::size_t>(k));
                    for (int& value : unavailable)
                        if (!(std::cin >> value)) return 1;
                    const int value = dice.roll_one_dice(upper, unavailable);
                    std::cout << value << '\n';
                } else if (command == "order") {
                    int n = 0;
                    if (!(std::cin >> n)) return 1;
                    const auto result = dice.roll_play_order(n);
                    std::cout << "Order:";
                    for (const auto& item : result) std::cout << ' ' << item.player_id;
                    std::cout << "\nRolls:";
                    for (const auto& item : result) std::cout << ' ' << item.value;
                    std::cout << '\n';
                } else return 1;
            } catch (const std::invalid_argument&) {
                std::cout << "ERROR\n";
            }
        }
    } catch (const std::logic_error&) { return 2; }
}
