// Copyright (C) 2000-2003, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://helm.cs.unibo.it/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#ifndef __BoxMLTextElement_hh__
#define __BoxMLTextElement_hh__

#include "BoxMLElement.hh"

class BoxMLTextElement : public BoxMLElement
{
protected:
  BoxMLTextElement(const SmartPtr<class BoxMLNamespaceContext>&);
  virtual ~BoxMLTextElement();

public:
  static SmartPtr<BoxMLTextElement> create(const SmartPtr<class BoxMLNamespaceContext>&);

#if 0
  virtual void construct(void);
  virtual void refine(class AbstractRefinementContext&);
#endif
  virtual AreaRef format(class BoxFormattingContext&);

  void setContent(const String&);
  String getContent(void) const { return content; }

private:
  String content;
};

#endif // __BoxMLTextElement_hh__
