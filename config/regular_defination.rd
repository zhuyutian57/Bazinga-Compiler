int -> i n t
float -> f l o a t
Integer -> 0 | [^0] digits *
Float -> Integer . digits *
CHARS -> ; | \+ | - | \* | / | = | \( | \)
ID -> ( _ | letters ) ( _ | letters | digits ) *
Lexeme -> int | float | Integer | Float | CHARS | ID
TESTS -> ( a | b ) * a b b