
namespace symbol {

class Token {

public:
	Token(const int t) : tag(t) {}

	const int& Tag() const { return tag; }

protected:
	int tag;

};	

} // Symbol

