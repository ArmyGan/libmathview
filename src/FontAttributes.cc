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
// http://cs.unibo.it/~lpadovan/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#include <config.h>
#include <assert.h>
#include <stddef.h>

#include "Iterator.hh"
#include "MathEngine.hh"
#include "FontAttributes.hh"

FontAttributes::FontAttributes()
{
  Null();
}

FontAttributes::FontAttributes(const FontAttributes& source, const FontAttributes& def)
{
  assert(NOT_IMPLEMENTED);
}

void
FontAttributes::Null()
{
  family = NULL;
  style  = FONT_STYLE_NOTVALID;
  weight = FONT_WEIGHT_NOTVALID;
  size.Null();
  mode = FONT_MODE_ANY;
}

bool
FontAttributes::DownGrade()
{
  bool res = true;

  if (HasMode()) mode = FONT_MODE_ANY;
  else if (HasWeight()) weight = FONT_WEIGHT_NOTVALID;
  else if (HasStyle()) style = FONT_STYLE_NOTVALID;
  else if (HasFamily()) family = NULL;
  else if (HasSize()) size.Null();
  else res = false;

  return res;
}

bool
FontAttributes::Equals(const FontAttributes& fa) const
{
  if (family == NULL && fa.family != NULL) return false;
  if (family != NULL && fa.family == NULL) return false;
  if (family != NULL && fa.family != NULL && strcmp(family, fa.family)) return false;
  if (style != fa.style) return false;
  if (weight != fa.weight) return false;
  if (mode != fa.mode) return false;
  if (size.IsNull() && !fa.size.IsNull()) return false;
  if (!size.IsNull() && fa.size.IsNull()) return false;
  if (!size.IsNull() && !fa.size.IsNull() && !scaledEq(size.ToScaledPoints(), fa.size.ToScaledPoints())) return false;

  return true;
}

unsigned
FontAttributes::Compare(const FontAttributes& fa) const
{
  unsigned eval = 0;

  if (mode != FONT_MODE_ANY && fa.mode != FONT_MODE_ANY && mode != fa.mode) return 0;

  if (!HasFamily() && !fa.HasFamily()) eval += 2;
  else if (HasFamily() && fa.HasFamily()) {
    if (strcmp(family, fa.family)) return 0;
    else eval += 2;
  } else eval++;

  if (!HasStyle() && !fa.HasStyle()) eval += 2;
  else if (HasStyle() && fa.HasStyle()) {
    if (style == fa.style) eval += 2;
  } else eval++;

  if (!HasWeight() && !fa.HasWeight()) eval += 2;
  else if (HasWeight() && fa.HasWeight()) {
    if (weight == fa.weight) eval += 2;
  } else eval++;

  if (!HasSize() && !fa.HasSize()) eval += 2;
  else if (HasSize() && fa.HasSize()) {
    if (scaledEq(size.ToScaledPoints(), fa.size.ToScaledPoints())) eval += 2;
  } else eval++;

  return eval;
}

void
FontAttributes::Dump() const
{
  const char* w[] = { "_", "normal", "bold" };
  const char* s[] = { "_", "normal", "bold" };
  const char* m[] = { "*", "text", "math" };

  MathEngine::logger(LOG_DEBUG, "font(%s,%s,%s,%s)",
		     HasFamily() ? family : "_", w[weight + 1], s[style + 1], m[mode]);
}

// ExtraFontAttributes

const char*
ExtraFontAttributes::GetProperty(const char* name) const
{
  assert(name != NULL);

  for (Iterator<ExtraFontAttribute*> i(content); i.More(); i.Next()) {
    assert(i() != NULL);
    assert(i()->name != NULL);
    assert(i()->value != NULL);
    if (!strcmp(i()->name, name)) return i()->value;
  }

  return NULL;
}

void
ExtraFontAttributes::AddProperty(const char* name, const char* value)
{
  assert(name != NULL);
  assert(value != NULL);

  ExtraFontAttribute* attribute = new ExtraFontAttribute;
  attribute->name = name;
  attribute->value = value;

  content.Append(attribute);
}
