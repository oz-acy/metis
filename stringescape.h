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
 * @file stringescape.h
 * @author oZ/acy
 *
 * @brief 文字列エスケープクラス
 *
 */

#ifndef INCLUDE_GUARD_METIS_STRING_ESCAPE_H
#define INCLUDE_GUARD_METIS_STRING_ESCAPE_H

#include <string>
#include <ostream>

namespace metis
{

class StringEscape;
std::ostream& operator<<(std::ostream&, const StringEscape&);

/*-----------------------------------------------------
*  class StringEscape
*  文字列の Metis 記述向けエスケープ用クラス
*----------------------------------------------------*/
class StringEscape
{
  friend std::ostream& operator<<(std::ostream&, const StringEscape&);

private:
  const std::string& str_;

public:
  explicit StringEscape(const std::string& s) : str_(s) {}
  operator std::string() const;
};


}// end of namespace metis


#endif // INCLUDE_GUARD_METIS_STRING_ESCAPE_H
