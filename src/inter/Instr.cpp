
#include "Instr.h"

using namespace inter;

Instr::Instr(InstrType t, string op[4]) : type(t) {
  for(int i = 0; i < 4; i++) operators[i] = op[i];
}

void Instr::SetLabel(string& l) { label = l; }

void Instr::Generate() {
  if(label != "") {
    std::cout.width(5);
    std::cout.setf(std::ios::left);
    std::cout << label << ":"; 
  }
  string code;
  if(type == CONDITIONAL_YES || type == CONDITIONAL_NO) {
    code = "if";    
    if(type == CONDITIONAL_NO) code += 'n';
    for(int i = 1; i <= 3; i++)
      code += " " + operators[i];
    code += " goto " + operators[0];
  } else if(type == UNCONDITIONAL) {
    code = "goto " + operators[0];
  } else {
    code = operators[0];
    code += " =";
    for(int i = 1; i <= 3; i++)
      code += " " + operators[i];
  }
  bin::Print(code);
}
