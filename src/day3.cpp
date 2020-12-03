#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::vector<bool>> trees;

  std::string line;
  std::ifstream myfile("./dat/day3.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      std::vector<bool> treeRow;
      try {
        for (int i = 0; i < line.length(); i++) {
          treeRow.push_back(line[i] == '#');
        }
      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
      trees.push_back(treeRow);
    }

    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  int w = trees[0].size();
  long count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;

  for (int i = 0, j = 0; i < trees.size(); i++, j += 1) {
    if (trees[i][j % w]) count1++;
  }

  for (int i = 0, j = 0; i < trees.size(); i++, j += 3) {
    if (trees[i][j % w]) count2++;
  }

  for (int i = 0, j = 0; i < trees.size(); i++, j += 5) {
    if (trees[i][j % w]) count3++;
  }

  for (int i = 0, j = 0; i < trees.size(); i++, j += 7) {
    if (trees[i][j % w]) count4++;
  }

  for (int i = 0, j = 0; i < trees.size(); i += 2, j++) {
    if (trees[i][j % w]) count5++;
  }

  std::cout << "Part 1: " << count2 << std::endl;
  std::cout << "Part 2: " << (count1 * count2 * count3 * count4 * count5)
            << std::endl;
}