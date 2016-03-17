#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void textQuest();

void main() {

	textQuest();
	system("pause");

}

void textQuest() {

	string playerName;
	cout << "Welcome to TextQuest!\n\nPlease input your name" << endl;
	cin >> playerName;

	//write name to file
	fstream playerFileStream;
	playerFileStream.open("PlayerData.txt");
	playerFileStream << playerName;
	playerFileStream.close();

	cout << "What class would you like to play?" << endl;


	//get character class data
	fstream characterFileStream;
	characterFileStream.open("CharacterData.txt");

	string item, line;
	vector <vector<string>> charClass;
	vector <string> charAttributes;

	//get line, seperate each item and add to vector
	while (getline(characterFileStream, line) && characterFileStream.good()) {

		stringstream lineStream(line);

		while (getline(lineStream, item, ',')) {
			charAttributes.push_back(item);
			cout << "Found item :" << item << endl;
		}
		charClass.push_back(charAttributes);
		charAttributes.clear();
	}

	//test
	unsigned int x = 0,
		y = 0;

	while (x < charClass.size()) {
		while (y < charClass.at(x).size()) {
			cout << charClass.at(x).at(y) << endl;
			y++;
		}
		x++;
	}



	unsigned int selectedClass = 999;	//assume we won't have >999 classes
	do {
		if ((selectedClass < 0 || selectedClass > static_cast<int>(charClass.size())) && selectedClass != 999) {
			cout << "Please enter a valid number!" << endl;
		}
		cout << "Select your class number" << endl;
		cin >> selectedClass;
	} while (selectedClass >= static_cast<int>(charClass.size()) || selectedClass <= 0);


	//harcoded index of each character classes attributes
	cout << "You selected to play as a: " << charClass.at(selectedClass).at(0)
	<< "\nHealth: " << charClass.at(selectedClass).at(1)
	<< "\nStrength: " << charClass.at(selectedClass).at(2)
	<< "\nMagic: " << charClass.at(selectedClass).at(3) << endl;
	//starting level : 1 



	//saving character data
	fstream pStream;
		pStream.open("PlayerData.txt");

	string classString;
	for (int i = 0; i < (int)charClass.at(selectedClass).size(); i++) {
		classString += "," + charClass.at(selectedClass).at(i);
	}

	pStream << playerName << classString;
	pStream.close();
}

// possibly move character selection to an enum
//string myCharacterData(int selectedClass) {
	



