#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::vector<long> numbers;

  std::string line;
  std::ifstream myfile("./dat/day9.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        numbers.push_back(std::stol(line));
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }

    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  int magicNumber;

  for (int i = 25; i < numbers.size(); i++) {
    for (int j = 1; j < i; j++) {
      for (int k = 0; k < j; k++) {
        if (numbers[j] + numbers[k] == numbers[i]) goto valid;
      }
    }
    magicNumber = numbers[i];
    break;
  valid:
    continue;
  }

  std::cout << "Part 1: " << magicNumber << std::endl;

  int first;
  int last;

  for (int i = 0; i < numbers.size(); i++) {
    int sum = 0;
    for (int j = i; j < numbers.size(); j++) {
      sum += numbers[j];
      if (sum == magicNumber) {
        first = i;
        last = j;
        goto end;
      } else if (sum > magicNumber) {
        break;
      }
    }
  }
end:

  int min = magicNumber;
  int max = 0;

  for (int i = first; i <= last; i++) {
    if (numbers[i] > max) max = numbers[i];
    if (numbers[i] < min) min = numbers[i];
  }

  std::cout << "Part 2: " << (min + max) << std::endl;
}