#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;

string get_censored_card(string card){
    string censored = "";
    for(int i = 0; i < 16; i++){
        if(i < 12){
            censored += "X";
        } else {
            censored += card[i];
        }
    }
    return censored;
}

int PaymentSimulation(){
    vector<string> post = getTokenPairs('&', getPostData());
    regex card ("[0-9]{16}");
    string session_id = getCookieKeyValue("SessionId");
    string card_number = getKeyOrValue(post[0],1);
    if(regex_match(card_number, card)){
        try{
            checkoutCart(session_id, get_censored_card(card_number));
        }catch(exception e){
            return -1;
        }
        return 1;
    }
    return 0;
}

int main(int argc, char** argv, char** envp){
    bool session = sessionStatus();
    if(!session){
        cout << "Location: Home\r\n\r\n";
    }
    int rst = PaymentSimulation();
    if(rst == 1){
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<body>\n";
        printOptions(session);
        cout << "<h2>You have succesfully bought all the items in your cart.</h2>\n";
        cout << "<input type='button' value='Continue' onclick=\"location.href='http://172.24.129.81/cgi-bin/Tarea1_Seguridad/Home'\">";
        cout << ("</body>\n");
        cout << ("</html>\n");
    } else {
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<body>\n";
        printOptions(session);
        if(rst == -1){
            cout << "<h2>An error ocurred while checking out your shopping cart.</h2>\n";
        } else {
            cout << "<h2>Invalid Card number entered.</h2>\n";
        }
        cout << "<input type='button' value='Cart' onclick=\"location.href='http://172.24.129.81/cgi-bin/Tarea1_Seguridad/review_cart'\">";
        cout << ("</body>\n");
        cout << ("</html>\n");
    }
  return EXIT_SUCCESS;
}
