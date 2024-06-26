// kana.h - Hiragana and Katakana Unicode characters.
/**
This file is part of KanaChord Keyboard.
 Copyright (C) 2024 Mac A. Cody

 KanaChord Keyboard is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

// Hiragana base table.
//    a       i       u       e       o       n
const uint16_t hiraBase[10][6] =
  {{0x3042, 0x3044, 0x3046, 0x3048, 0x304a, 0x3093},  // vowel
   {0x304b, 0x304d, 0x304f, 0x3051, 0x3053, 0x0000},  // k
   {0x3055, 0x3057, 0x3059, 0x305b, 0x305d, 0x0000},  // s
   {0x305f, 0x3061, 0x3064, 0x3066, 0x3068, 0x0000},  // t
   {0x306a, 0x306b, 0x306c, 0x306d, 0x306e, 0x0000},  // n
   {0x306f, 0x3072, 0x3075, 0x3078, 0x307b, 0x0000},  // h
   {0x307e, 0x307f, 0x3080, 0x3081, 0x3082, 0x0000},  // m
   {0x3084, 0x0000, 0x3086, 0x0000, 0x3088, 0x0000},  // y
   {0x3089, 0x308a, 0x308b, 0x308c, 0x308d, 0x0000},  // r
   {0x308f, 0x0000, 0x0000, 0x0000, 0x3092, 0x0000}}; // w
//    a       i       u       e       o       n

// Hiragana Ten-Ten table.
//    a       i       u       e       o       n
const uint16_t hiraTenTen[10][6] =
  {{0x0000, 0x0000, 0x3094, 0x0000, 0x0000, 0x0000},  // vowel
   {0x304c, 0x304e, 0x3050, 0x3052, 0x3054, 0x0000},  // k
   {0x3056, 0x3058, 0x305a, 0x305c, 0x305e, 0x0000},  // s
   {0x3060, 0x3062, 0x3065, 0x3067, 0x3069, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x3070, 0x3073, 0x3076, 0x3079, 0x307c, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; // w
//    a       i       u       e       o       n

// Hiragana Maru table.
//    a       i       u       e       o       n
const uint16_t hiraMaru[10][6] =
  {{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // vowel
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // k
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // s
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x3071, 0x3074, 0x3077, 0x307a, 0x307d, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; // w
//    a       i       u       e       o       n

// Hiragana Chiisai table.
//    a       i       u       e       o       n
const uint16_t hiraChiisai[10][6] =
  {{0x3041, 0x3043, 0x3045, 0x3047, 0x3049, 0x0000},  // vowel
   {0x3095, 0x0000, 0x0000, 0x3096, 0x0000, 0x0000},  // k
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // s
   {0x0000, 0x0000, 0x3063, 0x0000, 0x0000, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x3083, 0x0000, 0x3085, 0x0000, 0x3087, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x308E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; // w
//    a       i       u       e       o       n

const uint16_t specialHiraBase [2][6] =
  {{0x309d, 0x3033, 0x30fc, 0x3002, 0xff01, 0x3000},
   {0x300c, 0x300d, 0x3010, 0x3011, 0x301c, 0x0000}};

const uint16_t specialHiraTen [2][6] =
  {{0x309e, 0x3034, 0x0000, 0x0000, 0x0000, 0x0000},
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};

const uint16_t specialHiraChi [2][6] =
  {{0x0000, 0x3035, 0x30fb, 0x3001, 0xff1f, 0x2026},
   {0x300e, 0x300f, 0x3008, 0x3009, 0x203b, 0x0000}};

// Katakana base table.
//    a       i       u       e       o       n
const uint16_t kataBase[10][6] =
  {{0x30a2, 0x30a4, 0x30a6, 0x30a8, 0x30aa, 0x30f3},  // vowel
   {0x30ab, 0x30ad, 0x30af, 0x30b1, 0x30b3, 0x0000},  // k
   {0x30b5, 0x30b7, 0x30b9, 0x30bb, 0x30bd, 0x0000},  // s
   {0x30bf, 0x30c1, 0x30c4, 0x30c6, 0x30c8, 0x0000},  // t
   {0x30ca, 0x30cb, 0x30cc, 0x30cd, 0x30ce, 0x0000},  // n
   {0x30cf, 0x30d2, 0x30d5, 0x30d8, 0x30db, 0x0000},  // h
   {0x30de, 0x30df, 0x30e0, 0x30e1, 0x30e2, 0x0000},  // m
   {0x30e4, 0x0000, 0x30e6, 0x0000, 0x30e8, 0x0000},  // y
   {0x30e9, 0x30ea, 0x30eb, 0x30ec, 0x30ed, 0x0000},  // r
   {0x30ef, 0x0000, 0x0000, 0x0000, 0x30f2, 0x0000}}; // w
//    a       i       u       e       o       n

// Katakana Ten-Ten table.
//    a       i       u       e       o       n
const uint16_t kataTenTen[10][6] =
  {{0x0000, 0x0000, 0x30f4, 0x0000, 0x0000, 0x0000},  // vowel
   {0x30ac, 0x30ae, 0x30b0, 0x30b2, 0x30b4, 0x0000},  // k
   {0x30b6, 0x30b8, 0x30ba, 0x30bc, 0x30be, 0x0000},  // s
   {0x30c0, 0x30c2, 0x30c5, 0x30c7, 0x30c9, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x30d0, 0x30d3, 0x30d6, 0x30d9, 0x30dc, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x30f7, 0x0000, 0x0000, 0x0000, 0x30fa, 0x0000}}; // w
//    a       i       u       e       o       n

// Katakana Maru table.
//    a       i       u       e       o       n
const uint16_t kataMaru[10][6] =
  {{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // vowel
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // k
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // s
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x30d1, 0x30d4, 0x30d7, 0x30da, 0x30dd, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; // w
//    a       i       u       e       o       n

// Katakana Chiisai table.
//    a       i       u       e       o       n
const uint16_t kataChiisai[10][6] =
  {{0x30a1, 0x30a3, 0x30a5, 0x30a7, 0x30a9, 0x0000},  // vowel
   {0x30f5, 0x0000, 0x0000, 0x30f6, 0x0000, 0x0000},  // k
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // s
   {0x0000, 0x0000, 0x30c3, 0x0000, 0x0000, 0x0000},  // t
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // n
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // h
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // m
   {0x30e3, 0x0000, 0x30e5, 0x0000, 0x30e7, 0x0000},  // y
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // r
   {0x30ee, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; // w
//    a       i       u       e       o       n

const uint16_t specialKataBase [2][6] =
  {{0x30fd, 0x3033, 0x30fc, 0x3002, 0xff01, 0x3000},
   {0x300c, 0x300d, 0x3010, 0x3011, 0x301c, 0x0000}};

const uint16_t specialKataTen [2][6] =
  {{0x30fe, 0x3034, 0x0000, 0x0000, 0x0000, 0x0000},
   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};

const uint16_t specialKataChi [2][6] =
  {{0x0000, 0x3035, 0x30fb, 0x3001, 0xff1f, 0x2026},
   {0x300e, 0x300f, 0x3008, 0x3009, 0x203b, 0x0000}};
