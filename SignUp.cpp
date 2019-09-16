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

void createUserFromPost(string post){
    vector<string> postData = getTokenPairs('&',post);
    CreateUser(getKeyOrValue(postData[0],1),getKeyOrValue(postData[1],1), getKeyOrValue(postData[2],1), getKeyOrValue(postData[3],1));
}

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    int error_creating_user = 0;
    try{//Try to add the user to the database.
        if(post != ""){//Call the user registry.
            createUserFromPost(post);
            cout << "Location: http://localhost/cgi-bin/Tarea1_Seguridad/Home\r\n\r\n";
        }
    } catch (exception e){//If a value from the form is not unique in the db (except fullname), it will fail and set the error.
        error_creating_user = 1;
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    cout << ("<form action='sign_up' METHOD='POST'>\n");
    cout << ("<h2><b>Sign Up</b></h2>\n");
    if(error_creating_user != 0 ){
        cout << "<h4>There was an error creating the user, try with other values.</h4>";
    }
    cout << ("<div><label>Enter your Username:</label><br><input name='username' required></div><br>\n");
    cout << ("<div><label>Enter your Name:</label><br><input name='name' required></div><br>\n");
    cout << ("<div><label>Enter your E-mail:</label><br><input name='email' type='email' required></div><br>\n");
    cout << ("<div><label>Enter your Phone number:</label><br><input type=\"tel\" name=\"phone\" pattern=\"[0-9]{8}\" required></div><br>\n");
    cout << ("<div><input type='button' value='Cancel' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/Home'\"> <input type='submit' value='Sign up'></div>\n");
    cout << ("</form>\n");
    cout << ("</body>\n");
    cout << ("</html>\n");
    return EXIT_SUCCESS;
}