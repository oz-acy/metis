/*
 * Copyright 2005-2021 oZ/acy (ñºâÍåéçWék)
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
/*
 * @file stringdata.cpp
 * @author by oZ/acy
 *
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include "data.h"
#include "stringvisitor.h"


std::unique_ptr<metis::Datum>
metis::StringData::clone_() const
{
  StringData* neu = new StringData();
  for (const auto& upp : strs_)
    neu->push_back(upp->clone());

  return std::unique_ptr<Datum>(neu);
}




namespace
{
/*
 * @date 2008.2.17 create 
 * @date 2011.10.5 modify 
 * @date 2021.5.3 modify 
 */
class Visitor4Str2Cmp_ : public metis::StringVisitor
{
public:
  void visit(metis::CharReference& cr);
};


/*
 *  @date 2009.11.11 create  
 *  @date 2011.10.5 rewrite 
 *  @date 2012.3.8 modify
 */
void Visitor4Str2Cmp_::visit(metis::CharReference& cr)
{
  using namespace std;

  unsigned int uc = cr.codeval();

  if (uc < 0x80)
    oss() << (char)uc;
  else if (uc < 0x0800) {
    oss() << (char)(0xC0 | (uc >> 6))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x010000) {
    oss() << (char)(0xE0 | (uc >> 12))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x0200000) {
    oss() << (char)(0xF0 | (uc >> 18))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else if (uc < 0x04000000) {
    oss() << (char)(0xF8 | (uc >> 24))
          << (char)(0x80 | ((uc >> 18) & 0x3F))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
  else { // if (uc < 0x80000000)
    oss() << (char)(0xFC | (uc >> 30))
          << (char)(0x80 | ((uc >> 24) & 0x3F))
          << (char)(0x80 | ((uc >> 18) & 0x3F))
          << (char)(0x80 | ((uc >> 12) & 0x3F))
          << (char)(0x80 | ((uc >> 6) & 0x3F))
          << (char)(0x80 | (uc & 0x3F));
  }
}


}// end of namespace


/*
 * @date 2008.2.14 create 
 * @date 2011.10.05 modify 
 */
std::string metis::StringData::getUtf8Code() const
{
  using namespace std;

  ostringstream oss;

  string ts = getText();

  for (auto c : ts) {
    oss << uppercase << hex << setw(2) << setfill('0') << (c & 0x00ff);
  }

  //string::iterator it;
  //for (it = ts.begin(); it != ts.end(); ++it)
  //{
  //  oss << uppercase << hex << setw(2) << setfill('0') << (*it & 0x00FF);
  //}

  return oss.str();
}


/*
 * @date 2011.10.5 create
 */
std::string metis::StringData::getText() const
{
  using namespace std;

  Visitor4Str2Cmp_ vsc;
  //list<StringPiece*>::const_iterator it;

  for (auto& ups : strs_)
    ups->accept(vsc);

  //for (it = strs_.begin(); it != strs_.end(); ++it)
  //{
  //  (*it)->accept(vsc);
  //}

  return vsc.str();
}




//eof
