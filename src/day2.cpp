#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct entry {
  int min;
  int max;
  char character;
  std::string password;
};

int main() {
  std::string line;
  std::ifstream myfile("./dat/day2.txt");

  int valid1 = 0;
  int valid2 = 0;
  int checked = 0;

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        entry e;

        int dashLocation = line.find("-");
        int fistSpaceLocation = line.find(" ");
        int colonLocation = line.find(":");

        e.min = std::stoi(line.substr(0, dashLocation));
        e.max = std::stoi(
            line.substr(dashLocation + 1, colonLocation - dashLocation));
        e.character = line[colonLocation - 1];
        e.password = line.substr(colonLocation + 2, std::string::npos);

        int count = 0;
        for (int i = 0; i < e.password.length(); i++) {
          if (e.password[i] == e.character) count++;
        }

        checked++;

        if (count >= e.min && count <= e.max) valid1++;

        char first = e.password[e.min - 1];
        char second = e.password[e.max - 1];

        if ((first == e.character) != (second == e.character)) valid2++;

        std::cout << line << " ... " << e.min << ", " << e.max << ", "
                  << e.character << ", " << e.password << " ... " << count
                  << " - "
                  << (count >= e.min && count <= e.max ? "YES1" : "NO1")
                  << " ... " << first << ", " << second << " - "
                  << ((first == e.character) != (second == e.character) ? "YES2"
                                                                        : "NO2")
                  << std::endl;

      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }

    std::cout << "Part 1 answer = " << valid1 << " / " << checked << std::endl;
    std::cout << "Part 2 answer = " << valid2 << " / " << checked << std::endl;

    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  std::cout << std::endl;
}
