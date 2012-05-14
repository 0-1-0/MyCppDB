#include <string>
#include <map>
#include <string>

#include "DataBase.h"
#include "StringTokenizer.h"

DataBase::~DataBase(void){
	tables.clear();
}

string DataBase::getDump(void){
	res = "";
	StringTokenizer st;
	for (it = tables.begin() ; it != tables.end(); it++ ){
		res += "CREATE " + (*it).first + " (";
		Table t = (*it).second;
		
		for (int j = 0; j < t.nameOfCols.size(); j++ ){
			res += t.colTypes[j] + " " + t.nameOfCols[j];
			if (j + 1 < t.nameOfCols.size()) {
				res += ",";
			}
		}
		res += ")\n";
		
		for (int i = 0; i < t.rows.size(); i++) {
			r = t.rows.at(i);
			
			res += "INSERT into " + (*it).first + " VALUES(";
			for(int j = 0; j < r.size(); j++){
				res += st.zipValue(r.at(j));
				if(j + 1 != r.size()) res += ",";
			}
			res += ")\n";
		}
	}
	
	return res;	
}

