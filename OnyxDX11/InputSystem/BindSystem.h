// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include <map>
#include <string>
#include <Windows.h>

//Additional Virtual Key macroses
#define VK_LEFTCTRL 162
#define VK_RIGHTCTRL 163
#define VK_LEFTALT 164
#define VK_RIGHTALT 165

enum InputCommand
{
	FORWARD = 0,
	LEFTWARD = 1,
	BACKWARD = 2,
	RIGHTWARD = 3,
	SLOWSPEED = 4,
	HIGHSPEED = 5,
	PLAYMODE = 6,
	FULLSCREEN = 7,
	SLOT1 = 8,
	SLOT2 = 9,
};

static const std::map<std::string, InputCommand> InputList =
{
	//STRING		//ENUM
	{"FORWARD",		FORWARD		},
	{"LEFTWARD",	LEFTWARD	},
	{"BACKWARD",	BACKWARD	},
	{"RIGHTWARD",	RIGHTWARD	},
	{"SLOWSPEED",	SLOWSPEED	},
	{"HIGHSPEED",	HIGHSPEED	},
	{"PLAYMODE",	PLAYMODE	},
	{"FULLSCREEN",	FULLSCREEN	},
	{"SLOT1",		SLOT1		},
	{"SLOT2",		SLOT2		},
};

static const std::map<const char*, int> KeyList =
{
	//STRING		//KEY(INT)
	{"LEFTALT",		VK_LEFTALT	},
	{"RIGHTALT",	VK_RIGHTALT	},
	{"LEFTSHIFT",	VK_LSHIFT	},
	{"RIGHTSHIFT",	VK_RSHIFT	},
	{"CAPSLOCK",	VK_CAPITAL	},
	{"ESCAPE",		VK_ESCAPE	},
	{"SPACE",		VK_SPACE	},

};

class BindSystem
{
public:
	BindSystem();
	~BindSystem();

	void CreateBind(InputCommand input_command, char key);
	void CreateBind(InputCommand input_command, int key);
	void CreateBind(int index_command, char key);
	void CreateBind(int index_command, int key);

	int GetKeyByCommand(InputCommand input_command);

	static BindSystem* Get();
	void SetBinds(std::map<int, int> binds);

private:
	std::map<int, int> m_binds;
};