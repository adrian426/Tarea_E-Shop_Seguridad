#include <iostream>
#include <sstream>
#include <cstdlib>

// Include the Connector/C++ headers
using namespace std;

string getPostData(){
    string data = "";
    char * cnt_len = getenv("CONTENT_LENGTH");
    if(cnt_len != NULL){
      char* ptr;
      int data_len = atoi(cnt_len);
      ptr = new char[data_len];
      cin.read(ptr,data_len);
      data = ptr;
    }
    return data;
}
