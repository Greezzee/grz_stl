#define _CRT_SECURE_NO_WARNINGS

#include "MySTL.h"
#include <iostream>
int main()
{
	char test[] = "It is a testing text, it sucks";
	String buf = strtok(test, " ");
	Vector<String> vec;
	do {
		vec.Push_back(buf);
	} while ((buf = strtok(NULL, " ")).C_string() != nullptr);
	return 0;
}