
#include "Stl.h"

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace bin {

#define WIDTH 8
#define FORMAT std::cout.width(WIDTH), \
  std::cout.setf(std::ios::left)
#define PRINT_CHAR(n, fill_char) \
  for(int i = 0; i < n; i++) std::cout<< fill_char;

  
void Print(const std::string&);

void Error(const std::string&);

// Wrong regular defination
void ErrorRegularDefination(
    const std::string& name, std::istringstream& ss);

void PrintLabel(
    const int& side_space,
    const std::string& label,
    const char& fill_char);

} // namespace message

#endif
