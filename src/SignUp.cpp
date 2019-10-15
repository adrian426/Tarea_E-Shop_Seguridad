#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Encryption.cpp"
using namespace std;

int check_form_data(vector<string> postData){
    regex fullname_regex("[a-zA-Z]+[ a-zA-Z]*");
    regex username_regex ("^[a-zA-Z0-9\\_\\-\\.]{2,29}");
    regex password_regex ("[\\_\\-\\.0-9a-zA-Z]{3,20}");
    regex email_regex ("[a-zA-Z0-9\\_\\-\\.]+\\@[a-zA-Z][a-zA-Z\\.]+");
    regex phoneNumber_regex ("[0-9]{8}");
    string username = get_string_without_char(' ', '\0' ,getKeyOrValue(postData[0],1));
    string fullname = get_string_without_char(' ', '\0' ,getKeyOrValue(postData[1],1));
    string email = get_string_without_char(' ', '\0' ,getKeyOrValue(postData[2],1));
    string phone = get_string_without_char(' ', '\0' ,getKeyOrValue(postData[3],1));
    string password = get_string_without_char(' ', '\0' ,getKeyOrValue(postData[4],1));
    
    if(username == "" || !regex_match(username, username_regex)){
        return false;
    }
    
    if(password == "" || !regex_match(password, password_regex)){
        return false;
    }

    if(email == "" || !regex_match(email, email_regex)){
        return false;
    }

    if(fullname == "" || !regex_match(fullname, fullname_regex)){
        return false;
    }

    if(phone == "" || !regex_match(phone, phoneNumber_regex)){
        return false;
    }

    return true;
}

int check_password_match(vector<string> postData){
    //postData[4] = password;
    //postData[5] = password_conf
    if(getKeyOrValue(postData[4],1) != getKeyOrValue(postData[5],1)){
        return 0;// passwords dont match.
    }
    return 1;//passwords match.
}

void createUserFromPost(vector<string> postData){
    //TODO: AGREGAR PASSWORD.
    string username = getKeyOrValue(postData[0],1);
    string password = getKeyOrValue(postData[4],1);
    string hashed_password = hash_password(password, username);
    CreateUser(getKeyOrValue(postData[0],1),getKeyOrValue(postData[1],1), getKeyOrValue(postData[2],1), getKeyOrValue(postData[3],1), hashed_password);
}

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    vector<string> postData = getTokenPairs('&',post);
    int error_creating_user = 0;
    if(post != ""){
        if(check_form_data(postData)){
            if(check_password_match(postData)){//Call the user registry.
                try{//Try to add the user to the database.
                    createUserFromPost(postData);
                    cout << "Location: Home\r\n\r\n";
                } catch (exception e){//If a value from the form is not unique in the db (except fullname), it will fail and set the error.
                    error_creating_user = 1;
                }
            } else {
                error_creating_user = 2;
            }
        } else {
            error_creating_user = 3;
        }
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    printOptions(sessionStatus());
    cout << ("<form action='sign_up' METHOD='POST'>\n");
    cout << ("<h2><b>Sign Up</b></h2>\n");
    if(error_creating_user != 0 ){
        if(error_creating_user == 1){
            cout << "<h4>There was an error creating the user, try with other values.</h4>";    
        } else if(error_creating_user == 2){
            cout << "<h4>The passwords entered do not match.</h4>"; 
        } else if(error_creating_user == 3){
            cout << "<h4>A field had unexpected values, try again.</h4>"; 
        }
    }
    cout << ("<div><label>Enter your Username:</label><br><input name='username' required></div><br>\n");
    cout << ("<div><label>Enter your Name:</label><br><input name='name' required></div><br>\n");
    cout << ("<div><label>Enter your E-mail:</label><br><input name='email' type='email' required></div><br>\n");
    cout << ("<div><label>Enter your Phone number:</label><br><input type=\"tel\" name=\"phone\" pattern=\"[0-9]{8}\" required></div><br>\n");
    cout << ("<div><label>Enter your Password:</label><br><input name='password' type='password' required></div><br>\n");
    cout << ("<div><label>Confirm your Password:</label><br><input name='password_conf' type='password' required></div><br>\n");
    cout << ("<div><input type='button' value='Cancel' onclick=\"location.href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/Home'\"> <input type='submit' value='Sign up'></div>\n");
    cout << ("</form>\n");
    cout << ("</body>\n");
    cout << ("</html>\n");
    return EXIT_SUCCESS;
}
