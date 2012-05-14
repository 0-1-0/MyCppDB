#include<string>

#include "StringUtils.h"

using namespace std;

bool eq(string s1, string s2){
	return (s1.compare(s2) == 0);
}

bool ueq(string s10, string s20){
	string s1 = s10;
	string s2 = s20;
	std::transform(s1.begin(), s1.end(), s1.begin(), std::toupper);
	std::transform(s2.begin(), s2.end(), s2.begin(), std::toupper);
	return eq(s1, s2);
}

