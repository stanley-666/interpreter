#pragma once
#include<vector>
#include<iostream>
  using namespace std;
#include "Token.h"

enum ErrorType {
  UNKNOWN_ERROR = 21,
  Unrecognized_token = 22,
  Unexpected_token,
  Undefined_identifier,
  ILLEGAL_GETCHAR
};

class ErrorManager { // Singleton
  private:
    ErrorManager(){}
    std::vector<std::string> Lexicalerror ;
    std::vector<std::string> Syntaxerror ;

  public:
  static ErrorManager& getInstance(){
        static ErrorManager instance ;
        return instance;
  }
  void addLexicalError(string message) {
    Lexicalerror.push_back(message) ;
  }
  void addSyntaxError(string message) {
    Syntaxerror.push_back(message);
  }
  
  void ErrorHandling(ErrorType errorno, string message ) { 
    if ( errorno == Unrecognized_token )
      std::cout << "Unrecognized token with first char : '" << message[0] << "'" << std::endl ;
    else if ( errorno == Unexpected_token ) {
      std::cout << "Unexpected token : '" << message << "'" << std::endl ;
    } // else if 
    else if ( errorno == Undefined_identifier ) {
      std::cout << "Undefined identifier : '" << message << "'" << std::endl ;
    } // else if
    else if ( errorno == ILLEGAL_GETCHAR) {
      cout << "ILLEGAL_GETCHAR : '" << message << "'" << endl ;;
    }
    cout << "> " ;
  } // ErrorHandling()
};