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

#include <config.h>

#include "BoxMLAttributeSignatures.hh"
#include "BoxMLHElement.hh"
#include "BoxMLVElement.hh"
#include "FormattingContext.hh"
#include "BoxGraphicDevice.hh"
#include "ValueConversion.hh"
#include "AreaFactory.hh"

BoxMLHElement::BoxMLHElement(const SmartPtr<BoxMLNamespaceContext>& context)
  : BoxMLLinearContainerElement(context)
{ }

BoxMLHElement::~BoxMLHElement()
{ }

SmartPtr<BoxMLHElement>
BoxMLHElement::create(const SmartPtr<BoxMLNamespaceContext>& context)
{ return new BoxMLHElement(context); }

AreaRef
BoxMLHElement::format(FormattingContext& ctxt)
{
  if (dirtyLayout())
    {
      ctxt.push(this);

      TokenId align = ToTokenId(GET_ATTRIBUTE_VALUE(BoxML, H, align));

      step = 0;
      std::vector<AreaRef> c;
      c.reserve(content.getSize());
      for (std::vector< SmartPtr<BoxMLElement> >::const_iterator p = content.begin();
	   p != content.end();
	   p++)
	if (*p)
	  {
	    AreaRef area = (*p)->format(ctxt);
	    assert(area);
	    switch (align)
	      {
	      case T_TOP: area = ctxt.BGD()->getFactory()->top(area); break;
	      case T_BOTTOM: area = ctxt.BGD()->getFactory()->bottom(area); break;
	      case T_CENTER: area = ctxt.BGD()->getFactory()->middle(area); break;
	      case T_BASELINE:
		{
		  //std::cout << "making step of " << step.getValue() << std::endl;
		  if (step != scaled::zero())
		    area = ctxt.BGD()->getFactory()->shift(area, step);
		  step += (*p)->getStep();
		}
		break;
	      default:
		assert(false);
		break;
	      }

	    c.push_back(area);
	  }

      AreaRef res;
      if (c.size() == 1)
	res = c[0];
      else
	res = ctxt.BGD()->getFactory()->horizontalArray(c);

      res = ctxt.BGD()->wrapper(ctxt, res);
      setArea(res);

      ctxt.pop();
      resetDirtyLayout();
    }

  return getArea();
}
