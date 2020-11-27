
#ifndef _TAG_NAMESPACE_
#define _TAG_NAMESPACE_

namespace symbols {

namespace Tag {

  /* ================= Terminals ================= */
  // Types - int, float
  const int TYPE = 300;

  // Variables
  const int ID = 301;

  // Data types
  const int INTEGER = 302, REAL = 303;

  // Keyword
  const int IF = 304, ELSE = 305, WHILE = 306, DO = 307;

  // Logic Operators
  const int OR = 308, AND = 309, EQ = 310, NE = 311;
  const int LE = 312, GE = 313;

  // Bool Constants
  const int TRUE = 314, FALSE = 315;

  // Epsilon
  const int EPSILON = 399;
  /* ================= Terminals ================= */
  
  /* ================= Nonterminals ================= */
  const int STMTS = 400, STMT = 401;
  const int BOOL = 402, JOIN = 403, EQUAL = 404, INEQ = 405;
  const int ARITH = 406, TERM = 407, UNARY = 408, FACTOR = 409;
  const int INSTR = 410, JUMP = 411;

  const int PROGRAM = 499;
  /* ================= Nonterminals ================= */

} // namespace Tag

} // namespace symbols

#endif
