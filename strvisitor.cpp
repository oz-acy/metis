/**************************************************************************
*
*  strvisitor.cpp
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 15 Feb MMVIII
*
**************************************************************************/

#include "strvisitor.h"


/*================================================
*  StringVisitor::visit()
*
*  create: 2008.2.15
*===============================================*/
void metis::StringVisitor::visit(metis::StringData& s)
{
  metis::StringData::iterator it;
  for (it = s.begin(); it != s.end(); ++it)
    (*it)->accept(*this);
}


/*================================================
*  StringVisitor::str()
*
*  create: 2008.2.15
*===============================================*/
std::string metis::StringVisitor::str()
{
  std::string s = oss_->str();
  delete oss_;
  oss_ = new std::ostringstream();
  return s;
}




//eof
