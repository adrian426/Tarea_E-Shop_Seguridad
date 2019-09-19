#include <iostream>
#include <sstream>
#include <cstdlib>
#include "CookieHandler.cpp"
// Include the Connector/C++ headers
using namespace std;

int main(int argc, char** argv, char** envp){
  killCookie();
  cout<<"Location: Home\r\n\r\n";
  return EXIT_SUCCESS;
}