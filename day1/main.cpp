#include <iostream>
#include <fstream>
#include <string>

// Function to process updates
// Return 1 if ends at 0, 0 otherwise, also updates part2_counter for all zero crossings
int process_update(const std::string& command, int& current, int& part2_counter) {
    if (command.empty()) return -1;

    bool isLeft = command[0] == 'L';
    int steps = std::stoi(command.substr(1));
    int at = current;
    int count0 = steps / 100;
    steps = steps % 100;

    if (isLeft) {
        if (at == 0) at = 100;
        if (at <= steps) {
            at += (100 - steps);
            at %= 100;
            ++count0;
        } else {
            at -= steps;
        }
    } else {
        if (at + steps >= 100) {
            ++count0;
            steps -= 100;
        }
        at = (at + steps) % 100;
    }

    part2_counter += count0;
    current = at;
    return current == 0 ? 1 : 0;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "input.txt could not be found";
        return 1;
    }

    int part1_count = 0;
    int part2_count = 0;
    int current = 50;
    std::string line;

    while (std::getline(file, line)) {
        part1_count += process_update(line, current, part2_count);
    }

    std::cout << "Part 1: " << part1_count << std::endl;
    std::cout << "Part 2: " << part2_count << std::endl;
}
