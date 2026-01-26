#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Compile: clang++ -O3 render.cpp -o ~/.config/fastfetch/render

struct Cell {
    std::string content = " "; 
    std::string color = "";    
};

struct State {
    int x = 0;
    int y = 0;
    int saved_x = 0;
    int saved_y = 0;
    std::string current_color = "";
};

int main() {
    std::vector<std::vector<Cell>> grid;
    State state;

    auto ensure_size = [&](int r, int c) {
        if (r >= grid.size()) grid.resize(r + 1);
        if (c >= grid[r].size()) grid[r].resize(c + 1);
    };

    char c;
    while (std::cin.get(c)) {
        if (c == '\n') { state.y++; state.x = 0; continue; }
        if (c == '\r') { state.x = 0; continue; }

        if (c == '\033') {
            if (std::cin.peek() == '[') {
                std::cin.get(c); // consume '['
                std::string param_str;
                while (std::cin.peek() != EOF) {
                    char next = std::cin.peek();
                    if ((next >= '0' && next <= '9') || next == ';' || next == ':') {
                        std::cin.get(c); param_str += c;
                    } else break;
                }
                std::cin.get(c); // cmd
                char cmd = c;

                int num = 1;
                if (!param_str.empty()) {
                    try { num = std::stoi(param_str); } catch(...) { num = 1; }
                }

                if (cmd == 'A') state.y = std::max(0, state.y - num);
                else if (cmd == 'B') state.y += num;
                else if (cmd == 'C') state.x += num;
                else if (cmd == 'D') state.x = std::max(0, state.x - num);
                else if (cmd == 'G') state.x = std::max(0, num - 1);
                else if (cmd == 'H' || cmd == 'f') { state.y = 0; state.x = 0; }
                else if (cmd == 's') { state.saved_x = state.x; state.saved_y = state.y; }
                else if (cmd == 'u') { state.x = state.saved_x; state.y = state.saved_y; }
                
                // --- THE FIX: Append styles, don't overwrite ---
                else if (cmd == 'm') {
                     // If empty or "0", it's a reset. Clear the string.
                     if (param_str.empty() || param_str == "0") {
                         state.current_color = ""; 
                     } else {
                         // Otherwise, append this code to the existing active codes
                         // e.g. "Bold" + "Yellow" -> "\e[1m\e[33m"
                         state.current_color += "\033[" + param_str + "m";
                     }
                }
                
                else if (cmd == 'K') {
                    ensure_size(state.y, state.x);
                    if (state.y < grid.size()) {
                        for (size_t i = state.x; i < grid[state.y].size(); i++) grid[state.y][i] = {" ", ""};
                    }
                }
                continue;
            }
        }

        ensure_size(state.y, state.x);
        grid[state.y][state.x] = {std::string(1, c), state.current_color};
        state.x++;
    }

    for (const auto& row : grid) {
        std::string last_color = "";
        for (const auto& cell : row) {
            // Optimization: Only output color code if it changed from the previous cell
            if (cell.color != last_color) { 
                // Note: If we switched from "Bold Red" to just "Red", we technically need a reset first
                // But a simple state dump works for most simple fetches.
                // A perfect renderer would calculate the diff, but sending \e[0m then the new color is safest.
                if (cell.color.empty()) {
                    std::cout << "\033[0m";
                } else {
                    // Reset first to ensure we don't bleed attributes (like Bold) incorrectly
                    // then apply the full accumulated stack for this cell.
                    std::cout << "\033[0m" << cell.color;
                }
                last_color = cell.color;
            }
            std::cout << cell.content;
        }
        std::cout << "\033[0m" << std::endl;
    }
    return 0;
}
