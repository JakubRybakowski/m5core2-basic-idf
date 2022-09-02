// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: M5Stack

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Roller1;
lv_obj_t * ui_Slider3;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Chart2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Roller1

    ui_Roller1 = lv_roller_create(ui_Screen1);
    lv_roller_set_options(ui_Roller1, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_height(ui_Roller1, 100);
    lv_obj_set_width(ui_Roller1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller1, 0);
    lv_obj_set_y(ui_Roller1, 0);

    lv_obj_set_align(ui_Roller1, LV_ALIGN_CENTER);

    // ui_Slider3

    ui_Slider3 = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_Slider3, 0, 100);

    lv_obj_set_width(ui_Slider3, 150);
    lv_obj_set_height(ui_Slider3, 10);

    lv_obj_set_x(ui_Slider3, 0);
    lv_obj_set_y(ui_Slider3, 85);

    lv_obj_set_align(ui_Slider3, LV_ALIGN_CENTER);

}
void ui_Screen2_screen_init(void)
{

    // ui_Screen2

    ui_Screen2 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Chart2

    ui_Chart2 = lv_chart_create(ui_Screen2);

    lv_obj_set_width(ui_Chart2, 180);
    lv_obj_set_height(ui_Chart2, 100);

    lv_obj_set_x(ui_Chart2, 10);
    lv_obj_set_y(ui_Chart2, 10);

    lv_obj_set_align(ui_Chart2, LV_ALIGN_CENTER);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_Screen1);
}

