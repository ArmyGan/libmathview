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

#ifndef MathMLNode_hh
#define MathMLNode_hh

#include <config.h>

#include "MathMLObject.hh"

class MathMLNode: public MathMLObject {
public:
  MathMLNode(void);
  virtual bool IsNode(void) const;
  virtual ~MathMLNode();

  void SetParent(class MathMLElement* p) { parent = p; }
  class MathMLElement* GetParent(void) const { return parent; }

private:
  class MathMLElement* parent;
};

typedef MathMLNode* MathMLNodePtr;

#define TO_NODE(object) (dynamic_cast<MathMLNode*>(object))

#endif // MathMLNode_hh
