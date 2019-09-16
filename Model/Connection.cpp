#include "mysql_driver.h"
#include "mysql_connection.h"

// Include the Connector/C++ headers
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
using namespace std;
using namespace sql::mysql;

sql::Connection* getConnection(){
    sql::Driver *driver;
    sql::Connection *con;

    driver = get_mysql_driver_instance();
    con = driver->connect("localhost", "adrian", "Adrian426!");
    con->setSchema("Amazin");
    return con;
}