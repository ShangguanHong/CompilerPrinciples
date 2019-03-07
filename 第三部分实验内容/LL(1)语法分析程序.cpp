#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map> 
using namespace std;

char ch;
string tmp, X;
vector<string> grammar, stack;
map<string, vector<string>> analysisTable;
map<string, int> matchTable;
int idx = 0;

void M() {
	stack.pop_back();
	vector<string> res = analysisTable[X+ch];
	int index = matchTable[X+ch];
	if(res[0][0] >= 'a' && res[0][0] <= 'z') {
		cout << "Error in " << idx << ": ";
		cout << res[0] << endl;
		for(int i = res.size() - 1; i > 0; i --) {
			stack.push_back(res[i]);
		}
	} else {
		cout << grammar[index] << endl;
		if(index != 2 && index != 5) {
			for(int i = res.size() - 1; i > 0; i --) {
				stack.push_back(res[i]);
			}
		}
	}
}

void print() {
	string s;
	for(int i = 0; i < stack.size(); i ++) {
		s += stack[i];
	}
	cout << setw(20) << s;
	s.clear();
	for(int i = idx - 1; i < tmp.size(); i ++) {
		s += tmp[i];
	}
	cout << setw(20) << s;
}

void beginMatch() {
	cout << setw(20) << "stack" << setw(20) << "input" << "action" << endl << endl;
	X = stack.back();
	ch = tmp[idx ++];
	while(X != "$") {
		print();
		if(X[0] == ch) {
			cout << "match:" << ch << endl;
			stack.pop_back();
			ch = tmp[idx ++];
		} else if(X == ")") {
			stack.pop_back();
			cout << "Error in " << idx << ": never \')\'" << endl;
		} else if(ch == ')') {
			cout << "Error in " << idx << ": more \')\'" << endl;
			ch = tmp[idx ++];
		} else {
			M();
		}
		X = stack.back();
	}
	print();
}

void init() {
	ifstream stream;
	stream.open("input.txt");
	if(!stream.is_open()) {
		cout << "Error opening input.txt" << endl;
		exit (1);
	}
	printf("The grammar is as follows :\n");
	while(getline(stream, tmp)) {
		grammar.push_back(tmp);
		cout << tmp << endl;
	}
	stream.close();
	stream.open("FIRST.txt");
	if(!stream.is_open()) {
		cout << "Error opening FIRST.txt" << endl;
		exit (1);
	}
	printf("\nThe FIRST collection is as follows:\n");
	while(getline(stream, tmp)) {
		cout << tmp << endl;
	}
	stream.close();
	stream.open("FOLLOW.txt");
	if(!stream.is_open()) {
		cout << "Error opening FOLLOW.txt" << endl;
		exit (1);
	}
	printf("\nThe FOLLOW collection is as follows:\n");
	while(getline(stream, tmp)) {
		cout << tmp << endl;
	}
	stream.close();
	stream.open("in.txt");
	if(!stream.is_open()) {
		cout << "Error opening in.txt" << endl;
		exit (1);
	}
	printf("\nThe arithmetic expression is as follows:\n");
	getline(stream, tmp);
	cout << tmp << endl << endl;
	stream.close();
	//初始化分析表
	analysisTable.insert(pair<string, vector<string>>("Ei", vector<string> {"E", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E+", vector<string> {"E", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E*", vector<string> {"E", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E(", vector<string> {"E", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E)", vector<string> {"E", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E$", vector<string> {"E", "T", "E'"}));

	analysisTable.insert(pair<string, vector<string>>("E'i", vector<string> {"never \'+\' or \'*\'", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E'+", vector<string> {"E'", "+", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E'*", vector<string> {"E'", "ε"}));
	analysisTable.insert(pair<string, vector<string>>("E'(", vector<string> {"here can only be \'+'\' or \'*\' symbols.", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E')", vector<string> {"here can only be \'+'\' or \'*\' symbols.", "T", "E'"}));
	analysisTable.insert(pair<string, vector<string>>("E'$", vector<string> {"E'", "ε"}));


	analysisTable.insert(pair<string, vector<string>>("Ti", vector<string> {"T", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T+", vector<string> {"T", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T*", vector<string> {"T", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T(", vector<string> {"T", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T)", vector<string> {"T", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T$", vector<string> {"T", "F", "T'"}));

	analysisTable.insert(pair<string, vector<string>>("T'i", vector<string> {"never \'*\' or \'+\'", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T'+", vector<string> {"T'", "ε"}));
	analysisTable.insert(pair<string, vector<string>>("T'*", vector<string> {"T'", "*", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T'(", vector<string> {"here can only be \'+'\' or \'*\' symbols.", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T')", vector<string> {"here can only be \'+'\' or \'*\' symbols.", "F", "T'"}));
	analysisTable.insert(pair<string, vector<string>>("T'$", vector<string> {"T'", "ε"}));

	analysisTable.insert(pair<string, vector<string>>("Fi", vector<string> {"F", "i"}));
	analysisTable.insert(pair<string, vector<string>>("F+", vector<string> {"never \'i\'"}));
	analysisTable.insert(pair<string, vector<string>>("F*", vector<string> {"never \'i\'"}));
	analysisTable.insert(pair<string, vector<string>>("F(", vector<string> {"F", "(", "E", ")"}));
	analysisTable.insert(pair<string, vector<string>>("F)", vector<string> {"never \'i\'"}));
	analysisTable.insert(pair<string, vector<string>>("F$", vector<string> {"never \'i\'"}));
	//正确匹配
	matchTable.insert(pair<string, int>("Ei", 0));
	matchTable.insert(pair<string, int>("E+", 0));
	matchTable.insert(pair<string, int>("E*", 0));
	matchTable.insert(pair<string, int>("E(", 0));
	matchTable.insert(pair<string, int>("E)", 0));
	matchTable.insert(pair<string, int>("E$", 0));

	matchTable.insert(pair<string, int>("E'+", 1));
	matchTable.insert(pair<string, int>("E'*", 2));
	matchTable.insert(pair<string, int>("E'$", 2));

	matchTable.insert(pair<string, int>("Ti", 3));
	matchTable.insert(pair<string, int>("T+", 3));
	matchTable.insert(pair<string, int>("T*", 3));
	matchTable.insert(pair<string, int>("T(", 3));
	matchTable.insert(pair<string, int>("T)", 3));
	matchTable.insert(pair<string, int>("T$", 3));

	matchTable.insert(pair<string, int>("T'+", 5));
	matchTable.insert(pair<string, int>("T'*", 4));
	matchTable.insert(pair<string, int>("T'$", 5));

	matchTable.insert(pair<string, int>("F(", 6));
	matchTable.insert(pair<string, int>("Fi", 7));

	stack.push_back("$");
	stack.push_back("E");
}

int main() {
	cout.setf(ios::left);
	init();
	beginMatch();
	return 0;
}
