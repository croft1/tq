FIT 2071 - Portfolio exercise 1 Documentation

Added functionality specifications

LEVELLING AND EXPERIENCE SYSTEM

I created a level system whereby you earn xp according to the random events that occur and 
one it hits a threshold at the end of a turn, you get % derived bonuses to stats. Each character
has its designated value for the amount of xp it has earned, and the current level earned

VECTORS

Storing all data from classes into 2D vectors - one for the whole class, the other for the 
individual string data associated with the class. The retrieving the indexes on selected vectors
to find the values easily

SAVING MULTIPLE CHARACTERS

by saving character data in vectors, i scan through each individual item and add lines to 
a string that will be injected into the file.
Using the append file stream function, i'm able to set a "\n" at the start of the line before <<
sending it to the file, thus putting it on a new line

LOADING MULTIPLE CHARACTERS

from the loading character screen, I output each classes string, or if it is a saves character, i
output the whole string including the name by scanning through the vector holding the data
Upon loading the character, using the getline delimiter tool, i take the values from the save file 
and put then in their own index in the 2d vector. From there, the currently selected character - of
which has its own entity is occupied

DELETING CHARACTERS

Taking some of the code from saving and loading - i loaded all the data that was saved in file into
a 2d vector. from there, i gave the option of which character the player wanted to delete. I deleted
that index but couldn't put it into file yet since nothing will change - if there are 5 lines, only 
4 lines will be changed and the last 2 will be duplicate. So i used the truncate function using 
ofstream - admittedly i got this method from stack overflow and tweaked it to work for my needs - which
deleted the entire files content. Straight after that i filled it again using the save class data 
algorithms to file

STRINGSTREAM

The functionality to take a string and stream through it to perform tasks. Commonly i used the linestream on
a line and the getline function with the stream as an input to output data from character and 
player files
 

To note:
The index of values (health, armor) are hardcoded into the program for things like cout on menus
Need to put in the correct integers - after try{}catch{} functionality but i'm sure that's 
for future weeks.
Some methods created aren't too recursive, or necessary to be split from core logic flow,
but maybe if it's expanded on


Known things to work on:

Empty lines & spaces in text files cause problems saving and loading
letters where numbers need to be in text file (exception catching needed)

balancing the experience, health system
implementing class unique abilities - like critical damage against things weak against magic etc.
decimalisation of integers when saving in text file is a strange thing that happens. likely due to converting from string to int
enums
more random events - how much health is taken according to stats and enemy
c++ object orientation using character class instead of vectors (which were fun to figure out anyway)
cleaning up of code

