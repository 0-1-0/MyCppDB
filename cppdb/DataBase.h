#include <string>
#include <map>
#include <string>

#include "Table.h";

using namespace std;

class DataBase {
	
public:
	~DataBase(void);
	map<string, Table> tables;
	Row r;
	
	string getDump(void);
	
private:
	map<string, Table>::iterator it;
	map<string, int>::iterator jt;	
	string res;
};

