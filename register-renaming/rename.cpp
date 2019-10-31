#include "rename.h"
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "parser.h"

using namespace std;

queue<string> registerPool() {
	queue<string> q;
	q.push("$t0");
	q.push("$t1");
	q.push("$t2");
	q.push("$t3");
	q.push("$t4");
	q.push("$t5");
	q.push("$t6");
	q.push("$t7");
	q.push("$t8");
	q.push("$t9");
	return q;
}

string extract(queue<string>& pool) {
	if (pool.empty())
		return "$s0";
	string result = (pool.front());
	pool.pop();
	return result;
}

bool safe(string s) {
	static set<string> safeReg = {"$t0", "$t1", "$t2", "$t3",
								  "$t4", "$t5"};
	return (safeReg.find(s) != safeReg.end());
}

void renameRegisters(vector<unique_ptr<LineBase>>& code) {
	queue<string> pool = registerPool();
	unordered_map<string, string> mapping;
	for (size_t i = 0; i < code.size(); i++) {
		Instruction* inst = dynamic_cast<Instruction*>(code[i].get());
		if (inst) {
			vector<Operand>& operands = inst->operands;
			if (operands.size() == 0)
				continue;

			for (size_t i = 1; i < operands.size(); i++) {
				Operand& o = operands[i];
				if (safe(o.name)) {
					if (mapping.find(o.name) == mapping.end())
						mapping[o.name] = extract(pool);
					o.name = mapping[o.name];
				}
			}

			Operand& o = operands[0];
			if (safe(o.name)) {
				string newReg = extract(pool);
				if (mapping.find(o.name) != mapping.end()) {
					pool.push(mapping[o.name]);
				}
				mapping[o.name] = newReg;
				o.name = mapping[o.name];
			}
		}
	}
}
