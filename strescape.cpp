/**************************************************************************
*
*  strescape.cpp
*  by oZ/acy
*  (c) 2005 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 15 Feb 2005
*
*  Metis 文字列エスケープクラス
**************************************************************************/

#include <sstream>
#include "strescape.h"


namespace {

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*  StringConvertTable_ sctable_SG
*  文字列變換用テーブル
*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class StringConvertTable_
{
private:
  std::string table_[256];

public:
  StringConvertTable_();
  const std::string& get(unsigned char c) const { return table_[c]; }
};


StringConvertTable_::StringConvertTable_()
{
  for (int c = 0; c < 256; c++)
    table_[c] = static_cast<char>(c);

  // 例外文字列
  table_['@'] = "&at;";
  table_['#'] = "&sharp;";
  table_['{'] = "&lb;";
  table_['}'] = "&rb;";
  table_['&'] = "&amp;";
}

StringConvertTable_ sctable_SG;

}//end of namespace




/*====================================================
*  operator<<()
*  Metis 文字列エスケープクラス用出力演算子
*---------------------------------------------------*/
std::ostream& metis::operator<<(std::ostream& os, const metis::StringEscape& se)
{
  const std::string& tgt = se.str_;
  std::string::const_iterator pc;

  for (pc = tgt.begin(); pc != tgt.end(); ++pc)
    os << sctable_SG.get(*pc);

  return os;
}


/*====================================================
*  StringEscape::operator std::string() const
*===================================================*/
metis::StringEscape::operator std::string() const
{
  std::ostringstream oss;
  oss << *this;
  return oss.str();
}


//eof
