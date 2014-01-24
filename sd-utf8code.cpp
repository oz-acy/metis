/**************************************************************************
 *
 *  sd-utf8code.cpp
 *  by oZ/acy
 *  (c) 2005-2012 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update : 8 Mar MMXII
 *
 *  metis::StringData‚Ì’è‹`‚Ìˆê•”
 *************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include "data.h"
#include "strvisitor.h"


namespace {

/*------------------------------------------------
 *  Visitor4Str2Cmp_
 *  create 2008.02.17
 *  modify 2011.10.05
 */
class Visitor4Str2Cmp_ : public metis::StringVisitor
{
public:
  Visitor4Str2Cmp_() {}
  void visit(metis::CharReference& cr);
};


/*================================================
 *  Visitor4Str2Cmp_::visit(metis::CharReference&)
 *  create:  2009.11.11
 *  rewrite: 2011.10.05
 *  modify:  2012.03.08
 */
void Visitor4Str2Cmp_::visit(metis::CharReference& cr)
{
  using namespace std;

  unsigned int uc = cr.codeval();

  if (uc < 0x80)
    oss() << (char)uc;
  else if (uc < 0x0800)
  {
    oss() << (char)(0xC0 | (uc >> 6))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x010000)
  {
    oss() << (char)(0xE0 | (uc >> 12))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x0200000)
  {
    oss() << (char)(0xF0 | (uc >> 18))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x04000000)
  {
    oss() << (char)(0xF8 | (uc >> 24))
          << (char)(0x80 | ((uc >> 18) & 0x3F))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else// if (uc < 0x80000000)
  {
    oss() << (char)(0xFC | (uc >> 30))
          << (char)(0x80 | ((uc >> 24) & 0x3F))
          << (char)(0x80 | ((uc >> 18) & 0x3F))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
}


}// end of namespace


/*===========================================
 *  StringData::getUtf8Code()
 *  create: 2008.02.14
 *  modify: 2011.10.05
 */
std::string metis::StringData::getUtf8Code() const
{
  using namespace std;

  ostringstream oss;

  string ts = getText();

  string::iterator it;
  for (it = ts.begin(); it != ts.end(); ++it)
  {
    oss << uppercase << hex << setw(2) << setfill('0') << (*it & 0x00FF);
  }

  return oss.str();
}


/*===========================================
 *  StringData::getText()
 *  create: 2011.10.05
 */
std::string metis::StringData::getText() const
{
  using namespace std;

  Visitor4Str2Cmp_ vsc;
  list<StringPiece*>::const_iterator it;

  for (it = strs_.begin(); it != strs_.end(); ++it)
  {
    (*it)->accept(vsc);
  }

  return vsc.str();
}



//eof
