
#include "Instr.h"

#ifndef _INSTR_H_
#define _INSTR_H_

namespace inter {

class Manager {

public:
  Manager() {}
  ~Manager();

  void AddInstr(Instr*);
  void BackPatch(INSTRLIST*, string&);
  void GenerateInter();

private:
  std::vector<Instr*> instrs;

}; // class Manager

} // namespace inter

#endif
