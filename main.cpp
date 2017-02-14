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

using namespace std;

// ----------------------------- PRINT DATA ---------------------------------
// void *printData(int *lines, int *words, int *chars, string *fileName) {
// 	cout << lines << " " << words << " " << fileName;
// }

// // ------------------------------ GET WORDS ---------------------------------
// string *getWords(string in){
//     smatch sm;
//     regex wordReg ("\\s+"); //finds spaces, which we'll use to split up the words
//     sregex_token_iterator reg_end;

//     int i = 0;
//     int tokenCount = 0;
//     string tempy = "";
//     for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
//     	//check for matches here

//         i++;
//     }
//     string *newWords = new string[i];
//     wordCount = i;
    
//     int j = 0;
//     for(sregex_token_iterator it(in.begin(), in.end(), wordReg, -1); it != reg_end; ++it) {
//         newWords[j] = it->str();
//         j++;
//     }
//     return newWords;
// }


int main(int argc, const char * argv[]) {
	string word;
	string searchWord;
	string findChar = "-findchar=";
	string findWord = "-findword=";
	int findCharMatchCount;
	int findCharCount = 0;
	int findWordMatchCount;
	int findWordCount = 0;

    for(int i = 0; i < argc; i++){
    	findCharMatchCount = 0;
    	word = argv[i];

    	if(word[0] == '-'){
	        for(int j = 0; j < word.length(); j++){
	        	if(word[j] == findChar[j]){
	        		findCharMatchCount++;
	        	} 
	        	if(word[j] == findWord[j]){
	        		findWordMatchCount++;
	        	}
	        }
	        if(findCharMatchCount == 10){
		        if(word.length() != 11){
		        	cout << "Invalid entry for findchar. Expected char.";
		        	return 0;
		        } else {
		        	findCharCount++;
		        	cout<< word[10] << endl;
		        	// PUSH INTO LETTERS TO FIND.
		        }
		    } else if(findWordMatchCount == 10){
		    	if(word.length() <= 10){
		    		cout << "Invalid entry for findword. Expected word";
		    		return 0;
		    	} else {
		    		for(int x = 10; x < word.length(); x++ ){
		    			searchWord += word[x];
		    		}
		    		cout << searchWord;
		    	}
		    } else {
		    	cout << "Invalid flag";
		    	return 0;
		    }
		}

    }


    return 0;
}
