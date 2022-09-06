// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: M5Stack

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Logo;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Htop;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label6;
lv_obj_t * ui_labelCharge;
lv_obj_t * ui_labelDischarge;
lv_obj_t * ui_labelVoltage;
lv_obj_t * ui_labelVbus;
lv_obj_t * ui_labelIbus;

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
        _ui_screen_change(ui_Htop, LV_SCR_LOAD_ANIM_FADE_ON, 100, 1000);
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
void ui_Htop_screen_init(void)
{

    // ui_Htop

    ui_Htop = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Htop, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, -100);

    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label2, "HTOP");

    // ui_Label3

    ui_Label3 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, 50);
    lv_obj_set_y(ui_Label3, -60);

    lv_obj_set_align(ui_Label3, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label3, "Charge");

    // ui_Label4

    ui_Label4 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, 50);
    lv_obj_set_y(ui_Label4, -30);

    lv_obj_set_align(ui_Label4, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label4, "Discharge");

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 50);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label5, "Voltage");

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 50);
    lv_obj_set_y(ui_Label1, 30);

    lv_obj_set_align(ui_Label1, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label1, "Volatge USB");

    // ui_Label6

    ui_Label6 = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label6, 50);
    lv_obj_set_y(ui_Label6, 60);

    lv_obj_set_align(ui_Label6, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Label6, "USB current");

    // ui_labelCharge

    ui_labelCharge = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_labelCharge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelCharge, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelCharge, -50);
    lv_obj_set_y(ui_labelCharge, -60);

    lv_obj_set_align(ui_labelCharge, LV_ALIGN_RIGHT_MID);

    lv_label_set_text(ui_labelCharge, "Text");

    // ui_labelDischarge

    ui_labelDischarge = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_labelDischarge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelDischarge, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelDischarge, -50);
    lv_obj_set_y(ui_labelDischarge, -30);

    lv_obj_set_align(ui_labelDischarge, LV_ALIGN_RIGHT_MID);

    lv_label_set_text(ui_labelDischarge, "Text");

    // ui_labelVoltage

    ui_labelVoltage = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_labelVoltage, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelVoltage, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelVoltage, -50);
    lv_obj_set_y(ui_labelVoltage, 0);

    lv_obj_set_align(ui_labelVoltage, LV_ALIGN_RIGHT_MID);

    lv_label_set_text(ui_labelVoltage, "Text");

    // ui_labelVbus

    ui_labelVbus = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_labelVbus, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelVbus, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelVbus, -50);
    lv_obj_set_y(ui_labelVbus, 30);

    lv_obj_set_align(ui_labelVbus, LV_ALIGN_RIGHT_MID);

    lv_label_set_text(ui_labelVbus, "Text");

    // ui_labelIbus

    ui_labelIbus = lv_label_create(ui_Htop);

    lv_obj_set_width(ui_labelIbus, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelIbus, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelIbus, -50);
    lv_obj_set_y(ui_labelIbus, 60);

    lv_obj_set_align(ui_labelIbus, LV_ALIGN_RIGHT_MID);

    lv_label_set_text(ui_labelIbus, "Text");

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Logo_screen_init();
    ui_Htop_screen_init();
    lv_disp_load_scr(ui_Logo);
}

