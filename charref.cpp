/**************************************************************************
*
*  charref.cpp
*  by oZ/acy
*  (c) 2008-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 5 Oct MMXI
*
*  Metisクラス定義
*  文字參照關係
*
**************************************************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "data.h"


namespace{

void initCvtTable_S(std::map<std::string, std::string>& ct)
{
  // ギリシャ文字
  ct["alpha"] = "03B1";  // small letter alpha
  ct["beta"] = "03B2";
  ct["gamma"] = "03B3";
  ct["delta"] = "03B4";
  ct["epsilon"] = "03B5";
  ct["zeta"] = "03B6";
  ct["eta"] = "03B7";
  ct["theta"] = "03B8";
  ct["iota"] = "03B9";
  ct["kappa"] = "03BA";
  ct["lambda"] = "03BB";
  ct["mu"] = "03BC";
  ct["nu"] = "03BD";
  ct["xi"] = "03BE";
  ct["omicron"] = "03BF";
  ct["pi"] = "03C0";
  ct["rho"] = "03C1";
  ct["sigmaf"] = "03C2";  // final sigma
  ct["sigma"] = "03C3";
  ct["tau"] = "03C4";
  ct["upsilon"] = "03C5";
  ct["phi"] = "03C6";
  ct["chi"] = "03C7";
  ct["psi"] = "03C8";
  ct["omega"] = "03C9";
  ct["betav"] = "03D0";   // beta symbol
  ct["thetav"] = "03D1";  // theta symbol
  ct["phiv"] = "03D5";    // phi symbol
  ct["piv"] = "03D6";     // pi symbol
  ct["kaiv"] = "03D7";    // kai symbol
  ct["kappav"] = "03F0";  // kappa symbol
  ct["rhov"] = "03F1";    // rho symbol
  ct["alpha-t"] = "03AC";    // alpha with tonos
  ct["epsilon-t"] = "03AD";
  ct["eta-t"] = "03AE";
  ct["iota-t"] = "03AF";     // iota with tonos
  ct["omicron-t"] = "03CC";
  ct["upsilon-t"] = "03CD";
  ct["omega-t"] = "03CE";    // omega with tonos
  ct["Alpha-t"] = "0386";    // Capital Alpha with tonos
  ct["Epsilon-t"] = "0388";
  ct["Eta-t"] = "0389";
  ct["Iota-t"] = "038A";
  ct["Omicron-t"] = "038C";
  ct["Upsilon-t"] = "038E";
  ct["Omega-t"] = "038F";    // Capital Omega with tonos
  ct["Alpha"] = "0391";  // Capital Alpha
  ct["Beta"] = "0392";
  ct["Gamma"] = "0393";
  ct["Delta"] = "0394";
  ct["Epsilon"] = "0395";
  ct["Zeta"] = "0396";
  ct["Eta"] = "0397";
  ct["Theta"] = "0398";
  ct["Iota"] = "0399";
  ct["Kappa"] = "039A";
  ct["Lambda"] = "039B";
  ct["Mu"] = "039C";
  ct["Nu"] = "039D";
  ct["Xi"] = "039E";
  ct["Omicron"] = "039F";
  ct["Pi"] = "03A0";
  ct["Rho"] = "03A1";
  ct["Sigma"] = "03A3";
  ct["Tau"] = "03A4";
  ct["Upsilon"] = "03A5";
  ct["Phi"] = "03A6";
  ct["Chi"] = "03A7";
  ct["Psi"] = "03A8";
  ct["Omega"] = "03A9";   // Capital Omega
  ct["Thetav"] = "03F4";  // Capital Theta symbol
  ct["Koppa-a"] = "03D8";  // Capital Archaic Koppa
  ct["koppa-a"] = "03D9";  // small letter archaic koppa
  ct["Stigma"] = "03DA";   // Capital Stigma
  ct["stigma"] = "03DB";   // small letter stigma
  ct["Digamma"] = "03DC";  // Capital Digamma
  ct["digamma"] = "03DD";  // small letter digamma
  ct["Koppa"] = "03DE";    // Capital Koppa
  ct["koppa"] = "03DF";    // small letter koppa
  ct["Sun"] = "03FA";      // Capital Sun
  ct["sun"] = "03FB";      // small letter sun
  ct["rho-st"] = "03FC";   // rho with stroke symbol
  ct["Sampi"] = "03E0";    // Capital Sampi
  ct["sampi"] = "03E1";    // small letter sampi
  ct["Yot"] = "03F3";      // Yot


  // 修飾附ラテン文字
  ct["Ag"] = "00C0";
  ct["ag"] = "00E0";
  ct["Aa"] = "00C1";
  ct["aa"] = "00E1";
  ct["Aci"] = "00C2";
  ct["aci"] = "00E2";
  ct["Ati"] = "00C3";
  ct["ati"] = "00E3";
  ct["Au"] = "00C4";
  ct["au"] = "00E4";
  ct["Ar"] = "00C5";
  ct["ar"] = "00E5";
  ct["Ao"] = "0100";
  ct["ao"] = "0101";
  ct["AE"] = "00C6";
  ct["ae"] = "00E6";
  ct["Abr"] = "0102";
  ct["abr"] = "0103";
  ct["A-car"] = "01CD";
  ct["a-car"] = "01CE";

  ct["Cce"] = "00C7";
  ct["cce"] = "00E7";
  ct["Ca"] = "0106";
  ct["ca"] = "0107";
  ct["DH"] = "00D0";
  ct["dh"] = "00F0";
  ct["Eg"] = "00C8";
  ct["eg"] = "00E8";
  ct["Ea"] = "00C9";
  ct["ea"] = "00E9";
  ct["Eci"] = "00CA";
  ct["eci"] = "00EA";
  ct["Eu"] = "00CB";
  ct["eu"] = "00EB";
  ct["Eo"] = "0112";
  ct["eo"] = "0113";

  ct["Ig"] = "00CC";
  ct["ig"] = "00EC";
  ct["Ia"] = "00CD";
  ct["ia"] = "00ED";
  ct["Ici"] = "00CE";
  ct["ici"] = "00EE";
  ct["Iu"] = "00CF";
  ct["iu"] = "00EF";
  ct["io"] = "012B";
  ct["i-dl"] = "0131";
  ct["IJ"] = "0132";
  ct["ij"] = "0133";

  ct["Nti"] = "00D1";
  ct["nti"] = "00F1";
  ct["Og"] = "00D2";
  ct["og"] = "00F2";
  ct["Oa"] = "00D3";
  ct["oa"] = "00F3";
  ct["Oci"] = "00D4";
  ct["oci"] = "00F4";
  ct["Oti"] = "00D5";
  ct["oti"] = "00F5";
  ct["Ou"] = "00D6";
  ct["ou"] = "00F6";
  ct["Osl"] = "00D8";
  ct["osl"] = "00F8";
  ct["OE"] = "0152";
  ct["oe"] = "0153";
  ct["ss"] = "00DF";
  ct["Sci"] = "015C";
  ct["sci"] = "015D";
  ct["Sce"] = "015E";
  ct["sce"] = "015F";
  ct["S-car"] = "0160";
  ct["s-car"] = "0161";
  ct["TH"] = "00DE";
  ct["th"] = "00FE";
  ct["Ug"] = "00D9";
  ct["ug"] = "00F9";
  ct["Ua"] = "00DA";
  ct["ua"] = "00FA";
  ct["Uci"] = "00DB";
  ct["uci"] = "00FB";
  ct["Uu"] = "00DC";
  ct["uu"] = "00FC";
  ct["Uo"] = "016A";
  ct["uo"] = "016B";

  ct["wci"] = "0175";

  ct["Ya"] = "00DD";
  ct["ya"] = "00FD";
  ct["Yu"] = "0178";
  ct["yu"] = "00FF";


  // 記號
  ct["copy"] = "00A9";
  ct["LArr"] = "21D0";
  ct["RArr"] = "21D2";
  ct["heart"] = "2661";
  ct["sect"] = "00A7";
  ct["inv-exc"] = "00A1";
  ct["yen"] = "00A5";
  ct["not"] = "00AC";
  ct["reg"] = "00AE";
  ct["degree"] = "00B0";

  ct["pilcrow"] = "00B6";
  ct["inv-ques"] = "00BF";
  ct["postal"] = "3012";



}


}// end of namespace




/*================================================
*  CharReference::CharReference()
*  3タイプの表現から、十六進表現に統一
*  頭の #, #x や尻尾の ; も削除
*  
*  update: 2008.2.24
*===============================================*/
metis::CharReference::CharReference(const std::string& c)
{
  int l = c.length();

  if (c.substr(0, 2) == "#x")
  { // 十六進の場合
    code_ = c.substr(2, l - 3);
  }
  else if (c[0] == '#')
  { // 十進数の場合
    unsigned int t = boost::lexical_cast<unsigned int>(c.substr(1, l - 2));
    std::ostringstream oss;
    oss << std::hex << t;
    code_ = oss.str();
  }
  else
  { // 別名表現の場合
    static std::map<std::string, std::string> cvttable;
    code_ = "FFFFFFFF";

    if (cvttable.empty())
      initCvtTable_S(cvttable);

    std::map<std::string, std::string>::iterator it;
    it = cvttable.find(c.substr(0, l - 1));
    if (it != cvttable.end())
      code_ = it->second;
  }
}


/*================================================
*  CharReference::clone()
*  同内容のインスタンスを生成
*  
*  update: 2008.3.13
*===============================================*/
metis::CharReference* metis::CharReference::clone() const
{
  CharReference* r = new CharReference();
  r->code_ = code_;
  return r;
}


/*================================================
 *  CharReference::codeval()
 *  文字コードを整數値で返却
 *  create: 2008.2.15
 *  move to charref.cpp: 2011.10.5
 */
unsigned int metis::CharReference::codeval() const
{
  unsigned t = 0;
  std::string::const_iterator it;
  for (it = code_.begin(); it != code_.end(); ++it)
  {
    t <<= 4;

    if (*it >= '0' && *it <= '9')
      t += *it - '0';
    else if (*it >= 'a' && *it <= 'f')
      t += *it - 'a' + 10;
    else if (*it >= 'A' && *it <= 'F')
      t += *it - 'A' + 10;
  }
  return t;
}




//eof
