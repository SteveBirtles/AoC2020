#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct instruction {
  std::string opcode;
  int operand;
  int runCount;
};

int main() {
  std::vector<instruction> instructions;

  std::string line;
  std::ifstream myfile("./dat/day8.txt");

  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      try {
        std::string opcode = line.substr(0, 3);
        int operand = std::stoi(line.substr(4, std::string::npos));

        instruction newInstruction;
        newInstruction.opcode = opcode;
        newInstruction.operand = operand;
        newInstruction.runCount = 0;
        instructions.push_back(newInstruction);

      } catch (int e) {
        std::cout << "An error occured: " << e << std::endl;
      }
    }
    myfile.close();

  } else {
    std::cout << "Unable to open file";
  }

  int pc = 0;
  int acc = 0;

  const int MAX_INSTRUCTIONS = 1000;

  bool part1Done = false;

  for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
    if (!part1Done && instructions[pc].runCount > 0) {
      std::cout << "Part 1: " << acc << std::endl;
      part1Done = true;
    }
    instructions[pc].runCount++;

    if (instructions[pc].opcode == "nop") {
      pc++;
    } else if (instructions[pc].opcode == "jmp") {
      pc += instructions[pc].operand;
    } else if (instructions[pc].opcode == "acc") {
      acc += instructions[pc].operand;
      pc++;
    }
  }

  for (int toChange = 0; toChange < instructions.size(); toChange++) {
    pc = 0;
    acc = 0;
    for (int i = 0; pc < instructions.size() && i < MAX_INSTRUCTIONS; i++) {
      if (instructions[pc].opcode == "nop" ||
          (instructions[pc].opcode == "jmp" && pc == toChange)) {
        pc++;
      } else if (instructions[pc].opcode == "jmp" ||
                 (instructions[pc].opcode == "nop" && pc == toChange)) {
        pc += instructions[pc].operand;
      } else if (instructions[pc].opcode == "acc") {
        acc += instructions[pc].operand;
        pc++;
      }
    }
    if (pc >= instructions.size()) {
      std::cout << "Part 2: " << acc << std::endl;
      break;
    }
  }
}