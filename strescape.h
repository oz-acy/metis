/**************************************************************************
*
*  strescape.h
*  by oZ/acy
*  (c) 2005 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 15 Feb 2005
*
*  Metis 文字列エスケープクラス
**************************************************************************/

#ifndef INC_METIS_STRING_ESCAPE_H___
#define INC_METIS_STRING_ESCAPE_H___

#include <string>
#include <ostream>

namespace metis
{

class StringEscape;
std::ostream& operator<<(std::ostream&, const StringEscape&);

/*-----------------------------------------------------
*  class StringEscape
*  文字列の Metis 記述向けエスケープ用クラス
*----------------------------------------------------*/
class StringEscape
{
  friend std::ostream& operator<<(std::ostream&, const StringEscape&);

private:
  const std::string& str_;

public:
  explicit StringEscape(const std::string& s) : str_(s) {}
  operator std::string() const;
};


}// end of namespace metis


#endif // INC_METIS_STRING_ESCAPE_H___
