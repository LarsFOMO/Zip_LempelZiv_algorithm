#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Include the sstream header

std::string to_string(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

int main() {
    std::string input = "ABB ABB ABB BAA BABA";
    int window_length = 4;
    int l_max = 8;
    int starting_pos = 0;
    bool flag = true;
    int counter = 0;
    size_t position;
    int temp_window_size;
    bool no_match = false;

    std::string window(window_length, 'x');  // Fenster mit 4 'x' initialisieren
    std::vector<std::vector<std::string>> encoded_input;

    for (int i = 0; i < input.length(); i++) {
        temp_window_size = window_length;
        while (1) {
            if (i + temp_window_size > input.length()) {
                temp_window_size -= (i+temp_window_size)%input.length();
            }
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
                std::cout << "input STR: " << input.substr(i, temp_window_size);
                std::cout << "   match Length: " << temp_window_size;
                std::cout << "   Position: " << position;
                break;
            }
        }
        if (no_match) {
            encoded_input.push_back({to_string(0), std::string(1, input[i])});
        }
        else {
            encoded_input.push_back({to_string(1), to_string(position), to_string(temp_window_size)});
        }
        no_match = false;

        std::cout << "   Fenster: " << window;

        if (temp_window_size >= 1) {
            i += temp_window_size - 1;
        }

        // Update the window with the next characters
        for (int k = window_length; k > 0; k--) {
            if (i - (window_length - k) >= 0)
                window[k - 1] = input[i - (window_length - k)];
            else
                window[k - 1] = 'x';
        }
        std::cout << "   Fenster (update): " << window;

        // Access the last pushed element in encoded_input
        std::cout << "   encoded: " << encoded_input[encoded_input.size() - 1][0] << " " << encoded_input[encoded_input.size() - 1][1];
        if (encoded_input[encoded_input.size() - 1].size() > 2) {
            std::cout << " " << encoded_input[encoded_input.size() - 1][2] << std::endl;
        }
        else 
            std::cout << std::endl;
    }
    

    return 0;
}
