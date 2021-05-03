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
/**
 *
 * @file element.cpp
 * @author oZ/acy
 *
 * @brief ElementÇÃõâÂ‰ÇÃàÍïî
 */

#include "data.h"


std::unique_ptr<metis::Datum> metis::Element::clone_() const
{
  Element* res = new Element(name());

  for (auto& upd : data_)
    res->data_.push_back(upd->clone());

  //const_iterator it;
  //for (it = data_.begin(); it != data_.end(); ++it)
  //  res->data_.push_back((*it)->clone_(res));

  return std::unique_ptr<Datum>(res);
}


namespace {
// AttributeÇù…Ç÷ÇÈÇΩÇﬂÇÃVisitor
class AttrCounter_ : public metis::DatumVisitor
{
private:
  unsigned count_;

public:
  AttrCounter_() : count_(0) {}
  void visit(metis::Attribute&) { ++count_; }
  unsigned count() const { return count_; }
};

}//end of namespace


/*=================================================
*  Element::countAttribute()
*  AttributeÇù…Ç÷ÇÈ
*================================================*/
std::list<metis::Datum*>::size_type metis::Element::countAttribute() const
{
  AttrCounter_ ac;

  for (auto& upd : data_)
    upd->accept(ac);
  //const_iterator it;
  //for (it = data_.begin(); it != data_.end(); ++it)
  //  (*it)->accept(ac);
  return ac.count();
}



//eof
