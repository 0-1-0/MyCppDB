#include <string>

#include "Table.h"

using namespace std;

class MainDB {
public:
	MainDB(void);
	~MainDB(void);
	
	Table getTable(string name);
	
	void setTable(Table t, string name);
	
	string	getDBDump(void);
private:
	map<string, Table> tables;
	map<string, Table>::iterator it;
	map<string, int>::iterator jt;
};

