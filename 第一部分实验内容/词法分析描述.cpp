#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;
const string table[] = {"var", "if", "then", "else","while", "for", "begin", "writeln", "procedure", "end"};
int isReservedWord(string s) { // �ж�s�Ƿ�Ϊ������, ���ؽ��Ϊ-1�����Ǳ�����
	for(int i = 0; i < 10; i ++) {
		if(s == table[i]) {
			return i;
		}
	}
	return -1;
}
int main() {
	const string fileName = "in.txt";
	string temp;
	freopen(fileName.c_str(), "r", stdin);
	char c = getchar();
	while(c != EOF) {
		if(c == ' ' || c == '\n' || c == '\t' || c == EOF) { // �հ��ַ�������
			c = getchar();
			continue;
		}
		if((c >= 'a' && c <='z') || (c >='A' && c <='Z') || c == '_') { // �����ʶ��
			temp +=  c;
			c = getchar();
			while((c >= 'a' && c <='z') || (c >='A' && c <='Z') || (c >= '0' && c <= '9') || c == '_') {
				temp +=  c;
				c = getchar();
			}
			int index = isReservedWord(temp);
			if(index != -1) {
				printf("(%d, \"%s\")\n", 21 + index, temp.c_str());
			} else {
				printf("(1, \"%s\")\n", temp.c_str());
			}
			temp.clear();
		} else if(c >= '0' && c <= '9') { // ��������
			temp += c;
			c = getchar();
			while(c >= '0' && c <= '9') {
				temp += c;
				c = getchar();
			}
			printf("(2, %s)\n", temp.c_str());
			temp.clear();
		} else if(c == ';') {
			printf("(17, \";\")\n");
			c = getchar();
		} else if(c == ',') {
			printf("(18, \",\")\n");
			c = getchar();
		} else if(c == '<') { // ����С�ں�
			c = getchar();
			if(c == '=') {
				printf("(11, \"<=\")\n");
				c = getchar();
			} else if(c == '>') {
				c = getchar();
				printf("(10, \"<>\")\n");
			} else {
				printf("(9, \"<\")\n");
			}
		} else if(c == '>') { // ������ں�
			c = getchar();
			if(c == '=') {
				c = getchar();
				printf("(12, \">=\")\n");
			} else {
				printf("(8, \">\")\n");
			}
		} else if(c == '+') { // ����Ӻ�
			c = getchar();
			printf("(3, \"+\")\n");
		} else if(c == '-') { // �������
			c = getchar();
			printf("(4, \"-\")\n");
		} else if(c == '*') { // ����˺�
			c = getchar();
			printf("(5, \"*\")\n");
		} else if(c == '/') { // �������
			c = getchar();
			printf("(6, \"/\")\n");
		} else if(c == ':') { // ����ֵ��
			c = getchar();
			if(c == '=') {
				printf("(20, \":=\")\n");
				c = getchar();
			} else {
				printf("(100, \"error\")\n");
			}
		} else { // ��������
			printf("(100, \"error\")\n");
			c = getchar();
		}
	}
	fclose(stdin);
	return 0;
}
