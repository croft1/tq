#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//declaring functions
void textQuestBegin();


void main() {

	textQuestBegin();
	system("pause");
}

void textQuestBegin() {

	string playerName;
	cout << "Welcome to TextQuest!\n\nPlease input your name" << endl;
	cin >> playerName;

	//write name to file
	fstream playerFileStream;
	playerFileStream.open("PlayerData.txt");
	playerFileStream << playerName;

	cout << "What class would you like to play?" << endl;

	//get character class data
	fstream characterFileStream;
	characterFileStream.open("CharacterData.txt");
	string name, line;

	vector<string> charNames,
		charClasses;

	//displays character names from file
	if (characterFileStream.is_open()) {
		int i = 0;

		while (characterFileStream.good() && getline(characterFileStream, line)) {

			
			stringstream lineStream(line);
			charClasses.push_back(line);
			getline(lineStream, name, ',');	//grabs class name to print
			cout << i << ". " << name << "\n";
			charNames.push_back(name);
			i++;
		}

	}

	characterFileStream.close();


	int in;
	do {
	cin >> in;
	cout << charNames.size();
	} while (in >= charNames.size() || in <= 0);

	cout << "You selected to play as a " << charNames.at(in) << endl;

	//saving character data
	playerFileStream.open("PlayerData.txt");
	playerFileStream >>  playerName >> charClasses.at(in);
	playerFileStream.close();
	
	
}













//void writeToFile(string playerData, string fileName) {
//	fstream playerFile;
//	playerFile.open(fileName);
//	playerFile << playerData;
//}
//
//string readFromFile(string fileName){
//
//
//}



//enum characterType

