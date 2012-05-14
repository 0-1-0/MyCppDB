#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "StringTokenizer.h"

using namespace std;

StringTokenizer::~StringTokenizer(){
	buffer.clear();
	sval.clear();
}

void StringTokenizer::setInput(string line){
	buffer = line;
	bi = 0;
	char invisible = '\241';
	
	for (int i = 0; i < buffer.length(); i++) {
		if ( (i + 1 < buffer.length()) && (buffer.at(i) == '\\') &&  (buffer.at(i + 1) == '\'')) {
			buffer.at(i + 1) = invisible;
		}
	}
	
	
	std::replace(buffer.begin(), buffer.end(), ',', ' ');
	std::replace(buffer.begin(), buffer.end(), '(', ' ');
	std::replace(buffer.begin(), buffer.end(), '\'', ' ');
	std::replace(buffer.begin(), buffer.end(), ')', ' ');
}

string StringTokenizer::unzipValue(string value){
	char invisible = '\241';
	
	string res = "";string sw = "";
	for (int i = 0; i < value.length(); i++) {
		if (value.at(i) == '\\' && i + 1 < value.length()) {
			
			if (value.at(i + 1) == '\\') {
				sw += value.at(i);
				i++;
			}else if (value.at(i + 1) == invisible) {
				sw += '\'';
				i++;
			}else if (value.at(i + 1) >= '0' && value.at(i + 1) <= '9') {
				char code = value.at(i + 1);
				int cd = 0;
				if (code == '1') cd += 1;if (code == '2') cd += 2;if (code == '3') cd += 3;if (code == '4') cd += 4;if (code == '5') cd += 5;if (code == '6') cd += 6;if (code == '7') cd += 7;if (code == '8') cd += 8;if (code == '9') cd += 9;
				int j = 1;
				
				while (  (i + j + 1 < value.length())   &&  (value.at(i + j + 1) >= '0') && value.at(i + j + 1) <= '9' ) {
					code = value.at(i + j + 1);
					cd = cd* 10;
					if (code == '1') cd += 1;if (code == '2') cd += 2;if (code == '3') cd += 3;if (code == '4') cd += 4;if (code == '5') cd += 5;if (code == '6') cd += 6;if (code == '7') cd += 7;if (code == '8') cd += 8;if (code == '9') cd += 9;
					j++;
				}
				
				sw += char(cd);
				i += j;
			}
			
		}else {
			sw += value.at(i);
		}
	}
	
	return sw;
}

string StringTokenizer::zipValue(string value){
	
	string sw = "";
	for (int i = 0; i < value.length(); i++) {
			 if (value.at(i) >= 'a' && value.at(i) <= 'z') {sw += value.at(i);}
		else if (value.at(i) >= '0' && value.at(i) <= '9') {sw += value.at(i);}
		else if (value.at(i) >= 'A' && value.at(i) <= 'Z') {sw += value.at(i);}
		else if (value.at(i) == '_' || value.at(i) == '-') {sw += value.at(i);}
		else {
			int code =  value.at(i);
			stringstream x;
			string s;
			
			x << code;
			x >> s;

			sw += '\\' + s;
		}

	}
	
	return sw;
}


void StringTokenizer::blank(void){
	while (bi < buffer.length() && buffer.at(bi) == ' ') {
		bi++;
	}
}

void StringTokenizer::nextToken(){
	int i = bi , j = 0;
	while (bi < buffer.length() && buffer.at(bi) != ' ') {
		bi++;
		j++;
	}	
	sval = buffer.substr(i, j);	
}

string StringTokenizer::next(){
	blank();
	nextToken();
	return sval;
}

bool StringTokenizer::hasNext(){
	for (int i = bi; i < buffer.length(); i++) {
		if (buffer.at(i) != ' ') {
			return true;
		}
	}
	return false;
}
