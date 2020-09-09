#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H
#include "Op.h"

class Script
{
private:
	vector<string> cmds;
public:
	Script();
	Script(vector<string> input_cmds);
	Script(string &inp_cmds);
	string raw_serialize();
	string serialize();
	Script operator+(Script& operand);
	bool evaluate(string z);
};

#endif // !SCRIPT_H