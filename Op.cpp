#include "Op.h"

string encode_num(int num)
{
	if (!num)
		return "";
	int abs_num = abs(num);
	bool is_negative = num < 0;
	string result = "";
	while (abs_num) {
		result.append(to_string(abs_num & 0xff));
		abs_num >>= 8;
	}
	if (result.back() & 0x80) {
		if (is_negative)
			result.append(to_string(0x80));
		else
			result.append(to_string(0));
	}
	else if (is_negative) {
		result.back() = result.back() | 0x80;
	}
	return result;
}

cpp_int decode_num(string element)
{
	if (element == "")
		return 0;
	string big_endian = reverse_byte(element);

	bool is_negative;
	cpp_int result;
	if (stoi(big_endian.substr(0, BYTE_MULTIPLIER)) & 0x80) {
		is_negative = true;
		result = stoi(big_endian.substr(0, BYTE_MULTIPLIER)) & 0x7f;
	}
	else {
		is_negative = false;
		result = stoi(big_endian.substr(0, BYTE_MULTIPLIER));
	}
	for (int j = 2; j < big_endian.length(); j += 2)
	{
		result <<= 8;
		result += stoi(big_endian.substr(j, BYTE_MULTIPLIER));
	}
	if (is_negative)
		return -result;
	else
		return result;
}

bool op_0(vector<string>& stack)
{
	stack.push_back(encode_num(0));
	return true;
}

bool op_1negate(vector<string>& stack)
{
	stack.push_back(encode_num(-1));
	return true;
}

bool op_1(vector<string>& stack)
{
	stack.push_back(encode_num(1));
	return true;
}

bool op_2(vector<string>& stack)
{
	stack.push_back(encode_num(2));
	return true;
}

bool op_3(vector<string>& stack)
{
	stack.push_back(encode_num(3));
	return true;
}

bool op_4(vector<string>& stack)
{
	stack.push_back(encode_num(4));
	return true;
}

bool op_5(vector<string>& stack)
{
	stack.push_back(encode_num(5));
	return true;
}

bool op_6(vector<string>& stack)
{
	stack.push_back(encode_num(6));
	return true;
}

bool op_7(vector<string>& stack)
{
	stack.push_back(encode_num(7));
	return true;
}

bool op_8(vector<string>& stack)
{
	stack.push_back(encode_num(8));
	return true;
}

bool op_9(vector<string>& stack)
{
	stack.push_back(encode_num(9));
	return true;
}

bool op_10(vector<string>& stack)
{
	stack.push_back(encode_num(10));
	return true;
}

bool op_11(vector<string>& stack)
{
	stack.push_back(encode_num(11));
	return true;
}

bool op_12(vector<string>& stack)
{
	stack.push_back(encode_num(12));
	return true;
}

bool op_13(vector<string>& stack)
{
	stack.push_back(encode_num(13));
	return true;
}

bool op_14(vector<string>& stack)
{
	stack.push_back(encode_num(14));
	return true;
}

bool op_15(vector<string>& stack)
{
	stack.push_back(encode_num(15));
	return true;
}

bool op_16(vector<string>& stack)
{
	stack.push_back(encode_num(16));
	return true;
}

bool op_nop(vector<string>& stack)
{
	return true;
}

bool op_if(vector<string>& stack, vector<string> &items)
{
	if (stack.size() < 1)
		return false;
	vector<string> true_items;
	vector<string> false_items;
	vector<string> current_arr = true_items;
	bool found = false;
	int num_endifs_needed = 1;
	while (items.size() > 0) {
		int item = stoi(items.back()); items.pop_back();
		if (99 <= item && item >= 100) {
			num_endifs_needed++;
			current_arr.push_back(to_string(item));
		}
		else if (num_endifs_needed == 1 && item == 103)
			current_arr = false_items;
		else if (item == 104) {
			if (num_endifs_needed == 1) {
				found = true;
				break;
			}
			else {
				num_endifs_needed--;
				current_arr.push_back(to_string(item));
			}
		}
		else {
			current_arr.push_back(to_string(item));
		}
	}
	if (!found)
		return false;
	string element = stack.back();
	vector<string> result;

	if (decode_num(element) == 0)
		result.insert(result.begin(), false_items.begin(), false_items.end());
	else
		result.insert(result.begin(), true_items.begin(), true_items.end());

	result.insert(result.end(), items.begin(), items.end());
	items = result;
	return true;
}

bool op_notif(vector<string>& stack, vector<string>& items)
{
	if (stack.size() < 1)
		return false;
	vector<string> true_items;
	vector<string> false_items;
	vector<string> current_arr = true_items;
	bool found = false;
	int num_endifs_needed = 1;
	while (items.size() > 0) {
		int item = stoi(items.back()); items.pop_back();
		if (99 <= item && item >= 100) {
			num_endifs_needed++;
			current_arr.push_back(to_string(item));
		}
		else if (num_endifs_needed == 1 && item == 103)
			current_arr = false_items;
		else if (item == 104) {
			if (num_endifs_needed == 1) {
				found = true;
				break;
			}
			else {
				num_endifs_needed--;
				current_arr.push_back(to_string(item));
			}
		}
		else {
			current_arr.push_back(to_string(item));
		}
	}
	if (!found)
		return false;
	string element = stack.back();
	vector<string> result;

	if (decode_num(element) == 0)
		result.insert(result.begin(), true_items.begin(), true_items.end());
	else
		result.insert(result.begin(), false_items.begin(), false_items.end());

	result.insert(result.end(), items.begin(), items.end());
	items = result;
	return true;
}

bool op_verify(vector<string>& stack)
{
	if (stack.size() < 1)
		return false;
	string element = stack.back(); stack.pop_back();
	if (decode_num(element) == 0)
		return false;
	return true;
}

bool op_return(vector<string>& stack)
{
	return false;
}

bool op_toaltstack(vector<string>& stack, vector<string>& altstack)
{
	if (stack.size() < 1)
		return false;
	altstack.push_back(stack.back()); stack.pop_back();
	return true;
}

bool op_fromaltstack(vector<string>& stack, vector<string>& altstack)
{
	if (stack.size() < 1)
		return false;
	stack.push_back(altstack.back()); altstack.pop_back();
	return true;
}

bool op_2drop(vector<string> &stack)
{
	if (stack.size() < 2)
		return false;
	stack.pop_back();
	stack.pop_back();
	return true;
}

bool op_dup(vector<string> &stack)
{
	if (stack.size() < 1)
		return false;
	stack.push_back(stack.back());
	return true;
}

bool op_2dup(vector<string> &stack)
{
	if (stack.size() < 2)
		return false;
	string first_elem = stack.end()[-2];
	string last_elem = stack.back();
	stack.push_back(first_elem);
	stack.push_back(last_elem);
	return true;
}

bool op_3dup(vector<string> &stack)
{
	if (stack.size() < 3)
		return false;
	string first_elem = stack.end()[-3];
	string second_elem = stack.end()[-2];
	string last_elem = stack.back();
	stack.push_back(first_elem);
	stack.push_back(second_elem);
	stack.push_back(last_elem);
	return true;
}

bool op_2over(vector<string>& stack)
{
	if (stack.size() < 2)
		return false;
	string first_elem = stack.end()[-4];
	string last_elem = stack.end()[-3];
	stack.push_back(first_elem);
	stack.push_back(last_elem);
	return true;
}

bool op_hash256(vector<string> stack)
{
	if (stack.size() < 1)
		return false;
	stack.back() = hash256(stack.back());
	return true;
}

bool Op::OP_CODE_FUNC(int cmd, vector<string>& stack, vector<string> &altstack, vector<string> cmds, string z)
{
	switch (cmd)
	{
	case 0:
		op_0(stack);
		break;
	case 79:
		op_1negate(stack);
		break;
	case 81:
		op_1(stack);
		break;
	case 82:
		op_2(stack);
		break;
	case 83:
		op_3(stack);
		break;
	case 84:
		op_4(stack);
		break;
	case 85:
		op_5(stack);
		break;
	case 86:
		op_6(stack);
		break;
	case 87:
		op_7(stack);
		break;
	case 88:
		op_8(stack);
		break;
	case 89:
		op_9(stack);
		break;
	case 90:
		op_10(stack);
	case 91:
		op_11(stack);
		break;
	case 92:
		op_12(stack);
		break;
	case 93:
		op_13(stack);
		break;
	case 94:
		op_14(stack);
		break;
	case 95:
		op_15(stack);
		break;
	case 96:
		op_16(stack);
		break;
	case 97:
		op_nop(stack);
		break;
	/*case 99:
		op_if(stack);
		break;
	case 100:
		op_notif(stack);
		break;*/
	case 105:
		op_verify(stack);
		break;
	case 106:
		op_return(stack);
		break;
	//case 107:
	//	op_toaltstack(stack);
	//	break;
	//case 108:
	//	op_fromaltstack(stack);
	//	break;
	case 109:
		op_2drop(stack);
		break;
	case 110:
		op_2dup(stack);
		break;
	case 111:
		op_3dup(stack);
		break;
	case 112:
		op_2over(stack);
		break;
	//case 113:
	//	op_2rot(stack);
	//	break;
	//case 114:
	//	op_2swap(stack);
	//	break;
	//case 115:
	//	op_ifdup(stack);
	//	break;
	//case:
	//	op_(stack);
	//	break;
	//case 81:
	//	op_1(stack);
	//	break;
	default:
		break;
	}
	return false;
}

map<int, string> Op::OP_CODE_NAMES = {
	{0, "OP_0"},
	{76, "OP_PUSHDATA1"},
	{77, "OP_PUSHDATA2"},
	{78, "OP_PUSHDATA4"},
	{79, "OP_1NEGATE"},
	{81, "OP_1"},
	{82, "OP_2"},
	{83, "OP_3"},
	{84, "OP_4"},
	{85, "OP_5"},
	{86, "OP_6"},
	{87, "OP_7"},
	{88, "OP_8"},
	{89, "OP_9"},
	{90, "OP_10"},
	{91, "OP_11"},
	{92, "OP_12"},
	{93, "OP_13"},
	{94, "OP_14"},
	{95, "OP_15"},
	{96, "OP_16"},
	{97, "OP_NOP"},
	{99, "OP_IF"},
	{100, "OP_NOTIF"},
	{103, "OP_ELSE"},
	{104, "OP_ENDIF"},
	{105, "OP_VERIFY"},
	{106, "OP_RETURN"},
	{107, "OP_TOALTSTACK"},
	{108, "OP_FROMALTSTACK"},
	{109, "OP_2DROP"},
	{110, "OP_2DUP"},
	{111, "OP_3DUP"},
	{112, "OP_2OVER"},
	{113, "OP_2ROT"},
	{114, "OP_2SWAP"},
	{115, "OP_IFDUP"},
	{116, "OP_DEPTH"},
	{117, "OP_DROP"},
	{118, "OP_DUP"},
	{119, "OP_NIP"},
	{120, "OP_OVER"},
	{121, "OP_PICK"},
	{122, "OP_ROLL"},
	{123, "OP_ROT"},
	{124, "OP_SWAP"},
	{125, "OP_TUCK"},
	{130, "OP_SIZE"},
	{135, "OP_EQUAL"},
	{136, "OP_EQUALVERIFY"},
	{139, "OP_1ADD"},
	{140, "OP_1SUB"},
	{143, "OP_NEGATE"},
	{144, "OP_ABS"},
	{145, "OP_NOT"},
	{146, "OP_0NOTEQUAL"},
	{147, "OP_ADD"},
	{148, "OP_SUB"},
	{149, "OP_MUL"},
	{154, "OP_BOOLAND"},
	{155, "OP_BOOLOR"},
	{156, "OP_NUMEQUAL"},
	{157, "OP_NUMEQUALVERIFY"},
	{158, "OP_NUMNOTEQUAL"},
	{159, "OP_LESSTHAN"},
	{160, "OP_GREATERTHAN"},
	{161, "OP_LESSTHANOREQUAL"},
	{162, "OP_GREATERTHANOREQUAL"},
	{163, "OP_MIN"},
	{164, "OP_MAX"},
	{165, "OP_WITHIN"},
	{166, "OP_RIPEMD160"},
	{167, "OP_SHA1"},
	{168, "OP_SHA256"},
	{169, "OP_HASH160"},
	{170, "OP_HASH256"},
	{171, "OP_CODESEPARATOR"},
	{172, "OP_CHECKSIG"},
	{173, "OP_CHECKSIGVERIFY"},
	{174, "OP_CHECKMULTISIG"},
	{175, "OP_CHECKMULTISIGVERIFY"},
	{176, "OP_NOP1"},
	{177, "OP_CHECKLOCKTIMEVERIFY"},
	{178, "OP_CHECKSEQUENCEVERIFY"},
	{179, "OP_NOP4"},
	{180, "OP_NOP5"},
	{181, "OP_NOP6"},
	{182, "OP_NOP7"},
	{183, "OP_NOP8"},
	{184, "OP_NOP9"},
	{185, "OP_NOP10"}
};