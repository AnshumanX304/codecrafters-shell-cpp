#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>    // for std::getenv
#include <fstream>    // for std::ifstream

using namespace std;

int main() {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";

  std::string input;
  std::getline(std::cin, input);
  if(input == "exit 0") {
    return 0;
  }
  else if (input.substr(0, 4) == "echo") {
    std::cout << input.substr(5) << std::endl;
  }
  else if (input.substr(0, 4) == "type") {
    std::string data = input.substr(5);
    if (data == "echo" || data == "exit" || data == "type") {
      std::cout << data << " is a shell builtin" << std::endl;
    }
    else {
      const char* path_env = std::getenv("PATH");
      std::string path_str(path_env);
      string curr = "";
      vector<string> paths;

      for (int i = 0; i < path_str.size(); i++) {
        if (path_str[i] == ':') {
          paths.push_back(curr);
          curr = "";
        }
        else {
          curr += path_str[i];
        }
      }
      if (!curr.empty()) {
        paths.push_back(curr); 
      }

      bool found = false;
      for (auto& it : paths) {
        string newpath = it + "/" + data;
        std::ifstream file(newpath);
        if (file.good()) {
          std::cout << data << " is " << newpath << std::endl;
          found = true;
          break;
        }
      }

      if (!found) {
        std::cout << data << ": not found" << std::endl;
      }
    }
  }
  else {
    std::cout << input << ": command not found" << std::endl;
  }

  main(); // continue shell loop
}
