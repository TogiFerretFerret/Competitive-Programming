#include <iostream>
#include <string>
#include <regex>

// Compile: clang++ -O3 pad.cpp -o pad

int main(int argc, char* argv[]) {
    // Usage: <command> | ./pad <target_width>
    if (argc < 2) {
        std::cerr << "Usage: <input> | pad <width>" << std::endl;
        return 1;
    }

    int width = std::stoi(argv[1]);
    std::string line;
    
    // Read from Stdin (allows piping)
    std::getline(std::cin, line);

    // Regex to strip ANSI codes for measurement
    std::regex ansi_re("\033\\[[0-9;]*m");
    std::string plain = std::regex_replace(line, ansi_re, "");
    
    // Calculate padding
    int padding = width - plain.length();
    if (padding < 0) padding = 0;

    // Print Original Line + Spaces
    std::cout << line << std::string(padding, ' ');

    return 0;
}
