#include "mysql_driver.h"
#include "mysql_connection.h"
#include "Connection.cpp"

// Include the Connector/C++ headers
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
using namespace std;
using namespace sql::mysql;
//_________________________________________USER TABLE SECTION____________________________________
int CreateUser(string username, string fullname, string email, string phone_number){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    stmt = con->createStatement();
    stmt->executeUpdate("Insert into User (username, fullname, email, phone_number) Values('" + username + "', '" + fullname + "', '" + email + "', " + phone_number  + ");");
    return 0;
}

string loginQuery(string username){
    sql::Connection *con = getConnection();
    sql::Statement *stmt;
    sql::ResultSet *res;
    stmt = con->createStatement();
    res = stmt->executeQuery("Select id from User where username = '" + username + "';");
    string userId = "";
    while(res->next()){
        userId = res->getString("id");
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
}

int removeItemFromCart(string itemId, string userId){
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    string query = "Delete from Cart where user_fk = '" + userId + "' AND product_fk = '" + itemId + "';";
    stmt->executeUpdate(query);
    return 0; 
}

void checkoutCart(string userId){
    string getCartQuery = "Select * from Cart where user_fk = '" + userId + "';";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *rst = stmt->executeQuery(getCartQuery);
    while(rst->next()){
        stmt->executeUpdate("Insert into BoughtItem values (" + userId + ", " + rst->getString("product_fk") + ");");
        stmt->executeUpdate("Update Product Set product_status = 1 where id = " + rst->getString("product_fk") + ";");
        stmt->executeUpdate("Delete from Cart where product_fk = " + rst->getString("product_fk") + ";");
    }
}



void printBoughtItems(string userId){
    string query = "Select Distinct * from Product P, BoughtItem B where B.user_fk = '" + userId + "' AND P.id = B.product_fk;";
    sql::Connection *con = getConnection();
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *rst = stmt->executeQuery(query);
    while(rst->next()){
        cout << "<h4>" + rst->getString("product_name") + "</h4>";
        cout << "<label>" + rst->getString("product_descp") + "</label><br>";
        cout << "<label>Price: $" + rst->getString("price") + "</label><br><br>";
        cout << "__________________________________________________________________________________________________________________";
    }
}