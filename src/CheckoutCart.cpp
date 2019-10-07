#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Database.cpp"
// Include the Connector/C++ headers
using namespace std;

int PaymentSimulation(){
    vector<string> post = getTokenPairs('&', getPostData());
    string user_id = getCookieKeyValue("UserId");
    string card_number = getKeyOrValue(post[0],1);
    checkoutCart(user_id, card_number);
    return 0;
}

int main(int argc, char** argv, char** envp){
    if((getCookieKeyValue("UserId") == "")){
        cout << "Location: Home\r\n\r\n";
    }
    try{
        PaymentSimulation();
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<body>\n";
        printOptions(getCookieKeyValue("UserId"));
        cout << "<h2>You have succesfully bought all the items in your cart.</h2>\n";
        cout << "<input type='button' value='Continue' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/Home'\">";
        cout << ("</body>\n");
        cout << ("</html>\n");
    }catch(exception e){
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<body>\n";
        cout << e.what();
        printOptions(getCookieKeyValue("UserId"));
        cout << "<h2>An error ocurred while checking out your shopping cart..</h2>\n";
        cout << "<input type='button' value='Cart' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/review_cart'\">";
        cout << ("</body>\n");
        cout << ("</html>\n");
    }
  return EXIT_SUCCESS;
}