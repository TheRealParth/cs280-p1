//
//  main.cpp
//  cs280project1
//
//  Created by parth patel on 2/13/17.
//  Copyright © 2017 Parth. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>

using namespace std;
//fileCountMap[filename][lines]   fileCountMap[filename][words]  fileCountMap[filename][chars]

map <string, map <string, int>> fileCountMap;
map <char, map <string, map <string, int>>> charCountMap;
map <string, map <string, map <string, int>>> wordCountMap;
map <string, int> stdinCountMap;


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
string *getWords(string &in){
	int inSpace = 0;
	currWordLength = 0;
	int i = 0;

	if(!isspace(in[i])){
		currWordLength++;
	} else {
		inSpace = 1;
	}

	while(i < in.length()){
		
		while(!inSpace && (i<in.length())){
			if(isspace(in[i])){
				inSpace = 1;
				currWordLength++;
			}
			i++;
		}
		while(inSpace && (i<in.length())){
			if(!isspace(in[i])){
				inSpace = 0;
			}

			i++;
		}

	}

	i = 0;
	int j = 0;

	string *newWords = new string[currWordLength];

	while(i < in.length()){

		while(!inSpace && (i<in.length())){

			if(isspace(in[i])){
				inSpace = 1;
				j++;
			} else {
				newWords[j] += in[i];
			}
			i++;
			
		}
		while(inSpace && (i<in.length())){
			if(!isspace(in[i])){
				newWords[j] += in[i];
				inSpace = 0;
			}
			i++;
		}
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
	    		words[findWordCount] = searchWord;
	    		findWordCount++;
	    	}
			
		}
	} else if (findWordMatchCount == 9) {
		return poorlyFormedError(flag);
	} 
 	else if (findCharMatchCount == 9) {
 		return poorlyFormedError(flag);
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
	int totalLines = 0;
	int totalWords = 0;
	int totalChars = 0;

	if(fileCount){
		for(int i = 0; i < fileCount; i ++ ) {
			cout << setw(12) << right << fileCountMap[files[i]]["lines"]
			     << setw(12) << right << fileCountMap[files[i]]["words"]
				 << setw(12) << right << fileCountMap[files[i]]["chars"]
				 << setw(12) << left << " " + files[i] << endl;

			totalLines += fileCountMap[files[i]]["lines"];
			totalWords += fileCountMap[files[i]]["words"];
			totalChars += fileCountMap[files[i]]["chars"];
		}
		if(fileCount > 1){
			//PRINT TOTALS
			cout << setw(12) << right << totalLines
				<< setw(12) << right << totalWords 
				<< setw(12) << right << totalChars
				<< setw(12) << left << " total" << endl;
		}
		//PRINT WORDS ===================================
		for(int i=0; i < findWordCount; i++){
			int totalLines = 0;
			int totalWords = 0;
			for(int j=0; j<fileCount; j++){
				cout << left << words[i] + ":"
					<< setw(12) << right << wordCountMap[words[i]][files[j]]["lines"]
					<< setw(12) << right << wordCountMap[words[i]][files[j]]["words"]
			    	<< setw(12) << left << " " + files[j] << endl;

			    totalLines += wordCountMap[words[i]][files[j]]["lines"];
			    totalWords += wordCountMap[words[i]][files[j]]["words"];
			}
			if(fileCount > 1){
				cout << left << words[i] + ":"
					<< setw(12) << right << totalLines
					<< setw(12) << right << totalWords 
					<< setw(12) << left << " total" << endl;
			}

		}
		//PRINT CHARS ===================================
		for(int i=0; i < findCharCount; i++){
			int totalLines = 0;	
			int totalWords = 0;
			int totalChars = 0;
			for(int j=0; j<fileCount; j++){

				cout << left << chars[i] << ':'
				 	<< setw(12) << right << charCountMap[chars[i]][files[j]]["lines"]
				 	<< setw(12) << right << charCountMap[chars[i]][files[j]]["words"]
				 	<< setw(12) << right << charCountMap[chars[i]][files[j]]["chars"]
			    	<< setw(12) << left << " " + files[j] << endl;
			    totalChars += charCountMap[chars[i]][files[j]]["chars"];
			    totalLines += charCountMap[chars[i]][files[j]]["lines"];
			    totalWords += charCountMap[chars[i]][files[j]]["words"];
			}

			if(fileCount > 1){
				cout << left << chars[i] << ':'
					<< setw(12) << right << totalLines
					<< setw(12) << right << totalWords
					<< setw(12) << right << totalChars 
					<< setw(12) << left << " total" << endl;
			}
		}
	} else {
		cout << setw(12) << right << stdinCountMap["lines"]
		     << setw(12) << right << stdinCountMap["words"]
			 << setw(12) << right << stdinCountMap["chars"] << endl;

		//PRINT WORDS ===================================
		for(int i=0; i < findWordCount; i++){
			cout << left << words[i] + ":"
				<< setw(12) << right << wordCountMap[words[i]]["stdin"]["lines"]
				<< setw(12) << right << wordCountMap[words[i]]["stdin"]["words"]
		    	<< endl;
		}
		//PRINT CHARS ===================================
		for(int i=0; i < findCharCount; i++){
			int totalLines = 0;	
			int totalWords = 0;
			int totalChars = 0;

			cout << left << chars[i] << ':'
			 	<< setw(12) << right << charCountMap[chars[i]]["stdin"]["lines"]
			 	<< setw(12) << right << charCountMap[chars[i]]["stdin"]["words"]
			 	<< setw(12) << right << charCountMap[chars[i]]["stdin"]["chars"]
		        << endl;
		}
	}

	return 0;
}
// ------------------------------- FILE PARSER ---------------------------------
int fileParser(string &filename){
	string line;
	int wordCount = 0;
	int charCount = 0;

	fileCountMap[filename]["lines"] = 0;
	fileCountMap[filename]["words"] = 0;
	fileCountMap[filename]["chars"] = 0;
	for(int i=0; i < findCharCount; i++){
		charCountMap[chars[i]][filename]["lines"] = 0;
		charCountMap[chars[i]][filename]["words"] = 0;
		charCountMap[chars[i]][filename]["chars"] = 0;
	}
	for(int i=0; i < findWordCount; i++){
		wordCountMap[words[i]][filename]["lines"] = 0;
		wordCountMap[words[i]][filename]["words"] = 0;
		wordCountMap[words[i]][filename]["chars"] = 0;
	}
	ifstream file (filename);

	if(!file.is_open()) fileNotFoundError(filename);

	int i = 0;
	int wordsLength;

	while(getline(file, line)){
		fileCountMap[filename]["lines"]++;
		fileCountMap[filename]["chars"]+= line.length() + 1;
		if(!line.length()) continue;



		string *sWords = getWords(line);

		int foundWord = 0;
		for(int i=0; i < findWordCount; i++){
			for(int j=0; j<currWordLength; j++){
				if(sWords[j] == words[i]){
					wordCountMap[words[i]][filename]["words"]++;
					foundWord = 1;
				}
			}
			if(foundWord){
				wordCountMap[words[i]][filename]["lines"]++;
				foundWord = 0;
			}
		}
		int foundChar = 0;
		int foundCharCount;
		for(int i=0; i < findCharCount; i++){
			foundCharCount = 0;
			for(int j=0; j<currWordLength; j++){
				for(int k=0; k < sWords[j].length(); k++){
					if(sWords[j][k] == chars[i]) {
						charCountMap[chars[i]][filename]["chars"]++;
						foundCharCount++;
					}
				}
				if(foundCharCount){
					charCountMap[chars[i]][filename]["words"]++;
					foundChar = 1;
					foundCharCount = 0;
				}
			}
			if(foundChar){
				charCountMap[chars[i]][filename]["lines"]++;
				foundChar = 0;
			}
		}

		fileCountMap[filename]["words"] += currWordLength;
		
	}
	
	return 0;
}
// ------------------------------- STDIN PARSER ---------------------------------
int stdinParser(){
	string line;
	int wordCount = 0;
	int charCount = 0;
	stdinCountMap["lines"] = 0;
	stdinCountMap["words"] = 0;
	stdinCountMap["chars"] = 0;

	for(int i=0; i < findCharCount; i++){
		charCountMap[chars[i]]["stdin"]["lines"] = 0;
		charCountMap[chars[i]]["stdin"]["words"] = 0;
		charCountMap[chars[i]]["stdin"]["chars"] = 0;
	}
	for(int i=0; i < findWordCount; i++){
		wordCountMap[words[i]]["stdin"]["lines"] = 0;
		wordCountMap[words[i]]["stdin"]["words"] = 0;
	}
	while (getline(cin, line)) {
		if(cin.eof()) break;

		stdinCountMap["lines"]++;
		stdinCountMap["chars"]+= line.length() + 1;
		if(!line.length()) continue;

		string *sWords = getWords(line);
		int foundWord = 0;
		for(int i=0; i < findWordCount; i++){
			for(int j=0; j<currWordLength; j++){
				if(sWords[j] == words[i]){
					wordCountMap[words[i]]["stdin"]["words"]++;
					foundWord = 1;
				}
			}
			if(foundWord){
				wordCountMap[words[i]]["stdin"]["lines"]++;
				foundWord = 0;
			}
		}
		int foundChar = 0;
		int foundCharCount;
		for(int i=0; i < findCharCount; i++){
			foundCharCount = 0;
			for(int j=0; j<currWordLength; j++){
				for(int k=0; k < sWords[j].length(); k++){
					if(sWords[j][k] == chars[i]) {
						charCountMap[chars[i]]["stdin"]["chars"]++;
						foundCharCount++;
					}
				}
				if(foundCharCount){
					charCountMap[chars[i]]["stdin"]["words"]++;
					foundChar = 1;
					foundCharCount = 0;
				}
			}
			if(foundChar){
				charCountMap[chars[i]]["stdin"]["lines"]++;
				foundChar = 0;
			}
		}


	}



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
    	stdinParser();
    } else {
    	for(int i = 0; i < fileCount; i++){
    		fileParser(files[i]);
    	}
    }

    printResults();

    return 0;
}
