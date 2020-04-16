
#include "Action.h"

int main() {
	const char *g_path = "../config/grammars.cfg";
  parser::Action *ac_table = new parser::Action();
  cout << ac_table->Build(g_path) << endl;
  return 0;
}
