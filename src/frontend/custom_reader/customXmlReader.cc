// Copyright (C) 2000-2007, Luca Padovani <padovani@sti.uniurb.it>.
//
// This file is part of GtkMathView, a flexible, high-quality rendering
// engine for MathML documents.
// 
// GtkMathView is free software; you can redistribute it and/or modify it
// either under the terms of the GNU Lesser General Public License version
// 3 as published by the Free Software Foundation (the "LGPL") or, at your
// option, under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation (the "GPL").  If you do not
// alter this notice, a recipient may use your version of this file under
// either the GPL or the LGPL.
//
// GtkMathView is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL or
// the GPL for more details.
// 
// You should have received a copy of the LGPL and of the GPL along with
// this program in the files COPYING-LGPL-3 and COPYING-GPL-2; if not, see
// <http://www.gnu.org/licenses/>.

#include <config.h>

#include <cassert>

#include "customXmlReader.hh"

customXmlReader::customXmlReader(const c_customXmlReader* r, c_customModelUserData data)
  : reader(r), user_data(data)
{
  assert(reader);
}

customXmlReader::~customXmlReader()
{
  (*reader->free_data)(user_data);
  reader = 0;
  user_data = 0;
}

std::string
customXmlReader::fromReaderString(char* str) const
{
  if (str)
    {
      std::string res(str);
      (*reader->free_string)(str);
      return res;
    }
  else
    return std::string();
}

void
customXmlReader::getAttribute(int index, std::string& namespaceURI, std::string& name, std::string& value) const
{
  char* c_namespaceURI;
  char* c_name;
  char* c_value;
  (*reader->get_attribute_by_index)(user_data, index, &c_namespaceURI, &c_name, &c_value);
  namespaceURI = fromReaderString(c_namespaceURI);
  name = fromReaderString(c_name);
  value = fromReaderString(c_value);
}
