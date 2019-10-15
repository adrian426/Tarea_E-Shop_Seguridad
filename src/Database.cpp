#include "jdbc/mysql_driver.h"
#include "jdbc/mysql_connection.h"

// Include the Connector/C++ headers
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"
using namespace std;
using namespace sql::mysql;


sql::Connection* getConnection(){
    sql::Driver *driver;
    sql::Connection *con;

    driver = get_mysql_driver_instance();
    con = driver->connect("localhost", "amazin_user", "EstoEsSeguro");
    con->setSchema("Amazin");
    return con;
}

//_________________________________________USER TABLE SECTION____________________________________
int CreateUser(string username, string fullname, string email, string phone_number, string password_hash){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    stmt = con->createStatement();
    stmt->executeUpdate("Insert into User (username, fullname, email, phone_number, password_hash) Values('" + username + "', '" + fullname + "', '" + email + "', " + phone_number  + ", + '" + password_hash + "');");
    return 0;
}

string loginQuery(string username, string password_hash, string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    sql::ResultSet *res;
    stmt = con->createStatement();
    res = stmt->executeQuery("Select * from User where username = '" + username + "' and password_hash = '" + password_hash + "';");
    string userId = "";
    while(res->next()){
        userId = res->getString("id");
        stmt->executeUpdate("Insert into _Session Values('" + sessionId + "'," + userId + ", DATE_ADD(NOW(), INTERVAL 15 MINUTE));");
    }
    delete stmt;
    delete con;
    delete res;
    return userId;
}

//Closes the session on the database.
int sessionLogOut(string sessionId){
    sql::Connection *con = getConnection();
    sql::PreparedStatement *pstmt;
    int rst = 0;
    pstmt = con->prepareStatement("Delete from Amazin._Session where id = ?;");
    pstmt->setString(1, sessionId);
    try{
        pstmt->executeUpdate();
        rst = true;
    } catch(exception e) {
        rst = false;
    }
    delete pstmt;
    delete con;
    return rst;
}

bool updateSession(sql::Connection *con, string sessionId){
    sql::PreparedStatement *pstmt;
    int rst = true;
    pstmt = con->prepareStatement("update Amazin._Session SET session_expiration = DATE_ADD(NOW(), INTERVAL 15 MINUTE) where id = ?;");
    pstmt->setString(1, sessionId);
    try{
        pstmt->executeUpdate();
        rst = true;
    } catch(exception e) {
        rst = false;
    }
    delete pstmt;
    return rst;
}

// Queries the db to know if the session is still alive, if it is, updates the session expiration date.
bool isSessionAlive(string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    sql::ResultSet *res;
    int rst = 0;
    stmt = con->createStatement();
    res = stmt->executeQuery("Select * from Amazin._Session where id = '" + sessionId + "' and timestampdiff(MINUTE, session_expiration, NOW()) <= 15;");
    while(res->next()){
        rst = updateSession(con, sessionId);
        if(rst){
            delete con;
            delete stmt;
            delete res;
            return true;
        }
    }
    delete con;
    delete stmt;
    delete res;
    return false;
}

string getUserIdFromSession(sql::Connection *con, string sessionId){
    sql::Statement *stmt;
    sql::ResultSet *res;
    stmt = con->createStatement();
    res = stmt->executeQuery("Select * from _Session where id = '" + sessionId + "';");
    string userId = "";
    while(res->next()){
        userId = res->getString("user_fk");
    }
    delete stmt;
    delete res;
    return userId;
}

//_________________________________________PRODUCT TABLE SECTION____________________________________
int AddProductToSale(string name, string description, string price, string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    string seller_fk = getUserIdFromSession(con, sessionId);
    stmt = con->createStatement();
    stmt->executeUpdate("Insert into Product (product_name, product_descp, price, seller_fk) Values('" + name + "', '" + description + "', " + price + ", " + seller_fk  + ");");
    delete con;
    delete stmt;
    return 0;
}

void printProductList(bool userLogged, string keyword){
    string query = (keyword != "")? "Select * from Product where product_name like '%" + keyword + "%' AND product_status = 0;":"Select * from Product where product_status = 0;";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("product_name") + "</h4>";
        cout << "<label>" + rst->getString("product_descp") + "</label><br>";
        cout << "<label>Price: $" + rst->getString("price") + "</label><br><br>";
        if(userLogged){
            cout << "<a href='172.24.129.95/cgi-bin/Tarea1_Seguridad/add_to_cart?id=" + rst->getString("id") + "'>Add to cart</a><br>";
        }
        cout << "__________________________________________________________________________________________________________________";
    }
}

//_________________________________________CLAIM TABLE SECTION____________________________________

int addClaimToTable(string title, string msg, string type, bool anon, string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    string user = getUserIdFromSession(con, sessionId);
    string query = "";
    if(anon){
        query = "Insert into Claim (title, claim_type, msg, msg_timestamp) values ('" + title + "', " + type + ", '" + msg + "', CURRENT_TIMESTAMP())";
    } else {
        query = "Insert into Claim (title, claim_type, msg, msg_timestamp,user_fk) values ('" + title + "', " + type + ", '" + msg + "', NOW(), " + user + ")";
    }
    stmt = con->createStatement();
    stmt->executeUpdate(query);
    return 0;
}

void printClaims(){
    string query = "Select * from Claim order by (msg_timestamp) ASC;";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("title") + "</h4>";
        cout << "<label>" + rst->getString("msg") + "</label><br>";
        cout << "__________________________________________________________________________________________________________________";
    }
}

//_________________________________________CART TABLE SECTION____________________________________

int addItemToCart(string item_id, string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string userId = getUserIdFromSession(con, sessionId);
    string query = "Insert into Cart values ('" + userId + "', (Select id from Product where id = " + item_id + " and buyer_fk is null));";
    stmt->executeUpdate(query);
    delete con;
    delete stmt;
    return 0;
}

void printCart(string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string userId = getUserIdFromSession(con, sessionId);
    string query = "Select Distinct * from Product P, Cart C where C.user_fk = '" + userId + "' AND P.id = C.product_fk;";
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("product_name") + "</h4>";
        cout << "<label>" + rst->getString("product_descp") + "</label><br>";
        cout << "<label>Price: $" + rst->getString("price") + "</label><br><br>";
        cout << "<a href='172.24.129.95/cgi-bin/Tarea1_Seguridad/remove_from_cart?id=" + rst->getString("id") + "'>Remove from cart</a><br>";
        cout << "__________________________________________________________________________________________________________________";
    }
    delete con;
    delete stmt;
    delete rst;
}

int removeItemFromCart(string itemId, string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string userId = getUserIdFromSession(con, sessionId);
    string query = "Delete from Cart where user_fk = '" + userId + "' AND product_fk = '" + itemId + "';";
    stmt->executeUpdate(query);
    delete con;
    delete stmt;
    return 0; 
}

void checkoutCart(string sessionId, string card_number){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string userId = getUserIdFromSession(con, sessionId);
    stmt->executeUpdate("Insert into Bill_Info (user_fk, credit_card, amount, bill_date) values (" + userId + ", '" + card_number + "', (Select SUM(price) from Product where id IN (Select product_fk from Cart where user_fk = " + userId + ")),NOW());");
    stmt->executeUpdate("Update Product Set product_status = 1, buyer_fk = " + userId + ", bill_id = (select id from Bill_Info where user_fk = " + userId + " order by bill_date desc LIMIT 1) where id IN (Select product_fk from Cart where user_fk = " + userId + ");");
    stmt->executeUpdate("Delete from Cart where user_fk = " + userId +";");
    delete con;
    delete stmt;
}



void printBoughtItems(string sessionId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string userId = getUserIdFromSession(con, sessionId);
    string query = "Select Distinct * from Product where buyer_fk = '" + userId + "';";
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("product_name") + "</h4>";
        cout << "<label>" + rst->getString("product_descp") + "</label><br>";
        cout << "<label>Price: $" + rst->getString("price") + "</label><br><br>";
        cout << "__________________________________________________________________________________________________________________";
    }
    delete con;
    delete stmt;
    delete rst;
}
