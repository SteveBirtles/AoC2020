#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int main() {
  std::array<std::string, 8> keys = {"byr", "iyr", "eyr", "hgt",
                                     "hcl", "ecl", "pid", "cid"};

  std::vector<std::vector<std::tuple<std::string, std::string>>*> passports;

  std::string line;
  std::ifstream myfile("./dat/day4.txt");

  if (myfile.is_open()) {
    auto* codes = new std::vector<std::tuple<std::string, std::string>>;

    while (std::getline(myfile, line)) {
      try {
        if (line == "") {
          passports.push_back(codes);
          codes = new std::vector<std::tuple<std::string, std::string>>;
          std::cout << std::endl;
        } else {
          int start_key = 0;
          int start_value = -1;

          for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' || i == line.length() - 1) {
              if (start_value != -1) {
                codes->push_back(std::make_tuple(
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
    passports.push_back(codes);
    std::cout << std::endl;

    myfile.close();

    int count = 0;

    for (int i = 0; i < passports.size(); i++) {
      bool checks[] = {false, false, false, false, false, false, false, false};

      auto& codes = *passports[i];

      for (int j = 0; j < codes.size(); j++) {
        for (int k = 0; k < 8; k++) {
          std::string code = std::get<0>(codes[j]);
          if (keys[k] == code) {
            std::string value = std::get<1>(codes[j]);

            try {
              if (code == "byr") {
                int year = std::stoi(value);
                if (year >= 1920 && year <= 2002) checks[k] = true;
              }

              if (code == "iyr") {
                int year = std::stoi(value);
                if (year >= 2010 && year <= 2020) checks[k] = true;
              }

              if (code == "eyr") {
                int year = std::stoi(value);
                if (year >= 2020 && year <= 2030) checks[k] = true;
              }

              if (code == "hgt") {
                int height = std::stoi(value.substr(0, value.length() - 2));
                std::string units = value.substr(value.length() - 2, 2);
                if (units == "cm" || units == "in") checks[k] = true;
              }

              if (code == "hcl") {
              }

              if (code == "ecl") {
                if (value == "amb" || value == "blu" || value == "brn" ||
                    value == "gry" || value == "grn" || value == "hzl" ||
                    value == "oth")
                  checks[k] = true;
              }

              if (code == "pid") {
                if (value.length() == 9) {
                  std::stoi(value);
                }
              }

              if (code == "cid") checks[k] = true;

            } catch (int e) {
              std::cout << "An error occured: " << e << std::endl;
            }
          }
        }
      }

      // std::cout << std::endl;

      bool valid = true;
      for (int k = 0; k < 8; k++) {
        if (keys[k] == "cid") continue;
        if (!checks[k]) {
          //  std::cout << "Missing " << keys[k] << std::endl;
          valid = false;
        }
      }

      // std::cout << std::endl;

      if (valid) count++;
    }

    std::cout << "Part 1 " << count << " / " << passports.size() << std::endl;

  } else {
    std::cout << "Unable to open file";
  }
}