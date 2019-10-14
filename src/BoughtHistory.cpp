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
    cout << "<h2>Shopping History</h2>\n";
    cout << "__________________________________________________________________________________________________________________";
    printBoughtItems((getCookieKeyValue("SessionId")));//TODO: SACAR EL ID DE SESSION DEL LOGIN.
    cout << ("</body>\n");
    cout << ("</html>\n");

  return EXIT_SUCCESS;
}