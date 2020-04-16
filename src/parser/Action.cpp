
#include "Action.h"

using namespace parser;

bool Action::Build(const char* grammars) {
  if(!GenerateActionTable(grammars)) return false;
  Print("Action table is ok!");
  Informations();
  return true;
}

const std::string& Action::ACTION(
    const ACTION_STATE& s, const LOK& lok) {
  return action_table[s][unitset.Index(lok)];
}

Product* Action::GetProduct(const int& index) {
  return products[index];
}

UnitSet& Action::Units() { return unitset; }

bool Action::GenerateActionTable(const char* grammars) {
  if(!RecognizeCFL(grammars)) return false;
  CalculateFirstTerminalOfUnit();
  if(!GenerateLRZeroItemSet()) return false;
  BuildLokSet();
  if(!GenerateLALROneItemSet()) return false;
  if(!GenerateReduce()) return false;
  return true;
}

bool Action::RecognizeCFL(const char* grammars) {
  std::cin.clear();
  freopen(grammars, "r", stdin);
  std::string product;
  while(std::getline(std::cin, product)) {
    // head -> body1 body2 ...
    std::istringstream ss(product);
    Product *prod = new Product();
    std::string word;
    ss >> word;
    prod->SetHead(unitset[word]);
    ss >> word;
    if(word != "->") return false;
    while(ss >> word)
      prod->AddBody(unitset[word]);
    prod->SetNumber(products.size());
    products.push_back(prod);
  }
  return true;
}

void Action::CalculateFirstTerminalOfUnit() {
  for(auto unit : unitset.Units()) {
    int t = unit.Tag();
    first[t] = new std::set<int>;
    if(t < NONTERMINAL_BEGIN)
      first[t]->insert(t);
  }
  for(bool has_move = true; has_move; ) {
    has_move = false;
    for(auto prod : products) {
      int h = prod->Head();
      for(int i = 0, b; ; i++) {
        b = prod->Body(i);
        if(b == -1) break;
        int head_first_size = first[h]->size();
        MoveSetToSet(first[b], first[h]);
        if(first[h]->size() != head_first_size)
          has_move = true;
        if(first[b]->find(Tag::EPSILON)
            == first[b]->end())
          break;
      }
    }
  }
}

void Action::AddItemSet(ItemSet *itemset) {
  itemset->SetNumber(itemsets.size());
  itemsets.push_back(itemset);
  action_table.push_back(NEW_ACTION_SET);
}

void Action::BuildLokSet() {
  for(auto itemset : itemsets)
    itemset->BuildLokSet();
  itemsets[0]->LokSet(NEW_ITEM(0, 0))->insert('$');
}

ItemSet* Action::LRZeroClosure(const ItemSet *kernel_item) {
  ItemSet *n_itemset = new ItemSet(kernel_item);
  std::map<ITEM, bool> owned;
  std::queue<ITEM> item_queue;
  for(auto item : n_itemset->Items()) {
    owned[item] = true;
    item_queue.push(item);
  }
  while(!item_queue.empty()) {
    ITEM item = item_queue.front();
    item_queue.pop();
    n_itemset->AddItem(item);
    int& product_index = item.PRODUCT_INDEX;
    int& dot = item.DOT;
    int head = products[product_index]->Body(dot);
    if(head >= NONTERMINAL_BEGIN)
      for(auto product_ptr : products)
        if(product_ptr->Head() == head) {
          ITEM item = NEW_ITEM(product_ptr->Number(), 0);
          if(!owned[item]) {
            owned[item] = true;
            item_queue.push(item);
          }
        }
  }
  return n_itemset;
}

ItemSet* Action::LRZeroGoto(ItemSet *from, const Unit& unit) {
  ItemSet *n_itemset = new ItemSet();
  for(auto item : from->Items()) {
    const int& product_index = item.PRODUCT_INDEX;
    const int& dot = item.DOT;
    if(products[product_index]->Body(dot) == unit.Tag())
      n_itemset->AddItem(NEW_ITEM(product_index, dot + 1));
  }
  if(n_itemset->Size() == 0) {
    delete n_itemset;
    n_itemset = NULL;
  }
  return n_itemset;
}

bool Action::GenerateShiftAndGoto(ItemSet *from, Unit& unit, ItemSet *to) {
  const int i = from->Number();
  const int j = unitset.Index(unit.Tag());
  if(action_table[i][j] != ACTION_ERROR) {
    Error(std::string("Shift conflict : ") + '['
        + std::to_string(i) + ',' + unitset[unit.Tag()]
        + ']' + " already has " + action_table[i][j]);
    return false;
  }
  std::string action = "S";
  if(unit.Tag() >= NONTERMINAL_BEGIN) action = "";
  action += std::to_string(to->Number());
  action_table[i][j] = action;
  return true;
}

void Action::GetEpsilonItems(ItemSet *itemset) {
  const int& index = itemset->Number();
  for(auto item : itemset->Items()) {
    const int& product_index = item.PRODUCT_INDEX;
    const int& dot = item.DOT;
    if(products[product_index]->Body(dot) == Tag::EPSILON)
      itemsets[index]->AddItem(item);
  }
}

bool Action::GenerateLRZeroItemSet() {
  AddItemSet(new ItemSet(NEW_ITEM(0, 0), 0));
  std::map<ItemSet, ItemSet*> owned;
  std::queue<ItemSet*> itemset_queue;
  itemset_queue.push(itemsets[0]);
  owned[(*itemsets[0])] = itemsets[0];
  while(!itemset_queue.empty()) {
    ItemSet *from = itemset_queue.front();
    itemset_queue.pop();
    from = LRZeroClosure(from);
    GetEpsilonItems(from);
    for(auto unit : unitset.Units()) {
      if(!unitset.IsIndexed(unit)) continue;
      ItemSet *to = LRZeroGoto(from, unit);
      if(to == NULL) continue;
      if(owned.find((*to)) == owned.end()) {
        owned[(*to)] = to;
        AddItemSet(to);
        itemset_queue.push(to);
      } else {
        ItemSet *del = to;
        to = owned[(*to)];
        delete del;
      }
      if(!GenerateShiftAndGoto(from, unit, to))
        return false;
    }
  }
  return true;
}

LOKSET* Action::FirstBetaA(const std::vector<LOK>& beta, const LOK& a) {
  LOKSET* lokset = new LOKSET;
  bool epsilon = true;
  for(auto b : beta) {
    for(auto u : (*first[b]))
      if(u != Tag::EPSILON)
        lokset->insert(u);
    if(first[b]->find(Tag::EPSILON)
        == first[b]->end()) {
      epsilon = false; break;
    }
  }
  if(epsilon) lokset->insert(a);
  return lokset;
}

LOKSET* Action::FirstBetaA(const LRONE_ITEM& lrone_item) {
  std::vector<LOK> beta;
  const int& product_index = lrone_item.LRONE_PRODUCT_INDEX;
  int body_index = lrone_item.LRONE_DOT + 1;
  while(products[product_index]->Body(body_index) != -1)
    beta.push_back(products[product_index]->Body(body_index++));
  return FirstBetaA(beta, lrone_item.second);
}

LRONE_ITEMSET* Action::LROneClosure(const ITEM& item) {
  LRONE_ITEMSET *n_lrone_itemset = new LRONE_ITEMSET;
  std::queue<LRONE_ITEM> lrone_item_queue;
  lrone_item_queue.push(NEW_LRONE_ITEM(item, '#'));
  while(!lrone_item_queue.empty()) {
    LRONE_ITEM lrone_item = lrone_item_queue.front();
    lrone_item_queue.pop();
    n_lrone_itemset->insert(lrone_item);
    const int& product_index = lrone_item.LRONE_PRODUCT_INDEX;
    const int& dot = lrone_item.LRONE_DOT;
    const int head = products[product_index]->Body(dot);
    LOKSET *lokset = FirstBetaA(lrone_item);
    for(auto product_ptr : products)
      if(product_ptr->Head() == head) {
        ITEM n_item = NEW_ITEM(product_ptr->Number(), 0);
        for(auto lok : (*lokset)) {
          LRONE_ITEM n_lrone_item = NEW_LRONE_ITEM(n_item, lok);
          if(n_lrone_itemset->find(n_lrone_item) 
              == n_lrone_itemset->end())
            lrone_item_queue.push(n_lrone_item);
        }
      }
    delete lokset;
  }
  return n_lrone_itemset;
}

// Because that shift actions and goto actions
// are generated by GenerateLRZeoroItemSet() and
// that lookahead has no effect on determining shift
// actions and goto actions, we can get GOTO(I, X)
// by reading action_table builded before.
int Action::LROneGoto(const int& I, const int& X) {
  if(X == -1) return -1;
  if(!unitset.IsIndexed(X)) return I;
  std::string& action = action_table[I][unitset.Index(X)];
  if(action == ACTION_ERROR) return -1;
  if(action[0] != 'S') return std::stoi(action);
  return std::stoi(action.substr(1, action.size()));
}

Graph* Action::DetermineLookahead() {
  Graph *propagate_graph = new Graph();
  for(auto I : itemsets) {
    const int state = I->Number();
    for(auto kernel_item : I->Items()) {
      LOKSET *from= I->LokSet(kernel_item);
      propagate_graph->AddNode(from);
      LRONE_ITEMSET *J = LROneClosure(kernel_item);
      for(auto lrone_item : (*J)) {
        const int& product_index = lrone_item.LRONE_PRODUCT_INDEX;
        const int& dot = lrone_item.LRONE_DOT;
        const int X = products[product_index]->Body(dot);
        // GOTO(I, X) = K
        const int K = LROneGoto(I->Number(), X);
        if(K == -1) continue; // K == -1 means ERROR
        ITEM n_item = lrone_item.LRONE_KERNEL;
        if(X != Tag::EPSILON) n_item.DOT++;
        LOKSET *to = itemsets[K]->LokSet(n_item);
        if(lrone_item.LRONE_LOK == '#')
          propagate_graph->AddEdge(from, to);
        else
          to->insert(lrone_item.LRONE_LOK);
      }
      delete J;
    }
  }
  return propagate_graph;
}

bool Action::GenerateLALROneItemSet() {
  Graph *propagate_graph = DetermineLookahead();
  std::queue<LOKSET*> lokset_queue;
  for(auto lokset : propagate_graph->Nodes())
    if(!lokset->empty()) lokset_queue.push(lokset);
  while(!lokset_queue.empty()) {
    LOKSET *from = lokset_queue.front();
    lokset_queue.pop();
    for(auto to : propagate_graph->EdgesOfNode(from)) {
      const int& sz = to->size();
      MoveSetToSet(from, to);
      if(to->size() != sz)
        lokset_queue.push(to);
    }
  }
  delete propagate_graph;
  return true;
}

bool Action::GetAllBodies(const ITEM& item) {
  Product *product = products[item.PRODUCT_INDEX];
  if(product->Body(0) == Tag::EPSILON) return true;
  return item.DOT == product->BodySize();
}

bool Action::GenerateReduce() {
  for(auto itemset : itemsets) {
    const int& i = itemset->Number();
    for(auto item : itemset->Items()) {
      if(!GetAllBodies(item)) continue;
      for(auto lok : (*itemset->LokSet(item))) {
        const int& j = unitset.Index(lok);
        if(action_table[i][j] != ACTION_ERROR) {
          Error(std::string("Conflict : ") + '['
              + std::to_string(i) + ',' + unitset[lok]
              + "] already has " + action_table[i][j]);
          return false;
        }
        std::string action = "R";
        if(item.PRODUCT_INDEX == 0) action = "ACC";
        else action += std::to_string(item.PRODUCT_INDEX);
        action_table[i][j] = action;
      }
    }
  }
  return true;
}

void Action::InformationOfProducts() {
  const std::string label = "PRODUCTS";
  int side_space = 16;
  PrintLabel(side_space, label, '=');
  for(auto prod : products) {
    std::cout << "  " << prod->Number() << " . ";
    std::cout << unitset[prod->Head()] << " ->";
    for(int i = 0, j; j = prod->Body(i) ;i++) {
      if(j == -1) break;
      std::cout << ' ' << unitset[j];
    }
    std::cout << '\n';
  }
  PrintLabel(side_space, label, '=');
}

void Action::InformationOfFirstSets() {
  const std::string label = "FIRST SETS";
  int side_space = 16;
  PrintLabel(side_space, label, '=');
  for(auto f : first) {
    if(f.second->size() == 0) continue;
    std::cout << " - "<< unitset[f.first] << " :";
    for(auto tag : (*f.second))
      std::cout << ' ' << unitset[tag];
    std::cout << '\n';
  }
  PrintLabel(side_space, label, '=');
}

void Action::InformationOfItemSets() {
  const std::string label = "ITEMSETS";
  int side_space = 16;
  PrintLabel(side_space, label, '=');
  for(auto itemset : itemsets) {
    std::cout << " No." << itemset->Number();
    std::cout << " with " << itemset->Size() << " items\n";
    std::cout << " - Kernel Item:\n";
    for(auto item : itemset->Items()) {
      std::cout << " - " << item.PRODUCT_INDEX << ' '
        << item.DOT << " ,";
      for(auto lok : *itemset->LokSet(item))
        std::cout << ' ' << unitset[lok];
      std::cout << '\n';
    }
    std::cout << " - Shifts & Gotoes:\n";
    int state = itemset->Number();
    for(auto unit : unitset.Units()) {
      if(!unitset.IsIndexed(unit.Tag())) continue;
      int lo = unitset.Index(unit.Tag());
      if(action_table[state][lo] != "ERROR")
        std::cout << " - " << unitset[unit.Tag()] << ' '
          << action_table[state][lo] << '\n';
    }
    std::cout << '\n';
  }
  PrintLabel(side_space, label, '=');
}

void Action::InformationOfActionTable() {
  const std::string label = "ATION TABLE";
  int side_space = (unitset.Size() - 2) * WIDTH + 4;
  side_space -= label.size();
  side_space = (side_space + 1) / 2;
  PrintLabel(side_space, label, '=');
  FORMAT; std::cout << "State";
  for(auto unit : unitset.Units()) {
    if(unit.Tag() == Tag::EPSILON) continue;
    if(unit.Tag() == Tag::PROGRAM) continue;
    FORMAT; std::cout << unitset[unit.Tag()];
  }
  std::cout << '\n';
  int number = 0;
  for(auto actions : action_table) {
    FORMAT; std::cout << number++;
    for(auto action : actions) {
      FORMAT;
      if(action != "ERROR")
        std::cout << action;
      else std::cout << "-";
    }
    std::cout << '\n';
  }
  PrintLabel(side_space, label, '=');
}

void Action::Informations() {
  InformationOfProducts();
  InformationOfFirstSets();
  InformationOfItemSets();
  InformationOfActionTable();
}
