#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string line;
  std::string batch = "";
  int lines = 0;
  std::vector<std::pair<std::string, int>> batches;
  std::ifstream myfile("./dat/day6.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        if (line == "") {
          batches.push_back(std::make_pair(batch, lines));
          batch = "";
          lines = 0;
        } else {
          batch += line;
          lines++;
        }
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }
    if (lines > 0) batches.push_back(std::make_pair(batch, lines));
  }

  int uniqueTotal = 0;
  int allTotal = 0;

  for (auto batch : batches) {
    std::string unique = "";
    for (int i = 0; i < batch.first.length(); i++) {
      if (unique.find(batch.first[i]) == std::string::npos) {
        unique += batch.first[i];
      }
    }

    uniqueTotal += unique.length();

    std::vector<std::pair<char, int>> counts;
    for (int j = 0; j < unique.length(); j++) {
      int count = 0;
      for (int i = 0; i < batch.first.length(); i++) {
        if (unique[j] == batch.first[i]) count++;
      }
      counts.push_back(std::make_pair(unique[j], count));
    }

    for (auto pair : counts) {      
      if (pair.second == batch.second) allTotal++;
    }

  }

  std::cout << "Part 1: " << uniqueTotal << std::endl;
  std::cout << "Part 2: " << allTotal << std::endl;
}