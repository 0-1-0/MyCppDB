#include <vector>
#include <sstream>
#include <map>

using namespace std;

typedef vector<string> Row;

class Table {
public:
	Table(void);	
	~Table(void);
	
	map<string, int> colNames;
	map<int, string> nameOfCols;
	map<int, string> colTypes;
	vector<Row> rows;	
	
};