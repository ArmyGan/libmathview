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

#include <cassert>

// #ifdef HAVE_WCTYPE_H
// #include <wctype.h>
// #endif
// #ifdef HAVE_WCHAR_H
// #include <wchar.h>
// #endif

#include "AFont.hh"
#include "frameAux.hh"
#include "Globals.hh"
#include "traverseAux.hh"
#include "MathMLMarkNode.hh"
#include "MathMLTextNode.hh"
#include "MathMLStringNode.hh"
#include "mathVariantAux.hh"
#include "ValueConversion.hh"
#include "MathMLGlyphNode.hh"
#include "MathMLSpaceNode.hh"
#include "MathMLTextElement.hh"
#include "MathMLTokenElement.hh"
#include "MathMLNumberElement.hh"
#include "RenderingEnvironment.hh"
#include "MathMLOperatorElement.hh"
#include "MathMLIdentifierElement.hh"
#include "FormattingContext.hh"
#include "BoundingBoxAux.hh"

MathMLTokenElement::MathMLTokenElement()
{
}

#if defined(HAVE_GMETADOM)
MathMLTokenElement::MathMLTokenElement(const DOM::Element& node)
  : MathMLElement(node)
{
}
#endif

MathMLTokenElement::~MathMLTokenElement()
{
}

void
MathMLTokenElement::refine(AbstractRefinementContext& context)
{
  if (DirtyAttribute() || DirtyAttributeP())
    {
      REFINE_ATTRIBUTE(context, Token, fontsize);
      REFINE_ATTRIBUTE(context, Token, fontweight);
      REFINE_ATTRIBUTE(context, Token, fontstyle);
      REFINE_ATTRIBUTE(context, Token, fontfamily);
      REFINE_ATTRIBUTE(context, Token, color);
      REFINE_ATTRIBUTE(context, Token, mathvariant);
      REFINE_ATTRIBUTE(context, Token, mathsize);
      REFINE_ATTRIBUTE(context, Token, mathcolor);
      REFINE_ATTRIBUTE(context, Token, mathbackground);
      MathMLElement::refine(context);
    }
}

void
MathMLTokenElement::SetSize(unsigned i)
{
  assert(i <= content.size());
  while (i < content.size()) RemoveChild(content.size() - 1);
  content.reserve(i);
}

SmartPtr<MathMLTextNode>
MathMLTokenElement::GetChild(unsigned i) const
{
  if (i < content.size()) return content[i];
  else return 0;
}

void
MathMLTokenElement::SetChild(unsigned i, const SmartPtr<MathMLTextNode>& child)
{
  assert(i < content.size());
  assert(child);
  if (content[i] != child)
    {
      assert(!child->GetParent());
      content[i]->Unlink();
      child->SetParent(this);
      content[i] = child;
      SetDirtyLayout();
    }
}

void
MathMLTokenElement::Append(const String& s)
{
  SmartPtr<MathMLTextNode> node = MathMLStringNode::create(s);
  AppendChild(node);
}

void
MathMLTokenElement::AppendChild(const SmartPtr<MathMLTextNode>& node)
{
  assert(node);
  assert(!node->GetParent());
  node->SetParent(this);
  content.push_back(node);
  SetDirtyLayout();
}

void
MathMLTokenElement::RemoveChild(unsigned i)
{
  assert(i < content.size());
  content[i]->Unlink();
  content.erase(content.begin() + i);
  SetDirtyLayout();
}

void
MathMLTokenElement::InsertChild(unsigned i, const SmartPtr<MathMLTextNode>& node)
{
  assert(i <= content.size());
  assert(node);
  assert(!node->GetParent());
  node->SetParent(this);
  content.insert(content.begin() + i, node);
  SetDirtyLayout();
}

void
MathMLTokenElement::SwapChildren(std::vector< SmartPtr<MathMLTextNode> >& newContent)
{
  if (newContent != content)
    {
      // reset parent should be done first because the same elements
      // may be present in the following loop as well
      for (std::vector< SmartPtr<MathMLTextNode> >::iterator p = content.begin();
	   p != content.end();
	   p++)
	(*p)->Unlink();

      for (std::vector< SmartPtr<MathMLTextNode> >::iterator p = newContent.begin();
	   p != newContent.end();
	   p++)
	{
	  assert(*p);
	  (*p)->SetParent(this);
	}

      content.swap(newContent);

      SetDirtyLayout();
    }
}

void
MathMLTokenElement::Normalize(const SmartPtr<class MathMLDocument>&)
{
  if (DirtyStructure() && GetDOMElement())
    {
#if defined(HAVE_GMETADOM)
      content.clear();

      for (DOM::Node p = GetDOMElement().get_firstChild(); 
	   p;
	   p = p.get_nextSibling()) 
	{
	  switch (p.get_nodeType())
	    {
	    case DOM::Node::TEXT_NODE:
	      {
		// ok, we have a chunk of text
		String content = collapseSpaces(fromDOMString(p.get_nodeValue()));

		// ...but spaces at the at the beginning (end) are deleted only if this
		// is the very first (last) chunk in the token.
		if (!p.get_previousSibling()) content = trimSpacesLeft(content);
		if (!p.get_nextSibling()) content = trimSpacesRight(content);

		Append(content);
	      }
	    break;

#if 0
	    // to be rewritten or deleted
	    case DOM::Node::ENTITY_REFERENCE_NODE:
	      for (DOM::Node p = node.get_firstChild(); p != 0; p = p.get_nextSibling())
		MathMLizeTokenContent(p, parent);
	      break;
#endif

	    case DOM::Node::ELEMENT_NODE:
	      {	    
		if (p.get_namespaceURI() == MATHML_NS_URI)
		  {
		    if (nodeLocalName(p) == "mglyph")
		      {
			SmartPtr<MathMLTextNode> text = SubstituteMGlyphElement(p);
			if (text) AppendChild(text);
		      }
		    else if (nodeLocalName(p) == "malignmark")
		      {
			SmartPtr<MathMLTextNode> text = SubstituteAlignMarkElement(p);
			if (text) AppendChild(text);
		      }
		    else
		      {
			std::string s_name = nodeLocalName(p);
			Globals::logger(LOG_WARNING, "element `%s' inside token (ignored)\n", s_name.c_str());
		      }
		  } else
		    {
		      std::string s_name = p.get_nodeName();
		      Globals::logger(LOG_WARNING, "element `%s' inside token (ignored)\n", s_name.c_str());
		    }
	      }
	    break;
	  
	    default:
	      break;
	    }
	}
#endif // HAVE_GMETADOM

      ResetDirtyStructure();
    }
}

void
MathMLTokenElement::Setup(RenderingEnvironment& env)
{
  if (DirtyAttribute())
    {
      env.Push();

      if (!is_a<MathMLIdentifierElement>(SmartPtr<MathMLElement>(this)) &&
	  !is_a<MathMLOperatorElement>(SmartPtr<MathMLElement>(this)))
	env.SetFontMode(FONT_MODE_TEXT);

      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, mathsize))
	{
	  if (IsSet(ATTR_FONTSIZE))
	    Globals::logger(LOG_WARNING, "attribute `mathsize' overrides deprecated attribute `fontsize'");

	  if (IsKeyword(value))
	    switch (ToKeywordId(value))
	      {
	      case KW_SMALL: env.AddScriptLevel(1); break;
	      case KW_BIG: env.AddScriptLevel(-1); break;
	      case KW_NORMAL: break; // noop
	      default: assert(IMPOSSIBLE); break;
	      }
	  else
	    env.SetFontSize(ToNumberUnit(value));
	} 
      else if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, fontsize))
	{
	  Globals::logger(LOG_WARNING, "the attribute `fontsize' is deprecated in MathML 2");
	  env.SetFontSize(ToNumberUnit(value));
	}
  
      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, mathvariant))
	{
	  assert(IsKeyword(value));

	  const MathVariantAttributes& attr = attributesOfVariant(ToKeywordId(value));
	  assert(attr.kw != KW_NOTVALID);
	  env.SetFontFamily(attr.family);
	  env.SetFontWeight(attr.weight);
	  env.SetFontStyle(attr.style);

	  if (IsSet(ATTR_FONTFAMILY) || IsSet(ATTR_FONTWEIGHT) || IsSet(ATTR_FONTSTYLE))
	    Globals::logger(LOG_WARNING, "attribute `mathvariant' overrides deprecated font-related attributes");
	}
      else
	{
	  if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, fontfamily))
	    {
	      Globals::logger(LOG_WARNING, "the attribute `fontfamily' is deprecated in MathML 2");
	      env.SetFontFamily(ToString(value));
	    }

	  if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, fontweight))
	    {
	      Globals::logger(LOG_WARNING, "the attribute `fontweight' is deprecated in MathML 2");
	      env.SetFontWeight(ToFontWeightId(value));
	    }

	  if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, fontstyle))
	    {
	      Globals::logger(LOG_WARNING, "the attribute `fontstyle' is deprecated in MathML 2");
	      env.SetFontStyle(ToFontStyleId(value));
	    } 
	  else if (is_a<MathMLIdentifierElement>(SmartPtr<MathMLElement>(this)))
	    {
	      if (GetLogicalContentLength() == 1)
		env.SetFontStyle(FONT_STYLE_ITALIC);
	      else
		{
		  env.SetFontStyle(FONT_STYLE_NORMAL);
		  env.SetFontMode(FONT_MODE_TEXT);
		}
	    }
	}
      
      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, mathcolor))
	{
	  if (IsSet(ATTR_COLOR))
	    Globals::logger(LOG_WARNING, "attribute `mathcolor' overrides deprecated attribute `color'");
	  env.SetColor(ToRGB(value));
	} 
      else if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, color))
	{
	  Globals::logger(LOG_WARNING, "attribute `color' is deprecated in MathML 2");
	  env.SetColor(ToRGB(value));
	} 
      else
	if (HasLink()) env.SetColor(Globals::configuration.GetLinkForeground());

      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(Token, mathbackground))
	env.SetBackgroundColor(ToRGB(value));
      else if (HasLink() && !Globals::configuration.HasTransparentLinkBackground())
	env.SetBackgroundColor(Globals::configuration.GetLinkBackground());

      color      = env.GetColor();
      background = env.GetBackgroundColor();
      sppm       = env.GetScaledPointsPerEm();

      for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator p = GetContent().begin();
	   p != GetContent().end();
	   p++)
	{
	  assert(*p);
	  (*p)->Setup(env);
	}

      env.Drop();

      ResetDirtyAttribute();
    }
}

void
MathMLTokenElement::DoLayout(const class FormattingContext& ctxt)
{
  if (DirtyLayout(ctxt))
    {
      box.unset();
      for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
	   text != GetContent().end();
	   text++)
	{
	  assert(*text);
	  if (ctxt.GetLayoutType() == LAYOUT_MIN) (*text)->DoLayout(ctxt);

	  // if we do not insert MathMLSpaceNodes in the layout, they will not be
	  // positioned correctly, since positioning is done thru the layout.
	  // In such way, If a space node is the first inside a token, it will produce
	  // a zero-origin rectangle which is obviously incorrect
	  box.append((*text)->GetBoundingBox());
	  box.width += ((sppm * (*text)->GetSpacing()) / 18);
	}

      AddItalicCorrection();

      ResetDirtyLayout(ctxt);
    }
}

void
MathMLTokenElement::SetPosition(const scaled& x, const scaled& y)
{
  //printf("token %s set position %d %d\n", NameOfTagId(IsA()), sp2ipx(x), sp2ipx(y));
  MathMLElement::SetPosition(x, y);
  SetContentPosition(x, y);
}

void
MathMLTokenElement::SetContentPosition(const scaled& x0, const scaled& y)
{
  scaled x = x0;

  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin(); 
       text != GetContent().end();
       text++)
    {
      assert(*text);
      (*text)->SetPosition(x, y);
      x += (*text)->GetBoundingBox().width;
      x += (sppm * (*text)->GetSpacing()) / 18;
    }
}

void
MathMLTokenElement::Render(const DrawingArea& area)
{
  if (Exposed(area))
    {
      RenderBackground(area);

      if (fGC[Selected()] == NULL)
	{
	  GraphicsContextValues values;

	  values.foreground = Selected() ? area.GetSelectionForeground() : color;
	  values.background = Selected() ? area.GetSelectionBackground() : background;
	  fGC[Selected()] = area.GetGC(values, GC_MASK_FOREGROUND | GC_MASK_BACKGROUND);
	}

      for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
	   text != GetContent().end();
	   text++)
	{
	  assert(*text);
	  (*text)->Render(area);
	}

      //area.DrawRectangle(fGC[0], *shape);

      ResetDirty();
    }
}

scaled
MathMLTokenElement::GetLeftEdge() const
{
  scaled edge = 0;

  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
       text != GetContent().end();
       text++)
    {
      assert(*text);
      if (text == GetContent().begin()) edge = (*text)->GetLeftEdge();
      else edge = std::min(edge, (*text)->GetLeftEdge());
    }

  return edge;
}

scaled
MathMLTokenElement::GetRightEdge() const
{
  scaled edge = 0;

  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
       text != GetContent().end();
       text++)
    {
      assert(*text);
      if (text == GetContent().begin()) edge = (*text)->GetRightEdge();
      else edge = std::max(edge, (*text)->GetRightEdge());
    }

  return edge;
}

scaled
MathMLTokenElement::GetDecimalPointEdge() const
{
  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
       text != GetContent().end();
       text++)
    {
      assert(*text);
      if ((*text)->HasDecimalPoint()) return (*text)->GetDecimalPointEdge();
    }

  return GetRightEdge();
}

bool
MathMLTokenElement::IsNonMarking() const
{
  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator text = GetContent().begin();
       text != GetContent().end();
       text++)
    {
      assert(*text);
      if (!is_a<MathMLSpaceNode>(*text)) return false;
    }

  return true;
}

#if 0
SmartPtr<MathMLCharNode>
MathMLTokenElement::GetCharNode() const
{
#if 0
  if (GetSize() != 1) return 0;

  SmartPtr<MathMLTextNode> node = GetChild(0);
  assert(node);
  if (!is_a<MathMLCharNode>(node) || is_a<MathMLCombinedCharNode>(node)) return 0;

  return smart_cast<MathMLCharNode>(node);
#endif
  return 0; // ??????????????????????????????
}
#endif

void
MathMLTokenElement::AddItalicCorrection()
{
  if (!is_a<MathMLIdentifierElement>(SmartPtr<MathMLElement>(this)) &&
      !is_a<MathMLNumberElement>(SmartPtr<MathMLElement>(this)) &&
      !is_a<MathMLTextElement>(SmartPtr<MathMLElement>(this))) return;
  
  if (GetSize() == 0) return;

  SmartPtr<MathMLTextNode> lastNode = GetChild(GetSize() - 1);
  assert(lastNode);

  SmartPtr<MathMLElement> next = findRightSibling(this);
  if (!next) return;

  SmartPtr<MathMLOperatorElement> coreOp = next->GetCoreOperatorTop();
  if (!coreOp) return;
  bool isFence = coreOp->IsFence();
  if (!isFence) return;
}

SmartPtr<MathMLTextNode>
MathMLTokenElement::SubstituteMGlyphElement(const DOM::Element& node)
{
  assert(node);

  DOM::GdomeString alt        = node.getAttribute("alt");
  DOM::GdomeString fontFamily = node.getAttribute("fontfamily");
  DOM::GdomeString index      = node.getAttribute("index");

  if (alt.empty() || fontFamily.empty() || index.empty()) {
    Globals::logger(LOG_WARNING, "malformed `mglyph' element (some required attribute is missing)\n");
    return MathMLStringNode::create("?");
  }

  std::string s_index = index;
  char* endPtr;
  unsigned nch = strtoul(s_index.c_str(), &endPtr, 10);

  if (endPtr == NULL || *endPtr != '\0') {
    Globals::logger(LOG_WARNING, "malformed `mglyph' element (parsing error in `index' attribute)\n");
    nch = '?';
  }

  std::string s_alt = alt;
  std::string s_fontFamily = fontFamily;
  SmartPtr<MathMLGlyphNode> glyph = MathMLGlyphNode::create(s_alt.c_str(), s_fontFamily.c_str(), nch);

  return glyph;
}

SmartPtr<MathMLTextNode>
MathMLTokenElement::SubstituteAlignMarkElement(const DOM::Element& node)
{
  assert(node);

  DOM::GdomeString edge = node.getAttribute("edge");

  MarkAlignType align = MARK_ALIGN_NOTVALID;

  if (!edge.empty())
    {
      if      (edge == "left") align = MARK_ALIGN_LEFT;
      else if (edge == "right") align = MARK_ALIGN_RIGHT;
      else
	{
	  std::string s_edge = edge;
	  Globals::logger(LOG_WARNING,
			  "malformed `malignmark' element, attribute `edge' has invalid value `%s' (ignored)",
			  s_edge.c_str());
	}
    }

  return MathMLMarkNode::create(align);
}

String
MathMLTokenElement::GetRawContent() const
{
  String res;
  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator i = GetContent().begin();
       i != GetContent().end();
       i++)
    {
      assert(*i);
      res += (*i)->GetRawContent();
    }

  return res;
}

unsigned
MathMLTokenElement::GetLogicalContentLength() const
{
  unsigned len = 0;

  for (std::vector< SmartPtr<MathMLTextNode> >::const_iterator i = GetContent().begin();
       i != GetContent().end();
       i++)
    {
      assert(*i);
      len += (*i)->GetLogicalContentLength();
    }

  return len;
}
