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

#ifndef Char_hh
#define Char_hh

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <stddef.h>

#include "keyword.hh"

typedef guint8  Char8;
typedef guint16 Char16;
typedef guint32 Char32;
typedef Char32  Char;

inline bool isPlain(Char ch) { return ch < 0x80; }
inline bool isUnicode16(Char ch) { return ch < 0x10000; }
inline bool isUnicode32(Char ch) { return true; }

Char        getBiggestChar(const Char*, unsigned);
bool 	    isPlain(const char*);
bool 	    isPlain(const char*, unsigned);
bool 	    isPlain(const Char*, unsigned);
bool 	    isPlain(const class String&, unsigned, unsigned);

inline bool isModifier(Char ch) { return ch == 0x2063; }

unsigned    isNonMarkingChar(Char, int* = NULL, BreakId* = NULL);
unsigned    isNonMarkingChar(Char, Char, int* = NULL, BreakId* = NULL);
unsigned    isNonMarkingChar(const class String&, int* = NULL, BreakId* = NULL);
unsigned    isNonMarkingChar(const class String&, unsigned, int* = NULL, BreakId* = NULL);

#endif
