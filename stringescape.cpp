/*
 * Copyright 2005-2021 oZ/acy (名賀月晃嗣)
 * Redistribution and use in source and binary forms, 
 *     with or without modification, 
 *   are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * @file strescape.cpp
 * @author oZ/acy
 */
#include <sstream>
#include "stringescape.h"


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

}//end of NONAME namespace




/*====================================================
*  operator<<()
*  Metis 文字列エスケープクラス用出力演算子
*---------------------------------------------------*/
std::ostream& metis::operator<<(std::ostream& os, const metis::StringEscape& se)
{
  for (auto c : se.str_)
    os << sctable_SG.get(c);

  return os;


  //const std::string& tgt = se.str_;
  //std::string::const_iterator pc;

  //for (pc = tgt.begin(); pc != tgt.end(); ++pc)
  //  os << sctable_SG.get(*pc);

  //return os;
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
