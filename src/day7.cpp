#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct entry {
  std::string bag;
  std::vector<std::pair<std::string, int>> children;
  std::vector<entry*> parents;
  bool counted;
};

std::vector<entry*> entries;

int scanParents(entry* e, int depth = 0) {
  if (e->parents.size() == 0) {
    return 0;
  } else {
    int total = 0;
    for (auto p : e->parents) {
      for (int d = 0; d < depth; d++) std::cout << "    ";
      std::cout << e->bag << " are contained inside " << p->bag << std::endl;
      if (!p->counted) {
        p->counted = true;
        total++;
      }
      total += scanParents(p, depth + 1);
    }
    return total;
  }
}

int scanChildren(entry* e, int depth = 0) {
  if (e->children.size() == 0) {  
    return 0;
  } else {
    int total = 0;
    for (auto c : e->children) {      
      for (int d = 0; d < depth; d++) std::cout << "    ";
      std::cout << e->bag << " contain " << c.second << " x " << c.first
                << std::endl;      
      for (auto z : entries) {
        if (c.first == z->bag) total += (1 + scanChildren(z, depth + 1)) * c.second;
      }
    }
    return total;
  }
}

int main() {
  std::ifstream myfile("./dat/day7.txt");

  if (myfile.is_open()) {
    std::string line;
    while (std::getline(myfile, line)) {
      int endBag = line.find("bags contain") - 1;
      entry* e = new entry;
      e->bag = line.substr(0, endBag);
      e->counted = false;
      std::string children = line.substr(endBag + 14, std::string::npos);
      int lastBig = 0;
      for (int i = 0; i < children.length(); i++) {
        if (children[i] == ',' || children[i] == '.') {
          std::string bagsInside = children.substr(lastBig, i - lastBig - 4);
          if (bagsInside == "no other ") continue;
          int spacePlace = bagsInside.find(" ");
          int count = std::stoi(bagsInside.substr(0, spacePlace));
          std::string bag = bagsInside.substr(
              spacePlace + 1,
              bagsInside.length() - spacePlace - (count == 1 ? 1 : 2));
          e->children.push_back(std::make_pair(bag, count));
          lastBig = i + 2;
          i++;
        }
      }
      entries.push_back(e);
    }
    myfile.close();
  } else {
    std::cout << "Unable to open file";
  }

  for (auto e : entries) {
    for (auto c : e->children) {
      for (auto f : entries) {
        if (c.first == f->bag) f->parents.push_back(e);
      }
    }
  }

  for (auto e : entries) {
    if (e->bag == "shiny gold") {
      int count1 = scanParents(e);
      std::cout << "Part 1: " << count1 << std::endl;
      int count2 = scanChildren(e);
      std::cout << "Part 2: " << count2 << std::endl;
    }
  }
}