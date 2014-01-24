/**************************************************************************
*
*  strvisitor.h
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 15 Feb MMVIII
*
**************************************************************************/

#ifndef INC_METIS_STRING_VISITOR_H___
#define INC_METIS_STRING_VISITOR_H___


#include <sstream>
#include "data.h"


namespace metis {


/*------------------------------------------------
*  StringVisitor
*
*  create: 2008.2.15
*-----------------------------------------------*/
class StringVisitor : public metis::DatumVisitor
{
private:
  std::ostringstream* oss_;

protected:
  std::ostringstream& oss() { return *oss_; }

public:
  StringVisitor() { oss_ = new std::ostringstream(); }
  ~StringVisitor() { delete oss_; }

  void visit(metis::StringData& s);
  void visit(metis::NormalString& ns) { oss() << ns.refer(); }
  void visit(metis::CharReference& cr) { oss() << "&#x" << cr.code() << ";"; }
  std::string str();
};


}// end of namespace metis




#endif // INC_METIS_STRING_VISITOR_H___
