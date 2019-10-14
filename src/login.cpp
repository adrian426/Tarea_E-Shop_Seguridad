#include <iostream>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Database.cpp"
#include "Encryption.cpp"
using namespace std;
using namespace sql::mysql;


int checkFormFields(string username, string password){
  regex username_regex ("[a-zA-Z0-9\\_\\-\\.]{2,29}");
  regex password_regex ("[\\_\\-\\.0-9a-zA-Z]{3,20}");
  string clearedUsername = get_string_without_char(' ', '\0' , username);
  string password_cleared =  get_string_without_char(' ', '\0', password);
  if(clearedUsername == "" ||  !regex_match(clearedUsername, username_regex)){
    return false;
  }

  if(password_cleared == "" || !regex_match(password_cleared, password_regex)){
    return false;
  }

  //both fields are valid.
  return true;
}

string checkUserLogin(string username, string password){
  string password_hash = hash_password(password, username);
  string userId = loginQuery(username, password);
  return password_hash;
}


int main(int argc, char** argv, char** envp){
  string post = getPostData();
  string userId = "";
  int inexistent_user = 0;
  if(post != ""){
    vector<string> postData = getTokenPairs('&',post);
    string username = getKeyOrValue(postData[0], 1);
    string password = getKeyOrValue(postData[1], 1);
    if(checkFormFields(username, password)){
      userId = checkUserLogin(username, password);
      if(userId != ""){
        setCookiePair("UserId", userId);
        cout << "Location: Home\n";
      } else {
        //TODO: Indicar inexistencia del usuario.
        inexistent_user = 1;
      }
    } else {
      inexistent_user = 2;
    }
  }
  string userLoggedIn = getCookieKeyValue("UserId");
  if( userLoggedIn != "" ){//If the user is already logged in, redirect to Homepage.
    //cout << "Location: Home";
  }
  cout << "Content-type:text/html\r\n\r\n";
  cout << "<body>\n";
  printOptions(getCookieKeyValue("UserId"));  
  cout << ("<form action='login' METHOD='POST'>\n");
  cout << ("<h2><b>Login</b></h2>\n");
  if(inexistent_user == 1){
    cout<< "<h4>The username entered does not exist.</h4>";
  } else if(inexistent_user == 2){
    cout<< "<h4>Invalid character found in a field.</h4>";
  }
  cout << ("<div><label>Enter your username:</label><br><input name='username' required></div><br>\n");
  cout << ("<div><label>Enter your password:</label><br><input type='password' name='password' required></div><br>\n");
  cout << ("<div><input type='submit' value='Sign in'></div>\n");
  cout << ("</form>\n");
  cout << ("</body>\n");
  cout << ("</html>\n");
  return EXIT_SUCCESS;
}