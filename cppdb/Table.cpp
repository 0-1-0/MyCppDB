#include <map>
#include <vector>

using namespace std;

#include "Table.h"

Table::Table(void){
}

Table::~Table(void){
	colNames.clear();
	colTypes.clear();
	rows.clear();
}
