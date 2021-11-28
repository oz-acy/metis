/*
 * Copyright 2008-2021 oZ/acy (名賀月晃嗣)
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
 * @file charref.cpp
 * @author oZ/acy
 *
 * @brief 文字參照周りの處理
 */
#include <iostream>
#include <unordered_map>
#include <sstream>
#include "data.h"


namespace{

std::unordered_map<std::string, std::string> entityRefTable_
  = 
{
  // ギリシャ文字
  {"alpha", "03B1"}, // small letter alpha
  {"beta", "03B2"},
  {"gamma", "03B3"},
  {"delta", "03B4"},
  {"epsilon", "03B5"},
  {"zeta", "03B6"},
  {"eta", "03B7"},
  {"theta", "03B8"},
  {"iota", "03B9"},
  {"kappa", "03BA"},
  {"lambda", "03BB"},
  {"mu", "03BC"},
  {"nu", "03BD"},
  {"xi", "03BE"},
  {"omicron", "03BF"},
  {"pi", "03C0"}, 
  {"rho", "03C1"}, 
  {"sigmaf", "03C2"},   // final sigma
  {"sigma", "03C3"}, 
  {"tau", "03C4"}, 
  {"upsilon", "03C5"}, 
  {"phi", "03C6"}, 
  {"chi", "03C7"}, 
  {"psi", "03C8"}, 
  {"omega", "03C9"}, 
  {"betav", "03D0"},    // beta symbol
  {"thetav", "03D1"},   // theta symbol
  {"phiv", "03D5"},     // phi symbol
  {"piv", "03D6"},      // pi symbol
  {"kaiv", "03D7"},     // kai symbol
  {"kappav", "03F0"},   // kappa symbol
  {"rhov", "03F1"},     // rho symbol
  {"alpha-t", "03AC"},     // alpha with tonos
  {"epsilon-t", "03AD"}, 
  {"eta-t", "03AE"}, 
  {"iota-t", "03AF"},      // iota with tonos
  {"omicron-t", "03CC"}, 
  {"upsilon-t", "03CD"}, 
  {"omega-t", "03CE"},     // omega with tonos
  {"Alpha-t", "0386"},     // Capital Alpha with tonos
  {"Epsilon-t", "0388"}, 
  {"Eta-t", "0389"}, 
  {"Iota-t", "038A"}, 
  {"Omicron-t", "038C"}, 
  {"Upsilon-t", "038E"}, 
  {"Omega-t", "038F"},     // Capital Omega with tonos
  {"Alpha", "0391"},   // Capital Alpha
  {"Beta", "0392"}, 
  {"Gamma", "0393"}, 
  {"Delta", "0394"}, 
  {"Epsilon", "0395"}, 
  {"Zeta", "0396"}, 
  {"Eta", "0397"}, 
  {"Theta", "0398"}, 
  {"Iota", "0399"}, 
  {"Kappa", "039A"}, 
  {"Lambda", "039B"}, 
  {"Mu", "039C"}, 
  {"Nu", "039D"}, 
  {"Xi", "039E"}, 
  {"Omicron", "039F"}, 
  {"Pi", "03A0"}, 
  {"Rho", "03A1"}, 
  {"Sigma", "03A3"}, 
  {"Tau", "03A4"}, 
  {"Upsilon", "03A5"}, 
  {"Phi", "03A6"}, 
  {"Chi", "03A7"}, 
  {"Psi", "03A8"}, 
  {"Omega", "03A9"},    // Capital Omega
  {"Thetav", "03F4"},   // Capital Theta symbol
  {"Koppa-a", "03D8"},   // Capital Archaic Koppa
  {"koppa-a", "03D9"},   // small letter archaic koppa
  {"Stigma", "03DA"},    // Capital Stigma
  {"stigma", "03DB"},    // small letter stigma
  {"Digamma", "03DC"},   // Capital Digamma
  {"digamma", "03DD"},   // small letter digamma
  {"Koppa", "03DE"},     // Capital Koppa
  {"koppa", "03DF"},     // small letter koppa
  {"Sun", "03FA"},       // Capital Sun
  {"sun", "03FB"},       // small letter sun
  {"rho-st", "03FC"},    // rho with stroke symbol
  {"Sampi", "03E0"},     // Capital Sampi
  {"sampi", "03E1"},     // small letter sampi
  {"Yot", "03F3"},       // Yot

  // 修飾附ラテン文字
  {"Ag", "00C0"}, 
  {"ag", "00E0"}, 
  {"Aa", "00C1"}, 
  {"aa", "00E1"}, 
  {"Aci", "00C2"}, 
  {"aci", "00E2"}, 
  {"Ati", "00C3"}, 
  {"ati", "00E3"}, 
  {"Au", "00C4"}, 
  {"au", "00E4"}, 
  {"Ar", "00C5"}, 
  {"ar", "00E5"}, 
  {"Ao", "0100"}, 
  {"ao", "0101"}, 
  {"AE", "00C6"}, 
  {"ae", "00E6"}, 
  {"Abr", "0102"}, 
  {"abr", "0103"}, 
  {"A-car", "01CD"}, 
  {"a-car", "01CE"}, 

  {"Cce", "00C7"}, 
  {"cce", "00E7"}, 
  {"Ca", "0106"}, 
  {"ca", "0107"}, 
  {"DH", "00D0"}, 
  {"dh", "00F0"}, 
  {"Eg", "00C8"}, 
  {"eg", "00E8"}, 
  {"Ea", "00C9"}, 
  {"ea", "00E9"}, 
  {"Eci", "00CA"}, 
  {"eci", "00EA"}, 
  {"Eu", "00CB"}, 
  {"eu", "00EB"}, 
  {"Eo", "0112"}, 
  {"eo", "0113"}, 

  {"Ig", "00CC"}, 
  {"ig", "00EC"}, 
  {"Ia", "00CD"}, 
  {"ia", "00ED"}, 
  {"Ici", "00CE"}, 
  {"ici", "00EE"}, 
  {"Iu", "00CF"}, 
  {"iu", "00EF"}, 
  {"io", "012B"}, 
  {"i-dl", "0131"}, 
  {"IJ", "0132"}, 
  {"ij", "0133"}, 

  {"Nti", "00D1"}, 
  {"nti", "00F1"}, 
  {"Og", "00D2"}, 
  {"og", "00F2"}, 
  {"Oa", "00D3"}, 
  {"oa", "00F3"}, 
  {"Oci", "00D4"}, 
  {"oci", "00F4"}, 
  {"Oti", "00D5"}, 
  {"oti", "00F5"}, 
  {"Ou", "00D6"}, 
  {"ou", "00F6"}, 
  {"Osl", "00D8"}, 
  {"osl", "00F8"}, 
  {"OE", "0152"}, 
  {"oe", "0153"}, 
  {"ss", "00DF"}, 
  {"Sci", "015C"}, 
  {"sci", "015D"}, 
  {"Sce", "015E"}, 
  {"sce", "015F"}, 
  {"S-car", "0160"}, 
  {"s-car", "0161"}, 
  {"TH", "00DE"}, 
  {"th", "00FE"}, 
  {"Ug", "00D9"}, 
  {"ug", "00F9"}, 
  {"Ua", "00DA"}, 
  {"ua", "00FA"}, 
  {"Uci", "00DB"}, 
  {"uci", "00FB"}, 
  {"Uu", "00DC"}, 
  {"uu", "00FC"}, 
  {"Uo", "016A"}, 
  {"uo", "016B"}, 

  {"wci", "0175"}, 

  {"Ya", "00DD"}, 
  {"ya", "00FD"}, 
  {"Yu", "0178"}, 
  {"yu", "00FF"}, 

  // 記號
  {"copy", "00A9"}, 
  {"LArr", "21D0"}, 
  {"RArr", "21D2"}, 
  {"heart", "2661"}, 
  {"sect", "00A7"}, 
  {"inv-exc", "00A1"}, 
  {"yen", "00A5"}, 
  {"not", "00AC"}, 
  {"reg", "00AE"}, 
  {"degree", "00B0"}, 

  {"pilcrow", "00B6"}, 
  {"inv-ques", "00BF"}, 
  {"postal", "3012"}, 
};


}// end of NONAME namespace




/*
 *  表記における三種類の表現から、内部で用ゐる十六進表現に變換する。
 *  頭の #, #x や尻尾の ; は削除する。
 *  
 */
metis::CharReference::CharReference(const std::string& c)
{
  std::size_t l = c.length();

  if (c.substr(0, 2) == "#x") { // 十六進表現の場合
    code_ = c.substr(2, l - 3);
  }
  else if (c[0] == '#') { // 十進表現の場合
    std::size_t z;
    auto s = c.substr(1, l - 2); // 頭の#と尾の;を省く
    auto i = std::stoi(c.substr(1, l - 2), &z, 10);
    if (z == l - 2) { // l - 2 は #dddd; で期待される數字列の長さ
      std::ostringstream oss;
      oss << std::hex << i;
      code_ = oss.str();
    }
    else {
      code_ = "FFFFFFFF";
    }
  }
  else { // 別名表現の場合
    code_ = "FFFFFFFF";
    auto s = c.substr(0, l - 1);
    if (entityRefTable_.contains(s))
      code_ = entityRefTable_[s];
  }
}


std::unique_ptr<metis::StringPiece> metis::CharReference::clone_() const
{
  CharReference* r = new CharReference();
  r->code_ = code_;
  return std::unique_ptr<StringPiece>(r);
}


/*
 * @brief 文字コードを整數値で返却する。
 * @date 2008.2.15 create 
 * @date 2021.5.3 修正
 */
unsigned int metis::CharReference::codeval() const
{
  unsigned t = 0;
  
  for (auto c : code_) {
    t *= 16;

    if (c >= '0' && c <= '9')
      t += c - '0';
    else if (c >= 'a' && c <= 'f')
      t += c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      t += c - 'A' + 10;
    else {
      t /= 16;
      break;
    }
  }

  return t;
}




//eof
