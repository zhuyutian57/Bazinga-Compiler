
#ifndef _BIN_H_
#define _BIN_H_

#include "Functions.h"
#include "Messages.h"
#include "Stl.h"

// symbol
#define SYMBOL_TABLE std::unordered_map<std::string, Id*>
#define TYPE_MANAGER std::unordered_map<std::string, Type*>
// nonterminals
#define ENTRY std::string
#define INSTRLIST std::set<int>

// Lexer
#define DNF_STATE       int
#define DFA_EDGE        std::pair<DNF_STATE, char>
#define AST_LEAVES_SET  std::set<int>

// Parser
#define ACCEPTED  "ACC"
// LR0 item - ItemSet.h
#define ITEM                          std::pair<int, int>
#define NEW_ITEM(product_index, dot)  std::make_pair(product_index, dot)
#define ITEMSET                       std::set<ITEM>
#define LOK                           int
#define LOKSET                        std::set<LOK>
#define ITEM_TO_LOKSET                std::map<ITEM, LOKSET*>
#define PRODUCT_INDEX                 first
#define DOT                           second
// LR1 item
#define LRONE_KERNEL                first
#define LRONE_LOK                   second
#define LRONE_PRODUCT_INDEX         first.first
#define LRONE_DOT                   first.second
#define LRONE_ITEM                  std::pair<ITEM, LOK>
#define NEW_LRONE_ITEM(item, lok)   std::make_pair(item, lok)
#define LRONE_ITEMSET               std::set<LRONE_ITEM>
// Action table
#define ACTION_STATE                int
#define ACTION_ERROR                "ERROR"
#define ACTION_SET                  std::vector<std::string>
#define NEW_ACTION_SET              ACTION_SET(unitset.Size() - 2, ACTION_ERROR)
// Reduce
#define ENTRY_TYPE std::pair<ENTRY, Type*>
#define STACK_PUSH(state, nonterminal) \
  e_stack.Push(new State(state, nonterminal))
#define STACK_POP(states_size) \
  for(int i = 0; i < states_size; i++) { \
    delete e_stack.Top(); e_stack.Pop(); \
  }
#define STATE_IF_AND_IE 72
#define PRODUCT_JUMP 38
// Graph
#define VALTYPE         std::set<int>*
#define NODESET         std::vector<VALTYPE>
#define EDGESET_OF_NODE std::vector<VALTYPE>
#define EDGESET         std::vector<EDGESET_OF_NODE>

#endif
