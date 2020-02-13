
#include <string>

#include "Token.h"

namespace symbol {

class Word : public Token {

public:
	Word(const std::string& s, int t)
		: lexeme(s), Token(t) {}

	const std::string& Lexe() const { return lexeme; }

private:
	std::string lexeme;

}; // Word

} // symbol

