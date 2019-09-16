#include <iostream>
#include "mysql_driver.h"
#include "mysql_connection.h"

// Include the Connector/C++ headers
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
using namespace std;
using namespace sql::mysql;

void generateNavbarAndStyles(){
    cout << "<style>";
    cout << "ul {";
    cout << "list-style-type: none;";
    cout << "margin: 0;";
    cout << "padding: 0;";
    cout << "width: 60px;";
    cout << "}";
   /* cout << "ul {  list-style-type: none;  margin: 0;  padding: 0;  overflow: hidden;  background-color: #303;} li {  float: left;  border-right:1px solid #bbb;}" +
    " li:last-child {  border-right: none; } li a {  display: block;  color: white;  text-align: center;  padding: 14px 16px;  text-decoration: none; "+
    " } li a:hover:not(.
    active) {  background-color: #111; } .active {  background-color: #4CAF50;}"; 
    cout << "<style>";*/
}
