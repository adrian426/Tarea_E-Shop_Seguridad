#include <iostream>
#include <sstream>
#include <vector>
#include "string.h"
using namespace std;

const string past_time_to_kill_cookie = "01 Jan 1960 12:00:00 GMT";


int setCookiePair(string key, string value){
    cout << "Set-Cookie:" + key + " = " + value + ";\r\n";
    return 0;
}

void killCookie(){
    cout << "Set-Cookie:Expires = " + past_time_to_kill_cookie + ";\r\n";
    cout << "Set-Cookie:UserId = ;\r\n";
}


string getCookieKeyValue(string key){
    string foundValue = "";
    vector<string> tokens;
    bool found = false;
    try{
        string cookieString = getenv("HTTP_COOKIE");
        stringstream cookie(cookieString);
        string tmp;
        string tmpKey;
        string tmpValue;
        while(getline(cookie, tmp, ';')){
            tokens.push_back(tmp);
        }
        tmp = "";
        //Iterate through the pairs to get the searched token value;
        for(unsigned int i = 0; i < tokens.size() && !found; i++){
            for(unsigned int j = 0; j < tokens[i].length(); j++){
                //The key is formed, we restore the tmp string and make the value;
                if(tokens[i][j] == '='){
                    tmpKey = tmp;
                    tmp = "";
                } else {
                    tmp += tokens[i][j];
                }
            }
            tmpValue = tmp;
            tmp = "";
            //we found the searched key and return its value;
            if(tmpKey == key){
                foundValue = tmpValue;
                found = true;
            }
            tmpKey = "";
            tmpValue ="";
        }
    } catch (exception e) {
       foundValue = "";
    }
    return foundValue;
}