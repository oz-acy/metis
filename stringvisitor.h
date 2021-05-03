/*
 * Copyright 2008-2021 oZ/acy (名賀月晃嗣)
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
 *
 * @file stringvisitor.h
 * @author oZ/acy
 *
 */
#ifndef INCLUDE_GUARD_METIS_STRING_VISITOR_H
#define INCLUDE_GUARD_METIS_STRING_VISITOR_H


#include <sstream>
#include "data.h"


namespace metis {


/*
 * @date 2008.2.15 create
 */
class StringVisitor : public metis::DatumVisitor
{
private:
  std::ostringstream oss_;

protected:
  std::ostringstream& oss() { return oss_; }

public:
  void visit(metis::StringData& s)
    { s.forEach([&](auto& ups){ ups->accept(*this); }); }
  void visit(metis::NormalString& ns) { oss_ << ns.refer(); }
  void visit(metis::CharReference& cr) { oss_ << "&#x" << cr.code() << ";"; }

  std::string str()
  {
    auto s = oss_.str();
    oss_.str(std::string());
    oss_.clear();
    return s;
  }
};


}// end of namespace metis




#endif // INCLUDE_GUARD_METIS_STRING_VISITOR_H
