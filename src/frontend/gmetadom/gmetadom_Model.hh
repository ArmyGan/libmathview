// Copyright (C) 2000-2004, Luca Padovani <luca.padovani@cs.unibo.it>.
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

#ifndef __gmetadom_Model_hh__
#define __gmetadom_Model_hh__

#include <cassert>

#include "gmetadom.hh"
#include "String.hh"

#include "TemplateLinker.hh"
#include "TemplateRefinementContext.hh"

struct gmetadom_Model
{
  typedef DOM::GdomeString String;
  typedef DOM::Node Node;
  typedef DOM::Element Element;
  typedef TemplateLinker<gmetadom_Model> Linker;
  typedef class gmetadom_Builder Builder;
  typedef class TemplateRefinementContext<gmetadom_Model> RefinementContext;

  static DOM::Document parseXML(const ::String&, bool = false);
  static bool nodeIsBlank(const Node&);
  static ::String elementValue(const Element&);
  static ::String nodeLocalName(const Node&);
  inline static ::String fromModelString(const DOM::GdomeString& s) { return s; }
  inline static DOM::GdomeString toModelString(const ::String& s) { return s; }

  class NodeIterator
  {
  public:
    NodeIterator(const DOM::Node& root) : currentNode(root.get_firstChild()) { }

    DOM::Node node(void) const { return currentNode; }
    bool more(void) const { return currentNode; }
    void next(void) { currentNode = currentNode.get_nextSibling(); }

  private:
    DOM::Node currentNode;
  };

  class ElementIterator
  {
  public:
    ElementIterator(const DOM::Node& root, const String& ns = "*", const String& n = "*")
      : namespaceURI(ns), name(n)
    { currentElement = findValidNode(root.get_firstChild()); }

    DOM::Element element(void) const { return currentElement; }
    bool more(void) const { return currentElement; }

    bool valid(const DOM::Node& p) const
    {
      return (p.get_nodeType() == DOM::Node::ELEMENT_NODE)
	&& (namespaceURI == "*" || namespaceURI == p.get_namespaceURI())
	&& (name == "*" || name == gmetadom_Model::nodeLocalName(p));
    }
    
    void next(void)
    { currentElement = findValidNode(currentElement.get_nextSibling()); }

  protected:
    DOM::Element
    findValidNode(const DOM::Node& p0) const
    {
      for (DOM::Node p = p0; p; p = p.get_nextSibling())
	if (valid(p)) return p;
      return DOM::Element();
    }
    
  private:
    DOM::Element currentElement;
    DOM::GdomeString namespaceURI;
    DOM::GdomeString name;
  };

  struct Hash
  {
    size_t operator()(const DOM::Element& el) const
    {
      assert(el);
      return reinterpret_cast<size_t>(el.id());
    }
  };

};

#endif // __gmetadom_Model_hh__