#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Utils.cpp"
#include "CookieHandler.cpp"
// Include the Connector/C++ headers
using namespace std;

bool logout(){
  string sessionId = getCookieKeyValue("SessionId");
  sessionLogOut(sessionId);
  killCookie();
  return true;
}

int main(int argc, char** argv, char** envp){
  logout();
  cout<<"Location: Home\r\n\r\n";
  return EXIT_SUCCESS;
}