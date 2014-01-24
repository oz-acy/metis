/**************************************************************************
*
*  stringdata.cpp
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update : 5 Oct MMXI
*
*  metis::StringData‚Ì’è‹`
**************************************************************************/

#include "data.h"


/*===========================================
 *  StringData::~StringData()
 *
 */
metis::StringData::~StringData()
{
  iterator it;
  for (it = strs_.begin(); it != strs_.end(); ++it)
    delete *it;
}


/*===========================================
*  StringData::clone_()
*
*==========================================*/
metis::StringData* metis::StringData::clone_(metis::Element* e) const
{
  StringData* neu = new StringData(e);

  const_iterator it;
  for (it = strs_.begin(); it != strs_.end(); ++it)
    neu->push_back((*it)->clone());

  return neu;
}





//eof
