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
#include <stdlib.h>
#include <string.h>

#include "config.dirs"

#include "Clock.hh"
#include "Parser.hh"
#include "Iterator.hh"
#include "MathEngine.hh"
#include "CharMapper.hh"
#include "StringUnicode.hh"
#include "MathMLDocument.hh"
#include "T1_Gtk_DrawingArea.hh"
#include "RenderingEnvironment.hh"

EntitiesTable      MathEngine::entitiesTable;
OperatorDictionary MathEngine::dictionary;
Configuration      MathEngine::configuration;
Logger             MathEngine::logger;
bool               MathEngine::kerning = false;

MathEngine::MathEngine()
{
  area = NULL;
  fontManager = NULL;
  charMapper = NULL;

  defaultFontSize = configuration.GetFontSize();
  antiAliasing = false;
  kerning = false;

  document = NULL;
  root = NULL;
  selectionFirst = selectionRoot = selection = NULL;
}

MathEngine::~MathEngine()
{
  delete charMapper;
}

void
MathEngine::InitGlobalData(const char* confPath)
{
  static volatile bool firstTime = true;
  assert(firstTime);

  bool res = false;
  if (confPath != NULL) res = configuration.Load(confPath);
  if (!res) res = configuration.Load(PKGDATADIR"/math-engine-configuration.xml");
  if (!res) res = configuration.Load("config/math-engine-configuration.xml");
  if (!res) {
    logger(LOG_ERROR, "could not find configuration file");
    exit(-1);
  }

  // the entities table and the dictionary are static members of MathEngine,
  // so they have to be configured once only
  
  //res = entitiesTable.Load("/usr/local/share/gtkmathview/entities-table.xml", false);
  //if (!res) res = entitiesTable.Load("config/entities-table.xml", true);
  entitiesTable.LoadInternalTable();
  
  Iterator<String*> dit(configuration.GetDictionaries());
  if (dit.More()) {
    while (dit.More()) {
      assert(dit() != NULL);
      MathEngine::logger(LOG_DEBUG, "loading dictionary `%s'", dit()->ToStaticC());
      if (!dictionary.Load(dit()->ToStaticC())) {
	MathEngine::logger(LOG_WARNING, "could not load `%s'", dit()->ToStaticC());
      }
      dit.Next();
    }
  } else {
    bool res = dictionary.Load("config/dictionary.xml");
    if (!res) dictionary.Load(PKGDATADIR"/dictionary.xml");
  }

  if (getenv("T1LIB_CONFIG") == NULL && configuration.GetT1ConfigFiles().GetSize() == 1) {
    StringC s("T1LIB_CONFIG=");
    assert(configuration.GetT1ConfigFiles().GetFirst() != NULL);
    s.Append(*configuration.GetT1ConfigFiles().GetFirst());

    char *cs = strdup(s.ToStaticC());
    putenv(cs);
  }

  firstTime = false;
}

void
MathEngine::Init(class DrawingArea* a, class FontManager* fm)
{
  assert(a != NULL);
  assert(fm != NULL);

  area = a;
  fontManager = fm;

  if (charMapper != NULL) delete charMapper;
  charMapper = new CharMapper(*fm);

  Iterator<String*> cit(configuration.GetFonts());
  if (cit.More()) {
    while (cit.More()) {
      assert(cit() != NULL);
      if (!charMapper->Load(cit()->ToStaticC())) {
	MathEngine::logger(LOG_WARNING, "could not load `%s'", cit()->ToStaticC());
      }
      cit.Next();
    }
  } else {
    bool res = charMapper->Load("config/font-configuration.xml");
    if (!res) charMapper->Load(PKGDATADIR"/font-configuration.xml");
  }
}

bool
MathEngine::Load(const char* fileName)
{
  assert(fileName != NULL);

  Clock perf;
  perf.Start();
  MathMLParser *parser = new MathMLParser(fileName);
  document = parser->Parse();
  perf.Stop();
  logger(LOG_INFO, "parsing time: %dms", perf());
  delete parser;

  if (document != NULL) {
    perf.Start();
    document->Normalize();
    perf.Stop();
    logger(LOG_INFO, "normalization time: %dms", perf());
    
    root = document->GetRoot();
    assert(root != NULL);

    Setup();

    return true;
  } else
    logger(LOG_WARNING, "error while parsing `%s'", fileName);

  return false;
}

void
MathEngine::Unload()
{
  delete document;

  document = NULL;  
  root = NULL;

  selectionFirst = selectionRoot = selection = NULL;
}

void
MathEngine::Setup()
{
  if (root == NULL) return;

  Clock perf;

  UnitValue size;
  size.Set(defaultFontSize, UNIT_PT);

  assert(charMapper != NULL);
  RenderingEnvironment env(*charMapper);
  env.SetFontSize(size);
  perf.Start();
  root->Setup(&env);
  perf.Stop();
  logger(LOG_INFO, "setup time: %dms", perf());

  perf.Start();
  root->DoBoxedLayout(LAYOUT_MIN);
  perf.Stop();
  logger(LOG_INFO, "minimum layout time: %dms", perf());

  perf.Start();
  root->DoBoxedLayout(LAYOUT_MAX);
  perf.Stop();
  logger(LOG_INFO, "maximum layout time: %dms", perf());
}

void
MathEngine::Layout()
{
  assert(area != NULL);

  if (root == NULL) return;

  Clock perf;
  perf.Start();
  root->DoBoxedLayout(LAYOUT_AUTO, scaledMax(0, area->GetWidth() -  2 * area->GetXMargin()));
  root->SetPosition(area->GetXMargin(), area->GetYMargin() + root->GetBoundingBox().ascent);
  root->Freeze();
  perf.Stop();
  logger(LOG_INFO, "layout time: %dms", perf());
}

void
MathEngine::SetDirty(const Rectangle* rect)
{
  if (root == NULL) return;
  root->SetDirty(rect);
}

void
MathEngine::Render(const Rectangle* rect)
{
  if (root == NULL) return;
  root->SetDirty(rect);
  Update(rect);
}

void
MathEngine::Update(const Rectangle* rect)
{
  assert(area != NULL);

  if (root == NULL) return;

  Clock perf;
  perf.Start();
  root->Render(*area);
  if (rect != NULL) area->Update(*rect);
  else area->Update();
  perf.Stop();
  logger(LOG_INFO, "rendering time: %dms", perf());
}

void
MathEngine::GetDocumentBoundingBox(BoundingBox& box) const
{
  if (root == NULL) {
    box.Null();
    return;
  }

  box = root->GetBoundingBox();  
}

void
MathEngine::SetSelectionFirst(scaled x, scaled y)
{
  selectionFirst = GetElementAt(x, y);
}

MathMLElement*
MathEngine::SelectMinimumTree(MathMLElement* first, MathMLElement* last)
{
  assert(first != NULL);
  assert(last != NULL);

  if (first != last) {
    unsigned firstDepth = first->GetDepth();
    unsigned lastDepth  = last->GetDepth();

    while (firstDepth > lastDepth) {
      first = first->GetParent();
      firstDepth--;
    }

    while (lastDepth > firstDepth) {
      last = last->GetParent();
      lastDepth--;
    }

    assert(firstDepth == lastDepth);

    while (first != NULL && last != NULL && first != last) {
      first = first->GetParent();
      last = last->GetParent();
    }
  }

  assert(first == last);

  return first;
}

void
MathEngine::SetSelectionLast(scaled x, scaled y)
{
  if (selectionFirst == NULL) return;

  MathMLElement* selectionLast = GetElementAt(x, y);
  if (selectionLast == NULL) return;

  selectionRoot = SelectMinimumTree(selectionFirst, selectionLast);
  while (selectionRoot != NULL && selectionRoot->GetDOMNode() == NULL)
    selectionRoot = selectionRoot->GetParent();
}

void
MathEngine::ResetSelectionRoot()
{
  selectionFirst = selectionRoot = NULL;
}

void
MathEngine::SetSelection(MathMLElement* selected)
{
  if (selection == selected) return;

  if (selection != NULL) selection->ResetSelected();
  selection = selected;
  if (selection != NULL) selection->SetSelected();

  Update();
}

MathMLElement*
MathEngine::GetElementAt(scaled x, scaled y) const
{
  if (root == NULL) return NULL;
  // WARNING: x and y must be absolute coordinates w.r.t. the drawing area, because
  // at this level we do not known whether the drawing area is scrollable (as in
  // the case of Gtk_DrawingArea) or not (PS_DrawingArea). The caller must
  // properly adjust x and y before calling this method
  return root->Inside(x, y);
}

void
MathEngine::SetDefaultFontSize(unsigned size)
{
  assert(size > 0);
  defaultFontSize = size;
}

void
MathEngine::SetVerbosity(int level)
{
  logger.SetLogLevel(level);
}

int
MathEngine::GetVerbosity() const
{
  return logger.GetLogLevel();
}

void
MathEngine::SetAntiAliasing(bool aa)
{
  assert(area != NULL);

  antiAliasing = aa;

#ifdef HAVE_LIBT1
  T1_Gtk_DrawingArea* t1_area = TO_T1_GTK_DRAWING_AREA(area);
  if (t1_area != NULL) {
    t1_area->SetAntiAliasing(aa);
    return;
  }
#endif
  logger(LOG_WARNING, "anti-aliasing is available with the T1 font manager only");
}

void
MathEngine::SetKerning(bool k)
{
  kerning = k;
#ifndef HAVE_LIBT1
  logger(LOG_WARNING, "kerning is available with the T1 font manager only");
#endif
}
