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

#ifndef MathMLUnderOverElement_hh
#define MathMLUnderOverElement_hh

#include <config.h>

class MathMLUnderOverElement : public MathMLContainerElement {
public:
  MathMLUnderOverElement(mDOMNodeRef, TagId);
  virtual const AttributeSignature* GetAttributeSignature(AttributeId) const;
  virtual void Normalize(void);
  virtual void Setup(RenderingEnvironment*);
  virtual void DoBoxedLayout(LayoutId, BreakId, scaled);
  virtual void SetPosition(scaled, scaled);
  virtual ~MathMLUnderOverElement();

  virtual bool IsExpanding(void) const;

protected:
  bool   scriptize; // true if under and over are to be considered in script position

  bool   accentUnder;
  bool   accent;

  union {
    scaled underSpacing; // if scriptize == false
    scaled underShift;   // if scriptize == true
  };

  union {
    scaled overSpacing; // if scriptize == false
    scaled overShift;   // if scriptize == true
  };

  scaled scriptSpacing; // script spacing from base (if scriptize == true)

  MathMLElement* base;
  MathMLElement* underScript;
  MathMLElement* overScript;
};

#endif // MathMLUnderOverElement_hh
