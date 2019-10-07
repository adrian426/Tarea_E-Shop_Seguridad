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

int main(int argc, char** argv, char** envp){
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    printOptions(getCookieKeyValue("UserId"));
    cout << "<h2>User submitted feedback</h2>\n";
    cout << "<a href='http://172.24.129.81/cgi-bin/Tarea1_Seguridad/add_claim'>Make your claim</a><br>";
    cout << "__________________________________________________________________________________________________________________";
    printClaims();
    cout << ("</body>\n");
    cout << ("</html>\n");

  return EXIT_SUCCESS;
}