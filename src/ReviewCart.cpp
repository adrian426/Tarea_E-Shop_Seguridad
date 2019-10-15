#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;

int main(int argc, char** argv, char** envp){
    bool session = sessionStatus();
    if(!session){
        cout << "Location: Home\r\n\r\n";
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    printOptions(session);
    cout << ("<form action='checkout' METHOD='POST'>\n");
    cout << ("<h2><b>Buy</b></h2>\n");
    cout << ("<div><label>Enter your card number:</label><br><input name='cardNumber' type='tel' pattern=\"[0-9]{16}\" required></div><br>\n");
    cout << ("<div><label>CSC:</label><br><input name='csc' type='telr' pattern=\"[0-9]{3}\" required></div><br>\n");
    cout << ("<div><input type='submit' value='Checkout'></div>\n");
    cout << ("</form>\n");
    cout << "<h2>Items in your cart</h2>\n";
    //cout << "<input type='button' value='Checkout' onclick=\"location.href='localhost/cgi-bin/Tarea1_Seguridad/checkout'\"><br>";
    cout << "__________________________________________________________________________________________________________________";
    printCart((getCookieKeyValue("SessionId")));
    cout << ("</body>\n");
    cout << ("</html>\n");

  return EXIT_SUCCESS;
}