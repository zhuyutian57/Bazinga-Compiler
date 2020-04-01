
#include <iostream>
#include <sstream>

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

namespace bin {

#define WIDTH 8
#define FORMAT std::cout.width(WIDTH), \
  std::cout.setf(std::ios::left)
#define PRINT_CHAR(n, fill_char) \
  for(int i = 0; i < n; i++) std::cout<< fill_char;

  
inline void Print(const std::string& s) {
  std::cout << s << '\n';
}

inline void Error(const std::string& mes) { Print(mes); }

  // Wrong regular defination
inline void ErrorRegularDefination(/*{{{*/
  const std::string& name,
  std::istringstream& ss) {
  std::cout<< name << " ->";
  std::string x;
  while(ss >> x) std::cout << " " + x;
  std::cout << " is not a regular defination\n";
}/*}}}*/

inline void PrintLabel(/*{{{*/
    const int& side_space,
    const std::string& label,
    const char& fill_char) {
  std::cout << '\n';
  PRINT_CHAR(side_space, fill_char);
  std::cout << ' ' << label << ' ';
  PRINT_CHAR(side_space, fill_char);
  std::cout << "\n\n";
}/*}}}*/

} // namespace message

#endif
