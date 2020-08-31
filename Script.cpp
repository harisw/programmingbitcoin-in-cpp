#include "Script.h"

Script::Script()
{
}

Script::Script(string& inp)
{
	cpp_int length = read_varint(inp);

	vector<string> cmds;
	cpp_int count = 0;
	//cout << "Script Length : " << length << endl;
	while (count < length) {
		string current = inp.substr(2);
		inp.erase(0, 2);

		count++;
		cpp_int current_byte = cpp_int("0x" + current);

		if (current_byte >= 1 && current_byte <= 75) {
			size_t offset = (size_t)(current_byte * 2);

			cmds.push_back(inp.substr(0, offset));
			inp.erase(0, offset);
			count += offset;
		}
		else if (current_byte == 76) {
			//OP_PUSHDATA1
			cpp_int data_length = little_endian_to_int(inp.substr(2));
			size_t offset = (size_t)data_length;

			cmds.push_back(inp.substr(offset));
			count += (data_length + 2);
		}
		else if (current_byte == 77) {
			//OP_PUSHDATA2
			cpp_int data_length = little_endian_to_int(inp.substr(4));
			size_t offset = (size_t)data_length;

			cmds.push_back(inp.substr(offset));
			count += (data_length + 4);
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

void Script::parse(string& inp)
{

}

string Script::serialize()
{
	return string();
}
