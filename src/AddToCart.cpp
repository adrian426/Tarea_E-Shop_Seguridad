#include <iostream>
#include <sstream>
#include <cstdlib>
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;

void addItemToCartPrep(){
    //I think i should check if the item was already bought, since this ignores that.
    //and it could be added through QUERY_STRING
    string item_id = getKeyOrValue(getenv("QUERY_STRING"),1);
    string user_id = getCookieKeyValue("UserId");
    addItemToCart(item_id, user_id);
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