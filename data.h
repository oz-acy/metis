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
/*
 * @file data.h
 * @author oZ/acy
 *
 * @date 2021.5.3 v0.3に向けて大改修開始
 */

#ifndef INCLUDE_GUARD_METIS_DATA_H
#define INCLUDE_GUARD_METIS_DATA_H

#include <algorithm>
#include <string>
#include <list>
#include <memory>
#include <cstddef>
//#include <boost/utility.hpp>
#include <eunomia/noncopyable.h>


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




/*
 * @brief データの抽象基底
 */
class Datum : eunomia::Noncopyable<Datum>
{
  friend class Element;

protected:
  virtual std::unique_ptr<Datum> clone_() const =0;

public:
  virtual ~Datum() = default;
  std::unique_ptr<Datum> clone() const { return clone_(); }
  virtual void accept(DatumVisitor&) =0;
};




/**
 * @brief 文字列データ斷片
 * @date 2016.3.1 修正 デストラクタにvirtualを付ける
 */
class StringPiece : eunomia::Noncopyable<StringPiece>
{
private:
  virtual std::unique_ptr<StringPiece> clone_() const =0;

public:
  virtual ~StringPiece() = default;
  std::unique_ptr<StringPiece> clone() const { return clone_(); }
  virtual void accept(DatumVisitor&) =0;
};


/**
 * @brief ベタ文字列データ
 */
class NormalString : public StringPiece
{
private:
  std::string str_;

  std::unique_ptr<StringPiece> clone_() const override
  {
    return std::make_unique<NormalString>(str_);
  }

public:
  explicit NormalString(const std::string& s) : str_(s) {}

  std::unique_ptr<NormalString> clone() const
  {
    return
      std::unique_ptr<NormalString>(
        static_cast<NormalString*>(clone_().release()));
  }

  void accept(DatumVisitor& v) override { v.visit(*this); }
  std::string& refer() { return str_; }
  const std::string& refer() const { return str_; }
};


/*
 * @brief 文字参照
 *
 */
class CharReference : public StringPiece
{
private:
  std::string code_;

  // 内部的に利用する
  CharReference() = default;

  std::unique_ptr<StringPiece> clone_() const override;

public:
  explicit CharReference(const std::string& c);

  std::unique_ptr<CharReference> clone() const
  {
    return
      std::unique_ptr<CharReference>(
        static_cast<CharReference*>(clone_().release()));
  }

  void accept(DatumVisitor& v) { v.visit(*this); }
  const std::string& code() const { return code_; }
  unsigned int codeval() const;
};


/*
 * @brief 文字列データ
 *
 */
class StringData : public Datum
{
public:
  using iterator = std::list<std::unique_ptr<StringPiece>>::iterator;
  using const_iterator
    = std::list<std::unique_ptr<StringPiece>>::const_iterator;

private:
  std::list<std::unique_ptr<StringPiece>> strs_;
  //std::list<StringPiece*> strs_;

protected:
  std::unique_ptr<Datum> clone_() const override;

  //std::unique_ptr<Datum> clone_(Element* e) const override;

  //StringData* clone_(Element* e) const;

public:
  //StringData(Element* e =nullptr) : Datum(e) {}

  std::unique_ptr<StringData> clone() const
  {
    return
      std::unique_ptr<StringData>(
        static_cast<StringData*>(clone_().release()));
  }

  void accept(DatumVisitor& v) { v.visit(*this); }

  template<class UnaryFunction>
  void forEach(UnaryFunction f)
    { std::for_each(strs_.begin(), strs_.end(), f); }

  iterator begin() { return strs_.begin(); }
  const_iterator begin() const { return strs_.begin(); }
  iterator end() { return strs_.end(); }
  const_iterator end() const { return strs_.end(); }

  void clear() { strs_.clear(); }
  void push_back(std::unique_ptr<StringPiece>&& p)
    { strs_.push_back(std::move(p)); }

  std::string getUtf8Code() const;
  std::string getText() const;

  bool operator<(const StringData& x) const
    { return getUtf8Code() < x.getUtf8Code(); }
  bool operator==(const StringData& x) const
    { return getUtf8Code() == x.getUtf8Code(); }
};




/*
 * @brief 名前を持つデータの抽象基底
 *
 * clone_(), accept() は實裝せず、派生クラスの實裝に任せる。
 */
class HasName : public Datum
{
private:
  std::string name_;

public:
  explicit HasName(const std::string& n) : name_(n) {}
  //HasName(const std::string& s, Element* p) : Datum(p), name_(s) {}
  const std::string& name() const noexcept { return name_; }

  std::unique_ptr<HasName> clone() const
  {
    return
      std::unique_ptr<HasName>(
        static_cast<HasName*>(clone_().release()));
  }
};




/*
 * @brief 屬性
 *
 */
class Attribute : public HasName
{
private:
  std::unique_ptr<StringData> str_;

  //StringData* str_;

protected:
  std::unique_ptr<Datum> clone_() const override
    { return  std::unique_ptr<Datum>(new Attribute(name(), str_->clone())); }

  //std::unique_ptr<Datum> clone_(Element* e) const override
  //  { return new Attribute(name(), str_->clone(), e); }

  //Attribute* clone_(Element* e) const
  //  { return new Attribute(name(), str_->clone(), e); }

public:
  Attribute(const std::string& na, std::unique_ptr<StringData>&& s)
    //const std::string& na, std::unique_ptr<StringData>&& s, Element* e)
    : HasName(na/*, e*/), str_(std::move(s))
    {}

  std::unique_ptr<Attribute> clone() const
  {
    return
      std::unique_ptr<Attribute>(
        static_cast<Attribute*>(clone_().release()));
  }

  void accept(DatumVisitor& v) { v.visit(*this); }

  StringData* content() noexcept { return str_.get(); }
  const StringData* content() const noexcept { return str_.get(); }
};




/*
 * @brief 要素
 *
 */
class Element : public HasName
{
public:
  using iterator = std::list<std::unique_ptr<Datum>>::iterator;
  using const_iterator = std::list<std::unique_ptr<Datum>>::const_iterator;

  //typedef std::list<Datum*>::iterator iterator;
  //typedef std::list<Datum*>::const_iterator const_iterator;

private:
  std::list<std::unique_ptr<Datum>> data_;
  //std::list<Datum*> data_;

protected:
  std::unique_ptr<Datum> clone_() const override;
  //std::unique_ptr<Datum> clone_(Element* p) const override;

  //Element* clone_(Element* p) const;

public:
  explicit Element(const std::string& n) : HasName(n) {}
  //Element(const std::string& s, Element* p =nullptr) : HasName(s, p) {}

  std::unique_ptr<Element> clone() const
  {
    return
      std::unique_ptr<Element>(
        static_cast<Element*>(clone_(/*parent()*/).release()));
  }

  void accept(DatumVisitor& v) { v.visit(*this); }

  std::list<std::unique_ptr<Datum>>& children() { return data_; }
  const std::list<std::unique_ptr<Datum>>& children() const { return data_; }

  std::list<std::unique_ptr<Datum>>::size_type countChildren() const
    { return data_.size(); }
  std::list<std::unique_ptr<Datum>>::size_type countAttribute() const;

  //std::list<Datum*>& children() { return data_; }
  //const std::list<Datum*>& children() const { return data_; }
  //std::list<Datum*>::size_type countChildren() const { return data_.size(); }
  //std::list<Datum*>::size_type countAttribute() const;

  bool empty() const { return countChildren() == countAttribute(); }

  std::list<Element*> getChildElements() const;
  std::list<Element*> getChildElements(const std::string&) const;

  // 屬性をピックアップする
  std::list<Attribute*> getAttributes() const;

  // 指定した名前の屬性を取得する
  Attribute* getAttrByName(const std::string&) const;

  // 文字列データをピックアップする
  std::list<StringData*> getTexts() const;

  // 最初の文字列データを取得する
  StringData* text() const;
};


}//end of namespace metis


#endif // INCLUDE_GUARD_METIS_DATA_H
