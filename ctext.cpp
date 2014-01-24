/**************************************************************************
*
*  ctext.cpp
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 7 Nov 2011
*
*  Metis クラス定義
*  テキスト抽出用メソッド
**************************************************************************/

#include "data.h"

namespace {

class StrListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::StringData*> strs_;

public:
  StrListUpVisitor_() = default;

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



}// end of namespace


/*==========================================================
*  Element::getTexts()
*  文字列データをリストアップ
*=========================================================*/
std::list<metis::StringData*> metis::Element::getTexts() const
{
  StrListUpVisitor_ sv;
  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    (*it)->accept(sv);

  return sv.get();
}


/*==========================================================
*  Element::text()
*  最初の文字列データを取得
*=========================================================*/
metis::StringData* metis::Element::text() const
{
  StrChooseVisitor_ sv;
  const_iterator it;
  for (it = data_.begin(); it != data_.end() && !sv.get(); ++it)
    (*it)->accept(sv);

  return sv.get();
}




//eof
