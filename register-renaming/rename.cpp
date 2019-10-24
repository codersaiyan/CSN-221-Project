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
	q.push("$p0");
	q.push("$p1");
	q.push("$p2");
	q.push("$p3");
	q.push("$p4");
	q.push("$p5");
	q.push("$p6");
	q.push("$p7");
	q.push("$p8");
	q.push("$p9");
	q.push("$p10");
	q.push("$p11");
	q.push("$p12");
	q.push("$p13");
	q.push("$p14");
	q.push("$p15");
	q.push("$p16");
	return q;
}

string extract(queue<string>& pool) {
	if (pool.empty())
		return "$reg";
	string result = (pool.front());
	pool.pop();
	return result;
}

bool safe(string s) {
	static set<string> safeReg = {"$r0", "$r1", "$r2", "$r3",
								  "$r4", "$r5", "$r6", "$r7"};
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
