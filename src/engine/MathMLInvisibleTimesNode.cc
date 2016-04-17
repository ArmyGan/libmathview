// Copyright (C) 2000-2007, Luca Padovani <padovani@sti.uniurb.it>.
//
// This file is part of GtkMathView, a flexible, high-quality rendering
// engine for MathML documents.
// 
// GtkMathView is free software; you can redistribute it and/or modify it
// either under the terms of the GNU Lesser General Public License version
// 3 as published by the Free Software Foundation (the "LGPL") or, at your
// option, under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation (the "GPL").  If you do not
// alter this notice, a recipient may use your version of this file under
// either the GPL or the LGPL.
//
// GtkMathView is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL or
// the GPL for more details.
// 
// You should have received a copy of the LGPL and of the GPL along with
// this program in the files COPYING-LGPL-3 and COPYING-GPL-2; if not, see
// <http://www.gnu.org/licenses/>.

#include <config.h>

#include "MathMLOperatorElement.hh"
#include "MathMLFractionElement.hh"
#include "MathMLIdentifierElement.hh"
#include "MathMLInvisibleTimesNode.hh"
#include "FormattingContext.hh"
#include "MathGraphicDevice.hh"
#include "traverseAux.hh"

std::string
MathMLInvisibleTimesNode::getSpace(const FormattingContext& ctxt)
{
  static const std::string noSpace = u8"\u200b";
  static const std::string someSpace = u8"\u205f";

  // THESE CONSTANTS SHOULD BE CHECKED ON SOME MANUAL
  if (SmartPtr<MathMLOperatorElement> op = smart_cast<MathMLOperatorElement>(ctxt.getMathMLElement()))
    {
      SmartPtr<MathMLElement> prev = findLeftSibling(op);
      SmartPtr<MathMLElement> next = findRightSibling(op);
      if (!prev || !next) return noSpace;

      if (is_a<MathMLIdentifierElement>(prev) && is_a<MathMLIdentifierElement>(next))
	{
	  SmartPtr<MathMLTokenElement> prevToken = smart_cast<MathMLTokenElement>(prev);
	  SmartPtr<MathMLTokenElement> nextToken = smart_cast<MathMLTokenElement>(next);
	  assert(prevToken && nextToken);
    
	  if (prevToken->GetLogicalContentLength() <= 1 &&
	      nextToken->GetLogicalContentLength() <= 1) return noSpace;

	  return someSpace;
	} 
      else if (is_a<MathMLIdentifierElement>(prev))
	return someSpace;
      else if (is_a<MathMLFractionElement>(prev) && is_a<MathMLFractionElement>(next))
	return someSpace;
      else if (is_a<MathMLFractionElement>(prev) || is_a<MathMLFractionElement>(next))
	return someSpace;
    }

  return noSpace;
}

AreaRef
MathMLInvisibleTimesNode::format(FormattingContext& ctxt)
{ return ctxt.MGD()->string(ctxt, getSpace(ctxt)); }

std::string
MathMLInvisibleTimesNode::getContent()
{
  static const std::string content = u8"\u2062";
  return content;
}

std::string
MathMLInvisibleTimesNode::GetRawContent() const
{ return getContent(); }
