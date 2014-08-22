#include "../include/util.h"
string longlongtostr(unsigned long long numb){
	string result;
	    stringstream ss;
	    ss<<numb;
	    ss>>result;
	    return result;
}
