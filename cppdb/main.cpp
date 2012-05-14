#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "StringConsts.h"
#include "StringTokenizer.h"
#include "StringUtils.h"
#include "DataBase.h";

using namespace std;

string cmd;
string tableName;
string token;
string input;

DataBase db;

int main (int argc, char * const argv[]) {	
	StringTokenizer st;
	
	fstream infile;
	infile.open(DB_FILE_PATH);
	bool fromFile = true;
	
	while (true) {		
		fromFile = !infile.eof();
		
		if (fromFile)
			getline(infile, input, '\n');
		else
			getline(cin, input, '\n');
		
		st.setInput(input);
		
		cmd = st.next();//get command
		
////////////////////////////////SELECT///////////////////////////////////////		
		if (eq(cmd,SELECT_CMD)) {
			
			
			////////////////TEST
			fstream File;
			File.open(SELECT_TEST_PATH, ios::out);
			////////////////END TEST
			
			
			vector<string> rowNames;
			token = st.next();
						
			while (!ueq(token,FROM_EXPR)) {
				rowNames.push_back(token);
				token = st.next();
			}
			
			tableName = st.next();			
			Table t = db.tables[tableName];
					
			if (rowNames.size() == 1 && eq(rowNames.at(0), ALL_LITERAL)) { //add all if *
				rowNames.clear();
				for (int i = 0; i < t.nameOfCols.size(); i++ ){
					rowNames.push_back(t.nameOfCols[i]);
				}
			}
			
			vector<string> conditions;			
			if (st.hasNext()) {
				token = st.next();
			}
			
			if (eq(token, WHERE_EXPR)) {
				while (st.hasNext()) {
					token = st.next();
					if(!ueq(token, AND_STATEMENT))
					conditions.push_back(token);
				}
			}			
						
			for (int i = 0; i < t.rows.size(); i++) {
				db.r = t.rows.at(i);
				
				bool showRow = true;
				
				for (int j = 0; j < conditions.size(); j++) {
					string colName = conditions.at(j); j++;
					string condType = conditions.at(j); j++;
					string condValue = conditions.at(j);
					string cellValue = db.r.at(t.colNames[colName]);
					
					if (eq(condType, CND_EQ)) {
						showRow = eq(condValue, db.r.at(t.colNames[colName]));
					}
					
					if (eq(condType, CND_GE) || eq(condType, CND_LE)) {
						istringstream s0(cellValue);
						int i0;
						s0 >> i0;
						istringstream s1(condValue);
						int i1;
						s1 >> i1;
						
						if (eq(condType, CND_GE)) {
							showRow = (i0 > i1);
						}
						
						if (eq(condType, CND_LE)) {
							showRow = (i0 < i1);
						}
					}
					
					if (!showRow)
						break;
				}
				
				if(showRow){
					for (int j = 0; j < rowNames.size(); j++) {
						cout << rowNames.at(j) << " = " << db.r.at(t.colNames[rowNames.at(j)]) << " ";
					}
					cout << endl;
					
					////////////////TEST
					for (int j = 0; j < rowNames.size(); j++) {
						File << rowNames.at(j) << " = " << db.r.at(t.colNames[rowNames.at(j)]) << " ";
					}
					File << endl;
					////////////////END TEST
				}
			}
			
			////////////////TEST
			File.close();
			////////////////END TEST
			
			db.r.clear();
		}

////////////////////////////////SHOW DUMP///////////////////////////////////////
		if (eq(cmd,DUMP_CMD)) {
			cout << db.getDump();
		}

////////////////////////////////CREATE///////////////////////////////////////
		if (eq(cmd,CREATE_CMD)) {
			tableName = st.next();
			Table t;
			
			int i = 0;
				while (st.hasNext()) {
					token = st.next();		
					t.colTypes[i] = token;
					token = st.next();		
					t.colNames[token] = i;
					t.nameOfCols[i] = token;
					i++;
				}
			
			db.tables[tableName] = t;
			
			cout << "table " + tableName + " was successfully created" << endl;
		}

////////////////////////////////INSERT///////////////////////////////////////
		if (eq(cmd,INSERT_CMD)) {			
			st.next();//into			
			tableName = st.next();
			
			if (st.hasNext()) {
				vector<string> newRow;
				
				token = st.next();
				if (ueq(token, VALUES_EXPR)) {
					while (st.hasNext()){	
						token = st.unzipValue(st.next());	
						newRow.push_back(token);
					}
					
					db.tables[tableName].rows.push_back(newRow);	
					newRow.clear();
					
					cout << "values successfully inserted into " + tableName << endl;
				}
			}			
		}
		
////////////////////////////////DELETE///////////////////////////////////////
		if (eq(cmd,DELETE_CMD)) {
			token = st.next();
			
			while (!ueq(token,FROM_EXPR)) 
				token = st.next();
			
			tableName = st.next();			
			Table t = db.tables[tableName];
			
			vector<string> conditions;	
			vector<Row> newRows;
			if (st.hasNext()) {
				token = st.next();
				
				if (eq(token, WHERE_EXPR)) {
					while (st.hasNext()) {
						token = st.next();
						if(!eq(token, AND_STATEMENT))
							conditions.push_back(token);
					}
				}			
				
				for (int i = 0; i < t.rows.size(); i++) {
					db.r = t.rows.at(i);
					
					bool delRow = true;
					
					for (int j = 0; j < conditions.size(); j++) {
						string colName = conditions.at(j); j++;
						string condType = conditions.at(j); j++;
						string condValue = conditions.at(j);
						string cellValue = db.r.at(t.colNames[colName]);
						
						if (eq(condType, CND_EQ)) {
							delRow = eq(condValue, db.r.at(t.colNames[colName]));
						}
						
						if (eq(condType, CND_GE) || eq(condType, CND_LE)) {
							istringstream s0(cellValue);
							int i0;
							s0 >> i0;
							istringstream s1(condValue);
							int i1;
							s1 >> i1;
							
							delRow = (i0 > i1);
							if (eq(condType, CND_LE)) {
								delRow = !delRow;
							}
						}
						
						if (!delRow)
							break;
					}
					
					if(!delRow){
						newRows.push_back(db.r);
					}
				}
			}
			
			int delta = t.rows.size() - newRows.size();
			db.tables[tableName].rows = newRows;
			
			newRows.clear();
			
			cout << delta << " rows deleted from " + tableName << endl;
			
		}

////////////////////////////////SHUTDOWN AND SAVE///////////////////////////////////////		
		if (cmd.compare(SHUTDOWN_CMD) == 0) { //shutdown and dump database to file
			cout << "shutting down.." << endl;
			infile.close();
			
			fstream File;
			File.open(DB_FILE_PATH, ios::out);
			
			File << db.getDump();
			
			File.close();		
			exit(0);
		}
		
	}
	
    
    return 0;
}
