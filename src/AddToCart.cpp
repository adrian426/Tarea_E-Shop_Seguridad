#include <iostream>
#include <sstream>
#include <cstdlib>
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;


void addItemToCartPrep(){
    vector<string> getData = getTokenPairs('&',getenv("QUERY_STRING"));
    string item_id = getKeyOrValue(getData[0],1);
    regex number ("[0-9]{1-10}");
    if(regex_match(item_id, number)){
        string session_id = getCookieKeyValue("SessionId");
        addItemToCart(item_id, session_id);
    }
}

int main(int argc, char** argv, char** envp){
    try{
        addItemToCartPrep();
    }catch(exception e){
        //item was already in cart
    }
    cout<<"Location: Home\r\n\r\n";
    return EXIT_SUCCESS;
}