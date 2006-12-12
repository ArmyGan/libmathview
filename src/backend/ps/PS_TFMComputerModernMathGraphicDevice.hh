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

#ifndef __PS_TFMComputerModernMathGraphicDevice_hh__
#define __PS_TFMComputerModernMathGraphicDevice_hh__

#include "TFMComputerModernMathGraphicDevice.hh"

class PS_TFMComputerModernMathGraphicDevice : public TFMComputerModernMathGraphicDevice
{
protected:
  PS_TFMComputerModernMathGraphicDevice(const SmartPtr<class AbstractLogger>&,
					 const SmartPtr<class Configuration>&);
  virtual ~PS_TFMComputerModernMathGraphicDevice();

public:
  static SmartPtr<PS_TFMComputerModernMathGraphicDevice> create(const SmartPtr<class AbstractLogger>&,
								 const SmartPtr<class Configuration>&);

  virtual AreaRef script(const class FormattingContext&,
			 const AreaRef& base,
			 const AreaRef& subScript, const Length& subScriptShift,
			 const AreaRef& superScript, const Length& superScriptShift) const;
  virtual AreaRef multiScripts(const class FormattingContext&,
			       const AreaRef& base,
			       const std::vector<AreaRef>& subScripts,
			       const std::vector<AreaRef>& preSubScripts,
			       const Length& subScriptShift,
			       const std::vector<AreaRef>& superScripts,
			       const std::vector<AreaRef>& preSuperScripts,
			       const Length& superScriptShift) const;
 };

#endif // __PS_TFMComputerModernMathGraphicDevice_hh__
