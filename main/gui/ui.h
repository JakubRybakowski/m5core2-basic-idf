// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: M5Stack

#ifndef _M5STACK_UI_H
#define _M5STACK_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

void ui_event_Logo(lv_event_t * e);
extern lv_obj_t * ui_Logo;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Htop;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_labelCharge;
extern lv_obj_t * ui_labelDischarge;
extern lv_obj_t * ui_labelVoltage;
extern lv_obj_t * ui_labelVbus;
extern lv_obj_t * ui_labelIbus;


LV_IMG_DECLARE(ui_img_m5logo2022_png);    // assets/m5logo2022.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
