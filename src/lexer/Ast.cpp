
#include "Ast.h"
using namespace bin;
using namespace lexer;

Ast::Ast() : leaf_size(-1), lexeme_tree(NULL) {
  mpr["letters"] = BuildLetterTree(NULL);
  mpr["digits"] = BuildDigitTree(NULL);
}
Ast::~Ast() {
  if(lexeme_tree != NULL)
    delete lexeme_tree;
}

bool Ast::Build(const char* rd_path) {
  if(!BuildTrees(rd_path)) { Print("fail!");return false; }
  Print("Recognizing regular definations is ok!");
  lexeme_tree = new Node(CAT, mpr["Lexeme"], new Node('#'));
  Ast::Info* root = Calculate(lexeme_tree);
  MoveSetToSet(root->firstpos, &root_firstpos);
  delete root;
  Print("Ast is ok!");
  return true;
}

int Ast::LeafSize() { return leaf_size; }

const std::set<int>& Ast::RootFirstpos() {
  return root_firstpos;
}

const std::set<char>& Ast::Characters() {
  return characters;
}

char Ast::CharOfPosition(int i) { return posch[i]; }

const std::vector<std::set<int>* >& Ast::Followpos() {
  return followpos;
}

Node* Ast::CreateNode(const std::string& s) {
  if(s == "(") return new Node(LBR);
  if(s == ")") return new Node(RBR);
  if(s == "|") return new Node(OR);
  if(s == "+") return new Node(PLUS);
  if(s == "*") return new Node(STAR);
  Node *p;
  if(s[0] == '[') p = BuildNotTree(s);
  else if(mpr.find(s) != mpr.end()) p = mpr[s];
  else if(s[0] == '\\') p = new Node(s[1]);
  else p = new Node(s[0]);
  return new Node(SUBT, p, NULL);
}

Node* Ast::MergeNodes(std::stack<Node*>* S) {
  Node *p, *del;
  del = S->top(); S->pop();
  p = del->Ls();
  delete del; // delete extra node labeled "SUBT"
  while(!S->empty() && S->top()->Nt() != LBR) {
    if(S->top()->Nt() == OR) {
      S->top()->SetRs(p);
      p = S->top(); S->pop();
      del = S->top(); S->pop();
      p->SetLs(del->Ls());
    } else {
      del = S->top(); S->pop();
      p = new Node(CAT, del->Ls(), p);
    }
    delete del;
  }
  return p;
}

Node* Ast::BuildSubtrees(std::istringstream& ss) {
  std::string x;
  std::stack<Node*>* S = new std::stack<Node*>;
  while(ss >> x) {
    Node *t = CreateNode(x);
    switch(t->Nt()) {
      case OR:
        S->push(new Node(SUBT, MergeNodes(S), NULL));
        break;
      case RBR:
        delete t;
        t = new Node(SUBT, MergeNodes(S), NULL);
        delete S->top(); S->pop();
        break;
      case LBR: break;
      case SUBT: break;
      default: // FOr PLUS and STAR
        t->SetLs(S->top()->Ls());
        delete S->top(); S->pop();
        t = new Node(SUBT, t, NULL);
    }
    S->push(t);
  }
  return MergeNodes(S);
}

bool Ast::BuildTrees(const char* rd_path) {
  std::cin.clear();
  freopen(rd_path, "r", stdin);
  std::string rd;
  while(std::getline(std::cin, rd)) {
    std::istringstream ss(rd); // make rd as words stream 
    std::string name, flag;
    ss >> name >> flag;
    if(flag != "->") {
      ErrorRegularDefination(name, ss);
      return false;
    }
    mpr[name] = BuildSubtrees(ss);
  }
  return true;
}

Node* Ast::BuildOrTree(const std::string& s) {
  Node* rt = NULL;
  for(auto ch : s) {
    if(rt == NULL) {
      rt = new Node(ch);
      continue;
    }
    rt = new Node(OR, rt, new Node(ch));
  }
  return rt;
}

Node* Ast::BuildNotTree(const std::string& s) {
  if(s[1] != '^') return NULL;
  std::set<char>* del = new std::set<char>;
  for(int i = 2; i < s.size() - 1; i++)
    del->insert(s[i]);
  if(s[2] >= '0' && s[2] <= '9')
    return BuildDigitTree(del);
  return BuildLetterTree(del);
}

Node* Ast::BuildLetterTree(const std::set<char>* del) {
  std::string s = "";
  for(char c = 'a'; c <= 'z'; c++)
    if(del == NULL || del->find(c) == del->end())
      s += c;
  for(char c = 'A'; c <= 'Z'; c++)
    if(del == NULL || del->find(c) == del->end())
      s += c;
  return BuildOrTree(s);
}

Node* Ast::BuildDigitTree(const std::set<char>* del) {
  std::string s = "";
  for(char c = '0'; c <= '9'; c++)
    if(del == NULL || del->find(c) == del->end())
      s += c;
  return BuildOrTree(s);
}

void Ast::CalculateFollowPosition(
    std::set<int>* in, std::set<int>* out) {
  for(auto i : (*in))
    for(auto n : (*out))
      followpos[i]->insert(n);
}

Ast::Ast::Info* Ast::Calculate(const Node *p) {
  Ast::Info* info = new Info();
  switch(p->Nt()) {
    case LEAF:
      ++leaf_size;
      info->nullable = false;
      info->firstpos->insert(leaf_size);
      info->lastpos->insert(leaf_size);
      posch[leaf_size] = p->Ch();
      characters.insert(p->Ch());
      followpos.push_back(new std::set<int>);
      break;
    case STAR: {
      Ast::Info* i_ls = Calculate(p->Ls());
      info->nullable = true;
      MoveSetToSet(i_ls->firstpos, info->firstpos);
      MoveSetToSet(i_ls->lastpos, info->lastpos);
      CalculateFollowPosition(info->lastpos, info->firstpos);
      delete i_ls;
      break;
    }
    case CAT: {
      Ast::Info *i_ls = Calculate(p->Ls());
      Ast::Info *i_rs = Calculate(p->Rs());
      info->nullable = (i_ls->nullable && i_rs->nullable);
      CalculateFollowPosition(i_ls->lastpos, i_rs->firstpos);
      MoveSetToSet(i_ls->firstpos, info->firstpos);
      MoveSetToSet(i_rs->lastpos, info->lastpos);
      if(i_ls->nullable)
        MoveSetToSet(i_rs->firstpos, info->firstpos);
      if(i_rs->nullable)
        MoveSetToSet(i_ls->lastpos, info->lastpos);
      delete i_ls, i_rs;
      break;
    }
    case OR: {
      Ast::Info *i_ls = Calculate(p->Ls());
      Ast::Info *i_rs = Calculate(p->Rs());
      info->nullable = (i_ls->nullable || i_rs->nullable);
      MoveSetToSet(i_ls->firstpos, info->firstpos);
      MoveSetToSet(i_rs->firstpos, info->firstpos);
      MoveSetToSet(i_ls->lastpos, info->lastpos);
      MoveSetToSet(i_rs->lastpos, info->lastpos);
      delete i_ls, i_rs;
      break;
    }
    case PLUS: break; //TODO add PLUS
    default: Error("Fail to build AST!\n");
  }
  return info;
}
