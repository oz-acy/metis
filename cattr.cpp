/**************************************************************************
*
*  cattr.cpp
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 7 Nov 2011
*
*  Metis クラス定義
*  屬性抽出用メソッド
**************************************************************************/

#include "data.h"

namespace {

class AttrListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Attribute*> attrs_;

public:
  AttrListUpVisitor_() = default;

  void visit(metis::Attribute& a) { attrs_.push_back(&a); }
  std::list<metis::Attribute*>& get() { return attrs_; }
};


class AttrChooseByNameVisitor_ : public metis::DatumVisitor
{
private:
  metis::Attribute* attr_;
  std::string name_;

public:
  AttrChooseByNameVisitor_(const std::string& n) : attr_(nullptr), name_(n) {}

  void visit(metis::Attribute& a)
    {
      if (a.name() == name_)
        attr_ = &a;
    }

  metis::Attribute* get() { return attr_; }
};



}// end of namespace


/*==========================================================
 *  Element::getAttributes()
 *  屬性をリストアップ
 *========================================================*/
std::list<metis::Attribute*> metis::Element::getAttributes() const
{
  AttrListUpVisitor_ av;
  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    (*it)->accept(av);

  return av.get();
}


/*==========================================================
*  Element::getAttByName()
*  指定名の屬性を取得
*=========================================================*/
metis::Attribute* metis::Element::getAttrByName(const std::string& name) const
{
  AttrChooseByNameVisitor_ av(name);
  const_iterator it;
  for (it = data_.begin(); it != data_.end() && !av.get(); ++it)
    (*it)->accept(av);

  return av.get();
}




//eof
