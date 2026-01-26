#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Compile: clang++ -O3 inspect.cpp -o inspect

std::string escape_char(char c) {
    if (c == '\n') return "\\n";
    if (c == '\r') return "\\r";
    if (c == '\t') return "\\t";
    if (c == '\033') return "\\e";
    return std::string(1, c);
}

int main() {
    char c;
    long long byte_offset = 0;

    std::cout << "OFFSET | TYPE       | RAW           | DETAILS" << std::endl;
    std::cout << "-------|------------|---------------|------------------------" << std::endl;

    while (std::cin.get(c)) {
        byte_offset++;

        // --- ANSI ESCAPE SEQUENCE ---
        if (c == '\033') {
            std::string seq = "\\e";
            
            // Check for CSI (Control Sequence Introducer) '['
            if (std::cin.peek() == '[') {
                char next;
                std::cin.get(next);
                seq += next;

                // Read Parameters (digits, ;, :, ?, >)
                std::string params;
                while (std::cin.peek() != EOF) {
                    char p = std::cin.peek();
                    // Valid param chars in ANSI are 0-9, ;, :, ?, >, <, =, etc.
                    if ((p >= 0x30 && p <= 0x3F) || (p >= 0x20 && p <= 0x2F)) { 
                        std::cin.get(next);
                        seq += next;
                        params += next;
                    } else {
                        break;
                    }
                }

                // Read Command Letter
                char cmd = ' ';
                if (std::cin.peek() != EOF) {
                    std::cin.get(cmd);
                    seq += cmd;
                }

                // LOG THE COMMAND
                std::string desc;
                if (cmd == 'A') desc = "CUU: Cursor Up";
                else if (cmd == 'B') desc = "CUD: Cursor Down";
                else if (cmd == 'C') desc = "CUF: Cursor Right";
                else if (cmd == 'D') desc = "CUB: Cursor Left";
                else if (cmd == 'H') desc = "CUP: Cursor Position";
                else if (cmd == 'm') desc = "SGR: Set Graphics (Color)";
                else if (cmd == 'K') desc = "EL: Erase Line";
                else if (cmd == 's') desc = "SCP: Save Cursor";
                else if (cmd == 'u') desc = "RCP: Restore Cursor";
                else desc = "Unknown Command";

                printf("%-6lld | \033[1;33mSEQUENCE\033[0m   | %-13s | %s (Params: %s)\n", byte_offset, seq.c_str(), desc.c_str(), params.c_str());
                byte_offset += seq.length() - 1; 

            } else {
                // Not a CSI sequence (maybe OSC or just Alt+Key)
                printf("%-6lld | ESCAPE     | \\e            | Raw Escape Char\n", byte_offset);
            }
        } 
        // --- CONTROL CHARS ---
        else if (c == '\n') {
            printf("%-6lld | \033[1;34mCONTROL\033[0m    | \\n            | Newline (y++, x=0)\n", byte_offset);
        }
        else if (c == '\r') {
            printf("%-6lld | \033[1;34mCONTROL\033[0m    | \\r            | Carriage Return (x=0)\n", byte_offset);
        }
        // --- PRINTABLE CHARS ---
        else {
            // Buffer continuous text for cleaner output
            std::string text = ""; 
            text += c;
            while(std::cin.peek() != '\033' && std::cin.peek() != '\n' && std::cin.peek() != '\r' && std::cin.peek() != EOF) {
                 std::cin.get(c);
                 text += c;
                 byte_offset++;
            }
            printf("%-6lld | TEXT       | %-13s | Length: %zu\n", byte_offset, text.substr(0,13).c_str(), text.length());
        }
    }
    return 0;
}
