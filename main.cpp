/**************************************************************************
*  main.cpp
*  by oZ/acy
**************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "data.h"
#include "parser.h"
//#include "metis2xml.h"


class DumpVisitor : public metis::DatumVisitor
{
public:

  void visit(metis::StringData& sdat)
    {
      std::cout << "DUMP String Data {" << sdat.refer() << "}" << std::endl;
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
      std::cout << " = {" << attr.content() << "}" << std::endl;
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

  metis::Element* root = metis::Parser::parse(inpath);

  metis::WriteVisitor2Xml wv2x(cout);
  root->accept(wv2x);
  delete root;

  return 0;
}


//eof
