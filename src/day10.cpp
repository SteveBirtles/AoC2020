#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long countCombinations(std::vector<int>& adapters, int index, int end) {
  
  if (index == end) return 1;

  bool jumpOne = (adapters[index + 1] == adapters[index] + 1);
  bool jumpThree =
      (adapters[index + 1] == adapters[index] + 3 ||
       index < end - 1 && adapters[index + 2] == adapters[index] + 3);

  long count = 1;
  if (jumpOne && jumpThree) count = 2;

  if (jumpOne) count *= countCombinations(adapters, index + 1, end);
  if (jumpThree) count *= countCombinations(adapters, index + 3, end);

  return count;
}

int main() {
  std::vector<int> adapters{0};

  std::string line;
  std::ifstream myfile("./dat/day10.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        adapters.push_back(std::stoi(line));
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }

    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  std::sort(adapters.begin(), adapters.end(),
            [](int a, int b) { return a < b; });

  int diffs[]{0, 0, 0, 0};

  for (int i = 0; i < adapters.size() - 1; i++) {
    diffs[adapters[i + 1] - adapters[i]]++;
  }

  std::cout << "1: " << diffs[1] << " 3: " << diffs[3] << std::endl;

  std::cout << "Part 1: " << (diffs[1] * (diffs[3] + 1)) << std::endl;

  long combinations = countCombinations(adapters, 0, adapters.size() - 1);

  std::cout << "Part 2: " << combinations << std::endl;
}