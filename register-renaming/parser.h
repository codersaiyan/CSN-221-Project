#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class OperandType { Register, Other };

class Operand {
   public:
	string name;
	OperandType type;
	Operand(string name);
};

class LineBase {
   public:
	virtual string convert() = 0;
};

class IgnoreLine : public LineBase {
   public:
	string text;
	IgnoreLine(string text);
	string convert() override;
};

class Instruction : public LineBase {
   public:
	string op;
	vector<Operand> operands;
	Instruction(string op, vector<Operand> operands);
	string convert() override;
};

vector<unique_ptr<LineBase>> parse(vector<string>& code);
