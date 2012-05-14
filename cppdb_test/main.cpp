#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

char *DB_FILE_PATH = "/db.txt";
char *SELECT_TEST_PATH = "/select.txt.right";

int main (int argc, char * const argv[]) {
	
/////////APPLICATION AREA////////////////////////////////////////    
	fstream File;
	File.open(DB_FILE_PATH, ios::out);
	
	File << "CREATE table1 (Int i1, Int i2, Int i5, Int i10, Int i100)" << endl;
	
	for (int i = 0; i < 50000; i++) {
		File << "INSERT into table1 VALUES (" << i << "," << i/2 << "," << i/5 << "," << i/10 << "," << i/100 << ")" << endl;
	}
	
	File << "DELETE FROM table1 WHERE i10 > 10 AND i10 < 20" << endl;  // Condition1
	File << "DELETE FROM table1 WHERE i5 > 10 AND i5 < 20" << endl;
	
	File << "SELECT * FROM table1 WHERE i100 > 20 AND i100 < 23" << endl; //Condition 2
	
	File.close();	
	
/////////TEST AREA////////////////////////////////////////  
	File.open(SELECT_TEST_PATH, ios::out);
	
	for (int i = 0; i < 50000; i++){ // (!Condition1) && Condition 2
		if (	 !( (i/10 > 10 && i/10 < 20) && (i/5 > 10 && i/5 < 20) ) && 
			     (i/100 > 20 && i/100 < 23)	
		) { 
			File << "i1 = " << i << " i2 = " << i/2 << " i5 = " << i/5 << " i10 = " << i/10 << " i100 = " << i/100 << " " << endl;
		}
	}	
	
	File.close();

	
    return 0;
}
