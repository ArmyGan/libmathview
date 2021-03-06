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


#include <String.hh>

typedef struct TableEntry
{
  Char32 normal;
  Char32 variant;
} TableEntry;


static TableEntry bold_table[] =
{
  { 0x00030, 0x1D7CE },
  { 0x00031, 0x1D7CF },
  { 0x00032, 0x1D7D0 },
  { 0x00033, 0x1D7D1 },
  { 0x00034, 0x1D7D2 },
  { 0x00035, 0x1D7D3 },
  { 0x00036, 0x1D7D4 },
  { 0x00037, 0x1D7D5 },
  { 0x00038, 0x1D7D6 },
  { 0x00039, 0x1D7D7 },
  { 0x00041, 0x1D400 },
  { 0x00042, 0x1D401 },
  { 0x00043, 0x1D402 },
  { 0x00044, 0x1D403 },
  { 0x00045, 0x1D404 },
  { 0x00046, 0x1D405 },
  { 0x00047, 0x1D406 },
  { 0x00048, 0x1D407 },
  { 0x00049, 0x1D408 },
  { 0x0004A, 0x1D409 },
  { 0x0004B, 0x1D40A },
  { 0x0004C, 0x1D40B },
  { 0x0004D, 0x1D40C },
  { 0x0004E, 0x1D40D },
  { 0x0004F, 0x1D40E },
  { 0x00050, 0x1D40F },
  { 0x00051, 0x1D410 },
  { 0x00052, 0x1D411 },
  { 0x00053, 0x1D412 },
  { 0x00054, 0x1D413 },
  { 0x00055, 0x1D414 },
  { 0x00056, 0x1D415 },
  { 0x00057, 0x1D416 },
  { 0x00058, 0x1D417 },
  { 0x00059, 0x1D418 },
  { 0x0005A, 0x1D419 },
  { 0x00061, 0x1D41A },
  { 0x00062, 0x1D41B },
  { 0x00063, 0x1D41C },
  { 0x00064, 0x1D41D },
  { 0x00065, 0x1D41E },
  { 0x00066, 0x1D41F },
  { 0x00067, 0x1D420 },
  { 0x00068, 0x1D421 },
  { 0x00069, 0x1D422 },
  { 0x0006A, 0x1D423 },
  { 0x0006B, 0x1D424 },
  { 0x0006C, 0x1D425 },
  { 0x0006D, 0x1D426 },
  { 0x0006E, 0x1D427 },
  { 0x0006F, 0x1D428 },
  { 0x00070, 0x1D429 },
  { 0x00071, 0x1D42A },
  { 0x00072, 0x1D42B },
  { 0x00073, 0x1D42C },
  { 0x00074, 0x1D42D },
  { 0x00075, 0x1D42E },
  { 0x00076, 0x1D42F },
  { 0x00077, 0x1D430 },
  { 0x00078, 0x1D431 },
  { 0x00079, 0x1D432 },
  { 0x0007A, 0x1D433 },
  { 0x00391, 0x1D6A8 },
  { 0x00392, 0x1D6A9 },
  { 0x00393, 0x1D6AA },
  { 0x00394, 0x1D6AB },
  { 0x00395, 0x1D6AC },
  { 0x00396, 0x1D6AD },
  { 0x00397, 0x1D6AE },
  { 0x00398, 0x1D6AF },
  { 0x00399, 0x1D6B0 },
  { 0x0039A, 0x1D6B1 },
  { 0x0039B, 0x1D6B2 },
  { 0x0039C, 0x1D6B3 },
  { 0x0039D, 0x1D6B4 },
  { 0x0039E, 0x1D6B5 },
  { 0x0039F, 0x1D6B6 },
  { 0x003A0, 0x1D6B7 },
  { 0x003A1, 0x1D6B8 },
  { 0x003A3, 0x1D6BA },
  { 0x003A4, 0x1D6BB },
  { 0x003A5, 0x1D6BC },
  { 0x003A6, 0x1D6BD },
  { 0x003A7, 0x1D6BE },
  { 0x003A8, 0x1D6BF },
  { 0x003A9, 0x1D6C0 },
  { 0x003B1, 0x1D6C2 },
  { 0x003B2, 0x1D6C3 },
  { 0x003B3, 0x1D6C4 },
  { 0x003B4, 0x1D6C5 },
  { 0x003B5, 0x1D6C6 },
  { 0x003B6, 0x1D6C7 },
  { 0x003B7, 0x1D6C8 },
  { 0x003B8, 0x1D6C9 },
  { 0x003B9, 0x1D6CA },
  { 0x003BA, 0x1D6CB },
  { 0x003BB, 0x1D6CC },
  { 0x003BC, 0x1D6CD },
  { 0x003BD, 0x1D6CE },
  { 0x003BE, 0x1D6CF },
  { 0x003BF, 0x1D6D0 },
  { 0x003C0, 0x1D6D1 },
  { 0x003C1, 0x1D6D2 },
  { 0x003C2, 0x1D6D3 },
  { 0x003C3, 0x1D6D4 },
  { 0x003C4, 0x1D6D5 },
  { 0x003C5, 0x1D6D6 },
  { 0x003C6, 0x1D6D7 },
  { 0x003C7, 0x1D6D8 },
  { 0x003C8, 0x1D6D9 },
  { 0x003C9, 0x1D6DA },
  { 0x003D1, 0x1D6DD },
  { 0x003D5, 0x1D6DF },
  { 0x003D6, 0x1D6E1 },
  { 0x003F0, 0x1D6DE },
  { 0x003F1, 0x1D6E0 },
  { 0x003F4, 0x1D6B9 },
  { 0x02202, 0x1D6DB },
  { 0x02207, 0x1D6C1 },
  { 0x0220A, 0x1D6DC },
  { 0, 0 }
};

Char32
map_variant_bold
(Char32 ch)
{
  if (ch >= 0x0030 and ch <= 0x0039) return bold_table[ch - 0x0030].variant;
  if (ch >= 0x0041 and ch <= 0x005A) return bold_table[ch - 0x0037].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return bold_table[ch - 0x003D].variant;
  if (ch >= 0x0391 and ch <= 0x03A1) return bold_table[ch - 0x0353].variant;
  if (ch >= 0x03A3 and ch <= 0x03A9) return bold_table[ch - 0x0354].variant;
  if (ch >= 0x03B1 and ch <= 0x03C9) return bold_table[ch - 0x035B].variant;
  if (ch == 0x03D1) return 0x1D6DD;
  if (ch >= 0x03D5 and ch <= 0x03D6) return bold_table[ch - 0x0365].variant;
  if (ch >= 0x03F0 and ch <= 0x03F1) return bold_table[ch - 0x037E].variant;
  if (ch == 0x03F4) return 0x1D6B9;
  if (ch == 0x2202) return 0x1D6DB;
  if (ch == 0x2207) return 0x1D6C1;
  if (ch == 0x220A) return 0x1D6DC;
  return ch;
}

static TableEntry italic_table[] =
{
  { 0x00041, 0x1D434 },
  { 0x00042, 0x1D435 },
  { 0x00043, 0x1D436 },
  { 0x00044, 0x1D437 },
  { 0x00045, 0x1D438 },
  { 0x00046, 0x1D439 },
  { 0x00047, 0x1D43A },
  { 0x00048, 0x1D43B },
  { 0x00049, 0x1D43C },
  { 0x0004A, 0x1D43D },
  { 0x0004B, 0x1D43E },
  { 0x0004C, 0x1D43F },
  { 0x0004D, 0x1D440 },
  { 0x0004E, 0x1D441 },
  { 0x0004F, 0x1D442 },
  { 0x00050, 0x1D443 },
  { 0x00051, 0x1D444 },
  { 0x00052, 0x1D445 },
  { 0x00053, 0x1D446 },
  { 0x00054, 0x1D447 },
  { 0x00055, 0x1D448 },
  { 0x00056, 0x1D449 },
  { 0x00057, 0x1D44A },
  { 0x00058, 0x1D44B },
  { 0x00059, 0x1D44C },
  { 0x0005A, 0x1D44D },
  { 0x00061, 0x1D44E },
  { 0x00062, 0x1D44F },
  { 0x00063, 0x1D450 },
  { 0x00064, 0x1D451 },
  { 0x00065, 0x1D452 },
  { 0x00066, 0x1D453 },
  { 0x00067, 0x1D454 },
  { 0x00068, 0x0210E },
  { 0x00069, 0x1D456 },
  { 0x0006A, 0x1D457 },
  { 0x0006B, 0x1D458 },
  { 0x0006C, 0x1D459 },
  { 0x0006D, 0x1D45A },
  { 0x0006E, 0x1D45B },
  { 0x0006F, 0x1D45C },
  { 0x00070, 0x1D45D },
  { 0x00071, 0x1D45E },
  { 0x00072, 0x1D45F },
  { 0x00073, 0x1D460 },
  { 0x00074, 0x1D461 },
  { 0x00075, 0x1D462 },
  { 0x00076, 0x1D463 },
  { 0x00077, 0x1D464 },
  { 0x00078, 0x1D465 },
  { 0x00079, 0x1D466 },
  { 0x0007A, 0x1D467 },
  { 0x00131, 0x1D6A4 },
  { 0x00237, 0x1D6A5 },
  { 0x00391, 0x1D6E2 },
  { 0x00392, 0x1D6E3 },
  { 0x00393, 0x1D6E4 },
  { 0x00394, 0x1D6E5 },
  { 0x00395, 0x1D6E6 },
  { 0x00396, 0x1D6E7 },
  { 0x00397, 0x1D6E8 },
  { 0x00398, 0x1D6E9 },
  { 0x00399, 0x1D6EA },
  { 0x0039A, 0x1D6EB },
  { 0x0039B, 0x1D6EC },
  { 0x0039C, 0x1D6ED },
  { 0x0039D, 0x1D6EE },
  { 0x0039E, 0x1D6EF },
  { 0x0039F, 0x1D6F0 },
  { 0x003A0, 0x1D6F1 },
  { 0x003A1, 0x1D6F2 },
  { 0x003A3, 0x1D6F4 },
  { 0x003A4, 0x1D6F5 },
  { 0x003A5, 0x1D6F6 },
  { 0x003A6, 0x1D6F7 },
  { 0x003A7, 0x1D6F8 },
  { 0x003A8, 0x1D6F9 },
  { 0x003A9, 0x1D6FA },
  { 0x003B1, 0x1D6FC },
  { 0x003B2, 0x1D6FD },
  { 0x003B3, 0x1D6FE },
  { 0x003B4, 0x1D6FF },
  { 0x003B5, 0x1D700 },
  { 0x003B6, 0x1D701 },
  { 0x003B7, 0x1D702 },
  { 0x003B8, 0x1D703 },
  { 0x003B9, 0x1D704 },
  { 0x003BA, 0x1D705 },
  { 0x003BB, 0x1D706 },
  { 0x003BC, 0x1D707 },
  { 0x003BD, 0x1D708 },
  { 0x003BE, 0x1D709 },
  { 0x003BF, 0x1D70A },
  { 0x003C0, 0x1D70B },
  { 0x003C1, 0x1D70C },
  { 0x003C2, 0x1D70D },
  { 0x003C3, 0x1D70E },
  { 0x003C4, 0x1D70F },
  { 0x003C5, 0x1D710 },
  { 0x003C6, 0x1D711 },
  { 0x003C7, 0x1D712 },
  { 0x003C8, 0x1D713 },
  { 0x003C9, 0x1D714 },
  { 0x003D1, 0x1D717 },
  { 0x003D5, 0x1D719 },
  { 0x003D6, 0x1D71B },
  { 0x003F0, 0x1D718 },
  { 0x003F1, 0x1D71A },
  { 0x003F4, 0x1D6F3 },
  { 0x02202, 0x1D715 },
  { 0x02207, 0x1D6FB },
  { 0x0220A, 0x1D716 },
  { 0, 0 }
};

Char32
map_variant_italic
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return italic_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return italic_table[ch - 0x0047].variant;
  if (ch == 0x0131) return 0x1D6A4;
  if (ch == 0x0237) return 0x1D6A5;
  if (ch >= 0x0391 and ch <= 0x03A1) return italic_table[ch - 0x035B].variant;
  if (ch >= 0x03A3 and ch <= 0x03A9) return italic_table[ch - 0x035C].variant;
  if (ch >= 0x03B1 and ch <= 0x03C9) return italic_table[ch - 0x0363].variant;
  if (ch == 0x03D1) return 0x1D717;
  if (ch >= 0x03D5 and ch <= 0x03D6) return italic_table[ch - 0x036D].variant;
  if (ch >= 0x03F0 and ch <= 0x03F1) return italic_table[ch - 0x0386].variant;
  if (ch == 0x03F4) return 0x1D6F3;
  if (ch == 0x2202) return 0x1D715;
  if (ch == 0x2207) return 0x1D6FB;
  if (ch == 0x220A) return 0x1D716;
  return ch;
}

static TableEntry bold_italic_table[] =
{
  { 0x00041, 0x1D468 },
  { 0x00042, 0x1D469 },
  { 0x00043, 0x1D46A },
  { 0x00044, 0x1D46B },
  { 0x00045, 0x1D46C },
  { 0x00046, 0x1D46D },
  { 0x00047, 0x1D46E },
  { 0x00048, 0x1D46F },
  { 0x00049, 0x1D470 },
  { 0x0004A, 0x1D471 },
  { 0x0004B, 0x1D472 },
  { 0x0004C, 0x1D473 },
  { 0x0004D, 0x1D474 },
  { 0x0004E, 0x1D475 },
  { 0x0004F, 0x1D476 },
  { 0x00050, 0x1D477 },
  { 0x00051, 0x1D478 },
  { 0x00052, 0x1D479 },
  { 0x00053, 0x1D47A },
  { 0x00054, 0x1D47B },
  { 0x00055, 0x1D47C },
  { 0x00056, 0x1D47D },
  { 0x00057, 0x1D47E },
  { 0x00058, 0x1D47F },
  { 0x00059, 0x1D480 },
  { 0x0005A, 0x1D481 },
  { 0x00061, 0x1D482 },
  { 0x00062, 0x1D483 },
  { 0x00063, 0x1D484 },
  { 0x00064, 0x1D485 },
  { 0x00065, 0x1D486 },
  { 0x00066, 0x1D487 },
  { 0x00067, 0x1D488 },
  { 0x00068, 0x1D489 },
  { 0x00069, 0x1D48A },
  { 0x0006A, 0x1D48B },
  { 0x0006B, 0x1D48C },
  { 0x0006C, 0x1D48D },
  { 0x0006D, 0x1D48E },
  { 0x0006E, 0x1D48F },
  { 0x0006F, 0x1D490 },
  { 0x00070, 0x1D491 },
  { 0x00071, 0x1D492 },
  { 0x00072, 0x1D493 },
  { 0x00073, 0x1D494 },
  { 0x00074, 0x1D495 },
  { 0x00075, 0x1D496 },
  { 0x00076, 0x1D497 },
  { 0x00077, 0x1D498 },
  { 0x00078, 0x1D499 },
  { 0x00079, 0x1D49A },
  { 0x0007A, 0x1D49B },
  { 0x00391, 0x1D71C },
  { 0x00392, 0x1D71D },
  { 0x00393, 0x1D71E },
  { 0x00394, 0x1D71F },
  { 0x00395, 0x1D720 },
  { 0x00396, 0x1D721 },
  { 0x00397, 0x1D722 },
  { 0x00398, 0x1D723 },
  { 0x00399, 0x1D724 },
  { 0x0039A, 0x1D725 },
  { 0x0039B, 0x1D726 },
  { 0x0039C, 0x1D727 },
  { 0x0039D, 0x1D728 },
  { 0x0039E, 0x1D729 },
  { 0x0039F, 0x1D72A },
  { 0x003A0, 0x1D72B },
  { 0x003A1, 0x1D72C },
  { 0x003A3, 0x1D72E },
  { 0x003A4, 0x1D72F },
  { 0x003A5, 0x1D730 },
  { 0x003A6, 0x1D731 },
  { 0x003A7, 0x1D732 },
  { 0x003A8, 0x1D733 },
  { 0x003A9, 0x1D734 },
  { 0x003B1, 0x1D736 },
  { 0x003B2, 0x1D737 },
  { 0x003B3, 0x1D738 },
  { 0x003B4, 0x1D739 },
  { 0x003B5, 0x1D73A },
  { 0x003B6, 0x1D73B },
  { 0x003B7, 0x1D73C },
  { 0x003B8, 0x1D73D },
  { 0x003B9, 0x1D73E },
  { 0x003BA, 0x1D73F },
  { 0x003BB, 0x1D740 },
  { 0x003BC, 0x1D741 },
  { 0x003BD, 0x1D742 },
  { 0x003BE, 0x1D743 },
  { 0x003BF, 0x1D744 },
  { 0x003C0, 0x1D745 },
  { 0x003C1, 0x1D746 },
  { 0x003C2, 0x1D747 },
  { 0x003C3, 0x1D748 },
  { 0x003C4, 0x1D749 },
  { 0x003C5, 0x1D74A },
  { 0x003C6, 0x1D74B },
  { 0x003C7, 0x1D74C },
  { 0x003C8, 0x1D74D },
  { 0x003C9, 0x1D74E },
  { 0x003D1, 0x1D751 },
  { 0x003D5, 0x1D753 },
  { 0x003D6, 0x1D755 },
  { 0x003F0, 0x1D752 },
  { 0x003F1, 0x1D754 },
  { 0x003F4, 0x1D72D },
  { 0x02202, 0x1D74F },
  { 0x02207, 0x1D735 },
  { 0x0220A, 0x1D750 },
  { 0, 0 }
};

Char32
map_variant_bold_italic
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return bold_italic_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return bold_italic_table[ch - 0x0047].variant;
  if (ch >= 0x0391 and ch <= 0x03A1) return bold_italic_table[ch - 0x035D].variant;
  if (ch >= 0x03A3 and ch <= 0x03A9) return bold_italic_table[ch - 0x035E].variant;
  if (ch >= 0x03B1 and ch <= 0x03C9) return bold_italic_table[ch - 0x0365].variant;
  if (ch == 0x03D1) return 0x1D751;
  if (ch >= 0x03D5 and ch <= 0x03D6) return bold_italic_table[ch - 0x036F].variant;
  if (ch >= 0x03F0 and ch <= 0x03F1) return bold_italic_table[ch - 0x0388].variant;
  if (ch == 0x03F4) return 0x1D72D;
  if (ch == 0x2202) return 0x1D74F;
  if (ch == 0x2207) return 0x1D735;
  if (ch == 0x220A) return 0x1D750;
  return ch;
}

static TableEntry script_table[] =
{
  { 0x00041, 0x1D49C },
  { 0x00042, 0x0212C },
  { 0x00043, 0x1D49E },
  { 0x00044, 0x1D49F },
  { 0x00045, 0x02130 },
  { 0x00046, 0x02131 },
  { 0x00047, 0x1D4A2 },
  { 0x00048, 0x0210B },
  { 0x00049, 0x02110 },
  { 0x0004A, 0x1D4A5 },
  { 0x0004B, 0x1D4A6 },
  { 0x0004C, 0x02112 },
  { 0x0004D, 0x02133 },
  { 0x0004E, 0x1D4A9 },
  { 0x0004F, 0x1D4AA },
  { 0x00050, 0x1D4AB },
  { 0x00051, 0x1D4AC },
  { 0x00052, 0x0211B },
  { 0x00053, 0x1D4AE },
  { 0x00054, 0x1D4AF },
  { 0x00055, 0x1D4B0 },
  { 0x00056, 0x1D4B1 },
  { 0x00057, 0x1D4B2 },
  { 0x00058, 0x1D4B3 },
  { 0x00059, 0x1D4B4 },
  { 0x0005A, 0x1D4B5 },
  { 0x00061, 0x1D4B6 },
  { 0x00062, 0x1D4B7 },
  { 0x00063, 0x1D4B8 },
  { 0x00064, 0x1D4B9 },
  { 0x00065, 0x0212F },
  { 0x00066, 0x1D4BB },
  { 0x00067, 0x0210A },
  { 0x00068, 0x1D4BD },
  { 0x00069, 0x1D4BE },
  { 0x0006A, 0x1D4BF },
  { 0x0006B, 0x1D4C0 },
  { 0x0006C, 0x02113 },
  { 0x0006D, 0x1D4C2 },
  { 0x0006E, 0x1D4C3 },
  { 0x0006F, 0x02134 },
  { 0x00070, 0x1D4C5 },
  { 0x00071, 0x1D4C6 },
  { 0x00072, 0x1D4C7 },
  { 0x00073, 0x1D4C8 },
  { 0x00074, 0x1D4C9 },
  { 0x00075, 0x1D4CA },
  { 0x00076, 0x1D4CB },
  { 0x00077, 0x1D4CC },
  { 0x00078, 0x1D4CD },
  { 0x00079, 0x1D4CE },
  { 0x0007A, 0x1D4CF },
  { 0, 0 }
};

Char32
map_variant_script
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return script_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return script_table[ch - 0x0047].variant;
  return ch;
}

static TableEntry bold_script_table[] =
{
  { 0x00041, 0x1D4D0 },
  { 0x00042, 0x1D4D1 },
  { 0x00043, 0x1D4D2 },
  { 0x00044, 0x1D4D3 },
  { 0x00045, 0x1D4D4 },
  { 0x00046, 0x1D4D5 },
  { 0x00047, 0x1D4D6 },
  { 0x00048, 0x1D4D7 },
  { 0x00049, 0x1D4D8 },
  { 0x0004A, 0x1D4D9 },
  { 0x0004B, 0x1D4DA },
  { 0x0004C, 0x1D4DB },
  { 0x0004D, 0x1D4DC },
  { 0x0004E, 0x1D4DD },
  { 0x0004F, 0x1D4DE },
  { 0x00050, 0x1D4DF },
  { 0x00051, 0x1D4E0 },
  { 0x00052, 0x1D4E1 },
  { 0x00053, 0x1D4E2 },
  { 0x00054, 0x1D4E3 },
  { 0x00055, 0x1D4E4 },
  { 0x00056, 0x1D4E5 },
  { 0x00057, 0x1D4E6 },
  { 0x00058, 0x1D4E7 },
  { 0x00059, 0x1D4E8 },
  { 0x0005A, 0x1D4E9 },
  { 0x00061, 0x1D4EA },
  { 0x00062, 0x1D4EB },
  { 0x00063, 0x1D4EC },
  { 0x00064, 0x1D4ED },
  { 0x00065, 0x1D4EE },
  { 0x00066, 0x1D4EF },
  { 0x00067, 0x1D4F0 },
  { 0x00068, 0x1D4F1 },
  { 0x00069, 0x1D4F2 },
  { 0x0006A, 0x1D4F3 },
  { 0x0006B, 0x1D4F4 },
  { 0x0006C, 0x1D4F5 },
  { 0x0006D, 0x1D4F6 },
  { 0x0006E, 0x1D4F7 },
  { 0x0006F, 0x1D4F8 },
  { 0x00070, 0x1D4F9 },
  { 0x00071, 0x1D4FA },
  { 0x00072, 0x1D4FB },
  { 0x00073, 0x1D4FC },
  { 0x00074, 0x1D4FD },
  { 0x00075, 0x1D4FE },
  { 0x00076, 0x1D4FF },
  { 0x00077, 0x1D500 },
  { 0x00078, 0x1D501 },
  { 0x00079, 0x1D502 },
  { 0x0007A, 0x1D503 },
  { 0, 0 }
};

Char32
map_variant_bold_script
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return bold_script_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return bold_script_table[ch - 0x0047].variant;
  return ch;
}

static TableEntry fraktur_table[] =
{
  { 0x00041, 0x1D504 },
  { 0x00042, 0x1D505 },
  { 0x00043, 0x0212D },
  { 0x00044, 0x1D507 },
  { 0x00045, 0x1D508 },
  { 0x00046, 0x1D509 },
  { 0x00047, 0x1D50A },
  { 0x00048, 0x0210C },
  { 0x00049, 0x02111 },
  { 0x0004A, 0x1D50D },
  { 0x0004B, 0x1D50E },
  { 0x0004C, 0x1D50F },
  { 0x0004D, 0x1D510 },
  { 0x0004E, 0x1D511 },
  { 0x0004F, 0x1D512 },
  { 0x00050, 0x1D513 },
  { 0x00051, 0x1D514 },
  { 0x00052, 0x0211C },
  { 0x00053, 0x1D516 },
  { 0x00054, 0x1D517 },
  { 0x00055, 0x1D518 },
  { 0x00056, 0x1D519 },
  { 0x00057, 0x1D51A },
  { 0x00058, 0x1D51B },
  { 0x00059, 0x1D51C },
  { 0x0005A, 0x02128 },
  { 0x00061, 0x1D51E },
  { 0x00062, 0x1D51F },
  { 0x00063, 0x1D520 },
  { 0x00064, 0x1D521 },
  { 0x00065, 0x1D522 },
  { 0x00066, 0x1D523 },
  { 0x00067, 0x1D524 },
  { 0x00068, 0x1D525 },
  { 0x00069, 0x1D526 },
  { 0x0006A, 0x1D527 },
  { 0x0006B, 0x1D528 },
  { 0x0006C, 0x1D529 },
  { 0x0006D, 0x1D52A },
  { 0x0006E, 0x1D52B },
  { 0x0006F, 0x1D52C },
  { 0x00070, 0x1D52D },
  { 0x00071, 0x1D52E },
  { 0x00072, 0x1D52F },
  { 0x00073, 0x1D530 },
  { 0x00074, 0x1D531 },
  { 0x00075, 0x1D532 },
  { 0x00076, 0x1D533 },
  { 0x00077, 0x1D534 },
  { 0x00078, 0x1D535 },
  { 0x00079, 0x1D536 },
  { 0x0007A, 0x1D537 },
  { 0, 0 }
};

Char32
map_variant_fraktur
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return fraktur_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return fraktur_table[ch - 0x0047].variant;
  return ch;
}

static TableEntry double_struck_table[] =
{
  { 0x00030, 0x1D7D8 },
  { 0x00031, 0x1D7D9 },
  { 0x00032, 0x1D7DA },
  { 0x00033, 0x1D7DB },
  { 0x00034, 0x1D7DC },
  { 0x00035, 0x1D7DD },
  { 0x00036, 0x1D7DE },
  { 0x00037, 0x1D7DF },
  { 0x00038, 0x1D7E0 },
  { 0x00039, 0x1D7E1 },
  { 0x00041, 0x1D538 },
  { 0x00042, 0x1D539 },
  { 0x00043, 0x02102 },
  { 0x00044, 0x1D53B },
  { 0x00045, 0x1D53C },
  { 0x00046, 0x1D53D },
  { 0x00047, 0x1D53E },
  { 0x00048, 0x0210D },
  { 0x00049, 0x1D540 },
  { 0x0004A, 0x1D541 },
  { 0x0004B, 0x1D542 },
  { 0x0004C, 0x1D543 },
  { 0x0004D, 0x1D544 },
  { 0x0004E, 0x02115 },
  { 0x0004F, 0x1D546 },
  { 0x00050, 0x02119 },
  { 0x00051, 0x0211A },
  { 0x00052, 0x0211D },
  { 0x00053, 0x1D54A },
  { 0x00054, 0x1D54B },
  { 0x00055, 0x1D54C },
  { 0x00056, 0x1D54D },
  { 0x00057, 0x1D54E },
  { 0x00058, 0x1D54F },
  { 0x00059, 0x1D550 },
  { 0x0005A, 0x02124 },
  { 0x00061, 0x1D552 },
  { 0x00062, 0x1D553 },
  { 0x00063, 0x1D554 },
  { 0x00064, 0x1D555 },
  { 0x00065, 0x1D556 },
  { 0x00066, 0x1D557 },
  { 0x00067, 0x1D558 },
  { 0x00068, 0x1D559 },
  { 0x00069, 0x1D55A },
  { 0x0006A, 0x1D55B },
  { 0x0006B, 0x1D55C },
  { 0x0006C, 0x1D55D },
  { 0x0006D, 0x1D55E },
  { 0x0006E, 0x1D55F },
  { 0x0006F, 0x1D560 },
  { 0x00070, 0x1D561 },
  { 0x00071, 0x1D562 },
  { 0x00072, 0x1D563 },
  { 0x00073, 0x1D564 },
  { 0x00074, 0x1D565 },
  { 0x00075, 0x1D566 },
  { 0x00076, 0x1D567 },
  { 0x00077, 0x1D568 },
  { 0x00078, 0x1D569 },
  { 0x00079, 0x1D56A },
  { 0x0007A, 0x1D56B },
  { 0, 0 }
};

Char32
map_variant_double_struck
(Char32 ch)
{
  if (ch >= 0x0030 and ch <= 0x0039) return double_struck_table[ch - 0x0030].variant;
  if (ch >= 0x0041 and ch <= 0x005A) return double_struck_table[ch - 0x0037].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return double_struck_table[ch - 0x003D].variant;
  return ch;
}

static TableEntry bold_fraktur_table[] =
{
  { 0x00041, 0x1D56C },
  { 0x00042, 0x1D56D },
  { 0x00043, 0x1D56E },
  { 0x00044, 0x1D56F },
  { 0x00045, 0x1D570 },
  { 0x00046, 0x1D571 },
  { 0x00047, 0x1D572 },
  { 0x00048, 0x1D573 },
  { 0x00049, 0x1D574 },
  { 0x0004A, 0x1D575 },
  { 0x0004B, 0x1D576 },
  { 0x0004C, 0x1D577 },
  { 0x0004D, 0x1D578 },
  { 0x0004E, 0x1D579 },
  { 0x0004F, 0x1D57A },
  { 0x00050, 0x1D57B },
  { 0x00051, 0x1D57C },
  { 0x00052, 0x1D57D },
  { 0x00053, 0x1D57E },
  { 0x00054, 0x1D57F },
  { 0x00055, 0x1D580 },
  { 0x00056, 0x1D581 },
  { 0x00057, 0x1D582 },
  { 0x00058, 0x1D583 },
  { 0x00059, 0x1D584 },
  { 0x0005A, 0x1D585 },
  { 0x00061, 0x1D586 },
  { 0x00062, 0x1D587 },
  { 0x00063, 0x1D588 },
  { 0x00064, 0x1D589 },
  { 0x00065, 0x1D58A },
  { 0x00066, 0x1D58B },
  { 0x00067, 0x1D58C },
  { 0x00068, 0x1D58D },
  { 0x00069, 0x1D58E },
  { 0x0006A, 0x1D58F },
  { 0x0006B, 0x1D590 },
  { 0x0006C, 0x1D591 },
  { 0x0006D, 0x1D592 },
  { 0x0006E, 0x1D593 },
  { 0x0006F, 0x1D594 },
  { 0x00070, 0x1D595 },
  { 0x00071, 0x1D596 },
  { 0x00072, 0x1D597 },
  { 0x00073, 0x1D598 },
  { 0x00074, 0x1D599 },
  { 0x00075, 0x1D59A },
  { 0x00076, 0x1D59B },
  { 0x00077, 0x1D59C },
  { 0x00078, 0x1D59D },
  { 0x00079, 0x1D59E },
  { 0x0007A, 0x1D59F },
  { 0, 0 }
};

Char32
map_variant_bold_fraktur
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return bold_fraktur_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return bold_fraktur_table[ch - 0x0047].variant;
  return ch;
}

static TableEntry sans_serif_table[] =
{
  { 0x00030, 0x1D7E2 },
  { 0x00031, 0x1D7E3 },
  { 0x00032, 0x1D7E4 },
  { 0x00033, 0x1D7E5 },
  { 0x00034, 0x1D7E6 },
  { 0x00035, 0x1D7E7 },
  { 0x00036, 0x1D7E8 },
  { 0x00037, 0x1D7E9 },
  { 0x00038, 0x1D7EA },
  { 0x00039, 0x1D7EB },
  { 0x00041, 0x1D5A0 },
  { 0x00042, 0x1D5A1 },
  { 0x00043, 0x1D5A2 },
  { 0x00044, 0x1D5A3 },
  { 0x00045, 0x1D5A4 },
  { 0x00046, 0x1D5A5 },
  { 0x00047, 0x1D5A6 },
  { 0x00048, 0x1D5A7 },
  { 0x00049, 0x1D5A8 },
  { 0x0004A, 0x1D5A9 },
  { 0x0004B, 0x1D5AA },
  { 0x0004C, 0x1D5AB },
  { 0x0004D, 0x1D5AC },
  { 0x0004E, 0x1D5AD },
  { 0x0004F, 0x1D5AE },
  { 0x00050, 0x1D5AF },
  { 0x00051, 0x1D5B0 },
  { 0x00052, 0x1D5B1 },
  { 0x00053, 0x1D5B2 },
  { 0x00054, 0x1D5B3 },
  { 0x00055, 0x1D5B4 },
  { 0x00056, 0x1D5B5 },
  { 0x00057, 0x1D5B6 },
  { 0x00058, 0x1D5B7 },
  { 0x00059, 0x1D5B8 },
  { 0x0005A, 0x1D5B9 },
  { 0x00061, 0x1D5BA },
  { 0x00062, 0x1D5BB },
  { 0x00063, 0x1D5BC },
  { 0x00064, 0x1D5BD },
  { 0x00065, 0x1D5BE },
  { 0x00066, 0x1D5BF },
  { 0x00067, 0x1D5C0 },
  { 0x00068, 0x1D5C1 },
  { 0x00069, 0x1D5C2 },
  { 0x0006A, 0x1D5C3 },
  { 0x0006B, 0x1D5C4 },
  { 0x0006C, 0x1D5C5 },
  { 0x0006D, 0x1D5C6 },
  { 0x0006E, 0x1D5C7 },
  { 0x0006F, 0x1D5C8 },
  { 0x00070, 0x1D5C9 },
  { 0x00071, 0x1D5CA },
  { 0x00072, 0x1D5CB },
  { 0x00073, 0x1D5CC },
  { 0x00074, 0x1D5CD },
  { 0x00075, 0x1D5CE },
  { 0x00076, 0x1D5CF },
  { 0x00077, 0x1D5D0 },
  { 0x00078, 0x1D5D1 },
  { 0x00079, 0x1D5D2 },
  { 0x0007A, 0x1D5D3 },
  { 0, 0 }
};

Char32
map_variant_sans_serif
(Char32 ch)
{
  if (ch >= 0x0030 and ch <= 0x0039) return sans_serif_table[ch - 0x0030].variant;
  if (ch >= 0x0041 and ch <= 0x005A) return sans_serif_table[ch - 0x0037].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return sans_serif_table[ch - 0x003D].variant;
  return ch;
}

static TableEntry bold_sans_serif_table[] =
{
  { 0x00030, 0x1D7EC },
  { 0x00031, 0x1D7ED },
  { 0x00032, 0x1D7EE },
  { 0x00033, 0x1D7EF },
  { 0x00034, 0x1D7F0 },
  { 0x00035, 0x1D7F1 },
  { 0x00036, 0x1D7F2 },
  { 0x00037, 0x1D7F3 },
  { 0x00038, 0x1D7F4 },
  { 0x00039, 0x1D7F5 },
  { 0x00041, 0x1D5D4 },
  { 0x00042, 0x1D5D5 },
  { 0x00043, 0x1D5D6 },
  { 0x00044, 0x1D5D7 },
  { 0x00045, 0x1D5D8 },
  { 0x00046, 0x1D5D9 },
  { 0x00047, 0x1D5DA },
  { 0x00048, 0x1D5DB },
  { 0x00049, 0x1D5DC },
  { 0x0004A, 0x1D5DD },
  { 0x0004B, 0x1D5DE },
  { 0x0004C, 0x1D5DF },
  { 0x0004D, 0x1D5E0 },
  { 0x0004E, 0x1D5E1 },
  { 0x0004F, 0x1D5E2 },
  { 0x00050, 0x1D5E3 },
  { 0x00051, 0x1D5E4 },
  { 0x00052, 0x1D5E5 },
  { 0x00053, 0x1D5E6 },
  { 0x00054, 0x1D5E7 },
  { 0x00055, 0x1D5E8 },
  { 0x00056, 0x1D5E9 },
  { 0x00057, 0x1D5EA },
  { 0x00058, 0x1D5EB },
  { 0x00059, 0x1D5EC },
  { 0x0005A, 0x1D5ED },
  { 0x00061, 0x1D5EE },
  { 0x00062, 0x1D5EF },
  { 0x00063, 0x1D5F0 },
  { 0x00064, 0x1D5F1 },
  { 0x00065, 0x1D5F2 },
  { 0x00066, 0x1D5F3 },
  { 0x00067, 0x1D5F4 },
  { 0x00068, 0x1D5F5 },
  { 0x00069, 0x1D5F6 },
  { 0x0006A, 0x1D5F7 },
  { 0x0006B, 0x1D5F8 },
  { 0x0006C, 0x1D5F9 },
  { 0x0006D, 0x1D5FA },
  { 0x0006E, 0x1D5FB },
  { 0x0006F, 0x1D5FC },
  { 0x00070, 0x1D5FD },
  { 0x00071, 0x1D5FE },
  { 0x00072, 0x1D5FF },
  { 0x00073, 0x1D600 },
  { 0x00074, 0x1D601 },
  { 0x00075, 0x1D602 },
  { 0x00076, 0x1D603 },
  { 0x00077, 0x1D604 },
  { 0x00078, 0x1D605 },
  { 0x00079, 0x1D606 },
  { 0x0007A, 0x1D607 },
  { 0x00391, 0x1D756 },
  { 0x00392, 0x1D757 },
  { 0x00393, 0x1D758 },
  { 0x00394, 0x1D759 },
  { 0x00395, 0x1D75A },
  { 0x00396, 0x1D75B },
  { 0x00397, 0x1D75C },
  { 0x00398, 0x1D75D },
  { 0x00399, 0x1D75E },
  { 0x0039A, 0x1D75F },
  { 0x0039B, 0x1D760 },
  { 0x0039C, 0x1D761 },
  { 0x0039D, 0x1D762 },
  { 0x0039E, 0x1D763 },
  { 0x0039F, 0x1D764 },
  { 0x003A0, 0x1D765 },
  { 0x003A1, 0x1D766 },
  { 0x003A3, 0x1D768 },
  { 0x003A4, 0x1D769 },
  { 0x003A5, 0x1D76A },
  { 0x003A6, 0x1D76B },
  { 0x003A7, 0x1D76C },
  { 0x003A8, 0x1D76D },
  { 0x003A9, 0x1D76E },
  { 0x003B1, 0x1D770 },
  { 0x003B2, 0x1D771 },
  { 0x003B3, 0x1D772 },
  { 0x003B4, 0x1D773 },
  { 0x003B5, 0x1D774 },
  { 0x003B6, 0x1D775 },
  { 0x003B7, 0x1D776 },
  { 0x003B8, 0x1D777 },
  { 0x003B9, 0x1D778 },
  { 0x003BA, 0x1D779 },
  { 0x003BB, 0x1D77A },
  { 0x003BC, 0x1D77B },
  { 0x003BD, 0x1D77C },
  { 0x003BE, 0x1D77D },
  { 0x003BF, 0x1D77E },
  { 0x003C0, 0x1D77F },
  { 0x003C1, 0x1D780 },
  { 0x003C2, 0x1D781 },
  { 0x003C3, 0x1D782 },
  { 0x003C4, 0x1D783 },
  { 0x003C5, 0x1D784 },
  { 0x003C6, 0x1D785 },
  { 0x003C7, 0x1D786 },
  { 0x003C8, 0x1D787 },
  { 0x003C9, 0x1D788 },
  { 0x003D1, 0x1D78B },
  { 0x003D5, 0x1D78D },
  { 0x003D6, 0x1D78F },
  { 0x003F0, 0x1D78C },
  { 0x003F1, 0x1D78E },
  { 0x003F4, 0x1D767 },
  { 0x02202, 0x1D789 },
  { 0x02207, 0x1D76F },
  { 0x0220A, 0x1D78A },
  { 0, 0 }
};

Char32
map_variant_bold_sans_serif
(Char32 ch)
{
  if (ch >= 0x0030 and ch <= 0x0039) return bold_sans_serif_table[ch - 0x0030].variant;
  if (ch >= 0x0041 and ch <= 0x005A) return bold_sans_serif_table[ch - 0x0037].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return bold_sans_serif_table[ch - 0x003D].variant;
  if (ch >= 0x0391 and ch <= 0x03A1) return bold_sans_serif_table[ch - 0x0353].variant;
  if (ch >= 0x03A3 and ch <= 0x03A9) return bold_sans_serif_table[ch - 0x0354].variant;
  if (ch >= 0x03B1 and ch <= 0x03C9) return bold_sans_serif_table[ch - 0x035B].variant;
  if (ch == 0x03D1) return 0x1D78B;
  if (ch >= 0x03D5 and ch <= 0x03D6) return bold_sans_serif_table[ch - 0x0365].variant;
  if (ch >= 0x03F0 and ch <= 0x03F1) return bold_sans_serif_table[ch - 0x037E].variant;
  if (ch == 0x03F4) return 0x1D767;
  if (ch == 0x2202) return 0x1D789;
  if (ch == 0x2207) return 0x1D76F;
  if (ch == 0x220A) return 0x1D78A;
  return ch;
}

static TableEntry sans_serif_italic_table[] =
{
  { 0x00041, 0x1D608 },
  { 0x00042, 0x1D609 },
  { 0x00043, 0x1D60A },
  { 0x00044, 0x1D60B },
  { 0x00045, 0x1D60C },
  { 0x00046, 0x1D60D },
  { 0x00047, 0x1D60E },
  { 0x00048, 0x1D60F },
  { 0x00049, 0x1D610 },
  { 0x0004A, 0x1D611 },
  { 0x0004B, 0x1D612 },
  { 0x0004C, 0x1D613 },
  { 0x0004D, 0x1D614 },
  { 0x0004E, 0x1D615 },
  { 0x0004F, 0x1D616 },
  { 0x00050, 0x1D617 },
  { 0x00051, 0x1D618 },
  { 0x00052, 0x1D619 },
  { 0x00053, 0x1D61A },
  { 0x00054, 0x1D61B },
  { 0x00055, 0x1D61C },
  { 0x00056, 0x1D61D },
  { 0x00057, 0x1D61E },
  { 0x00058, 0x1D61F },
  { 0x00059, 0x1D620 },
  { 0x0005A, 0x1D621 },
  { 0x00061, 0x1D622 },
  { 0x00062, 0x1D623 },
  { 0x00063, 0x1D624 },
  { 0x00064, 0x1D625 },
  { 0x00065, 0x1D626 },
  { 0x00066, 0x1D627 },
  { 0x00067, 0x1D628 },
  { 0x00068, 0x1D629 },
  { 0x00069, 0x1D62A },
  { 0x0006A, 0x1D62B },
  { 0x0006B, 0x1D62C },
  { 0x0006C, 0x1D62D },
  { 0x0006D, 0x1D62E },
  { 0x0006E, 0x1D62F },
  { 0x0006F, 0x1D630 },
  { 0x00070, 0x1D631 },
  { 0x00071, 0x1D632 },
  { 0x00072, 0x1D633 },
  { 0x00073, 0x1D634 },
  { 0x00074, 0x1D635 },
  { 0x00075, 0x1D636 },
  { 0x00076, 0x1D637 },
  { 0x00077, 0x1D638 },
  { 0x00078, 0x1D639 },
  { 0x00079, 0x1D63A },
  { 0x0007A, 0x1D63B },
  { 0, 0 }
};

Char32
map_variant_sans_serif_italic
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return sans_serif_italic_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return sans_serif_italic_table[ch - 0x0047].variant;
  return ch;
}

static TableEntry sans_serif_bold_italic_table[] =
{
  { 0x00041, 0x1D63C },
  { 0x00042, 0x1D63D },
  { 0x00043, 0x1D63E },
  { 0x00044, 0x1D63F },
  { 0x00045, 0x1D640 },
  { 0x00046, 0x1D641 },
  { 0x00047, 0x1D642 },
  { 0x00048, 0x1D643 },
  { 0x00049, 0x1D644 },
  { 0x0004A, 0x1D645 },
  { 0x0004B, 0x1D646 },
  { 0x0004C, 0x1D647 },
  { 0x0004D, 0x1D648 },
  { 0x0004E, 0x1D649 },
  { 0x0004F, 0x1D64A },
  { 0x00050, 0x1D64B },
  { 0x00051, 0x1D64C },
  { 0x00052, 0x1D64D },
  { 0x00053, 0x1D64E },
  { 0x00054, 0x1D64F },
  { 0x00055, 0x1D650 },
  { 0x00056, 0x1D651 },
  { 0x00057, 0x1D652 },
  { 0x00058, 0x1D653 },
  { 0x00059, 0x1D654 },
  { 0x0005A, 0x1D655 },
  { 0x00061, 0x1D656 },
  { 0x00062, 0x1D657 },
  { 0x00063, 0x1D658 },
  { 0x00064, 0x1D659 },
  { 0x00065, 0x1D65A },
  { 0x00066, 0x1D65B },
  { 0x00067, 0x1D65C },
  { 0x00068, 0x1D65D },
  { 0x00069, 0x1D65E },
  { 0x0006A, 0x1D65F },
  { 0x0006B, 0x1D660 },
  { 0x0006C, 0x1D661 },
  { 0x0006D, 0x1D662 },
  { 0x0006E, 0x1D663 },
  { 0x0006F, 0x1D664 },
  { 0x00070, 0x1D665 },
  { 0x00071, 0x1D666 },
  { 0x00072, 0x1D667 },
  { 0x00073, 0x1D668 },
  { 0x00074, 0x1D669 },
  { 0x00075, 0x1D66A },
  { 0x00076, 0x1D66B },
  { 0x00077, 0x1D66C },
  { 0x00078, 0x1D66D },
  { 0x00079, 0x1D66E },
  { 0x0007A, 0x1D66F },
  { 0x00391, 0x1D790 },
  { 0x00392, 0x1D791 },
  { 0x00393, 0x1D792 },
  { 0x00394, 0x1D793 },
  { 0x00395, 0x1D794 },
  { 0x00396, 0x1D795 },
  { 0x00397, 0x1D796 },
  { 0x00398, 0x1D797 },
  { 0x00399, 0x1D798 },
  { 0x0039A, 0x1D799 },
  { 0x0039B, 0x1D79A },
  { 0x0039C, 0x1D79B },
  { 0x0039D, 0x1D79C },
  { 0x0039E, 0x1D79D },
  { 0x0039F, 0x1D79E },
  { 0x003A0, 0x1D79F },
  { 0x003A1, 0x1D7A0 },
  { 0x003A3, 0x1D7A2 },
  { 0x003A4, 0x1D7A3 },
  { 0x003A5, 0x1D7A4 },
  { 0x003A6, 0x1D7A5 },
  { 0x003A7, 0x1D7A6 },
  { 0x003A8, 0x1D7A7 },
  { 0x003A9, 0x1D7A8 },
  { 0x003B1, 0x1D7AA },
  { 0x003B2, 0x1D7AB },
  { 0x003B3, 0x1D7AC },
  { 0x003B4, 0x1D7AD },
  { 0x003B5, 0x1D7AE },
  { 0x003B6, 0x1D7AF },
  { 0x003B7, 0x1D7B0 },
  { 0x003B8, 0x1D7B1 },
  { 0x003B9, 0x1D7B2 },
  { 0x003BA, 0x1D7B3 },
  { 0x003BB, 0x1D7B4 },
  { 0x003BC, 0x1D7B5 },
  { 0x003BD, 0x1D7B6 },
  { 0x003BE, 0x1D7B7 },
  { 0x003BF, 0x1D7B8 },
  { 0x003C0, 0x1D7B9 },
  { 0x003C1, 0x1D7BA },
  { 0x003C2, 0x1D7BB },
  { 0x003C3, 0x1D7BC },
  { 0x003C4, 0x1D7BD },
  { 0x003C5, 0x1D7BE },
  { 0x003C6, 0x1D7BF },
  { 0x003C7, 0x1D7C0 },
  { 0x003C8, 0x1D7C1 },
  { 0x003C9, 0x1D7C2 },
  { 0x003D1, 0x1D7C5 },
  { 0x003D5, 0x1D7C7 },
  { 0x003D6, 0x1D7C9 },
  { 0x003F0, 0x1D7C6 },
  { 0x003F1, 0x1D7C8 },
  { 0x003F4, 0x1D7A1 },
  { 0x02202, 0x1D7C3 },
  { 0x02207, 0x1D7A9 },
  { 0x0220A, 0x1D7C4 },
  { 0, 0 }
};

Char32
map_variant_sans_serif_bold_italic
(Char32 ch)
{
  if (ch >= 0x0041 and ch <= 0x005A) return sans_serif_bold_italic_table[ch - 0x0041].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return sans_serif_bold_italic_table[ch - 0x0047].variant;
  if (ch >= 0x0391 and ch <= 0x03A1) return sans_serif_bold_italic_table[ch - 0x035D].variant;
  if (ch >= 0x03A3 and ch <= 0x03A9) return sans_serif_bold_italic_table[ch - 0x035E].variant;
  if (ch >= 0x03B1 and ch <= 0x03C9) return sans_serif_bold_italic_table[ch - 0x0365].variant;
  if (ch == 0x03D1) return 0x1D7C5;
  if (ch >= 0x03D5 and ch <= 0x03D6) return sans_serif_bold_italic_table[ch - 0x036F].variant;
  if (ch >= 0x03F0 and ch <= 0x03F1) return sans_serif_bold_italic_table[ch - 0x0388].variant;
  if (ch == 0x03F4) return 0x1D7A1;
  if (ch == 0x2202) return 0x1D7C3;
  if (ch == 0x2207) return 0x1D7A9;
  if (ch == 0x220A) return 0x1D7C4;
  return ch;
}

static TableEntry monospace_table[] =
{
  { 0x00030, 0x1D7F6 },
  { 0x00031, 0x1D7F7 },
  { 0x00032, 0x1D7F8 },
  { 0x00033, 0x1D7F9 },
  { 0x00034, 0x1D7FA },
  { 0x00035, 0x1D7FB },
  { 0x00036, 0x1D7FC },
  { 0x00037, 0x1D7FD },
  { 0x00038, 0x1D7FE },
  { 0x00039, 0x1D7FF },
  { 0x00041, 0x1D670 },
  { 0x00042, 0x1D671 },
  { 0x00043, 0x1D672 },
  { 0x00044, 0x1D673 },
  { 0x00045, 0x1D674 },
  { 0x00046, 0x1D675 },
  { 0x00047, 0x1D676 },
  { 0x00048, 0x1D677 },
  { 0x00049, 0x1D678 },
  { 0x0004A, 0x1D679 },
  { 0x0004B, 0x1D67A },
  { 0x0004C, 0x1D67B },
  { 0x0004D, 0x1D67C },
  { 0x0004E, 0x1D67D },
  { 0x0004F, 0x1D67E },
  { 0x00050, 0x1D67F },
  { 0x00051, 0x1D680 },
  { 0x00052, 0x1D681 },
  { 0x00053, 0x1D682 },
  { 0x00054, 0x1D683 },
  { 0x00055, 0x1D684 },
  { 0x00056, 0x1D685 },
  { 0x00057, 0x1D686 },
  { 0x00058, 0x1D687 },
  { 0x00059, 0x1D688 },
  { 0x0005A, 0x1D689 },
  { 0x00061, 0x1D68A },
  { 0x00062, 0x1D68B },
  { 0x00063, 0x1D68C },
  { 0x00064, 0x1D68D },
  { 0x00065, 0x1D68E },
  { 0x00066, 0x1D68F },
  { 0x00067, 0x1D690 },
  { 0x00068, 0x1D691 },
  { 0x00069, 0x1D692 },
  { 0x0006A, 0x1D693 },
  { 0x0006B, 0x1D694 },
  { 0x0006C, 0x1D695 },
  { 0x0006D, 0x1D696 },
  { 0x0006E, 0x1D697 },
  { 0x0006F, 0x1D698 },
  { 0x00070, 0x1D699 },
  { 0x00071, 0x1D69A },
  { 0x00072, 0x1D69B },
  { 0x00073, 0x1D69C },
  { 0x00074, 0x1D69D },
  { 0x00075, 0x1D69E },
  { 0x00076, 0x1D69F },
  { 0x00077, 0x1D6A0 },
  { 0x00078, 0x1D6A1 },
  { 0x00079, 0x1D6A2 },
  { 0x0007A, 0x1D6A3 },
  { 0, 0 }
};

Char32
map_variant_monospace
(Char32 ch)
{
  if (ch >= 0x0030 and ch <= 0x0039) return monospace_table[ch - 0x0030].variant;
  if (ch >= 0x0041 and ch <= 0x005A) return monospace_table[ch - 0x0037].variant;
  if (ch >= 0x0061 and ch <= 0x007A) return monospace_table[ch - 0x003D].variant;
  return ch;
}
