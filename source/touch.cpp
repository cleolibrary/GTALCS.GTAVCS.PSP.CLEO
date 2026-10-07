#include "touch.h"
#include "utils.h"
#include "ui.h"

namespace touch
{

	bool menu_button_state = false;
	uint32_t menu_button_event_time = 0;

	void menu_button_event(bool state)
	{		
		if (menu_button_state != state)
			menu_button_event_time = utils::get_tick_count();
		menu_button_state = state;
	}

	bool menu_button_pressed()
	{
		return menu_button_state;
	}

	bool menu_button_pressed_timed(uint32_t mintime)
	{
		return menu_button_state && menu_button_event_time + mintime <= utils::get_tick_count();
	}

	bool ctrl_state[CTRL_SIZE];
	uint32_t ctrl_disabled[CTRL_SIZE];
	uint32_t ctrl_time[CTRL_SIZE];

	void control_event(ePspControl control, bool state)
	{
		if (ctrl_state[control] != state)
			ctrl_time[control] = utils::get_tick_count();
		if (!state)
			ctrl_disabled[control] = 0;
		ctrl_state[control] = state;
	}

	void psp_input_event(SceCtrlData *pad_data)
	{
		menu_button_event((pad_data->Buttons & PSP_CTRL_START) != 0);
		//if (menu_button_state && !menu_button_pressed_timed(2000))
		//	pad_data->Buttons &= ~(uint32_t)PSP_CTRL_START;

		#define CONTROL_EVENT(control) control_event(CTRL_##control, (pad_data->Buttons & PSP_CTRL_##control) != 0)

		CONTROL_EVENT(SELECT);
		CONTROL_EVENT(UP);
		CONTROL_EVENT(RIGHT);
		CONTROL_EVENT(DOWN);
		CONTROL_EVENT(LEFT);
		CONTROL_EVENT(LTRIGGER);
		CONTROL_EVENT(RTRIGGER);
		CONTROL_EVENT(TRIANGLE);
		CONTROL_EVENT(CIRCLE);  
		CONTROL_EVENT(CROSS);   
		CONTROL_EVENT(SQUARE);
		CONTROL_EVENT(HOLD);

		#undef CONTROL_EVENT

		control_event(CTRL_STICK_UP, pad_data->Ly == 0);
		control_event(CTRL_STICK_DOWN, pad_data->Ly == 255);
		control_event(CTRL_STICK_RIGHT, pad_data->Lx == 255);
		control_event(CTRL_STICK_LEFT, pad_data->Lx == 0);
	}

	bool psp_control_pressed(ePspControl control)
	{
		return uint32_t(control) < CTRL_SIZE && ctrl_state[control] && ctrl_disabled[control] <= utils::get_tick_count();
	}

	bool psp_control_pressed_timed(ePspControl control, uint32_t mintime)
	{
		return uint32_t(control) < CTRL_SIZE && ctrl_state[control] && ctrl_disabled[control] <= utils::get_tick_count() && ctrl_time[control] + mintime <= utils::get_tick_count();
	}

	void psp_control_disable(ePspControl control, uint32_t mintime)
	{
		ctrl_disabled[control] = utils::get_tick_count() + mintime;
	}
}
