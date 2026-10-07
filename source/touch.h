#pragma once

#include "common.h"


enum ePspControl
{
	CTRL_SELECT,
	CTRL_UP,
	CTRL_RIGHT,
	CTRL_DOWN,
	CTRL_LEFT,
	CTRL_LTRIGGER,
	CTRL_RTRIGGER,
	CTRL_TRIANGLE,
	CTRL_CIRCLE,  
	CTRL_CROSS,   
	CTRL_SQUARE,
	CTRL_HOLD,

	CTRL_STICK_UP,
	CTRL_STICK_DOWN,
	CTRL_STICK_RIGHT,
	CTRL_STICK_LEFT,

	CTRL_SIZE
};


namespace touch
{
	void psp_input_event(SceCtrlData *pad_data);
	bool psp_control_pressed(ePspControl control);
	bool psp_control_pressed_timed(ePspControl control, uint32_t mintime);
	void psp_control_disable(ePspControl control, uint32_t mintime);
	void menu_button_event(bool state);
	bool menu_button_pressed();
	bool menu_button_pressed_timed(uint32_t mintime);
}
