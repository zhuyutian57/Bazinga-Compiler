
#include "Bin.h"

#ifndef _INSTR_H_
#define _INSTR_H_

namespace inter {

enum InstrType {
  REGULAR,
  CONDITIONAL_YES,
  CONDITIONAL_NO,
  UNCONDITIONAL
};

class Instr {

public:
  Instr(InstrType, string[4]);
  ~Instr() {}

  void SetLabel(string&);
  void Generate();

private:
  InstrType type;
  string label;
  // opt1 = opt2 op opt3
  string operators[4];

}; // class Instr

} // namespace inter

#endif
