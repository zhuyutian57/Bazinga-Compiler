
#ifndef _TAG_NAMESPACE_
#define _TAG_NAMESPACE_

namespace symbol {

namespace Tag {

  /* ================= Lexer ================= */
  // Types - int, float
  const static int TYPE = 300;

  // Variables
  const static int ID = 301;

  // Data types
  const static int INTEGER = 302, FLOAT = 303;

  // End flog
  const static int END = '$';
  /* ================= Lexer ================= */
  
  /* ================= Parser ================= */
  // Terminal
  const static int EPSILON = 400;
  // Nonterminals
  const static int PROGRAM = 401;
  const static int STMTS = 402, STMT = 403;
  const static int EXPR = 404, TERM = 405;
  const static int UNARY = 406, FACTOR = 407;
  const static int ADD_ID = 408, ID_EXIST = 409;
  /* ================= Parser ================= */

  /* ================= Test ================= */
  // Nonterminals
  const static int
    P = 501, S = 502, L = 503, R = 504;

  /* ================= Test ================= */

} // namespace Tag

} // namespace symbol

#endif
