#include "Script.h"

Script::Script()
{

}

Script::Script(vector<string> input_cmds)
{
	this->cmds = input_cmds;
}

Script::Script(string& inp)
{
	cpp_int length = read_varint(inp);

	cpp_int count = 0;
	while (count < length) {

		string current = inp.substr(0, 1*BYTE_MULTIPLIER);
		inp.erase(0, 2);

		count += 1;
		cpp_int current_byte = cpp_int("0x" + current);

		if (current_byte >= 1 && current_byte <= 75) {
			size_t offset = (size_t)(current_byte * BYTE_MULTIPLIER);

			cmds.push_back(inp.substr(0, offset));
			inp.erase(0, offset);
			count += current_byte;
		}
		else if (current_byte == 76) {
			//OP_PUSHDATA1
			cpp_int data_length = little_endian_to_int(inp.substr(0, 2));
			inp.erase(0, 2);
			size_t offset = (size_t)data_length * BYTE_MULTIPLIER;

			cmds.push_back(inp.substr(0, offset));
			inp.erase(0, offset);
			count += data_length + 1;
		}
		else if (current_byte == 77) {
			//OP_PUSHDATA2
			cpp_int data_length = little_endian_to_int(inp.substr(0, 4));
			inp.erase(0, 4);
			size_t offset = (size_t)data_length * BYTE_MULTIPLIER;

			cmds.push_back(inp.substr(0, offset));
			inp.erase(0, offset);
			count += data_length + 2;
		}
		else {
			stringstream stream;
			stream << hex << current_byte;
			string op_code = stream.str();
			cmds.push_back(op_code);
		}
	}

	if (count != length)
		throw("Parsing failed");
}

string Script::raw_serialize()
{
	string result = "";
	string cmd;
	ofstream out("raw_serial.txt");

	for (int j = 0; j < this->cmds.size(); j++) {
		cmd = this->cmds[j];
		if (is_integer(cmd)) {
			result += byte_to_little_endian(dec_to_hex_byte(cpp_int("0x"+cmd), 1));
		}
		else {
			cpp_int length = cmd.length();
			if (length < 75)					//AMBIGUOUS < 75 INCLUSIVE
				result += byte_to_little_endian(dec_to_hex_byte(length, 1));
			else if(length > 75 && length < 0x100) {
				result += byte_to_little_endian(dec_to_hex_byte(76, 1));
				result += byte_to_little_endian(dec_to_hex_byte(length, 1));
			} else if (length > 0x100 && length <= 520) {
				result += byte_to_little_endian(dec_to_hex_byte(77, 1));
				result += byte_to_little_endian(dec_to_hex_byte(length, 2));
			}
			else {
				throw("Cmd is too Long!!");
			}
			result += cmd;
		}
		out << result <<endl << endl;
		
	}
	out.close();
	return result;
}

string Script::serialize()
{
	string result = this->raw_serialize();
	cpp_int total = result.length()/2;
	cout << "TOTAL : " << total << endl;
	return string(encode_varint(total) + result);
}

Script Script::operator+(Script& operand)
{
	vector<string> result = this->cmds;
	result.insert(result.end(), operand.cmds.begin(), operand.cmds.end());
	return Script(result);
}

bool Script::evaluate(string z)
{
	vector<string> temp_cmds = this->cmds;
	vector<string> stack;
	vector<string> altstack;
	
	while (temp_cmds.size() > 0)
	{
		string cmd = temp_cmds.back(); temp_cmds.pop_back();
		
		if (is_integer(cmd)) {
			int cmd_int = stoi(cmd);

			if (99 <= cmd_int && cmd_int <= 100) {
				if (!Op::OP_CODE_FUNC(cmd_int, stack, altstack, temp_cmds)) {
					cout << "Bad op : " << Op::OP_CODE_NAMES[cmd_int] << endl;
					return false;
				}
			} else if (107 <= cmd_int && cmd_int <= 108) {
				if (!Op::OP_CODE_FUNC(cmd_int, stack, altstack, temp_cmds)) {
					cout << "Bad op : " << Op::OP_CODE_NAMES[cmd_int] << endl;
					return false;
				}
			} else if (172 <= cmd_int && cmd_int <= 175) {
				if (!Op::OP_CODE_FUNC(cmd_int, stack, altstack, temp_cmds, z)) {
					cout << "Bad op : " << Op::OP_CODE_NAMES[cmd_int] << endl;
					return false;
				}
			}
			else {
				if(!Op::OP_CODE_FUNC(cmd_int, stack, altstack, temp_cmds)) {
					cout << "Bad op : " << Op::OP_CODE_NAMES[cmd_int] << endl;
					return false;
				}
			}
		}
		else
			stack.push_back(cmd);
	}
	if (stack.size() == 0)
		return false;
	if (stack.back() == "")
		return false;

	return true;
}