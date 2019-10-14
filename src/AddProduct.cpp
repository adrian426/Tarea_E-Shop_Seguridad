#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;
using namespace sql::mysql;

bool check_fields(string name, string descp, string price){
    if(get_string_without_char(' ', '\0', name) == "" || !regex_match(name, get_generic_regex())){
        return false;
    }
    regex gen ("[\\w \\,\\.\\n]+");
    if(get_string_without_char(' ', '\0', descp) == "" || !regex_match(descp, get_generic_regex())){
        return false;
    }
    regex number("[0-9]{1-10}");
    if(!regex_match(price, number)){
        return false;
    }

    return true;
}

int addProduct(string post){
    vector<string> postData = getTokenPairs('&', post);
    string name = getKeyOrValue(postData[0],1);
    string descp = getKeyOrValue(postData[1],1);
    string price = getKeyOrValue(postData[2],1);
    if(check_fields(name, descp, price)){
        string sessionId = getCookieKeyValue("SessionId");
        try{
            AddProductToSale(getKeyOrValue(postData[0],1),getKeyOrValue(postData[1],1),getKeyOrValue(postData[2],1),sessionId);
        } catch(exception e) {
            return -1;
        }
        return 1;
    }
    return 0;
}

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    int error_adding_product = 0;
    bool session = sessionStatus();
    if(!session){
        cout << "Location: Home\r\n\r\n";
    }
    if(post != ""){
        error_adding_product = addProduct(post);
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    printOptions(session);
    cout << ("<form action='add_product' METHOD='POST'>\n");
    cout << ("<h2><b>Add a Product to sale</b></h2>\n");
    if(error_adding_product == 0 ){
        cout << "<h4>Invalid character found in the submitted form.</h4>";
    } else if (error_adding_product == -1) {
        cout << "<h4>There was an error publishing your sale.</h4>";
    }
    cout << ("<div><label>Product name:</label><br><input name='name' required></div><br>\n");
    cout << ("<div><label>Product description:</label><br><textarea rows='3' name='desc' required></textarea></div><br>\n");
    cout << ("<div><label>Product price:</label><br><input type=\"tel\" name=\"price\" pattern=\"[0-9]{1,11}\" required></div><br>\n");
    cout << ("<div><input type='button' value='Cancel' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/Home'\"> <input type='submit' value='Submit'></div>\n");
    cout << ("</form>\n");
    cout << ("</body>\n");
    cout << ("</html>\n");
    return EXIT_SUCCESS;
}