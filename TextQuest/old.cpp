//NOTE::

//a lot of this is the same
//got to a stage where i converted things to vectors for management since 
//teaching myself c++ objects would be too much considering we're doing it for the next assignment







#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//declaring functions
void textQuestBegin();

/*
void main() {

textQuestBegin();
system("pause");
}
*/

void textQuestBegin() {


	//get character class data
	fstream characterFileStream;
	characterFileStream.open("CharacterData.txt");
	string line;

	vector<string> charClasses;

	do {

		getline(characterFileStream, line);
		charClasses.push_back(line);
		cout << "c" << charClasses.at(1);

	} while (line != "");

	cout << charClasses.size();

	characterFileStream.close();
	

	//player name 
	string playerName;
	cout << "Welcome to TextQuest!\n\nPlease input your name" << endl;
	cin >> playerName;

	fstream playerFileStream;
	playerFileStream.open("PlayerData.txt");
	playerFileStream << playerName;

	cout << "What class would you like to play?" << endl;
	//sss
	//player selects character
	for (size_t i = 0; i < charClasses.size(); i++) {
		string word;
		stringstream lineStream(charClasses[i]);
		getline(lineStream, word, ',');	//grabs class name to print
		cout << charClasses[i];
	}

	int in;
	do {

		cin >> in;
		cout << in;

		if (in < 0 || in > 2) {
			cout << " Please select a valid class";
		}

	} while (in < 0 || in > 2);

	cout << "You selected to play as a " << charClasses.at(in) << endl;


	//saving character data to file

	string selectedLine;
	string textToSave;
	do {
		getline(cin, selectedLine);
		if (selectedLine[0] == '#' || selectedLine.length() == 0) {
			cout << " " << selectedLine << "x" << selectedLine.empty() << selectedLine[0];
		}
		else {
			textToSave += selectedLine;

		}

	} while (!selectedLine.empty());

	//saves class data from array to file ontop of the rest.
	textToSave += "\n" + playerName + "," + charClasses.at(in);
	playerFileStream << textToSave;
	playerFileStream.close();

}