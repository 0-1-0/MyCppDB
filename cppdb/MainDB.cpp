#include <string>

#include "Table.h"

using namespace std;

#include "MainDB.h"

MainDB::MainDB(void){
}

MainDB::~MainDB(void){
	tables.clear();
}

Table MainDB::getTable(string name){
	return tables[name];
}

void MainDB::setTable(Table t, string name){
	tables[name] = t;
}

string	MainDB::getDBDump(void){
	string res = "";
	for (it = tables.begin() ; it != tables.end(); it++ ){
		res += "CREATE " + (*it).first + " (";
		Table t = (*it).second;
		
		for (int j = 0; j < t.nameOfCols.size(); j++ ){
			res += t.colTypes[j] + " " + t.nameOfCols[j];
			if(j + 1 != t.nameOfCols.size()) res += ",";
		}
		res += ")\n";
		
		for (int i = 0; i < t.rows.size(); i++) {
			r = t.rows.at(i);
			
			res += "INSERT into " + (*it).first + " VALUES(";
			for(int j = 0; j < r.size(); j++){
				res += r.at(j);
				if(j + 1 != r.size()) res += ",";
			}
			res += ")\n";
		}
	}
	
	return res;
}