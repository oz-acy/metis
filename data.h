/**************************************************************************
 *
 *  data.h
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 7 Nov MMXI
 *
 *  Metisデータクラス
 *************************************************************************/

#ifndef INC_METIS_DATA_H___
#define INC_METIS_DATA_H___

#include <string>
#include <list>
#include <cstddef>
#include <boost/utility.hpp>


namespace metis {

class StringData;
class NormalString;
class CharReference;
class Element;
class Attribute;


/*------------------------------------------------
*  class DatumVisitor
*  Metis の扱ふデータの Visitor の基底
*-----------------------------------------------*/
class DatumVisitor
{
protected:
  DatumVisitor() = default;  // インスタンス化防止

public:
  virtual ~DatumVisitor() {}

  virtual void visit(StringData&) {}
  virtual void visit(NormalString&) {}
  virtual void visit(CharReference&) {}
  virtual void visit(Element&) {}
  virtual void visit(Attribute&) {}
};




/*------------------------------------------------
*  class Datum
*  データの抽象基底
*-----------------------------------------------*/
class Datum : boost::noncopyable
{
  friend class Element;

private:
  Element* parent_;

protected:
  virtual Datum* clone_(Element* p) const =0;

public:
  Datum(Element* p) : parent_(p) {}
  virtual ~Datum() {}

  virtual void accept(DatumVisitor&) =0;
  virtual Datum* clone() const =0;

  Element* parent() const { return parent_; }
};




/*--------------------------------------
*  class StringPiece
*  文字列データ斷片
*
*  v0.2.0で追加
*-------------------------------------*/
class StringPiece
{
protected:
  StringPiece() = default; // インスタンス化防止

public:
  ~StringPiece() {}
  virtual void accept(DatumVisitor&) =0;
  virtual StringPiece* clone() const =0;
};


/*--------------------------------------
*  class NormalString
*  ベタ文字列データ
*
*  v0.2.0で追加
*-------------------------------------*/
class NormalString : public StringPiece
{
private:
  std::string str_;

public:
  NormalString(const std::string& s) : str_(s) {}

  void accept(DatumVisitor& v) { v.visit(*this); }
  NormalString* clone() const { return new NormalString(str_); }
  std::string& refer() { return str_; }
  const std::string& refer() const { return str_; }
};


/*--------------------------------------
*  class CharReference
*  文字参照
*
*  v0.2.0で追加
*  update: 2008.3.13
*-------------------------------------*/
class CharReference : public StringPiece
{
private:
  std::string code_;

private:
  // 内部で使用
  CharReference() = default;

public:
  CharReference(const std::string& c);

  void accept(DatumVisitor& v) { v.visit(*this); }
  CharReference* clone() const;
  const std::string& code() const { return code_; }
  unsigned int codeval() const;
};


/*--------------------------------------
*  class StringData
*  文字列データ
*
*  v0.2.0で改變
*  update: 2011.10.05
*-------------------------------------*/
class StringData : public Datum
{
public:
  typedef std::list<StringPiece*>::iterator iterator;
  typedef std::list<StringPiece*>::const_iterator const_iterator;

private:
  std::list<StringPiece*> strs_;

protected:
  StringData* clone_(Element* e) const;

public:
  StringData(Element* e =nullptr) : Datum(e) {}
  ~StringData();

  void accept(DatumVisitor& v) { v.visit(*this); }
  StringData* clone() const { return clone_(parent()); }

  iterator begin() { return strs_.begin(); }
  const_iterator begin() const { return strs_.begin(); }
  iterator end() { return strs_.end(); }
  const_iterator end() const { return strs_.end(); }

  void push_back(StringPiece* p) { strs_.push_back(p); }
  void clear() { strs_.clear(); }

  std::string getUtf8Code() const;
  std::string getText() const;

  bool operator<(const StringData& x) const
    { return getUtf8Code() < x.getUtf8Code(); }
  bool operator==(const StringData& x) const
    { return getUtf8Code() == x.getUtf8Code(); }
};




/*----------------------------------------------------------
*  class HasName
*  名前附きデータの抽象基底
*
*  clone(), accept() が未實裝故抽象クラスのまま
*---------------------------------------------------------*/
class HasName : public Datum
{
private:
  std::string name_;

public:
  HasName(const std::string& s, Element* p) : Datum(p), name_(s) {}
  const std::string& name() const { return name_; }
};



/*--------------------------------------
*  class Attribute
*  屬性
*
*  v0.2.0で改變
*-------------------------------------*/
class Attribute : public HasName
{
private:
  StringData* str_;

protected:
  Attribute* clone_(Element* e) const
    { return new Attribute(name(), str_->clone(), e); }

public:
  Attribute(const std::string& nm, StringData* s, Element* e)
    : HasName(nm, e), str_(s)
    {}

  ~Attribute();

  Attribute* clone() const { return clone_(parent()); }
  void accept(DatumVisitor& v) { v.visit(*this); }

  StringData* content() { return str_; }
  const StringData* content() const { return str_; }
};




/*--------------------------------------
*  class Element
*  要素
*-------------------------------------*/
class Element : public HasName
{
public:
  typedef std::list<Datum*>::iterator iterator;
  typedef std::list<Datum*>::const_iterator const_iterator;

private:
  std::list<Datum*> data_;

protected:
  Element* clone_(Element* p) const;

public:
  Element(const std::string& s, Element* p =nullptr) : HasName(s, p) {}
  ~Element();

  Element* clone() const { return clone_(parent()); }
  void accept(DatumVisitor& v) { v.visit(*this); }

  std::list<Datum*>& children() { return data_; }
  const std::list<Datum*>& children() const { return data_; }
  std::list<Datum*>::size_type countChildren() const { return data_.size(); }
  std::list<Datum*>::size_type countAttribute() const;

  bool empty() const { return countChildren() == countAttribute(); }

  std::list<Element*> getChildElements() const;
  std::list<Element*> getChildByName(const std::string&) const;
  std::list<Attribute*> getAttributes() const;
  Attribute* getAttrByName(const std::string&) const;
  std::list<StringData*> getTexts() const;
  StringData* text() const;
};


}//end of namespace metis


#endif // INC_METIS_DATA_H__
