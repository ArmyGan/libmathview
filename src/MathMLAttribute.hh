// Copyright (C) 2000, Luca Padovani <luca.padovani@cs.unibo.it>.
// 
// This file is part of GtkMathView, a Gtk widget for MathML.
// 
// GtkMathView is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// GtkMathView is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GtkMathView; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// For details, see the GtkMathView World-Wide-Web page,
// http://cs.unibo.it/~lpadovan/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#ifndef MathMLAttribute_hh
#define MathMLAttribute_hh

#include "SmartPtr.hh"
#include "Object.hh"
#include "Value.hh"
#include "keyword.hh"
#include "String.hh"
#include "MathMLAttributeSignature.hh"

class MathMLAttribute : public Object
{
protected:
  MathMLAttribute(const class MathMLAttributeSignature&, const String&);
  virtual ~MathMLAttribute();

public:
  static SmartPtr<MathMLAttribute> create(const class MathMLAttributeSignature& sig, const String& value)
  { return new MathMLAttribute(sig, value); }

  const class MathMLAttributeSignature& getSignature(void) const { return signature; }
  String getUnparsedValue(void) const { return unparsedValue; }
  SmartPtr<Value> getValue(void) const;
  bool equal(const SmartPtr<MathMLAttribute>&) const;

private:
  const class MathMLAttributeSignature& signature;
  String unparsedValue;
  mutable SmartPtr<Value> value;
};

#endif // MathMLAttribute_hh
