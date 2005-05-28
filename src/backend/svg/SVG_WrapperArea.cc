// Copyright (C) 2000-2005, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://helm.cs.unibo.it/mml-widget/, or send a mail to
// <lpadovan@cs.unibo.it>

#include <config.h>

#include "SVG_WrapperArea.hh"
#include "SVG_RenderingContext.hh"
#include "Element.hh"

SVG_WrapperArea::SVG_WrapperArea(const AreaRef& area, const BoundingBox& b, const SmartPtr<Element>& el)
  : WrapperArea(area, b, el)
{ }

SVG_WrapperArea::~SVG_WrapperArea()
{ }

SmartPtr<SVG_WrapperArea>
SVG_WrapperArea::create(const AreaRef& area, const BoundingBox& b, const SmartPtr<Element>& el)
{ return new SVG_WrapperArea(area, b, el); }

AreaRef
SVG_WrapperArea::clone(const AreaRef& area) const
{ return create(area, box(), getElement()); }

void
SVG_WrapperArea::render(RenderingContext& c, const scaled& x, const scaled& y) const
{
  SVG_RenderingContext& context = dynamic_cast<SVG_RenderingContext&>(c);
  context.wrapperStart(x, y, box(), getElement());
  WrapperArea::render(context, x, y);
  context.wrapperEnd();
}
