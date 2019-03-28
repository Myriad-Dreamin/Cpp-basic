

#include <iostream>
#include "collect.h"
#include "tools.h"

int main() {
	CsvHandle fha("./test.csv", std::ios::out | std::ios::app);
	fha.block("test");fha.block("go");
	fha.newline();
	fha.block(1);fha.block('A');
	fha.newline();
	fha.block(1.24);fha.block(15.5);
	fha.newline();

	fha.close();
}