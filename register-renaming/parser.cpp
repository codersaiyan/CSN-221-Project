#include "parser.h"
#include <iostream>
#include <set>
#include <sstream>

set<string> supportedInstructions() {
	return {"move", "la",  "li",  "lw",  "lb",  "sw",
			"add",  "sub", "mul", "div", "sll", "sllv",
			"addi", "mult", "srl"};
}

void trim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
	str.erase(0, str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars) + 1);
}

bool isRegister(string& name) {
	return (name[0] == '$');
}

Operand::Operand(string name) : name(name) {
	type = isRegister(name) ? OperandType::Register : OperandType::Other;
}

IgnoreLine::IgnoreLine(string text) : text(text) {}

Instruction::Instruction(string op, vector<Operand> operands)
	: op(op), operands(operands) {}

string IgnoreLine::convert() {
	return text;
}

string Instruction::convert() {
	stringstream ss;
	ss << op << " ";
	for (size_t i = 0; i < operands.size(); i++) {
		ss << operands[i].name;
		if (i != operands.size() - 1)
			ss << ",";
	}
	return ss.str();
}

vector<unique_ptr<LineBase>> parse(vector<string>& code) {
	vector<unique_ptr<LineBase>> result;
	auto opSyntax = supportedInstructions();
	for (size_t i = 0; i < code.size(); i++) {
		stringstream ss(code[i]);
		string op;
		ss >> op;
		if (opSyntax.find(op) != opSyntax.end()) {
			string operand;
			vector<Operand> vec;
			while (getline(ss, operand, ',')) {
				trim(operand);
				vec.push_back(Operand(operand));
			}
			result.push_back(unique_ptr<LineBase>(new Instruction(op, vec)));
		} else {
			result.push_back(unique_ptr<LineBase>(new IgnoreLine(code[i])));
		}
	}
	return result;
}
