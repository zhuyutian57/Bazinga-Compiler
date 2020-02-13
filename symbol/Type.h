
#include <string>

#include "Tag.h"
#include "Word.h"

namespace symbol {

class Type : public Word {

public:
	Type(const std::string& s, int tag, int w)
		: Word(s, tag), width(w) {}

	const int& Width() const { return width; }

private:
	int width;

}; // Type

} // symbol

