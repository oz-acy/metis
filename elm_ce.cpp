/*
 * Copyright 2005-2021 oZ/acy (���ꌎ�W�k)
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
 * @file elm_ce.cpp
 * @author oZ/acy
 *
 * @brief Element����̎q�v�f���o�|��
 *
 */

#include "data.h"

namespace {

class ElmListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Element*> elms_;

public:
  void visit(metis::Element& e) { elms_.push_back(&e); }
  std::list<metis::Element*>& get() { return elms_; }
};


class ElmListUpByNameVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Element*> elms_;
  std::string name_;

public:
  explicit ElmListUpByNameVisitor_(const std::string& n) : name_(n) {}

  void visit(metis::Element& e)
  {
    if (e.name() == name_)
      elms_.push_back(&e);
  }

  std::list<metis::Element*>& get() { return elms_; }
};


}// end of namespace


/*==========================================================
*  Element::getChildElements()
*  �q�G�������g�����X�g�A�b�v
*=========================================================*/
std::list<metis::Element*> metis::Element::getChildElements() const
{
  ElmListUpVisitor_ ev;
  for (auto& upd : data_)
    upd->accept(ev);
  return ev.get();
}


std::list<metis::Element*>
metis::Element::getChildElements(const std::string& name) const
{
  ElmListUpByNameVisitor_ ev(name);
  for (auto& upd: data_)
    upd->accept(ev);
  return ev.get();
}




//eof
