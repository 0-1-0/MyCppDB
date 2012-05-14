#include <string>

using namespace std;

class StringTokenizer{
	
public:
	~StringTokenizer();
	
	string next(void);
	
	bool hasNext(void);
	
	void setInput(string line);
	
	string unzipValue(string value);
	
	string zipValue(string value);
	
private:
	void blank(void);
	
	void nextToken(void);
	
	int bi;
	string sval;
	string buffer;
};

