#pragma once
#ifndef OP_H
#define OP_H
#include "Helper.h"
#include <map>
class Op
{
public:
	static bool OP_CODE_FUNC(int cmd, vector<string> &stack, vector<string> &altstack, vector<string> cmds, string z = 0);
	static map<int, string> OP_CODE_NAMES;
private:
	Op();
};

#endif // !OP_H