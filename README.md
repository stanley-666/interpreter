# Compiler Implementation C++

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

抓error的順序如下：

  第一防線： Unrecognized token with first char
  
  第二防線(token recognized, parse grammar)： Unexpected token
  
  第三防線(grammar OK, evaluate it)：Undefined identifier

Of course, there may be errors that are neither "unrecognized token error" nor "syntax error" nor "undefined ID error".  When there is such an error (e.g., division by zero), your program should just output 'Error'. E.g.,

...
> 3/0
Error
> a:bc
