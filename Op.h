#pragma once

#ifndef OP_H
#define OP_H
#include "Helper.h"

#include <map>

class Script;

class Op
{
public:
	static bool OP_CODE_FUNC(int cmd, vector<string> &stack, vector<string> &altstack, vector<string> cmds, string z = 0);
	static Script p2pkh_script(string h160);
	static map<int, string> OP_CODE_NAMES;
private:
	Op();
};

#include "Script.h"

#endif // !OP_H