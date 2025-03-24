
// ZIP Komprimierung (LZ77)

#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Include the sstream header
#include <bitset>
#include <cctype>

std::string to_string(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

int main() {
    std::string input = "00000000000000001111000011110000000000111111111011010101010101011010101010101010101010100101101101011011011010101010101010101010101010110000111110000111100111000101010101010101010101010101010101010101010010101001010101010101010101010101010101010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111101010101010101010101010101010101010101010101010100011100100110011001100000000000000000000000000000000000000000000000000000000000000000000000001010101010101010101010101010101010101010101010101010101010101010101010000011111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100000000000000000000000011011111111111111111111111111111111111111111111111111111111111111111111111111010101011111111101111111111100000001010101000010101101010101010101010101001010101010011000010101010000111111111111000000000101010101000000001010101010101010101010101010000001010101110111111011111100000001010101010101010111111101010101010100000000000000101011111100101010101010000000000000000000000000000010101011011111110100110101110101011010101010101101010100010111010110111111111010101011111010101010100000101";
    int window_length = 16;
    int l_max = 32;
    int starting_pos = 0;
    bool flag = true;
    int counter = 0;
    size_t position;
    int temp_window_size;
    bool no_match = false;
    std::string output = "";

    std::string window(window_length, 'x');  // Fenster mit 4 'x' initialisieren
    std::vector<std::vector<std::string>> encoded_input;

    for (int i = 0; i < input.length(); i++) {
        temp_window_size = window_length;
        while (1) {
            if (i + temp_window_size > input.length())
                temp_window_size -= (i+temp_window_size)%input.length();
            position = window.find(input.substr(i, temp_window_size));
            if (position == std::string::npos) {
                temp_window_size--;
                if (temp_window_size == 0) {
                    no_match = true;
                    break;
                }
            }
            else {
                // max length of 8
                int static_window_size = temp_window_size;
                while (input.substr(i+temp_window_size, static_window_size) == window.substr(position, static_window_size)) {
                    if (l_max > temp_window_size) {
                        temp_window_size = temp_window_size+static_window_size;
                    }
                    else {
                        break;
                    }    
                }
                break;
            }
        }
        if (no_match)
            encoded_input.push_back({to_string(0), std::string(1, input[i])});
        else
            encoded_input.push_back({to_string(1), to_string(position), to_string(temp_window_size)});
        no_match = false;

        if (temp_window_size == 0) {
            std::cout << "input STR: " << input[i];
            std::cout << "   Position: x";
        }
        else {
            std::cout << "input STR: " << input.substr(i, temp_window_size);
            std::cout << "   Position: " << position;
        }    
        std::cout << "   match Length: " << temp_window_size;
        std::cout << "   Fenster: " << window;

        if (temp_window_size >= 1)
            i += temp_window_size - 1;

        // Update the window with the next characters
        for (int k = window_length; k > 0; k--) {
            if (i - (window_length - k) >= 0)
                window[k - 1] = input[i - (window_length - k)];
            else
                window[k - 1] = 'x';
        }

        // Access the last pushed element in encoded_input
        std::cout << "   encoded: " << encoded_input[encoded_input.size() - 1][0] << " " << encoded_input[encoded_input.size() - 1][1];
        if (encoded_input[encoded_input.size() - 1].size() > 2)
            std::cout << " " << encoded_input[encoded_input.size() - 1][2] << std::endl;
        else 
            std::cout << std::endl;
    }
    std::cout << "Input: " << input << std::endl;
    std::cout << std::endl;
    std::cout << "Encoded: ";
        for (const auto& row : encoded_input) {
            //std::cout << " ";
            for (const auto& elem : row) {
                std::cout << elem;
            }
        }
        std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Length normal: " << input.length() << " --- Length encoded (upper Bound): " << encoded_input.size()*3 << " --- Compression: " << (1 - (encoded_input.size()*3.0)/input.length())*100 << "%";

    return 0;
}