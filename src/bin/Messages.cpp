
#include "Messages.h"

void bin::Print(const std::string& s) {
  std::cout << s << '\n';
}

void bin::Error(const std::string& mes) { bin::Print(mes); }

// Wrong regular defination
void bin::ErrorRegularDefination(
  const std::string& name,
  std::istringstream& ss) {
  std::cout<< name << " ->";
  std::string x;
  while(ss >> x) std::cout << " " + x;
  std::cout << " is not a regular defination\n";
}

void bin::PrintLabel(
    const int& side_space,
    const std::string& label,
    const char& fill_char) {
  std::cout << '\n';
  PRINT_CHAR(side_space, fill_char);
  std::cout << ' ' << label << ' ';
  PRINT_CHAR(side_space, fill_char);
  std::cout << "\n\n";
}
