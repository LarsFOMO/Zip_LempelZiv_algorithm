
    // Lempel-Ziv Algorithm (LZ77) [does not work as expected!]

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream> // Include the sstream header

std::string to_string(int value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

int main() {

    char input[] = "ABBABBABBBAABABA";
    int window_length = 4;
    int l_max = 8;
    int starting_pos = 0;
    bool flag = true;
    int counter = 0;

    std::vector<char> window(window_length + 1);
    std::fill(window.begin(), window.end(), '\0');
    std::vector<std::vector<std::string>> encoded_input; // Change to vector of strings

    for (int i = 0; i < strlen(input); i++) {
        counter = 0;
        starting_pos = 0;
        for (int k = 0; k < l_max; k++) {
            if (input[i] == window[k]) {
                if (flag == true) {
                    starting_pos = window_length - k;
                    counter = 1;
                    flag = false;
                }
                else {
                    counter++;
                    //if (k > 3)
                        //i =+ (k);
                }
            }
            else
                if (flag == false) {
                    
                    break;
                }
        }
        if (counter == 0)
            encoded_input.push_back({to_string(0), std::string(1, input[i])});  // (0, B) oder (0, A)
        else
            encoded_input.push_back({to_string(1), to_string(starting_pos), to_string(counter)});   // (1, start_pos, counter)
        flag = true;

        // Ensure i is within bounds before accessing encoded_input
        if (i < encoded_input.size()) {
            for (const auto& num : encoded_input[i]) {
                std::cout << num << " ";
            }
        }
        std::cout << "---";
        printf(" %i --- ", i);
        for (int c = 0; c < window_length; c++) {
            std::cout << window[c] << " ";
        }
        std::cout << std::endl;

        for (int x = 0; x < window_length - 1; x++) {
            window[x] = window[x + 1];
        }
        window[window_length - 1] = input[i];
    }

    return 0;
}