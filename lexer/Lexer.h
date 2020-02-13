
#include <map>
#include <string>
#include <vector>

#include "../symbol/Type.h"
using namespace symbol;

namespace lexer {

class Lexer {

public:
	Lexer() {
		words = new std::map<std::string, void*>;
		tokens = new std::vector<void*>;
		
		reserve(new Type("int", Tag::BASIC, 4));
		reserve(new Type("float", Tag::BASIC, 8));
	}

	void Run() { }

	void* Find(const std::string& s) {
		return (*words)[s];
	}

private:
	std::map<std::string, void*>* words; 
	std::vector<void*>* tokens;

	void reserve(const Word* w) {
		(*words)[w->Lexe()] = (void*)w;
	}

}; // Lexer

} // lexer

