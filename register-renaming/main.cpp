#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
	for (size_t i = 0; i < inputCode.size(); i++) {
		cout << inputCode[i] << endl;
	}
	return 0;
}
