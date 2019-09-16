#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Model/Database.cpp"
// Include the Connector/C++ headers
using namespace std;

int main(int argc, char** argv, char** envp){
    if((getCookieKeyValue("UserId") == "")){
        cout << "Location: Home\r\n\r\n";
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    cout << "<h2>Items in your cart</h2>\n";
    cout << "<input type='button' value='Checkout' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/checkout'\"><br>";
    cout << "__________________________________________________________________________________________________________________";
    printCart((getCookieKeyValue("UserId")));
    cout << ("</body>\n");
    cout << ("</html>\n");

  return EXIT_SUCCESS;
}