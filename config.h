/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

//#define TAPPING_FORCE_HOLD  //Mod Tap keyをTap後にすぐにHoldしたときに、Holdとして扱われるようになる。
#define TAPPING_TERM 200    //TapからHoldに切り替わるまでの押下時間(ms)。デフォルト値は200。
//#define RETRO_TAPPING     //TAPPING_TERMを経過しても、他のキーを押していなければTapとして扱われるようになる。
                            //TAPPING_TERMが短くてTapのつもりがHold扱いになってしまう場合の対策になるが、好み次第。

//#difine PERMISSIVE_HOLD//TAPPING_TERM経過前に他のキーを押すと、Holdとして扱われるようになる。
//キーの同時押しが速いひとにおすすめ。
//#define TAPPING_FORCE_HOLD//Mod Tap keyをTap後にすぐにHoldしたときに、Holdとして扱われるようになる。
//#define IGNORE_MOD_TAP_INTERRUPT//Mod Tap keyと通常キーを連続して高速に押したとき、両方のキーをTapとして扱うようになる。

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
