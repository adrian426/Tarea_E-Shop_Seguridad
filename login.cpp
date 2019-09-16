#include <iostream>
#include <sstream>
#include <cstdlib>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Model/Database.cpp"
// Include the Connector/C++ headers
using namespace std;
using namespace sql::mysql;

string checkUserLogin(string postData){
  string username = getKeyOrValue(postData, 1);
  string userId = loginQuery(username);
  return userId;
}


int main(int argc, char** argv, char** envp){
  string post = getPostData();
  string userId = "";
  int inexistent_user = 0;
  if(post != ""){
    userId = checkUserLogin(post);
    if(userId != ""){
      setCookiePair("UserId", userId);
      cout << "Location: Home\n";
    } else {
      //TODO: Indicar inexistencia del usuario.
      inexistent_user = 1;
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
  if(inexistent_user != 0){
    cout<< "<h4>The username entered does not exist</h4>";
  }
  cout << ("<div><label>Enter your username:</label><br><input name='username' required></div><br>\n");
  cout << ("<div><input type='submit' value='Sign in'></div>\n");
  cout << ("</form>\n");
  cout << ("</body>\n");
  cout << ("</html>\n");
  return EXIT_SUCCESS;
}