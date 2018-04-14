/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{

	enum E_EVENT_TYPE
	{
		EET_INVALID			= -1,

		EET_LEFT_DOWN		= 0,
		EET_LEFT_UP,
		EET_RIGHT_DOWN,
		EET_RIGHT_UP,
		EET_MIDDLE_DOWN,
		EET_MIDDLE_UP,
		EET_MOVE,

		EET_WHEEL,

		EET_LEFT_CLICK,
		EET_LEFT_SWIPE,
		EET_LEFT_HOLDDRAG,
		EET_RIGHT_HOLDDRAG,

		EET_KEY_DOWN,
		EET_KEY_UP,

        EET_HEAVY_CLICK,
        EET_HEAVY_HOLDDRAG,

		EET_ZOOMIN,
		EET_ZOOMOUT,

		EET_DOUBLE_CLICK,
        
		EET_TOTAL,
	};


	enum E_KEYEVENT_TYPE
	{
		EKET_UNKNOWN,

		EKET_UP,
		EKET_DOWN,
		EKET_LEFT,
		EKET_RIGHT,

		EKET_A,
		EKET_B,
		EKET_C,
		EKET_D,

		EKET_L1,
		EKET_L2,
		EKET_R1,
		EKET_R2,

		EKET_ESCAPE,
		EKET_OK,
		EKET_SELECT,

		EKET_FUNC1,
		EKET_FUNC2,

		// for XY Editor
		EKET_DELETE,
		EKET_FOCUS,

		EKET_COUNT,
	};
}