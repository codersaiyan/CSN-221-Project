#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "parser.h"
#include "rename.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "argument error";
		return -1;
	}
	string inputFileName = string(argv[1]);
	string outputFileName = string(argv[2]);
	cout << "input file:" << inputFileName << endl;
	cout << "output file:" << outputFileName << endl;
	vector<string> inputCode;
	ifstream file(inputFileName);
	if (!file) {
		cout << "error reading input file:" << inputFileName << endl;
		return -1;
	}
	string line;
	while (getline(file, line)) {
		inputCode.push_back(line);
	}
	file.close();
	auto result = parse(inputCode);
	renameRegisters(result);
	ofstream file2(outputFileName);
	if (!file2) {
		cout << "error writing output file:" << outputFileName << endl;
		return -1;
	}
	for (size_t i = 0; i < result.size(); i++) {
		file2 << result[i]->convert() << endl;
	}
	file2.close();
	return 0;
}
