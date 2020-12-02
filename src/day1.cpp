#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<int> numbers;

  std::string line;
  std::ifstream myfile("./dat/day1.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        numbers.push_back(std::stoi(line));
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }

    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  for (int i = 0; i < numbers.size() - 1; i++) {
    std::cout << ".";
    for (int j = i + 1; j < numbers.size(); j++) {
      if (numbers[i] + numbers[j] == 2020) {
        std::cout << std::endl
                  << numbers[i] << " x " << numbers[j] << " = "
                  << (numbers[i] * numbers[j]) << std::endl;
        goto endloop1;
      }
    }
  }
endloop1:

  for (int i = 0; i < numbers.size() - 2; i++) {
    std::cout << ".";
    for (int j = i + 1; j < numbers.size() - 1; j++) {
      for (int k = j + 1; k < numbers.size(); k++) {
        if (numbers[i] + numbers[j] + numbers[k] == 2020) {
          std::cout << std::endl
                    << numbers[i] << " x " << numbers[j] << " x " << numbers[k]
                    << " = " << (numbers[i] * numbers[j] * numbers[k])
                    << std::endl;
          goto endloop2;
        }
      }
    }
  }
endloop2:

  std::cout << std::endl;
}
