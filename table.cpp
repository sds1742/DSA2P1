#include "table.hpp"
string table::randomgen()
{
	const int SIZE = 26;
	char lowercase[SIZE] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string password = "";
	for (int i = 0; i < 9; i++) {
		password = password + lowercase[rand() % SIZE];
		//the rand function produces a random integer. 
		//by taking mod of rand over size, it selects a random number from 0 to 25, which is used to select a letter
		//this iterates 9 times to produce the password
	}
	return password;
}
table::table()
{
	hashtable = new node * [size];
	for (int i = 0; i < size; i++) {
		hashtable[i] = nullptr;
	}
}
void table::rawinput()
{
	ifstream nameinput;
	string name;
	double decimal1;
	double decimal2;
	int rank;
	nameinput.open("lastNames.txt");
	ofstream rawoutput;
	rawoutput.open("raw.txt");
	if (nameinput.fail()) {
		cout << "could not open lastNames.txt" << endl;
		return;
		//error checking
	}
	if (rawoutput.fail()) {
		cout << "could not open raw.txt" << endl;
		return;
		//error checking
	}
	while (!nameinput.eof() && nameinput.good()) {
		nameinput >> name;
		nameinput >> decimal1;
		nameinput >> decimal2;
		nameinput >> rank;
		//inputting the name and the extra numbers
		for (int i = 0; i < name.size(); ++i) {
			if (!isalpha(name.at(i))) {
				cout << "bad data" << endl;
				nameinput.clear();
				nameinput.close();
				//error checking if data contains nonalphanumeric characters
			}
		}
		if (!nameinput.fail() && !rawoutput.fail()) {
			string password = randomgen();
			rawoutput << name <<" "<<password<<endl;
			//outputing to file
		}
	}
	if (nameinput.eof() && rawoutput.eof()) {
		nameinput.close();
		rawoutput.close();
	}
}

string table::encryption(string unencrypt)
{
	string key = "structure";
	string encrypt = "";
	for (int i = 0; i < unencrypt.size(); i++) {
		encrypt += ((unencrypt[i] - 'a' + key[i] - 'a') % 26) + 'a';
	}
	return encrypt;
}

void table::encryptinput()
{
	ifstream rawinput;
	string name;
	string rawpassword;
	rawinput.open("raw.txt");
	ofstream encryptoutput;
	encryptoutput.open("encrypted.txt");
	if (rawinput.fail()) {
		//error checking
		return;
	}
	if (encryptoutput.fail()) {
		//error checking
		return;
	}
	while (!rawinput.eof() && rawinput.good()) {
		rawinput >> name;
		rawinput >> rawpassword;
		for (int i = 0; i < name.size(); ++i) {
			if (!isalpha(name.at(i))) {
				cout << "bad data" << endl;
				rawinput.clear();
				rawinput.close();
				//checking for nonalphanumeric characters
			}
		}
		if (!rawinput.fail() && !encryptoutput.fail()) {
			string encryptpassword = encryption(rawpassword);
			encryptoutput << name << " " << encryptpassword << endl;
			//file output
		}
	}
	if (rawinput.eof() && encryptoutput.eof()) {
		rawinput.close();
		encryptoutput.close();
	}
}

int table::hashing(string inputname)
{
	int k = 0;
	for (int i = 0; i < inputname.length(); ++i) {
		k = (inputname.at(0) - 'A')+k;
		//takes the sum of the numeric values of the letters in the name for hashing
	}
	int j = k % 100;
	return j;
}

void table::addname(string name, string password)
{
	int hashnumber = hashing(name);
	node* placeholder = nullptr;
	//this is used as a temp variable to iterate through the hashtable
	node* entry = hashtable[hashnumber];
	while (entry != NULL) {
		placeholder = entry;
		entry=entry->getnext();
		//this code checks for a linked list at the source, and iterates until the end of the list
	}
	if (entry == NULL) {
		entry = new node(name, password);
		if (placeholder == nullptr) {
			hashtable[hashnumber] = entry;
			//this code cheks to see if the entry is at the end of the chain before adding the node
		}
		else {
			placeholder->setnext(entry);
		}
	}
	else {
		entry->name = name;
	}
}

void table::iterate_over_encrypt()
{
	ifstream encryptinput;
	string name;
	string encryptpassword;
	encryptinput.open("encrypted.txt");
	if (encryptinput.fail()) {
		return;
		//error checking
	}
	while (!encryptinput.eof() && encryptinput.good()) {
		encryptinput >> name;
		encryptinput >> encryptpassword;
		for (int i = 0; i < name.size(); ++i) {
			if (!isalpha(name.at(i))) {
				cout << "bad data" << endl;
				encryptinput.clear();
				encryptinput.close();
				//checks for non-alphanumeric characters
			}
		}
		if (!encryptinput.fail()) {
			addname(name, encryptpassword);
			//runs the function to add an entry to the hashtable
		}
	}
	if (encryptinput.eof()) {
		encryptinput.close();
	}
}

bool table::search_name(string keyname, string keypassword)
{
	int hashval = hashing(keyname);
	//hash into the table by the name
	bool found = false;
	node* entry = hashtable[hashval];
	if (entry != nullptr) {
		//is there anything at the hash entry
		while (entry != nullptr) {
			if ((entry->name == keyname) && (entry->encryptedpassword == keypassword)) {
				found = true;
			}
			if (found) {
				break;
			}
			entry = entry->getnext();
			//iterate down the linked list
		}
	}
	return found;
}

void table::firsttest()
{
	cout << "Legal" << endl;
	cout << "Userid	" << "Password	" << "Result" << endl;
	ifstream input;
	string testname, rawpassword, testpassword;
	int i=0;
	input.open("raw.txt");
	while (!input.eof() && !input.fail() && i < 5) {
		input >> testname;
		input >> rawpassword;
		//standard text input
		testpassword=encryption(rawpassword);
		//produce encrypted password
		bool testbit = search_name(testname, testpassword);
		//test using the search function
		i++;
		if (testbit) {
			cout << testname << "	" << testpassword << "	match" << endl;
		}
		else {
			cout << testname << "	" << testpassword << "	no match" << endl;
		}
	}
	if (input.eof()||i>5) {
		input.close();
	}
}

void table::secondtest()
{
	cout << "Illegal" << endl;
	cout << "Userid	" << "Password	" << "Result" << endl;
	ifstream input;
	string testname, rawpassword, testpassword;
	int i = 0;
	input.open("raw.txt");
	while (!input.eof() && !input.fail() && i < 5) {
		input >> testname;
		input >> rawpassword;
		//same input stream
		rawpassword[0] = rawpassword[0] + 1;
		//change first letter in raw password
		testpassword = encryption(rawpassword);
		bool testbit = search_name(testname, testpassword);
		i++;
		if (testbit) {
			cout << testname << "	" << testpassword << "	match" << endl;
		}
		else {
			cout << testname << "	" << testpassword << "	no match" << endl;
		}
	}
	if (input.eof() || i > 5) {
		input.close();
	}
}

