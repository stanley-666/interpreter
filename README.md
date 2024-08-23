# Compiler Implementation C++
## setup
```
vscode, coderunner or any others C/C++ compiler
```

## Features
```
1.Tokenizer
2.Syntax analyser
3.declare variables, +, -, *, /, compare, comment operation
4.calculator
```

## Future enhancements
```
increase caculate speed, error manager decision
```

## On the roadmap
```
1.Symbol table for declare a function
2.ListAllfunction, ListAllVariable
3.trace line number
4.type error
5.Implement stack and function call 
```
# Interface
## Scanner(Tokenizer)

## Parser(Syntax Analyzer)

## ErrorManager

## Calculator



# For CYCU ourC's structures

## Tokenizer
```
%token  Identifier
%token  Constant   // e.g., 35, 35.67, 'a', "Hi, there", true, false
                   //       .35, 35., 0023
%token  INT     // int
%token  FLOAT   // float
%token  CHAR    // char
%token  BOOL    // bool
%token  STRING  // string <----------- 注意全小寫！
%token  VOID    // void
%token  IF      // if
%token  ELSE    // else
%token  WHILE   // while
%token  DO      // do
%token  RETURN  // return
%token  '('
%token  ')'
%token  '['
%token  ']'
%token  '{'
%token  '}'
%token  '+'
%token  '-'
%token  '*'
%token  '/'
%token  '%'
%token  '^'
%token  '>'
%token  '<'
%token  GE      // >= 
%token  LE      // <= 
%token  EQ      // == 
%token  NEQ     // != 
%token  '&'
%token  '|'
%token  '='
%token  '!'
%token  AND     // && 
%token  OR      // || 
%token  PE      // += 
%token  ME      // -= 
%token  TE      // *= 
%token  DE      // /= 
%token  RE      // %= 
%token  PP      // ++ 
%token  MM      // -- 
%token  RS      // >> 
%token  LS      // << 
%token  ';'
%token  ','
%token  '?'
%token  ':'

/* 
 * (僅供參考) precedence (lower ones are given higher precedence) and associativity
 */

%left   ','
%right  '=' PE ME TE DE RE
%right  '?'+':'
%left   OR
%left   AND
%left   '|'
%left   '^'
%left   '&'
%left   EQ NEQ
%left   '<' '>' GE LE
%left   '+' '-'
%left   '*' '/' '%'
%right  PP MM sign       // sign is '+' or '-' or '!'
%%  // the syntactical part (in EBNF)

user_input 
    : ( definition | statement ) { definition | statement }

definition 
    :           VOID Identifier function_definition_without_ID 
    | type_specifier Identifier function_definition_or_declarators

type_specifier 
    : INT | CHAR | FLOAT | STRING | BOOL

function_definition_or_declarators 
    : function_definition_without_ID
    | rest_of_declarators

rest_of_declarators 
    : [ '[' Constant ']' ] 
      { ',' Identifier [ '[' Constant ']' ] } ';'

function_definition_without_ID 
    : '(' [ VOID | formal_parameter_list ] ')' compound_statement

formal_parameter_list 
    : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
      { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }

compound_statement 
    : '{' { declaration | statement } '}'

declaration 
    : type_specifier Identifier rest_of_declarators

statement
    : ';'     // the null statement
    | expression ';'  /* expression here should not be empty */
    | RETURN [ expression ] ';'
    | compound_statement
    | IF '(' expression ')' statement [ ELSE statement ]
    | WHILE '(' expression ')' statement
    | DO statement WHILE '(' expression ')' ';'
    
expression
    : basic_expression { ',' basic_expression }

basic_expression
    : Identifier rest_of_Identifier_started_basic_exp
    | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
    | sign { sign } signed_unary_exp romce_and_romloe
    | ( Constant | '(' expression ')' ) romce_and_romloe

rest_of_Identifier_started_basic_exp
    : [ '[' expression ']' ]
      ( assignment_operator basic_expression 
        | 
        [ PP | MM ] romce_and_romloe 
      )
    | '(' [ actual_parameter_list ] ')' romce_and_romloe

rest_of_PPMM_Identifier_started_basic_exp
    : [ '[' expression ']' ] romce_and_romloe 

sign
    : '+' | '-' | '!'

actual_parameter_list 
    : basic_expression { ',' basic_expression }

assignment_operator
    : '=' | TE | DE | RE | PE | ME

rest_of_maybe_conditional_exp_and_rest_of_maybe_logical_OR_exp // 即romce_and_romloe
    : rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]

rest_of_maybe_logical_OR_exp 
    : rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }

maybe_logical_AND_exp 
    : maybe_bit_OR_exp { AND maybe_bit_OR_exp }
rest_of_maybe_logical_AND_exp 
    : rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }

maybe_bit_OR_exp 
    : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
rest_of_maybe_bit_OR_exp 
    : rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

maybe_bit_ex_OR_exp 
    : maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
rest_of_maybe_bit_ex_OR_exp 
    : rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }

maybe_bit_AND_exp 
    : maybe_equality_exp { '&' maybe_equality_exp }
rest_of_maybe_bit_AND_exp 
    : rest_of_maybe_equality_exp { '&' maybe_equality_exp }

maybe_equality_exp 
    : maybe_relational_exp 
      { ( EQ | NEQ ) maybe_relational_exp}
rest_of_maybe_equality_exp 
    : rest_of_maybe_relational_exp 
      { ( EQ | NEQ ) maybe_relational_exp }

maybe_relational_exp 
    : maybe_shift_exp 
      { ( '<' | '>' | LE | GE ) maybe_shift_exp }
rest_of_maybe_relational_exp 
    : rest_of_maybe_shift_exp 
      { ( '<' | '>' | LE | GE ) maybe_shift_exp }

maybe_shift_exp 
    : maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
rest_of_maybe_shift_exp 
    : rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }

maybe_additive_exp 
    : maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
rest_of_maybe_additive_exp 
    : rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }

maybe_mult_exp 
    : unary_exp rest_of_maybe_mult_exp
rest_of_maybe_mult_exp 
    : { ( '*' | '/' | '%' ) unary_exp }  /* could be empty ! */

unary_exp
    : sign { sign } signed_unary_exp
    | unsigned_unary_exp
    | ( PP | MM ) Identifier [ '[' expression ']' ]

signed_unary_exp
    : Identifier [ '(' [ actual_parameter_list ] ')' 
                   |
                   '[' expression ']'
                 ]
    | Constant 
    | '(' expression ')'

unsigned_unary_exp
    : Identifier [ '(' [ actual_parameter_list ] ')' 
                   |
                   [ '[' expression ']' ] [ ( PP | MM ) ]
                 ]
    | Constant 
    | '(' expression ')'

```
## Syntax Analyser
For this project, an interpreter that is capable of interpreting commands that are specified using the following syntax.  
```
  <Command>      ::= <Statement> ';' | <BooleanExp> ';' | <ArithExp> ';' | QUIT  
  <Statement>    ::= IDENT ':=' <ArithExp>  
  <BooleanExp>   ::= <ArithExp> ( '=' | '<>' | '>' | '<' | '>=' | '<=' ) <ArithExp>  
  <ArithExp>     ::= <Term> | <ArithExp> '+' <Term> | <ArithExp> '-' <Term>  
  <Term>         ::= <Factor> | <Term> '*' <Factor> | <Term> '/' <Factor>  
  <Factor>       ::= [ SIGN ] NUM | IDENT | '(' <ArithExp> ')'  
```

where  

QUIT is the word 'quit', an IDENT starts with a letter and is followed by digits or letters or underlines (however, an IDENT cannot be the word 'quit' ), a NUM is either an integer or a float number (e.g., 35, 7, 43.8, 43., .35, 1.0 and 07) and SIGN is either '+' or '-'.  
Finally, your program should terminate when the current input command is 'quit'.  

It may be desirable to implement a recursive descent parser in writing your program. Therefore, a translation of the above grammar is given below.  This translation ought to be "usable" in producing a recursive descent parser.  However, there is no guarantee! You yourself bear the ultimate responsibility of producing a "right" translation for the above grammar (one that can be used in producing a recursive descent parser).




```
  <Command> ::= IDENT ( ':=' <ArithExp> | <IDlessArithExpOrBexp> ) ';'  
                | <NOT_IDStartArithExpOrBexp> ';'   
                | QUIT  

  <IDlessArithExpOrBexp>  ::= {   '+' <Term>   | '-' <Term>   
                                | '*' <Factor> | '/' <Factor>     
                              }  
                              [ <BooleanOperator> <ArithExp> ]  

  <BooleanOprator>        ::= '=' | '<>' | '>' | '<' | '>=' | '<='  

  <NOT_ID_StartArithExpOrBexp>   
                          ::= <NOT_ID_StartArithExp>   
                              [ <BooleanOperator> <ArithExp> ]  

  <NOT_ID_StartArithExp>  ::= <NOT_ID_StartTerm> { '+' <Term> | '-' <Term> }  
  <NOT_ID_StartTerm>      ::= <NOT_ID_StartFactor> { '*' <Factor> | '/' <Factor> }  
  <NOT_ID_StartFactor>    ::= [ SIGN ] NUM | '(' <ArithExp> ')'  
  <ArithExp>              ::= <Term> { '+' <Term> | '-' <Term> }  
  <Term>                  ::= <Factor> { '*' <Factor> | '/' <Factor> }  
  <Factor>                ::= IDENT | [ SIGN ] NUM | '(' <ArithExp> ')'  
```


There are three kinds of errors : error on the token level, error on the syntax level, error on the semantics level

  Unrecognized token with first char : '$'   // lexical error (error on the token level)  -- 第一道防線
  Unexpected token : '*'                               // syntactic error (token recognized) -- 第二道防線
  Undefined identifier : 'bcd'                       // semantic error (grammar OK) -- 第三道防線

## error detection sequence：

  first： Unrecognized token with first char
  
  second(token recognized, parse grammar)： Unexpected token
  
  third(grammar OK, evaluate it)：Undefined identifier

Of course, there may be errors that are neither "unrecognized token error" nor "syntax error" nor "undefined ID error".  When there is such an error (e.g., division by zero), your program should just output 'Error'. E.g.,

...
> 3/0
Error



> a:bc



