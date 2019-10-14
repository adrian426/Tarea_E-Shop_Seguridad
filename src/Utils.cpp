#include <vector>
#include <iostream>
#include "string.h"
#include <math.h>
#include <time.h>
#include <regex>
using namespace std;

//The following two functions were obtained from https://www.fi.muni.cz/usr/jkucera/tic/tic0305.html

char translateHex(char hex){
    if(hex >= 'A'){
        return (hex & 0xdf) - 'A' + 10;
    } else {
        return hex - '0';
    }
}

string generate_random_string(){
    string chars = "1234567890-=_+qwertyuiopasdfghjklzxcvbnm.,[]{}!@#$%()";
    time_t t;
	srand(time( &t ));
    string rst = "";
    for(int i = 0; i < 24; i++){
        rst += chars[((int)rand() % (54))];
    }
    return rst;
}

string decode(string encoded_string){
    int len = encoded_string.length();
    string decoded_string = "";
    for(int i = 0; i < len; i++){
        if(encoded_string[i] == '+'){
            decoded_string += ' ';
        } else if(encoded_string[i] == '%'){
            decoded_string += translateHex(encoded_string[i+1]) *16 + translateHex(encoded_string[i+2]);
            i += 2;
        } else {
            decoded_string += encoded_string[i];
        }
    }
    return decoded_string;
}

vector<string> getTokenPairs(char dividingCharacter, string stringToSeparate){
    vector<string> tokens;
    stringstream stringToSeparateStream(stringToSeparate);
    string tmp;
    while(getline(stringToSeparateStream, tmp, dividingCharacter)){
        tokens.push_back(tmp);
    }
    return tokens;
}

string getKeyOrValue(string pairToDivide, int indicator){
    string currentValue;
    string value1;
    for(unsigned int j = 0; j < pairToDivide.length(); j++){
        //The key is formed, we restore the tmp string and make the value;
        if(pairToDivide[j] == '='){
            value1 = currentValue;
            currentValue = "";
        } else {
            currentValue += pairToDivide[j];
        }
    }
    if(indicator == 1){
        return decode(currentValue);
    } 
    return value1;
}

string get_string_without_char(char charToReplace, char newChar, string string_to_change){
    string rst = "";
    for(unsigned int i = 0; i < string_to_change.length(); i++){
        if(string_to_change[i] == charToReplace){
            if(newChar != '\0'){
                rst += newChar;   
            }
        } else {
            rst += string_to_change[i];
        }
    }
    return rst;
}

void printEnv(char ** envp){
  for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    cout << "\n";
    printf("%s\n<br>", thisEnv);
  }
}