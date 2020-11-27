
#include "Manager.h"

using namespace inter;

Manager::~Manager() {
  for(auto ptr : instrs) delete ptr;
}

void Manager::AddInstr(Instr* instr) {
  instrs.push_back(instr);
}

void Manager::BackPatch(INSTRLIST* list, string& label) {
  for(auto i : (*list)) instrs[i]->SetLabel(label);
}

void Manager::GenerateInter() {
  for(auto instr : (*instrs))
    instr->Generate(); 
} 
