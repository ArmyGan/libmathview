// Copyright (C) 2000, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://cs.unibo.it/~lpadovan/mml-widget/, or send a mail to
// <luca.padovani@cs.unibo.it>

#include <config.h>
#include <assert.h>

#include "Clock.hh"
#include "Globals.hh"
#include "MathMLDocument.hh"
#include "MathMLParseFile.hh"
#include "MathMLActionElement.hh"
#include "RenderingEnvironment.hh"
#include "MathMLRenderingEngine.hh"
#include "RefinementContext.hh"
#include "FormattingContext.hh"
#include "ShaperManager.hh"

#include "config.dirs"

#ifdef HAVE_LIBT1
#include "T1_FontManager.hh"
#include "T1_Gtk_DrawingArea.hh"
#endif

MathMLRenderingEngine::MathMLRenderingEngine()
  : document(0)
{
  area = 0;
  fontManager = 0;
  shaperManager = 0;
  areaFactory = 0;

  defaultFontSize = Globals::configuration.GetFontSize();
}

MathMLRenderingEngine::~MathMLRenderingEngine()
{
  Unload();
  assert(!document);

  // WARNING: do we have to delete the font manager?
  fontManager = 0;

  areaFactory = 0;
  shaperManager = 0;
}

void
MathMLRenderingEngine::Init(class DrawingArea* a, class FontManager* fm,
			    class AreaFactory* af, class ShaperManager* sm)
{
  assert(a != NULL);
  assert(fm != NULL);

  if (document)
    {
      document->ReleaseGCs();
      document->SetDirtyAttributeD();
      document->SetDirtyLayout();
      //document->SetDirty();
    }

  area = a;
  fontManager = fm;

  if (areaFactory) delete areaFactory;
  areaFactory = af;
  if (shaperManager) delete shaperManager;
  shaperManager = sm;
}

bool
MathMLRenderingEngine::Load(const char* fileName)
{
  assert(fileName != NULL);

  Unload();

  Clock perf;
  perf.Start();
#if defined(HAVE_MINIDOM)
  mDOMDocRef doc = MathMLParseFile(fileName, true);
#elif defined(HAVE_GMETADOM)
  DOM::Document doc = MathMLParseFile(fileName, true);
#endif
  perf.Stop();
  Globals::logger(LOG_INFO, "parsing time: %dms", perf());

  if (!doc) {
    Globals::logger(LOG_WARNING, "error while parsing `%s'", fileName);
    return false;
  }

  return Load(doc);
}

#if defined(HAVE_GMETADOM)
bool
MathMLRenderingEngine::Load(const DOM::Document& doc)
{
  assert(doc);

  Unload();

  document = MathMLDocument::create(doc);
  assert(document);

  return true;
}

#if 0
bool
MathMLRenderingEngine::Load(const DOM::Element& elem)
{
  assert(elem);

  Unload();

  SmartPtr<MathMLDocument> document = MathMLDocument::create(elem);
  assert(document);

  root = document->GetRoot();
  assert(root);

  return true;
}
#endif
#endif

void
MathMLRenderingEngine::Unload()
{
  document = 0;
}

void
MathMLRenderingEngine::Layout() const
{
  assert(area != NULL);

  if (document)
    {
      Clock formatTime;
      formatTime.Start();

      if (document->DirtyStructure())
	{
	  Clock perf;
	  perf.Start();
	  document->Normalize();
	  perf.Stop();
	  Globals::logger(LOG_INFO, "normalization time: %dms", perf());
	}

      if (document->DirtyAttribute() || document->DirtyAttributeP())
	{
	  Clock perf;
	  RefinementContext rc;
	  perf.Start();
	  document->refine(rc);
	  perf.Stop();
	  Globals::logger(LOG_INFO, "refinement time: %dms", perf());
	  UnitValue size(defaultFontSize, UNIT_PT);
	  RenderingEnvironment env(areaFactory, *shaperManager);
	  env.SetFontSize(size);
	  perf.Start();
	  document->Setup(env);
	  perf.Stop();
	  Globals::logger(LOG_INFO, "setup time: %dms", perf());
	}

      if (document->DirtyLayout())
	{
	  Clock perf;
	  perf.Start();
	  document->DoLayout(FormattingContext(LAYOUT_MIN,0));
	  perf.Stop();
	  Globals::logger(LOG_INFO, "minimum layout time: %dms", perf());

	  perf.Start();
	  document->DoLayout(FormattingContext(LAYOUT_AUTO, std::max(scaled(0), area->GetWidth() -  2 * area->GetXMargin())));
	  document->SetPosition(area->GetXMargin(), area->GetYMargin() + document->GetBoundingBox().height);
	  perf.Stop();
	  Globals::logger(LOG_INFO, "layout time: %dms", perf());
	}

      formatTime.Stop();
      Globals::logger(LOG_INFO, "FORMATTING TIME: %dms", formatTime());
    }
}

void
MathMLRenderingEngine::SetDirty(const Rectangle* rect) const
{
  //if (document) document->SetDirty(rect);
}

#include "MathMLStringNode.hh"
#include "scaledConv.hh"

void
MathMLRenderingEngine::Render(const Rectangle* rect) const
{
  assert(area);

  Layout();
  //SetDirty(rect);

  if (document)
    {
      Clock perf;
      perf.Start();
      MathMLStringNode::visited = 0;
      document->Render(*area);
      perf.Stop();
      Globals::logger(LOG_INFO, "rendering time: %dms (visited %d)", perf(), MathMLStringNode::visited);
    }

  if (rect) area->Update(*rect);
  else area->Update();
}

void
MathMLRenderingEngine::GetDocumentBoundingBox(BoundingBox& box) const
{
  Layout();
  if (document)
    box = document->GetBoundingBox();
  else
    box.unset();
}

void
MathMLRenderingEngine::GetDocumentRectangle(Rectangle& rect) const
{
  Layout();
  if (document)
    {
      BoundingBox box;
      GetDocumentBoundingBox(box);
      rect = Rectangle(document->GetX(), document->GetY(), box);
    }
  else
    rect.Zero();
}

SmartPtr<MathMLElement>
MathMLRenderingEngine::GetElementAt(const scaled& x, const scaled& y) const
{
  if (document) return document->Inside(x, y);
  else return 0;
  // WARNING: x and y must be absolute coordinates w.r.t. the drawing area, because
  // at this level we do not known whether the drawing area is scrollable (as in
  // the case of Gtk_DrawingArea) or not (PS_DrawingArea). The caller must
  // properly adjust x and y before calling this method
}

void
MathMLRenderingEngine::SetDefaultFontSize(unsigned size)
{
  assert(size > 0);
  if (defaultFontSize != size) defaultFontSize = size;

  if (document)
    {
      document->SetDirtyAttributeD();
      document->SetDirtyLayout();
      //document->SetDirty();
    }
}

void
MathMLRenderingEngine::SetAntiAliasing(bool aa)
{
  assert(area != NULL);

#ifdef HAVE_LIBT1
  T1_Gtk_DrawingArea* t1_area = TO_T1_GTK_DRAWING_AREA(area);
  if (t1_area != NULL)
    t1_area->SetAntiAliasing(aa);
  else
#endif
    Globals::logger(LOG_WARNING, "anti-aliasing is available with the T1 font manager only");
}

bool
MathMLRenderingEngine::GetAntiAliasing() const
{
  assert(area != NULL);

#ifdef HAVE_LIBT1
  T1_Gtk_DrawingArea* t1_area = TO_T1_GTK_DRAWING_AREA(area);
  if (t1_area != NULL) return t1_area->GetAntiAliasing();
#endif
  Globals::logger(LOG_WARNING, "anti-aliasing is available with the T1 font manager only");
  return false;
}

void
MathMLRenderingEngine::SetTransparency(bool b)
{
  assert(area != NULL);

#ifdef HAVE_LIBT1
  T1_Gtk_DrawingArea* t1_area = TO_T1_GTK_DRAWING_AREA(area);
  if (t1_area != NULL)
    t1_area->SetTransparency(b);
  else
#endif
    Globals::logger(LOG_WARNING, "transparency is available with the T1 font manager only");
}

bool
MathMLRenderingEngine::GetTransparency() const
{
  assert(area != NULL);

#ifdef HAVE_LIBT1
  T1_Gtk_DrawingArea* t1_area = TO_T1_GTK_DRAWING_AREA(area);
  if (t1_area != NULL) return t1_area->GetTransparency();
#endif
  Globals::logger(LOG_WARNING, "kerning is available with the T1 font manager only");
  return false;
}
