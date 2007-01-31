// Copyright (C) 2000-2006, Luca Padovani <padovani@sti.uniurb.it>.
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
// <padovani@sti.uniurb.it>

#ifndef __PS_InkArea_hh__
#define __PS_InkArea_hh__

#include "InkArea.hh"

class PS_InkArea : public InkArea
{
protected:
  PS_InkArea(const AreaRef& area) : InkArea(area) { }
  virtual ~PS_InkArea() { }

public:
  static SmartPtr<PS_InkArea> create(const AreaRef& area)
  { return new PS_InkArea(area); }
  virtual AreaRef clone(const AreaRef& area) const { return create(area); }

  virtual void render(RenderingContext&, const scaled&, const scaled&) const;
};

#endif // __PS_InkArea_hh__