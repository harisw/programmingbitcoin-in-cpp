#include "Script.h"

Script::Script()
{
}

Script::Script(string& inp)
{
	cpp_int length = read_varint(inp);

	vector<string> cmds;
	cpp_int count = 0;
	cout << "Script Length : " << length << endl;
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
			count += data_length + 2;
		}
		else if (current_byte == 77) {
			//OP_PUSHDATA2
			cpp_int data_length = little_endian_to_int(inp.substr(0, 4));
			inp.erase(0, 4);
			size_t offset = (size_t)data_length * BYTE_MULTIPLIER;

			cmds.push_back(inp.substr(0, offset));
			inp.erase(0, offset);
			count += data_length + 4;
		}
		else {
			stringstream stream;
			stream << hex << current_byte;
			string op_code = stream.str();
			cmds.push_back(op_code);
		}
	}
	cout << "COUNT = " << count << endl;
	cout << "LENGTH = " << length << endl;
	if (count != length)
		throw("Parsing failed");
}

string Script::raw_serialize()
{
	string result = "";
	for (int j = 0; j < this->cmds.size(); j++) {
		cout << "CMD : " << this->cmds[j] << endl;
	}
	return string();
}

string Script::serialize()
{
	string result = this->raw_serialize();
	cpp_int total = result.length();
	return string(encode_varint(total) + result);
}
