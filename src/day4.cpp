#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using stringPair = std::pair<std::string, std::string>;
using pairVec = std::vector<stringPair>;

int main() {
  std::string keys[]{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  std::vector<pairVec*> passports;

  std::string line;
  std::ifstream myfile("./dat/day4.txt");

  if (myfile.is_open()) {
    auto* pairs = new pairVec;

    while (std::getline(myfile, line)) {
      try {
        if (line == "") {
          passports.push_back(pairs);
          pairs = new pairVec;
          std::cout << std::endl;
        } else {
          int start_key = 0;
          int start_value = -1;

          for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || i == line.length() - 1) {
              if (start_value != -1) {
                pairs->push_back(std::make_pair(
                    line.substr(start_key, 3),
                    line.substr(
                        start_value,
                        i - start_value + (i == line.length() - 1 ? 1 : 0))));
                std::cout << line.substr(start_key, 3) << ":"
                          << line.substr(start_value,
                                         i - start_value +
                                             (i == line.length() - 1 ? 1 : 0))
                          << std::endl;
              }
              start_key = i + 1;
            } else if (line[i] == ':') {
              start_value = i + 1;
            }
          }
        }

      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }
    passports.push_back(pairs);
    std::cout << std::endl;

    myfile.close();

    int count1 = 0, count2 = 0;

    for (auto pairs : passports) {
      bool checks1[] = {false, false, false, false, false, false, false};
      bool checks2[] = {false, false, false, false, false, false, false};

      for (auto pair : *pairs) {
        for (int k = 0; k < 7; k++) {
          std::string key = pair.first;

          if (keys[k] == key) {
            checks1[k] = true;

            std::string value = pair.second;

            try {
              if (key == "byr") {
                int year = std::stoi(value);
                if (year >= 1920 && year <= 2002) checks2[k] = true;
              }

              if (key == "iyr") {
                int year = std::stoi(value);
                if (year >= 2010 && year <= 2020) checks2[k] = true;
              }

              if (key == "eyr") {
                int year = std::stoi(value);
                if (year >= 2020 && year <= 2030) checks2[k] = true;
              }

              if (key == "hgt") {
                std::string units = value.substr(value.length() - 2, 2);
                if (units == "cm" || units == "in") {
                  int height = std::stoi(value.substr(0, value.length() - 2));
                  if (height >= 150 && height <= 193 && units == "cm" ||
                      height >= 59 && height <= 76 && units == "in") {
                    checks2[k] = true;
                  }
                }
              }

              if (key == "hcl") {
                if (value.length() == 7 && value[0] == '#') {
                  int hex = std::stoi(value.substr(1, 6), nullptr, 16);
                  checks2[k] = true;
                }
              }

              if (key == "ecl") {
                if (value == "amb" || value == "blu" || value == "brn" ||
                    value == "gry" || value == "grn" || value == "hzl" ||
                    value == "oth")
                  checks2[k] = true;
              }

              if (key == "pid") {
                if (value.length() == 9) {
                  std::stoi(value);
                  checks2[k] = true;
                }
              }

            } catch (int e) {
              std::cerr << "An error occured: " << e << std::endl;
            }

            break;
          }
        }
      }

      bool valid1 = true, valid2 = true;
      for (int k = 0; k < 7; k++) {
        if (!checks1[k]) valid1 = false;
        if (!checks2[k]) valid2 = false;
      }

      if (valid1) count1++;
      if (valid2) count2++;
    }

    std::cout << "Part 1 " << count1 << " / " << passports.size() << std::endl;
    std::cout << "Part 2 " << count2 << " / " << passports.size() << std::endl;

  } else {
    std::cout << "Unable to open file";
  }
}