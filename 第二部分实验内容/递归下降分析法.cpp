#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void E();
void E_prime();
void T();
void T_prime();
void F();

vector<string> grammar;
char ch;
string tmp;
bool success = true;
int index = 0, cnt = 0;

void E() {
	cout << setw(10) << grammar[0] << "\t\t" << ch << endl;
	T();
	E_prime();
}

void E_prime() {
	if(ch == '+') {
		cout << setw(10) << grammar[1] << "\t\t" << ch << endl;
		ch = tmp[index ++];
		T();
		E_prime();
	} else if(ch == 'i') {
		success = false;
		printf("error in %d : never \'+\' or \'*\'\n", index);
		T();
		E_prime();
	} else if(ch == ')' && cnt == 0) {
		success = false;
		printf("error in %d: more \')\'\n", index);
		ch = tmp[index ++];
	} else if (ch != '$' && ch != '*') {
		success = false;
		printf("error in %d : Here can only be \'+'\' or \'*\' symbols.\n", index);
		ch = tmp[index ++];
		T();
		E_prime();
	} else {
		cout << setw(10) << grammar[2] << "\t\t" << ch << endl;
	}
}

void T() {
	cout << setw(10) << grammar[3] << "\t\t" << ch << endl;
	F();
	T_prime();
}

void T_prime() {
	if(ch == '*') {
		cout << setw(10) << grammar[4] << "\t\t" << ch << endl;
		ch = tmp[index ++];
		F();
		T_prime();
	} else if(ch == 'i') {
		success = false;
		printf("error in %d: never \'*\' or \'+\'\n", index);
		F();
		T_prime();
	}  else if(ch == ')' && cnt == 0) {
		success = false;
		printf("error in %d : more \')\'\n", index);
		ch = tmp[index ++];
	} else if (ch != '$' && ch != '+') {
		success = false;
		printf("error in %d : Here can only be \'+'\' or \'*\' symbols.\n", index);
		ch = tmp[index ++];
		F();
		T_prime();
	} else {
		cout << setw(10) << grammar[5] << "\t\t" << ch << endl;
	}
}

void F() {
	if(ch == '(') {
		cnt ++;
		cout << setw(10) << grammar[6] << "\t\t" << ch << endl;
		ch = tmp[index ++];
		E();
		if(ch == ')') {
			cnt --;
			ch = tmp[index ++];
		} else {
			printf("error in %d : never \')\'\n", index);
			success = false;
		}
	} else if(ch == 'i') {
		cout << setw(10) << grammar[7] << "\t\t" << ch << endl;
		ch = tmp[index ++];
	} else {
		printf("error in %d: never \'i\'\n", index);
		success = false;
	}
}

int main() {
	cout.setf(ios::left);
	ifstream stream;
	stream.open("input.txt");
	if(!stream.is_open()) {
		cout << "Error opening input.txt" << endl;
		exit (1);
	}
	while(getline(stream, tmp)) {
		grammar.push_back(tmp);
	}
	printf("The grammar is as follows :\n");
	for(int i = 0; i < grammar.size(); i ++) {
		cout << grammar[i] << endl;
	}
	stream.close();
	stream.open("in.txt");
	if(!stream.is_open()) {
		cout << "Error opening in.txt" << endl;
		exit (1);
	}
	printf("\nThe arithmetic expression is as follows:\n");
	getline(stream, tmp);
	cout << tmp << endl;
	stream.close();
	printf("\nThe recursive descent analysis process is as follows:\n");
	ch = tmp[index ++];
	E();
	printf("\nThe analytic result is as follows:\n");
	if(success) {
		printf("success!\n");
	} else {
		printf("no success!\n");
	}
	return 0;
}