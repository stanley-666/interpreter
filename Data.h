#pragma once
#include <vector>
#include<iostream>
#include "Token.h"

class Data {
  private :
  std::vector < std::vector < Token > > mtokenlist ;
  std::vector<ID> midlist ;

  public :
  void PushIDENT( ID newID ) {
    int size = midlist.size() ;
    // if ID already declare
    for ( int i = 0 ; i < size ; i++ ) {
      if ( midlist[i].val == newID.val ) {
        midlist[i].num = newID.num ;
        return;
      } // if
    } // for

    midlist.push_back( newID ) ;
    return;
  } // PushIDENT()

  void Pushlist( vector < Token > buffer ) {
    mtokenlist.push_back( buffer ) ;
  } // Pushlist()

  void Clear() {
    mtokenlist.clear() ;
  } // Clear()

  void Print() {
    for ( int i = 0 ; i < mtokenlist.size() ; i++ ) {
      cout << '[' << i+1 << ']' ;
      for ( int j = 0 ; j < mtokenlist[i].size() ; j++ ) {
        cout << mtokenlist[i][j].val  ;
      } // for

      cout << endl;
    } // for
  } // Print()

  vector <Token> Getnewest() {
    int newest = mtokenlist.size() - 1 ;
    vector <Token> tmp ;
    for ( int i = 0 ; i < mtokenlist[ newest ].size() ; i++ )
      tmp.push_back( mtokenlist[ newest ][i] ) ;
      
    return tmp ;
  } // Getnewest()

  Token GetIDENTVALUE( Token &token ) {
    int size = midlist.size() ;
    Token tmp;
    tmp.val = "\0";
    tmp.type = UNKNOWN ;
    for ( int i = 0 ; i < size ; i++ ) {
      if ( midlist[i].val == token.val ) {
        tmp.type = NUM ;
        tmp.val = to_string( midlist[i].num );
        return tmp;
      } // if

    } // for

    return tmp;
  } // GetIDENTVALUE()

  bool Find( Token &token ) {
    int size = midlist.size() ;
    for ( int i = 0 ; i < size ; i++ ) {
      if ( midlist[i].val == token.val )
        return true;
    } // for
      
    return false;
  } // Find()
};