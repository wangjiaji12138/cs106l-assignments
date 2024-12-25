#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int run_autograder() {
  auto run_program = [](std::string program, std::initializer_list<std::string> args) {
    std::stringstream ss;

    ss << program;
    for (const auto& arg : args) {
      ss << ' ' << arg;
    }

    std::cout.flush();
    return system(ss.str().c_str());
  };

  std::string python;
  for (const auto& option : {"python", "python3", "/usr/bin/python3", "/usr/bin/python"}) {
    if (run_program(option, {"--version"}) == 0) {
      python = option;
      break;
    }
  }

  if (python.empty()) {
    std::cerr << "Python was not found on your system. Please install Python and "
                 "try again."
              << "\n";
    std::exit(1);
  }

  /* #### Assignment Specific Operations #### */
  auto allMatches = get_applicants("students.txt");
  auto studentMatches = find_matches(kYourName, allMatches);
  auto match = get_match(studentMatches);

  std::fstream matchFile("autograder/student_output/match.txt");
  std::fstream setFile("autograder/student_output/set.txt");

  matchFile << kYourName << '\n' << "Your match is: " << match << '\n';
  for (const auto& student : allMatches) {
    setFile << student << '\n';
  }

  // Flush streams so that the Python autograder is guaranteed to see their changes
  matchFile.flush();
  setFile.flush();
  /* #### End of Assignment Specific Operations #### */

  return run_program(python, {"autograder/autograder.py"});
}

bool matchName(std::string myName,std::string hisName){
  size_t mypos = myName.find(' ');
  std::string myFirstName = myName.substr(0,mypos);
  std::string myLastName = myName.substr(mypos+1);

  size_t hispos = hisName.find(' ');
  std::string hisFirstName = hisName.substr(0,hispos);
  std::string hisLastName = hisName.substr(hispos+1);

  if(myFirstName[0] == hisFirstName[0] && myLastName[0] == hisLastName[0]){
    return true;
  }
  return false;
}