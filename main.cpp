/*
 *  @file main.cpp
 *  @author oZ/acy
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "data.h"
#include "parser.h"
#include "lexer.h"
//#include "metis2xml.h"


// テストのためのダンプ出力を行ふVisitor
class DumpVisitor : public metis::DatumVisitor
{
public:

  void visit(metis::StringData& sdat)
    {
      std::cout << "DUMP String Data {" << sdat.getText() << "}" << std::endl;
    }

  void visit(metis::Element& selm)
    {
      std::cout << "START Element " << selm.name() << std::endl;

      metis::Element::iterator it;
      for (it = selm.children().begin(); it != selm.children().end(); ++it)
        (*it)->accept(*this);
      std::cout << "END Element " << selm.name() << std::endl;
    }

  void visit(metis::Attribute& attr)
    {
      std::cout << "Attribute " << attr.name();
      std::cout << " = {";
      attr.content()->accept(*this);
      std::cout << "}" << std::endl;
    }
};



int main(int argc, char** argv)
{
  using namespace std;

  if (argc != 2)
  {
    cerr << "usage: metistest infile" << endl;
    return 1;
  }

  string inpath = argv[1];
  std::ifstream ifs(inpath);
  if (ifs) {
    metis::Lexer lexer;
    lexer.switch_streams(&ifs, &std::cout);

    std::unique_ptr<metis::Element> root;
    metis::Parser parser(lexer, root);

    if (parser.parse() == 0) {
      std::cout << "成功!" << std::endl;
      DumpVisitor dv;
      root->accept(dv);
    }
    else {
      std::cout << "失敗orz" << std::endl;
    }
  }

  return 0;
}


//eof
