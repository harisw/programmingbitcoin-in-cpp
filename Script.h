#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H

#include "Helper.h"

class Script
{
private:
	string cmds;
public:
	Script();
	Script(string &inp_cmds);
	string raw_serialize();
	string serialize();
};

#endif // !SCRIPT_H