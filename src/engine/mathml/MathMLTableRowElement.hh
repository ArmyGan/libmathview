// Copyright (C) 2000-2007, Luca Padovani <padovani@sti.uniurb.it>.
// 
// This file is part of GtkMathView, a flexible, high-quality rendering
// engine for MathML documents.
// 
// GtkMathView is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// GtkMathView is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MathMLTableRowElement_hh
#define MathMLTableRowElement_hh

#include "MathMLLinearContainerElement.hh"

class GMV_MathView_EXPORT MathMLTableRowElement
  : public MathMLLinearContainerElement
{
protected:
  MathMLTableRowElement(const SmartPtr<class MathMLNamespaceContext>&);
  virtual ~MathMLTableRowElement();

public:
  static SmartPtr<MathMLTableRowElement> create(const SmartPtr<class MathMLNamespaceContext>& view)
  { return new MathMLTableRowElement(view); }

#if 0
  virtual void Setup(RenderingEnvironment&);
  
  virtual bool IsInside(const scaled&, const scaled&) const;
#endif

  virtual SmartPtr<MathMLElement> GetLabel(void) const;

  friend class MathMLTableElement;

  virtual void setDirtyStructure(void);
  virtual void setDirtyAttribute(void);
  virtual void setDirtyLayout(void);

protected:
#if 0
  void SetupAux(RenderingEnvironment&, bool);
  void SetupCellSpanning(RenderingEnvironment&);
  void SetupGroupAlign(RenderingEnvironment&);
  void SetupRowIndex(unsigned);
#endif

private:
  unsigned rowIndex;
};

#endif // MathMLTableRowElement_hh
