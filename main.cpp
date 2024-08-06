
# include <sstream> // to string
# include <stdlib.h>
# include <math.h>
#include "parser.h"


class Interpreter {
  private :
    Parser mp = Parser();
  public:
  void ReadExp() {
    mp.Parse()  ;
  } // ReadExp()
};

int main() {
  Interpreter interpreter ;
  interpreter.ReadExp();
} // main()
