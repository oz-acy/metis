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
 * @file elm_attr.cpp
 * @author oZ/acy
 *
 * @brief ElementからのAttribute抽出處理
 */

#include "data.h"

namespace {

class AttrListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Attribute*> attrs_;

public:
  void visit(metis::Attribute& a) { attrs_.push_back(&a); }
  std::list<metis::Attribute*>& get() { return attrs_; }
};


class AttrChooseByNameVisitor_ : public metis::DatumVisitor
{
private:
  metis::Attribute* attr_;
  std::string name_;

public:
  explicit AttrChooseByNameVisitor_(const std::string& n)
    : attr_(nullptr), name_(n)
    {}

  void visit(metis::Attribute& a)
  {
    if (a.name() == name_)
      attr_ = &a;
  }

  metis::Attribute* get() { return attr_; }
};


}// end of NONAME namespace


/*
 * 屬性をピックアップする。
 */
std::list<metis::Attribute*> metis::Element::getAttributes() const
{
  AttrListUpVisitor_ av;
  for (auto& upd : data_)
    upd->accept(av);

  //const_iterator it;
  //for (it = data_.begin(); it != data_.end(); ++it)
  //  (*it)->accept(av);

  return av.get();
}


/*
 * 指定した名前の屬性を取得する。
 */
metis::Attribute* metis::Element::getAttrByName(const std::string& name) const
{
  AttrChooseByNameVisitor_ av(name);

  for (auto& upd : data_) {
    upd->accept(av);
    if (av.get())
      return av.get();
  }

  return nullptr;

  //const_iterator it;
  //for (it = data_.begin(); it != data_.end() && !av.get(); ++it)
  //  (*it)->accept(av);

  //return av.get();
}




//eof
