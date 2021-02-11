#include <iostream>
#include <fstream>
#include <string>
#include "table.hpp"
using namespace std;
int main() {
	table t;
	t.rawinput();
	t.encryptinput();
	t.iterate_over_encrypt();
	t.firsttest();
	t.secondtest();
	return 0;
}