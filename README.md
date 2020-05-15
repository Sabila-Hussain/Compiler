# Compiler created in C++ for a mini language
Contains a Lexical Analyzer, Parser, and Interpreter.
Uses the following grammar rules for the language:

Prog := Slist

Slist := SC { Slist } | Stmt SC { Slist }

Stmt := IfStmt | PrintStmt | LetStmt | LoopStmt 

IfStmt := IF Expr BEGIN Slist END

LetStmt := LET ID Expr

LoopStmt := LOOP Expr BEGIN Slist END

PrintStmt := PRINT Expr

Expr := Prod { (PLUS | MINUS) Prod }

Prod := Rev { (STAR | SLASH) Rev }

Rev := BANG Rev | PRIMARY

Primary := ID | INT | STR | LPAREN Expr RPAREN

The following items describe the language.
1. The language contains two types: integer and string.
2. The PLUS MINUS STAR and SLASH operators are left associative.
3. The BANG operator is right associative.
4. An IfStmt evaluates the Expr. The Expr must evaluate to an integer. If the integer is
nonzero, then the Slist is executed.
5. A LetStmt evaluates Expr and saves its value in memory associated with the ID. If the ID
does not exist, it is created. If the ID already exists, its value is replaced.
6. A LoopStmt evaluates the Expr. The Expr must evaluate to an integer. If the integer is
nonzero, then the Slist is executed. This process repeats until the Expr evaluation does
not result in a nonzero integer.
7. A PrintStmt evaluates the Expr and prints its value.
8. The type of an ID is the type of the value assigned to it.
9. The PLUS and MINUS operators in Expr represent addition and subtraction.
10. The STAR and SLASH operators in Prod represents multiplication and division.
11. The BANG operator represents reversing its operand.
12. It is an error if a variable is used before a value is assigned to it.
13. Addition is defined between two integers (the result being the sum) or two strings (the
result being the concatenation).
14. Subtraction is defined between two integers (the result being the difference).
15. Multiplication is defined between two integers (the result being the product) or for an integer and a string (the result being the string repeated integer times).
16. Division is defined between two integers.
17. Reversing is defined for integers and strings. The result of reversing an integer is the
operand in reverse order ( ! 123 is 321 ). The result of reversing a string is the operand
in reverse order ( ! “hello” is “olleh” ).
18. Performing an operation with incorrect types or type combinations is an error.
19. Multiplying a string by a negative integer is an error.
20. An IF or LOOP statement whose Expr is not integer typed is an error.

Lexical Rules:
1. The language has identifiers, which are defined to be a letter followed by zero or more
letters or numbers. This will be the Token ID.
2. The language has integer constants, which are defined to be one or more digits. This will
be the Token INT.
3. The language has string constants, which are a double-quoted sequence of characters,
all on the same line. This will be the Token STR.
4. A string constant can include escape sequences: a backslash followed by a character.
The sequence \n should be interpreted as a newline. The sequence \\ should be interpreted as a backslash. All other escapes should simply be interpreted as the character after the backslash.
5. The language has reserved the keywords print, let, if, loop, begin, end. They will be Tokens PRINT LET IF LOOP BEGIN END.
6. The language has several operators. They are + - * / ! ( ) which will be Tokens PLUS MINUS STAR SLASH BANG LPAREN RPAREN
7. The language recognizes a semicolon as the token SC
8. A comment is all characters from // to the end of the line; it is ignored and is not returned
as a token. NOTE that a // in the middle of an STR is NOT a comment!
9. Whitespace between tokens can be used for readability, and it serves to delimit tokens. 
10. An error will be denoted by the ERR token.
11. End of file will be denoted by the DONE token.
