
#include <map>
#include <string>
#include <vector>

namespace lexer {

/* Build DFA directly from regular defination
 * */
class Automata {

public:
	Automata(){}

private:
	class Node;
	class Container;
	Node* root; // Abstract Syntax Tree root
	std::vector<Container*> cv;

}; // Automata

class Automata::Node {

public:
	Node(const std::string& s)
		: name(s) { edge.clear(); }

private:
	std::string name;
	std::map<std::string, Node*> edge;
	
}; // Automata::Node

class Automata::Container {

public:
	Container(const std::string& s)
		: name(s) {}

private:
	std::string name;
	vector<char> ch;

}; // Automata::Container

} // lexer

