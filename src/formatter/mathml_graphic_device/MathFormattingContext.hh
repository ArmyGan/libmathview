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

#ifndef __MathFormattingContext_hh__
#define __MathFormattingContext_hh__

#include <string>

#include "scaled.hh"
#include "Length.hh"
#include "RGBColor.hh"
#include "MathVariant.hh"
#include "FormattingContext.hh"

class MathFormattingContext : public FormattingContext
{
public:
  MathFormattingContext(const SmartPtr<class MathGraphicDevice>& d);

  enum PropertyId {
    ZOOM,
    SIZE,
    ACTUAL_SIZE,
    VARIANT,
    COLOR,
    BACKGROUND_COLOR,
    SCRIPT_LEVEL,
    MIN_SIZE,
    DISPLAY_STYLE,
    SIZE_MULT,
    ELEMENT,
    STRETCH_OP,
    STRETCH_TO_WIDTH,
    STRETCH_TO_HEIGHT,
    STRETCH_TO_DEPTH,
    STRETCH_HORIZ,
    STRETCH_VERT,
    NEGATIVE_VERYVERYTHICK_SPACE,
    NEGATIVE_VERYTHICK_SPACE,
    NEGATIVE_THICK_SPACE,
    NEGATIVE_MEDIUM_SPACE,
    NEGATIVE_THIN_SPACE,
    NEGATIVE_VERYTHIN_SPACE,
    NEGATIVE_VERYVERYTHIN_SPACE,
    ZERO_SPACE,
    VERYVERYTHIN_SPACE,
    VERYTHIN_SPACE,
    THIN_SPACE,
    MEDIUM_SPACE,
    THICK_SPACE,
    VERYTHICK_SPACE,
    VERYVERYTHICK_SPACE,
    
    LAST_NAMED_PROPERTY_ENTRY
  };
  
  SmartPtr<class MathGraphicDevice> getDevice(void) const;

  int getZoom(void) const { return get<int>(ZOOM); }
  void setZoom(int n) { set<int>(ZOOM, n); }
  scaled getSize(void) const { return get<scaled>(SIZE) * getZoom() / 100; }
  void setSize(const scaled& s) { set<scaled>(SIZE, s); }
  scaled getActualSize(void) const { return get<scaled>(ACTUAL_SIZE); }
  void setActualSize(const scaled& s) { set<scaled>(ACTUAL_SIZE, s); }
  MathVariant getVariant(void) const { return get<MathVariant>(VARIANT); }
  void setVariant(MathVariant v) { set<MathVariant>(VARIANT, v); }
  RGBColor getColor(void) const { return get<RGBColor>(COLOR); }
  void setColor(const RGBColor& c) { set<RGBColor>(COLOR, c); }
  RGBColor getBackground(void) const { return get<RGBColor>(BACKGROUND_COLOR); }
  void setBackground(const RGBColor& c) { set<RGBColor>(BACKGROUND_COLOR, c); }
  int getScriptLevel(void) const { return get<int>(SCRIPT_LEVEL); }
  void setScriptLevel(int l) { addScriptLevel(l - getScriptLevel()); }
  void addScriptLevel(int);
  scaled getMinSize(void) const { return get<scaled>(MIN_SIZE); }
  void setMinSize(scaled s) { set<scaled>(MIN_SIZE, s); }
  bool getDisplayStyle(void) const { return get<bool>(DISPLAY_STYLE); }
  void setDisplayStyle(bool b) { set<bool>(DISPLAY_STYLE, b); }
  double getSizeMultiplier(void) const { return get<double>(SIZE_MULT); }
  void setSizeMultiplier(double f) { set<double>(SIZE_MULT, f); }
  SmartPtr<class MathMLElement> getElement(void) const { return get<SmartPtr<class MathMLElement> >(ELEMENT); }
  Length getMathSpace(int i) const { return get<Length>(ZERO_SPACE + i); }
  void setMathSpace(int i, const Length& l) { set<Length>(ZERO_SPACE + i, l); }
  SmartPtr<class MathMLElement> getStretchOperator(void) const { return get< SmartPtr<class MathMLElement> >(STRETCH_OP); }
  void setStretchOperator(const SmartPtr<class MathMLElement>& op) { set< SmartPtr<class MathMLElement> >(STRETCH_OP, op); }

  scaled getStretchToWidth(void) const { return get<scaled>(STRETCH_TO_WIDTH); }
  void setStretchToWidth(const scaled& w) { set<scaled>(STRETCH_TO_WIDTH, w); }
  scaled getStretchToHeight(void) const { return get<scaled>(STRETCH_TO_HEIGHT); }
  void setStretchToHeight(const scaled& h) { set<scaled>(STRETCH_TO_HEIGHT, h); }
  scaled getStretchToDepth(void) const { return get<scaled>(STRETCH_TO_DEPTH); }
  void setStretchToDepth(const scaled& d) { set<scaled>(STRETCH_TO_DEPTH, d); }
  scaled getStretchH(void) const { return get<scaled>(STRETCH_HORIZ); }
  void setStretchH(const scaled& h) { set<scaled>(STRETCH_HORIZ, h); }
  scaled getStretchV(void) const { return get<scaled>(STRETCH_VERT); }
  void setStretchV(const scaled& v) { set<scaled>(STRETCH_VERT, v); }

  void push(const SmartPtr<class MathMLElement>& el)
  {
    FormattingContext::push();
    set(ELEMENT, el);
  }
  
private:
  SmartPtr<class MathGraphicDevice> device;
};

#endif // __MathFormattingContext_hh__
