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
 * @file elm_text.cpp
 * @author oZ/acy
 *
 * @brief Elementからのテキスト抽出處理
 */

#include "data.h"

namespace {

class StrListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::StringData*> strs_;

public:
  void visit(metis::StringData& s) { strs_.push_back(&s); }
  std::list<metis::StringData*>& get() { return strs_; }
};


class StrChooseVisitor_ : public metis::DatumVisitor
{
private:
  metis::StringData* str_;

public:
  StrChooseVisitor_() : str_(nullptr) {}

  void visit(metis::StringData& s) { str_ = &s; }
  metis::StringData* get() { return str_; }
};


}// end of NONAME namespace


/*
 *  文字列データをピックアップする
 */
std::list<metis::StringData*> metis::Element::getTexts() const
{
  StrListUpVisitor_ sv;
  for (auto& upd : data_)
    upd->accept(sv);
  return sv.get();
}


/*
 *  最初の文字列データを取得する
 */
metis::StringData* metis::Element::text() const
{
  StrChooseVisitor_ sv;

  for (auto& upd : data_) {
    upd->accept(sv);
    if (sv.get())
      return sv.get();
  }

  return nullptr;
}




//eof
