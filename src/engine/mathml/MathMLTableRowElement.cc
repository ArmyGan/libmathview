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

#include <algorithm>

#include "Adapters.hh"
#include "Globals.hh"
#include "ValueConversion.hh"
#include "MathMLTableElement.hh"
#include "MathMLTableRowElement.hh"
#include "MathMLTableCellElement.hh"
#include "MathMLAttributeSignatures.hh"

MathMLTableRowElement::MathMLTableRowElement(const SmartPtr<class MathMLNamespaceContext>& context)
  : MathMLLinearContainerElement(context)
{
  rowIndex = 0;
}

MathMLTableRowElement::~MathMLTableRowElement()
{ }

#if 0
void
MathMLTableRowElement::construct()
{
  if (dirtyStructure())
    {
#if defined(HAVE_GMETADOM)
      if (getDOMElement())
	{
	  ChildList children(getDOMElement(), MATHML_NS_URI, "mtd");
	  unsigned n = children.get_length();

	  std::vector< SmartPtr<MathMLElement> > newContent;
	  newContent.reserve(n);
	  for (unsigned i = 0; i < n; i++)
	    {
	      DOM::Node node = children.item(i);
	      SmartPtr<MathMLElement> elem = getFormattingNode(node);
	      assert(elem);
	      newContent.push_back(elem);
	    }
	  swapContent(newContent);
	}
#endif
      
      std::for_each(content.begin(), content.end(), ConstructAdapter<MathMLElement>());

      resetDirtyStructure();
    }
}

void
MathMLTableRowElement::refine(AbstractRefinementContext& context)
{
  if (dirtyAttribute() || dirtyAttributeP())
    {
      REFINE_ATTRIBUTE(context, MathML, TableRow, rowalign);
      REFINE_ATTRIBUTE(context, MathML, TableRow, columnalign);
      REFINE_ATTRIBUTE(context, MathML, TableRow, groupalign);
      MathMLLinearContainerElement::refine(context);
    }
}
#endif

#if 0
void
MathMLTableRowElement::SetupRowIndex(unsigned i)
{
  rowIndex = i;
}

void
MathMLTableRowElement::SetupCellSpanning(RenderingEnvironment& env)
{
  for (std::vector< SmartPtr<MathMLElement> >::iterator p = content.begin();
       p != content.end();
       p++)
    {
      assert(is_a<MathMLTableCellElement>(*p));
      SmartPtr<MathMLTableCellElement> mtd = smart_cast<MathMLTableCellElement>(*p);
      assert(mtd);
      mtd->SetupCellSpanning(env);
    }
}

void
MathMLTableRowElement::Setup(RenderingEnvironment& env)
{
  SetupAux(env, false);
}

void
MathMLTableRowElement::SetupAux(RenderingEnvironment& env, bool labeledRow)
{
#if 0
  if (dirtyAttribute() || dirtyAttributeP())
    {
#endif
      SmartPtr<MathMLTableElement> mtable = getParent<MathMLTableElement>();
      assert(mtable);

      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(TableRow, columnalign))
	mtable->SetupColumnAlignAux(value, rowIndex, 1, labeledRow);

      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(TableRow, rowalign))
	mtable->SetupRowAlignAux(value, rowIndex, labeledRow);

      if (SmartPtr<Value> value = GET_ATTRIBUTE_VALUE(TableRow, groupalign))
	mtable->SetupGroupAlignAux(value, rowIndex, 1);

      MathMLLinearContainerElement::Setup(env);
      resetDirtyAttribute();
#if 0
    }
#endif
}

bool
MathMLTableRowElement::IsInside(const scaled& x, const scaled& y) const
{
  // same arguments as for the SetDirty method above
  for (std::vector< SmartPtr<MathMLElement> >::const_iterator elem = content.begin();
       elem != content.end();
       elem++)
    {
      assert(*elem);
      if ((*elem)->IsInside(x, y)) return true;
    }

  return false;
}
#endif

SmartPtr<MathMLElement>
MathMLTableRowElement::GetLabel(void) const
{
  return 0;
}

void
MathMLTableRowElement::setDirtyStructure()
{
  SmartPtr<MathMLTableElement> table = getParent<MathMLTableElement>();
  assert(table);
  table->setDirtyStructure();
  MathMLLinearContainerElement::setDirtyStructure();
}

void
MathMLTableRowElement::setDirtyAttribute()
{
  SmartPtr<MathMLTableElement> table = getParent<MathMLTableElement>();
  assert(table);
  table->setDirtyAttribute();
  MathMLLinearContainerElement::setDirtyAttribute();
}

void
MathMLTableRowElement::setDirtyLayout()
{
  SmartPtr<MathMLTableElement> table = getParent<MathMLTableElement>();
  assert(table);
  table->setDirtyLayout();
  MathMLLinearContainerElement::setDirtyLayout();
}
