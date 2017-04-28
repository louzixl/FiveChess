#pragma once
#include "stdafx.h"

typedef struct tagStep{
	int x;
	int y;
	int color;
} STEP;

typedef struct tagMsgStruct{
	UINT uMsg;
	int x;
	int y;
	int color;
	TCHAR szMsg[128];
} MSGSTRUCT;

// Âä×ÓÏûÏ¢
#define MSG_DROPDOWN     0x00000001