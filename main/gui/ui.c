// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: M5Stack

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Logo;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Button1;
lv_obj_t * ui_Button2;
lv_obj_t * ui_Slider1;
lv_obj_t * ui_Roller1;
lv_obj_t * ui_Roller2;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Button3;
lv_obj_t * ui_Button4;
lv_obj_t * ui_Dropdown1;
lv_obj_t * ui_Spinner1;
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Button5;
lv_obj_t * ui_Button6;
lv_obj_t * ui_Colorwheel2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_Logo(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 1000);
    }
}
static void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_Button2(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_Button3(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_Button4(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_Button5(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_Button6(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Logo_screen_init(void)
{

    // ui_Logo

    ui_Logo = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Logo, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Logo, ui_event_Logo, LV_EVENT_ALL, NULL);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_Logo);
    lv_img_set_src(ui_Image1, &ui_img_m5logo2022_png);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, 0);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

}
void ui_Screen1_screen_init(void)
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Button1

    ui_Button1 = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_Button1, 40);
    lv_obj_set_height(ui_Button1, 40);

    lv_obj_set_x(ui_Button1, -140);
    lv_obj_set_y(ui_Button1, 0);

    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

    // ui_Button2

    ui_Button2 = lv_btn_create(ui_Screen1);

    lv_obj_set_width(ui_Button2, 40);
    lv_obj_set_height(ui_Button2, 40);

    lv_obj_set_x(ui_Button2, 140);
    lv_obj_set_y(ui_Button2, 0);

    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button2, ui_event_Button2, LV_EVENT_ALL, NULL);

    // ui_Slider1

    ui_Slider1 = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_Slider1, 0, 100);

    lv_obj_set_width(ui_Slider1, 150);
    lv_obj_set_height(ui_Slider1, 10);

    lv_obj_set_x(ui_Slider1, 0);
    lv_obj_set_y(ui_Slider1, 85);

    lv_obj_set_align(ui_Slider1, LV_ALIGN_CENTER);

    // ui_Roller1

    ui_Roller1 = lv_roller_create(ui_Screen1);
    lv_roller_set_options(ui_Roller1, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_height(ui_Roller1, 100);
    lv_obj_set_width(ui_Roller1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller1, 60);
    lv_obj_set_y(ui_Roller1, 0);

    lv_obj_set_align(ui_Roller1, LV_ALIGN_CENTER);

    // ui_Roller2

    ui_Roller2 = lv_roller_create(ui_Screen1);
    lv_roller_set_options(ui_Roller2, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_height(ui_Roller2, 100);
    lv_obj_set_width(ui_Roller2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller2, -60);
    lv_obj_set_y(ui_Roller2, 0);

    lv_obj_set_align(ui_Roller2, LV_ALIGN_CENTER);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, -80);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "TEST");

}
void ui_Screen2_screen_init(void)
{

    // ui_Screen2

    ui_Screen2 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Button3

    ui_Button3 = lv_btn_create(ui_Screen2);

    lv_obj_set_width(ui_Button3, 40);
    lv_obj_set_height(ui_Button3, 40);

    lv_obj_set_x(ui_Button3, -140);
    lv_obj_set_y(ui_Button3, 0);

    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button3, ui_event_Button3, LV_EVENT_ALL, NULL);

    // ui_Button4

    ui_Button4 = lv_btn_create(ui_Screen2);

    lv_obj_set_width(ui_Button4, 40);
    lv_obj_set_height(ui_Button4, 40);

    lv_obj_set_x(ui_Button4, 140);
    lv_obj_set_y(ui_Button4, 0);

    lv_obj_set_align(ui_Button4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button4, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button4, ui_event_Button4, LV_EVENT_ALL, NULL);

    // ui_Dropdown1

    ui_Dropdown1 = lv_dropdown_create(ui_Screen2);
    lv_dropdown_set_options(ui_Dropdown1, "Option 1\nOption 2\nOption 3");
    lv_dropdown_set_text(ui_Dropdown1, "");

    lv_obj_set_width(ui_Dropdown1, 150);
    lv_obj_set_height(ui_Dropdown1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Dropdown1, 0);
    lv_obj_set_y(ui_Dropdown1, 20);

    lv_obj_set_align(ui_Dropdown1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Dropdown1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_set_style_text_color(ui_Dropdown1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Dropdown1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Spinner1

    ui_Spinner1 = lv_spinner_create(ui_Screen2, 1000, 90);

    lv_obj_set_width(ui_Spinner1, 80);
    lv_obj_set_height(ui_Spinner1, 80);

    lv_obj_set_x(ui_Spinner1, 0);
    lv_obj_set_y(ui_Spinner1, -50);

    lv_obj_set_align(ui_Spinner1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_Spinner1, LV_OBJ_FLAG_CLICKABLE);

}
void ui_Screen3_screen_init(void)
{

    // ui_Screen3

    ui_Screen3 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Button5

    ui_Button5 = lv_btn_create(ui_Screen3);

    lv_obj_set_width(ui_Button5, 40);
    lv_obj_set_height(ui_Button5, 40);

    lv_obj_set_x(ui_Button5, -140);
    lv_obj_set_y(ui_Button5, 0);

    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button5, ui_event_Button5, LV_EVENT_ALL, NULL);

    // ui_Button6

    ui_Button6 = lv_btn_create(ui_Screen3);

    lv_obj_set_width(ui_Button6, 40);
    lv_obj_set_height(ui_Button6, 40);

    lv_obj_set_x(ui_Button6, 140);
    lv_obj_set_y(ui_Button6, 0);

    lv_obj_set_align(ui_Button6, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);

    // ui_Colorwheel2

    ui_Colorwheel2 = lv_colorwheel_create(ui_Screen3, true);

    lv_obj_set_width(ui_Colorwheel2, 200);
    lv_obj_set_height(ui_Colorwheel2, 200);

    lv_obj_set_x(ui_Colorwheel2, 0);
    lv_obj_set_y(ui_Colorwheel2, 0);

    lv_obj_set_align(ui_Colorwheel2, LV_ALIGN_CENTER);

    lv_obj_set_style_arc_width(ui_Colorwheel2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Logo_screen_init();
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    lv_disp_load_scr(ui_Logo);
}

