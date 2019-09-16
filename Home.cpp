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
    string keyword = "";
    string get = getenv("QUERY_STRING");
    if( get != ""){
      keyword = get;
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    cout << "<h2>Product List</h2>\n";
    cout << ("<form action='Home' METHOD='GET'>\n");
    cout << ("<div><label>Keyword search:</label><br><input name='keyword'></div><br>\n");
    cout << ("<div><input type='submit' value='Search'></div>\n");
    cout << ("</form>\n");
    cout << "__________________________________________________________________________________________________________________";
    printProductList((getCookieKeyValue("UserId") != "")? true:false, getKeyOrValue(keyword, 1));
    cout << ("</body>\n");
    cout << ("</html>\n");

  return EXIT_SUCCESS;
}