/**************************************************************************
*
*  strescape.h
*  by oZ/acy
*  (c) 2005 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 15 Feb 2005
*
*  Metis ������G�X�P�[�v�N���X
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
*  ������� Metis �L�q�����G�X�P�[�v�p�N���X
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
