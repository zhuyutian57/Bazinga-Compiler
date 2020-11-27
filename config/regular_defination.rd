int -> i n t
float -> f l o a t
if -> i f
else -> e l s e
while -> w h i l e
do -> d o
Op -> \+ | - | \* | / | \| \| | & & | ! | < | > | < = | > = | = = | ! =
Integer -> 0 | [^0] digits *
Float -> Integer . digits *
Characters -> ; | = | \( | \)
ID -> ( _ | letters ) ( _ | letters | digits ) *
Lexeme -> int | float | Op | Integer | Float | Characters | ID
