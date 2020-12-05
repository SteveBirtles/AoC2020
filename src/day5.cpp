#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> seats;

  std::string line;
  std::ifstream myfile("./dat/day5.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        seats.push_back(line);
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }
    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  int max = 0, min = 9999999;
  std::vector<int> ids;

  for (auto seat : seats) {
    int row = 0;
    for (int i = 0; i < 7; i++) {
      if (seat[i] == 'B') row += std::pow(2, 6 - i);
    }

    int column = 0;
    for (int i = 0; i < 3; i++) {
      if (seat[i + 7] == 'R') column += std::pow(2, 2 - i);
    }

    int id = row * 8 + column;
    ids.push_back(id);
    if (id > max) max = id;
    if (id < min) min = id;
  }

  std::cout << "Part 1: Max = " << max << std::endl;
  std::cout << "        Min = " << min << std::endl;

  for (int i = min; i <= max; i++) {
    bool found = false;
    for (auto j : ids) {
      if (j == i) found = true;
    }
    if (!found) std::cout << "Part 2: id = " << i << std::endl;
  }
}