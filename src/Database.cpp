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
    res = stmt->executeQuery("Select id from User where username = '" + username + "' and password_hash = '" + password_hash + "';");
    string userId = "";
    while(res->next()){
        userId = res->getString("id");
    }
    if (userId != ""){
        try{
            stmt->executeUpdate("Insert into _Session Values('" + sessionId + "'," + userId + ", DATE_ADD(NOW(), INTERVAL 15 MINUTE))");
        } catch (exception e){
            userId = "";
        }
    }
    delete stmt;
    delete con;
    delete res;
    return userId;
}

//_________________________________________PRODUCT TABLE SECTION____________________________________
int AddProductToSale(string name, string description, string price, string seller_fk){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
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
            cout << "<a href='http://localhost/cgi-bin/Tarea1_Seguridad/add_to_cart?id=" + rst->getString("id") + "'>Add to cart</a><br>";
        }
        cout << "__________________________________________________________________________________________________________________";
    }
}

//_________________________________________CLAIM TABLE SECTION____________________________________

int addClaimToTable(string title, string msg, string type, bool anon, string user){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    string query = "Insert into Claim (title, claim_type, msg, msg_timestamp";
    if(anon){
        query += ") values ('" + title + "', " + type + ", '" + msg + "', CURRENT_TIMESTAMP())";
    } else {
        query += ",user_fk) values ('" + title + "', " + type + ", '" + msg + "', NOW(), '" + user + "')";
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

int addItemToCart(string item_id, string userId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string query = "Insert into Cart values ('" + userId + "', '" + item_id + "');";
    stmt->executeUpdate(query);
    delete con;
    delete stmt;
    return 0;
}

void printCart(string userId){
    string query = "Select Distinct * from Product P, Cart C where C.user_fk = '" + userId + "' AND P.id = C.product_fk;";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("product_name") + "</h4>";
        cout << "<label>" + rst->getString("product_descp") + "</label><br>";
        cout << "<label>Price: $" + rst->getString("price") + "</label><br><br>";
        cout << "<a href='http://localhost/cgi-bin/Tarea1_Seguridad/remove_from_cart?id=" + rst->getString("id") + "'>Remove from cart</a><br>";
        cout << "__________________________________________________________________________________________________________________";
    }
    delete con;
    delete stmt;
    delete rst;
}

int removeItemFromCart(string itemId, string userId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string query = "Delete from Cart where user_fk = '" + userId + "' AND product_fk = '" + itemId + "';";
    stmt->executeUpdate(query);
    delete con;
    delete stmt;
    return 0; 
}

void checkoutCart(string userId, string card_number){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    stmt->executeUpdate("Insert into Bill_Info (user_fk, credit_card, amount, bill_date) values (" + userId + ", " + card_number + ", (Select SUM(price) from Product where id IN (Select product_fk from Cart where user_fk = " + userId + ")),NOW());");
    stmt->executeUpdate("Update Product Set product_status = 1, buyer_fk = " + userId + ", bill_id = (select id from Bill_Info where user_fk = " + userId + " order by bill_date desc LIMIT 1) where id IN (Select product_fk from Cart where user_fk = " + userId + ");");
    stmt->executeUpdate("Delete from Cart where user_fk = " + userId +";");
    delete con;
    delete stmt;
}



void printBoughtItems(string userId){
    string query = "Select Distinct * from Product where buyer_fk = '" + userId + "';";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
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