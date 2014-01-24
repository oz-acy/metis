/**************************************************************************
*
*  metis_celm.cpp
*  by oZ/acy
*  (c) 2005 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 17 Feb 2005
*
*  Metis クラス定義 
*  子要素抽出用メソッド
**************************************************************************/

#include "data.h"

namespace {

class ElmListUpVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Element*> elms_;

public:
  ElmListUpVisitor_() {}

  void visit(metis::Element& e) { elms_.push_back(&e); }
  std::list<metis::Element*>& get() { return elms_; }
};


class ElmListUpByNameVisitor_ : public metis::DatumVisitor
{
private:
  std::list<metis::Element*> elms_;
  std::string name_;

public:
  ElmListUpByNameVisitor_(const std::string& n) : name_(n) {}

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
*  子エレメントをリストアップ
*=========================================================*/
std::list<metis::Element*> metis::Element::getChildElements() const
{
  ElmListUpVisitor_ ev;
  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    (*it)->accept(ev);

  return ev.get();
}


std::list<metis::Element*>
metis::Element::getChildByName(const std::string& name) const
{
  ElmListUpByNameVisitor_ ev(name);
  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    (*it)->accept(ev);

  return ev.get();
}




//eof
