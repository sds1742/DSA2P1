#pragma once
#include <string>
using namespace std;
class node
{
private:
	node* next;
	//next is held as a private varaible, with associated accessors and mutators
public:
	string name;
	string encryptedpassword;
	node* getnext();
	node(string userid, string data);
	void setnext(node* newnext);
	;
};

