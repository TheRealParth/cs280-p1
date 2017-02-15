//
//  main.cpp
//  cs280project1
//
//  Created by parth patel on 2/13/17.
//  Copyright © 2017 Parth. All rights reserved.
//

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

string word;
string findChar = "-findchar=";
string findWord = "-findword=";
int findCharMatchCount;
int findCharCount = 0;
int findWordMatchCount;
int findWordCount = 0;

//----------------------------- ERROR HANDLERS -------------------------------
int poorlyFormedError(string &arg){
	cout << "Argument "  <<  arg << " is poorly formed" << endl;
	return 0;
}

int notRecognizedError(string &arg){
	cout << "Argument "  <<  arg << " is not recognized" << endl;
	return 0;
}

int fileNotFoundError(string &filename){
	cout << "File " << filename << " is not found" << endl;
	return 0;
}

// ------------------------------ GET WORDS ---------------------------------
string *getWords(string &in){
    smatch sm;
    regex wordReg ("\\s+"); //finds spaces, which we'll use to split up the words
    sregex_token_iterator reg_end;

    int i = 0;
    int tokenCount = 0;
    string tempy = "";
    for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
        i++;
    }
    string *newWords = new string[i];
    int wordCount = i;
    int letterCount = 0;
    int j = 0;
    for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
        newWords[j] = it->str();
        letterCount += newWords[j].length();
        j++;
    }
    return newWords;
}

// ----------------------------- FLAG HANDLER --------------------------------
int flagHandler(string &flag){
	string searchWord = "";
	
	for(int j = 0; j < flag.length(); j++){
		if(flag[j] == findChar[j]){
			findCharMatchCount++;
		} 
		if(word[j] == findWord[j]){
			findWordMatchCount++;
		}
	}
	//If the flag is findchar
	if(findCharMatchCount == 10){
	    if(flag.length() != 11){
	    	return poorlyFormedError(flag);
	    } else {
	    	findCharCount++;

	    	cout << "Search letter: " << word[10] << endl;
	    	// CHECK IF LETTER EXISTS 
	    	// PUSH INTO LETTERS TO FIND.
	    }
	//If the flag is findword
	} else if(findWordMatchCount == 10){
		if(flag.length() <= 10){
			return poorlyFormedError(flag);
		} else {
			for(int x = 10; x < word.length(); x++ ){
				searchWord += word[x];
			}
			cout << "Search Word: " << searchWord << endl;
			// CHECK IF WORD EXISTS 
			//PUSH WORD INTO WORDS TO FIND.
		}
	} else {
		return notRecognizedError(flag);
	}
	return 0;
}
// ------------------------------ FILE HANDLER ---------------------------------
int fileHandler(string &filename){
	return 0;
}

int main(int argc, const char * argv[]) {


    for(int i = 0; i < argc; i++){
    	findCharMatchCount = 0;
    	findWordMatchCount = 0;
    	word = argv[i];

    	if(word[0] == '-'){
    		flagHandler(word);
		} else {
			fileHandler(word);
		}

    }


    return 0;
}
