#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
using namespace std;

/*
Type 1 : letter(letter | digit)*  infinite set
Type 2 : constant    (digit)+  infinite set
Type 3 : reserved words(32)
auto       break    case     char        const      continue
default    do       double   else        enum       extern
float      for      goto     if          int        long
register   return   short    signed      sizeof     static
struct     switch   typedef  union       unsigned   void
volatile    while
Type 4 : delimiter  comment symbol () { } [ ] " '
Type 5 : operator < <= > >= = + - * / ^
*/

unordered_set<string> reservedWords {
	"asm", "auto",
	"bool", "break",
	"case", "catch", "char", "class", "const", "const_cast", "continue",
	"default", "delete", "do", "double", "dynamic_cast",
	"else", "enum", "explicit", "export", "extern",
	"false", "float", "for", "friend",
	"goto",
	"if", "inline", "int",
	"long",
	"mutable",
	"namespace", "new",
	"operator",
	"private", "protected", "public",
	"register", "reinterpret_cast", "return",
	"short", "signed", "sizeof", "static", "static_cast", "struct", "switch",
	"template", "this", "throw", "true", "try", "typedef", "typeid", "typename",
	"union", "unsigned", "using",
	"virtual", "void", "volatile",
	"while"
};


unordered_set<char> delimiters {
	';', '(', ')', ',', '\"', '\'', '#', '[', ']', '{', '}', '\\'
};

//remove the comment, white space and so on
string preProcess(const string &raw) {
	string res;
	cout << "the length of raw string: " << raw.length() << endl;
	for (int i = 0; i < static_cast<int>(raw.length()); ) {
		//perhaps there will be some comment
		if (raw[i] == '/' && i + 1 < static_cast<int>(raw.length())) {
			if (raw[i + 1] == '/') { //single line
				while (raw[i] != '\n') {
					i++;
				}
			} else if (raw[i + 1] == '*') { //multiple lines /* ...*/
				i += 2;
				bool flag = false;
				for (; i + 1 < static_cast<int>(raw.length()); i++) {
					//find the matched symbol
					if (raw[i] == '*' && raw[i + 1] == '/') {
						flag = true;
						i += 2;//pass the */
						break;
					}
				}
				if (flag == false) {
					cout << "no matched" << endl;
					exit(-1);
				}
			}
		}
		if (raw[i] == '\n' || raw[i] == '\t') {
			res.append(1, ' ');
		} else {
			res.append(1, raw[i]);
		}
		i++;
	}
	return res;
}

string getRawString(string filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "open " << filename << " failed" << endl;
		exit(-1);
	}
	char c;
	string res;
	while (inFile.get(c)) {
		res.append(1, c);
	}
	inFile.close();
	return res;
}


inline bool isReservedWord(const string &word) {
	return reservedWords.find(word) != reservedWords.end();
}

inline bool isletter(char ch) {
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_';
}

inline bool isDelimiter(char ch) {
	return delimiters.find(ch) != delimiters.end();
}



void Scanner(const string &str, const string &filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cerr << "open " << filename << " failed" << endl;
		exit(-1);
	}

	int len = static_cast<int>(str.length());
	for (int i = 0; i < len; ) {
		//start with the letter
		string cur;


		if (isletter(str[i])) { //a identifier or a reserved word will happen
			while (i < len && (isletter(str[i]) || isdigit(str[i]))) {
				cur.append(1, str[i]);
				i++;
			}
			if (isReservedWord(cur)) {
				outFile << "reserved word ";
			} else {
				outFile << "identifier ";
			}
			outFile << cur << endl;
		} else if (isdigit(str[i])) {
			bool isInteger = true;
			while (i < len) {
				if (isdigit(str[i])) {
					cur.append(1, str[i++]);
				} else if (str[i] == '.' || str[i] == 'e') {
					if (isInteger) {
						isInteger = false;
						cur.append(1, str[i++]);
					} else {
						cerr << "Error" << endl;
						outFile.close();
						exit(-1);
					}
				} else {
					break;
				}
				i++;
			}
			outFile << "constant " << cur << endl;
		} else if (isDelimiter(str[i])) {
			outFile << "delimiter " << str[i++] << endl;
		} else if (str[i] == '.' || str[i] == '?' || str[i] == ':') {
			outFile << "operator " << str[i++] << endl;
		} else {
			bool isWhiteChar = str[i] == ' '; // mark the character is the white char or not
			int start = i; //record the start position
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
			        str[i] == '^' || str[i] == '~' || str[i] == '%') {
				cur.append(1, str[i++]);
				if (i < len && str[i] == '=') {
					cur.append(1, '=');
					i++;
				}
			} else if (str[i] == '<' || str[i] == '>'
			           || str[i] == '&' || str[i] == '|') { // shaped like a aa a=
				cur.append(1, str[i++]);
				if (i < len && (str[i] == str[i - 1] || str[i] == '=')) {
					cur.append(1, str[i++]);
				}
			} else if (str[i] == '=' || str[i] == '!') {
				cur.append(1, str[i++]);
				if (i < len && str[i] == '=') {
					cur.append(1, '=');
					i++;
				}
			}
			if (!isWhiteChar) {
				//some if or else if statement has been reached
				//so the index i will not be equal to the origin start position
				if (i != start) {
					outFile << "operator " << cur << endl;
				} else {
					cerr << "Error" << endl;
					outFile.close();
					exit(-1);
				}
			} else {
				//remember that the index should be moved
				i++;
			}

		}

	}
	outFile.close();
}


int main(void) {
	//read the string in and process the raw string
	string str = preProcess(getRawString("1.txt"));
	cout << "str:" << endl;
	cout << str << endl;


	//begin to scan the preprocessed string
	Scanner(str, "1.out");

	return 0;
}
