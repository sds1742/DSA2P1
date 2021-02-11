#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "node.hpp"
using namespace std;
class table
{
private:
	string randomgen();
	const int size = 100;
public:
	node** hashtable;
	table();
	void rawinput();
	string encryption(string unencrypt);
	void encryptinput();
	int hashing(string name);
	void addname(string name, string password);
	void iterate_over_encrypt();
	bool search_name(string keyname, string keypassword);
	void firsttest();
	void secondtest();
};

