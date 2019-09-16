#include <iostream>
#include <sstream>
#include <cstdlib>
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Model/Database.cpp"
// Include the Connector/C++ headers
using namespace std;

void removeItemFromCartPrep(){
    //I think i should check if the item was already bought, since this ignores that and the query_string can be added with one unavailable item.
    string item_id = getKeyOrValue(getenv("QUERY_STRING"),1);
    string user_id = getCookieKeyValue("UserId");
    removeItemFromCart(item_id, user_id);
}

int main(int argc, char** argv, char** envp){
    try{
        removeItemFromCartPrep();
    }catch(exception e){
        //item wasn't in the cart, or other problem that should be handled.
    }
    cout<<"Location: review_cart\r\n\r\n";
    return EXIT_SUCCESS;
}