// Copyright (C) 2000-2007, Luca Padovani <padovani@sti.uniurb.it>.
// 
// This file is part of GtkMathView, a flexible, high-quality rendering
// engine for MathML documents.
// 
// GtkMathView is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// GtkMathView is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __NamespaceRegistry_hh__
#define __NamespaceRegistry_hh__

#include "Object.hh"
#include "HashMap.hh"
#include "String.hh"
#include "SmartPtr.hh"

class NamespaceRegistry : public Object
{
protected:
  NamespaceRegistry(void);
  virtual ~NamespaceRegistry();

public:
  static SmartPtr<NamespaceRegistry> create(void) { return new NamespaceRegistry(); }

  SmartPtr<class NamespaceContext> get(const String&) const;
  bool add(const SmartPtr<class NamespaceContext>&);
  bool remove(const String&);

private:
  typedef HASH_MAP_NS::hash_map<String,SmartPtr<class NamespaceContext>,StringHash,StringEq> ElementFactoryMap;
  ElementFactoryMap map;
};

#endif // __NamespaceRegistry_hh__
