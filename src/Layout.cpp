#include <iostream>
using namespace std;

void printOptions(bool sessionAlive){
    cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/Home'>Home</a><br>";
    cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/review_claims'>Feedback</a><br>";
    //cout << "<input type='button' value='AddClaim' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/add_claim'\"><br>";
    if(sessionAlive == false){
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/login'>Sign in</a><br>";
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/sign_up'>Sign Up</a><br>";
    } else {
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/add_product'>Sell a Product</a><br>";
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/review_cart'>Shopping Cart</a><br>";
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/history'>Shopping History</a><br>";
        cout << "<a href='http://172.24.129.95/cgi-bin/Tarea1_Seguridad/logout'>Sign out</a><br>";
    }
}
