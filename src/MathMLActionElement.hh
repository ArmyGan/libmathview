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

#ifndef MathMLActionElement_hh
#define MathMLActionElement_hh

#if defined(HAVE_GMETADOM)
#include "gmetadom.hh"
#endif

#include "MathMLEmbellishment.hh"
#include "MathMLLinearContainerElement.hh"

class MathMLActionElement
  : public MathMLLinearContainerElement, public MathMLEmbellishment
{
protected:
  MathMLActionElement(void);
#if defined(HAVE_GMETADOM)
  MathMLActionElement(const DOM::Element&);
#endif
  virtual ~MathMLActionElement();

public:
  static SmartPtr<MathMLElement> create(void)
  { return SmartPtr<MathMLElement>(new MathMLActionElement()); }
#if defined(HAVE_GMETADOM)
  static SmartPtr<MathMLElement> create(const DOM::Element& el)
  { return SmartPtr<MathMLElement>(new MathMLActionElement(el)); }
#endif

  virtual void refine(class AbstractRefinementContext&);
  virtual void Setup(class RenderingEnvironment&);
  virtual void DoLayout(const class FormattingContext&);
  virtual void SetPosition(const scaled&, const scaled&);
  virtual void Render(const DrawingArea&);

  virtual scaled GetLeftEdge(void) const;
  virtual scaled GetRightEdge(void) const;

  virtual SmartPtr<MathMLElement> Inside(const scaled&, const scaled&);
  SmartPtr<MathMLElement> GetSelectedElement(void) const;

  unsigned GetSelectedIndex(void) const;
  void     SetSelectedIndex(unsigned);

  virtual SmartPtr<MathMLOperatorElement> GetCoreOperator(void);

private:
  unsigned selection;
};

#endif // MathMLActionElement_hh
