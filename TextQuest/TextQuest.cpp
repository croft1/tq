#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>



using namespace std;

//declare functions
void newGame();
vector <vector <string>> sortedDataFromFile(string);
void saveDataToFile(vector <string>, string, bool);
int selectMenuValidation(int, int);
void performGameEvent();
void showPlayerCharacterStats();
void checkXpAndLevel();
bool canGetNextLevel();
string name();
string vocation();
int xp();
int level();
int health();
int armor();
int magic();
int xp();
void levelUp();
bool hasHealth();
void gameEvent();
void modifyHealth(int);
void loadGame();
int processMainMenu();
void modifyXP(int);
int untilLevelUp();
void deleteGame();

//global vars
vector<string> currentCharacter;

void main() {

	//not using main for game functions, just simple calls like this
	newGame();
	cout << " in MAIN" << endl;
	system("pause");

}


void newGame() {

	cout << "Welcome to TextQuest!\n\n 0. Load game \n 1. Create new game\n" << endl;

	string playerName;
	if (selectMenuValidation(1, 0) == 0) {

		//TODO: add in file validation  - if file empty, no saves etc
		loadGame();

	}
	else {	//NEWGAME

		cout << "Input your characters name (one word)\n" << endl;
		cin >> playerName;

		cout << "\nWhat class would you like to play, " << playerName << "?\n" << endl;

		//calls method that takes the values in text file and sorts them in vector
		vector <vector<string>> characterClass = sortedDataFromFile("CharacterData.txt");

		//cycles vector and prints out name for selection
		for (int i = 0; i < (int)characterClass.size(); i++) {
			cout << i << ". " << characterClass.at(i).at(0) << endl;
		}
		cout << "\n" << endl;	//just formatting

		//unsigned so its impossible to get a negative number when searching vector
		unsigned int selectedClass = selectMenuValidation(static_cast<int>(characterClass.size()), 0);

		//populating currently loaded characters data into vector 
		currentCharacter.push_back(playerName);
		for (int i = 0; i < (int)characterClass.at(selectedClass).size(); i++) {
			currentCharacter.push_back(characterClass.at(selectedClass).at(i));
		}
	}

	//show stats and selection before commencing game
	cout << "You selected to play as:\n" << endl;
	showPlayerCharacterStats();
	cout << "\n" << endl;
	system("pause");



	//GAME LOOP STARTS
	bool gameRunning = true;
	do {

		//for comparing health and showing how much was lost last turn
		int prevHealth = health();

		switch (processMainMenu()) {
		case 0:
			gameEvent();
			if (hasHealth()) {
				cout << name();	//add name to print queue, then append dialogue depending on previous turn result
				if (prevHealth > health()) {
					cout << " lost " << (health() - prevHealth) << " health that turn" << endl;
				}
				else {
					cout << " has " << health() << " health " << endl;
				}
			}
			else {
				cout << "YOU DIED" << endl;
				//flips game running so it breaks out of loop to move on
				gameRunning = false;
			}
			break;
		case 1:
			//performs save action- refer to method for detail
			saveDataToFile(currentCharacter, "PlayerData.txt", true);
			break;
		case 2:
			//load from file - refer to method for detail
			//saves current file
			saveDataToFile(currentCharacter, "PlayerData.txt", true);
			cout << "current game was saved" << endl;
			//then asks which file to load next
			loadGame();
			break;
		case 3:
			//stats - - refer to method for detail
			showPlayerCharacterStats();
			break;
		case 4: //new game - refer to method for detail
			cout << "Save current game?\n0. No \n1. Yes" << endl;
			if (selectMenuValidation(1, 0) == 1) {
				saveDataToFile(currentCharacter, "PlayerData.txt", true);
			}
			else {
				newGame();
			}
			break;
		case 5: //quit - gets option, flips gameRunning to exit loop if desired
			cout << "really quit?\n0. No \n1. Yes" << endl;
			if (selectMenuValidation(1, 0) == 1) {
				gameRunning = false;
				cout << "quitting" << endl;
			}
			else {
				cout << "not quitting" << endl;
			}
			break;
		case 6: //delete char -refer to method for detail
			deleteGame();
			break;
		default:
			cout << "Need a valid input" << endl;
		}
	} while (gameRunning);


}

void gameEvent() {

	//the randomly generated game event from switch statement
	checkXpAndLevel();
	srand(time(NULL));
	modifyXP(2);

	//a collection of reactions from events that affect health and xp
	switch (rand() % 9 + 1) {
	case 0:
		cout << "You got attacked by a dragon" << endl;
		modifyHealth(-150);
		modifyXP((level() * 5));
		break;
	case 1:
		cout << "You found a health pack!" << endl;
		modifyHealth(30);
		break;
	case 2:
		cout << "Enemy mage fired at you!" << endl;
		modifyHealth(-30);
		modifyXP((level() * 2));
		break;
	case 3:
		cout << "Got hit by an arrow" << endl;
		modifyHealth(-10);
		break;
	case 4:
		cout << "Ambush!" << endl;
		modifyHealth(-30);
		break;
	case 5:
		cout << "Found fresh water" << endl;
		modifyHealth(5);
		break;
	case 6:
		cout << "Ate poisoned food" << endl;
		modifyHealth(-10);
		break;
	case 7:
		cout << "Feel evil" << endl;
		modifyHealth(-5);
		break;
	case 8:
		cout << "Found a book!" << endl;
		modifyXP(30);
		break;
	case 9:
		cout << "Arm wrestle and lost" << endl;
		modifyHealth(-5);
		break;
	default: {
		cout << "nothing.." << endl;
	}

	}

}

void loadGame() {

	//stores each line in returned 2d array from storeddatafromfile method
	vector <vector<string>> savedPlayers = sortedDataFromFile("PlayerData.txt");
	cout << "Choose your save game\n";
	for (int i = 0; i < (int)savedPlayers.size(); i++) {
		if (savedPlayers.at(i).at(0) == "") {	//hardcoded length in so selecting incorrectly formatted players can't cause crashing
			//ignore empty line
		}
		else {
			//outputs saved character screen - if formatting is incorrect, crashing will occur here
			cout << i << ". "
				<< savedPlayers.at(i).at(0) << endl;
		}
	}

	//to choose save file
	int choice = selectMenuValidation(savedPlayers.size(), 0);
	currentCharacter = savedPlayers.at(choice);

	cout << "Loaded " << currentCharacter.at(0) << endl;

}

void deleteGame() {


	//takes all save files out and stores in array
	vector <vector<string>> savedPlayers = sortedDataFromFile("PlayerData.txt");
	cout << "Delete which character?\n";
	//player chooses what to select
	for (int i = 0; i < (int)savedPlayers.size(); i++) {
		if (savedPlayers.at(i).at(0) == "") {
			//ignore empty line
		}
		else {
			cout << i << ". "
				<< savedPlayers.at(i).at(0) << endl;

		}
	}

	//game deletes save file from array
	int choice = selectMenuValidation(savedPlayers.size(), 0);
	savedPlayers.erase(savedPlayers.begin() + choice);

	//this is the process of clearing / truncating the text file. 
	//If save number gets too large it will destroy your computer
	ofstream x;
	x.open("PlayerData.txt", ofstream::out | ofstream::trunc);

	//once save file is cleared, the stored data in the array without the character that was chosen is deleted
	for (int i = 0; i < (int)savedPlayers.size(); i++) {
		saveDataToFile(savedPlayers.at(i), "PlayerData.txt", false);
	}

	cout << "Deleted. " << endl;

}


//simple output of character data
void showPlayerCharacterStats() {
	//harcoded index of each character classes attributes
	cout << "\nClass: " << vocation()
	<< "\nHealth: " << health()
	<< "\Armor: " << armor()
	<< "\nMagic: " << magic()
	<< "\nLevel: " << level()
	<< "\nExperience: " << xp()
	<< endl;
}

//simple cout of main menu with return of selection
//itd be better to have this seperated into print main menu and return main menu selection
int processMainMenu() {
	int mmSel;
	cout << "\n\n~ Main Menu ~\n\n 0. GO!\n 1. Save\n 2. Load\n 3. Stats\n 4. New Game\n 5. Quit\n 6. Delete\n Health: " <<
		health() << ", Armor " << armor() << ", Magic " << magic() << "\n" << endl;
	mmSel = selectMenuValidation(5, 0);
	return mmSel;
}

//checks file
bool fileNotEmpty(string fileName) {
	fstream file(fileName);
	if (file) {
		return false;
	}
	else {
		return true;
	}
}

//attempt at input validation on number menus
int numberInputCheck() {
	int number;

	cin >> number;		//seems to break here if a letter is input, not sure how to do it
	do {
		if (cin.fail()) {		//supposed to be if cin assignment fails
			cin.clear();		//you clear it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	//then ignore the input so you can get another one
																	//the 3 lines here are with help froim this post stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
		}
		else {
			return number;	//but if it worked, you just get the number back

		}
		cin >> number;		//and this is the inside line of user input that repeats
	} while (isdigit(number));	
}



//returns vector of correctly formatted data in file
//incorrect formatting will result in crashing
vector <vector <string>> sortedDataFromFile(string fileName) {

	//setup memory for use
	fstream fileStream;
	string line,
		item;

	fileStream.open(fileName);
	vector <vector<string>> playerClass;

	//so you get the line from the file
	while (getline(fileStream, line)) {

		//create vector to add in the data of each individual character / player class
		vector <string> playerAttr;
		//then split that line up using a stringstream
		stringstream lineStream(line);		

		//searching through the line, item is set to the word that is between the current position and the next comma
		while (getline(lineStream, item, ',')) {	//hard code comma as default delimiter
			
													//then the item retrieved is added to the temporary arrayList
			playerAttr.push_back(item);
		}

		//if(playerAttr.size() == 7){	

		//cout << playerAttr.size();		for an unknown reason, this vector returns 6666

			////must have the correct number of values in the file. ie. 1,2,3,4,5,6,7
			////if there is less than 7 name/vocation/health/armor/magic/xp/level then it will crash on loading character
			//// only other addition would be to catch an exception if letters are 
			////where the numbers need to be. but we haven't done exception catching in c++ yet
			//	playerClass.push_back(playerAttr);

			//}

		//the vector is then added to the full array list when the smaller one has finished filling
		playerClass.push_back(playerAttr);
		//clear the small array so no duplicates are features in the 2d array playerClass
		playerAttr.clear();
		

	}
	//when finishing the retrieval, clean up and close stream
	fileStream.close();

	//return 2d array of all saved / stored players from text filie
	return playerClass;
}

void saveDataToFile(vector <string> data, string fileName, bool append) {
	//preparing
	fstream saveStream;
	string playerString;


	//opening streams, depending on if we want to overwrite lines, or append character to next line
	if (append) {
		//ios::app is the namespace of iostream that allows us to append to file
		//adding lines to the end of a file when we have a outstream open
		saveStream.open(fileName, ios::app);
	}
	else {
		saveStream.open(fileName);
	}

	//converting player data to the delimeted format in text
	for (int i = 0; i < (int)data.size(); i++) {
		if (i == 0)
			playerString += data.at(i);
		else
			playerString += "," + data.at(i);
	}

	//add \n to format text file
	saveStream << "\n" << playerString;
	saveStream.close();

	//when we do expection catching, this will be more valuable. It just assumes it will always save, or crash at the moment
	cout << "Save successful" << endl; //validate this in future.
}



//for numbered menus, this function takes in parameters for the size of the menu, and controls that input
//only problem is the numberInputCheck() doesn't work too great if letters are input
//it crashes if you try to sort that out, so for now this is probably that best way to do it - don't use letters
int selectMenuValidation(int upper, int lower) {
	int menuSelect;
	cin >> menuSelect;

	while (!(menuSelect >= lower || menuSelect <= upper)) {
		cout << "Please enter a valid number" << endl;
		menuSelect = numberInputCheck();
	}

	return menuSelect;

}


//quick method to change stored character health. parameter is signed for losing or gaining health
//hardcoded index of health

void modifyHealth(int change) {
	int h = health() + change;
	currentCharacter.at(2) = to_string(h);
}

//same as modifyHealth() except does it for xp
//hardcoded position of xp
void modifyXP(int change) {
	int x = xp() + change;
	currentCharacter.at(6) = to_string(x);
}

//self explanatory
bool hasHealth() {
	if (health() > 0)
		return true;
	else
		return false;
}

//name could be improved
//checks to see if you've accumulated enough xp to level up
//if you have it performs the task, if not, it outputs your remaining xp to the level
void checkXpAndLevel() {
	if (canGetNextLevel()) {
		levelUp();
		cout << "With " << xp() << " xp, you evolved to level " << level() << "!!" << endl;
	}
	else {
		cout << untilLevelUp() << " xp until level up!" << endl;
	}
}


//self explanatory
bool canGetNextLevel() {

	if (untilLevelUp() < 0) {
		return true;
	}
	else {
		return false;
	}
}

//xp until level up
int untilLevelUp() {
	return ((level() + 1) * 50 - xp());
}

//returns the values for character - this is obviously hard coded in. 
//a way to stop the hardcoding index is to have a getNameIndex function perhaps. If its important
string name() {
	return currentCharacter.at(0);
}

string vocation() {
	return currentCharacter.at(1);
}

int health() {
	return stoi(currentCharacter.at(2));
}

int armor() {
	return stoi(currentCharacter.at(3));
}

int magic() {
	return stoi(currentCharacter.at(4));
}

int xp() {
	return stoi(currentCharacter.at(6));
}

int level() {
	return stoi(currentCharacter.at(5));
}


//performs level up actions - changing in array
void levelUp() {
	currentCharacter.at(5) = to_string(level() + 1);
	for (int i = 2; i < 5; i++) { //hardcoding the positions of attributes
		//stoi converts string to integer
		currentCharacter.at(i) = to_string((stoi(currentCharacter.at(i)) * 1.05));	//increase attr by 5% - no cap on health so far
	}
}


