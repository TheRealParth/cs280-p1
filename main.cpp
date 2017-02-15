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
#include <map>

using namespace std;
//fileCountMap[filename][lines]   fileCountMap[filename][words]  fileCountMap[filename][chars]

map <string, map <string, int>> fileCountMap;
map <char, map <string, map <string, int>>> charCountMap;
map <string, map <string, map <string, int>>> wordCountMap;

map <int, char> chars;
map <int, string> words;
map <int, string> files;

string word;
string findChar = "-findchar=";
string findWord = "-findword=";

int findCharCount = 0;
int findWordCount = 0;
int fileCount = 0;

int currWordLength = 0;

//----------------------------- ERROR HANDLERS -------------------------------
int poorlyFormedError(string &arg){
	cout << "Argument "  <<  arg << " is poorly formed" << endl;
	exit(0);
}

int notRecognizedError(string &arg){
	cout << "Argument "  <<  arg << " is not recognized" << endl;
	exit(0);
}

int fileNotFoundError(string &filename){
	cout << "File " << filename << " is not found" << endl;
	exit(0);
}

// ------------------------------ DOES EXIST FUNCTIONS ---------------------------------
int doesExistChar(char &c){
	for(int i = 0; i < findCharCount; i++){
		if(chars[i] == c){
			return 1;
		}
	}
	return 0;
}
int doesExistWord(string &w){
	for(int i = 0; i < findWordCount; i++){
		if(!words[i].compare(w)){
			return 1;
		}
	}
	return 0;
}
int doesExistFile(string &f){
		for(int i = 0; i < fileCount; i++){
		if(!files[i].compare(f)){
			return 1;
		}
	}
	return 0;
}
// ------------------------------ GET WORDS ---------------------------------
string *getWords(string &in, string &filename){
    smatch sm;
    regex wordReg ("\\s+"); //finds spaces, which we'll use to split up the words
    sregex_token_iterator reg_end;

    int i = 0;
    int tokenCount = 0;
    string tempy = "";
    for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
        i++;
    }
    currWordLength = i;
    cout << "LENGTH : " << i << endl;
    string *newWords = new string[i];
    int j = 0;
    for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
        newWords[j] = it->str();
        j++;
    }
    return newWords;
}

// ----------------------------- FLAG HANDLER --------------------------------
int flagHandler(string &flag){
	int findCharMatchCount = 0;
    int findWordMatchCount = 0;
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
	    	int doesExist = doesExistChar(word[10]);
	    	//add to chars map
	    	if(!doesExist){
	    		cout << "Search Char: " << word[10] << endl;
	    		chars[findCharCount] = word[10];
	    		findCharCount++;
	    	}
	    }
	//If the flag is findword
	} else if(findWordMatchCount == 10){
		if(flag.length() <= 10){
			return poorlyFormedError(flag);
		} else {
			for(int x = 10; x < word.length(); x++ ){
				searchWord += word[x];
			}
	    	int doesExist = doesExistWord(searchWord);
	    	//add to chars map
	    	if(!doesExist){
	    		cout << "Search Word: " << searchWord << endl;
	    		words[findWordCount] = searchWord;
	    		findWordCount++;
	    	}
			
		}
	} else {
		return notRecognizedError(flag);
	}
	return 0;
}
// ------------------------------ FILE HANDLER ---------------------------------
int fileHandler(string &filename){
	int doesExist = doesExistFile(filename);
	if(!doesExist){
		files[fileCount] = filename;
		fileCount++;
	}
	return 0;
}
// ------------------------------ PRINT RESULTS --------------------------------
int printResults(){
	if(fileCount){
		for(int i = 0; i < fileCount; i ++ ) {
			cout << fileCountMap[files[i]]["lines"] << " ";
			cout << fileCountMap[files[i]]["words"] << " ";
			cout << fileCountMap[files[i]]["chars"] << " ";
			cout << files[i] << endl;
		}
	} else {
		//PRINT STDIN results
	}
	if(fileCount > 1){
		//PRINT TOTALS
	}
	return 0;
}
// ------------------------------- FILE READER ---------------------------------
int fileParser(string &filename){
	string line;
	int wordCount = 0;
	int charCount = 0;

	fileCountMap[filename]["lines"] = 0;
	fileCountMap[filename]["words"] = 0;
	fileCountMap[filename]["chars"] = 0;

	ifstream file (filename);

	if(!file.is_open()) fileNotFoundError(filename);

	cout << "File to read: " << filename << endl;
	int i = 0;
	int wordsLength;

	while(getline(file, line)){
			currWordLength = 0;

			if(!line.length()) continue;

			fileCountMap[filename]["chars"] += line.length();

			string *words = getWords(line, filename);
			



			// cout << wordsLength << endl;
			fileCountMap[filename]["words"] += currWordLength;
			for(int j = 0; j < currWordLength; j++){
				// cout << words[j] << " ";
				cout << words[j] << " ";
			}
			cout << endl;
		fileCountMap[filename]["lines"]++;
	}
	
	printResults();
	return 0;
}

// ---------------------------------- MAIN -------------------------------------
int main(int argc, const char * argv[]) {

    for(int i = 1; i < argc; i++){

    	word = argv[i];

    	if(word[0] == '-'){
    		flagHandler(word);
		} else {
			fileHandler(word);
		}

    }

    if(!fileCount){
    	// IF NO FILE READ FROM STDIN
    	cout << "READING FROM STDIN" << endl;

    } else {
    	for(int i = 0; i < fileCount; i++){
    		fileParser(files[i]);
    	}
    }
    
    //FOR EVERY FILE
    // READ FILE
    // Search each line 
    // Put lines into array
    //
		cout << "-----------------------------" << endl;
		cout << "Word count: " << findWordCount << endl;
		cout << "Letter count: " << findCharCount << endl;
		cout << "File count: " << fileCount << endl;
		cout << "-----------------------------" << endl;


    return 0;
}
