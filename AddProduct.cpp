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
using namespace sql::mysql;

void addProduct(string post){
    string seller = getCookieKeyValue("UserId");
    vector<string> postData = getTokenPairs('&', post);
    AddProductToSale(getKeyOrValue(postData[0],1),getKeyOrValue(postData[1],1),getKeyOrValue(postData[2],1),seller);
}

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    int error_adding_product = 0;
    try{//Try to add the user to the database.
        if(post != ""){//Call the user registry.
            addProduct(post);
            //cout << "Location: http://localhost/cgi-bin/Tarea1_Seguridad/Home\r\n\r\n";
        }
    } catch (exception e){//If a value from the form is not unique in the db (except fullname), it will fail and set the error.
        error_adding_product = 1;
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    cout << ("<form action='add_product' METHOD='POST'>\n");
    cout << ("<h2><b>Add a Product to sale</b></h2>\n");
    if(error_adding_product != 0 ){
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