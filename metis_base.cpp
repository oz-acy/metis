/**************************************************************************
*
*  metis_base.cpp
*  by oZ/acy
*  (c) 2005-2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 14 Feb MMVIII
*
*  Metis�N���X��`
**************************************************************************/

#include "data.h"




/*===========================================
*  Attribute::~Attribute()
*
*  v0.2.0�Œǉ�
*==========================================*/
metis::Attribute::~Attribute()
{
  delete str_;
}




/*===========================================
*  Element::~Element()
*
*==========================================*/
metis::Element::~Element()
{
  iterator it;
  for (it = data_.begin(); it != data_.end(); it++)
    delete *it;
}


/*===========================================
*  Element::clone_()
*  protected
*
*==========================================*/
metis::Element* metis::Element::clone_(Element* p) const
{
  Element* res = new Element(name(), p);

  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    res->data_.push_back((*it)->clone_(res));

  return res;
}


namespace {
// Attribute��ɂւ邽�߂�Visitor
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
*  Attribute��ɂւ�
*================================================*/
std::list<metis::Datum*>::size_type metis::Element::countAttribute() const
{
  AttrCounter_ ac;
  const_iterator it;
  for (it = data_.begin(); it != data_.end(); ++it)
    (*it)->accept(ac);
  return ac.count();
}



//eof
