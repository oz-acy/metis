/**************************************************************************
*
*  parser.h
*  by oZ/acy
*  (c) 2005 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 12 Feb 2005
*
*  Metis パーサクラス
**************************************************************************/

#ifndef INC_METIS_PARSER_H___
#define INC_METIS_PARSER_H___

#include "data.h"

namespace metis {


/*--------------------------------------------------
*  Parser
*  構文解析
*-------------------------------------------------*/
class Parser
{
private:
  Parser();

public:
  static Element* parse(const std::string& path);
};


}// end of namespace metis



#endif // INC_METIS_PARSER_H__
