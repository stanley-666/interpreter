# compiler-by-C++

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
