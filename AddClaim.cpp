#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
#include "Model/Database.cpp"
// Include the Connector/C++ headers
using namespace std;
using namespace sql::mysql;

void addClaim(string post){
    vector<string> postData = getTokenPairs('&', post);
    int indexIfLogged = (postData.size() <= 3)?1:2;
    string userId = getCookieKeyValue("UserId");
    addClaimToTable(getKeyOrValue(postData[0],1), getKeyOrValue(postData[indexIfLogged+1],1), getKeyOrValue(postData[indexIfLogged],1), (postData.size() <= 3)?1:0,
                    userId);
}

/*
    Claim type:
        0 = Query
        1 = feedback
        2 = claim
*/

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    int error_adding_claim = 0;
    try{//Try to add the user to the database.
        if(post != ""){//Call the user registry.
            addClaim(post);
            cout << "Location: review_claims\r\n\r\n";
        }
    } catch (exception e){//If a value from the form is not unique in the db (except fullname), it will fail and set the error.
        error_adding_claim = 1;
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    cout << ("<form action='add_claim' METHOD='POST'>\n");
    cout << ("<h2><b>Thanks for the Feedback!</b></h2>\n");
    if(error_adding_claim != 0 ){
        cout << "<h4>There was an submitting your claim.</h4>";
    }
    cout << ("<div><label>Title:</label><br><input name='title' required></div><br>\n");
    if(getCookieKeyValue("UserId") != ""){
        cout << "<label>Reveal identity on the claim?</label><input type='checkbox' name='anon' value='Y'><br><br>";
    }
    cout << "<label>Choose the type of feedback:</label>";
    cout << "<input type='radio' name='type' value='0' checked> Query";
    cout << "<input type='radio' name='type' value='1'> Feedback";
    cout << "<input type='radio' name='type' value='2'> Claim";
    cout << ("<br><br><div><label>Description:</label><br><textarea rows='3' name='msg' required></textarea></div><br>\n");
    cout << ("<div><input type='button' value='Cancel' onclick=\"location.href='http://localhost/cgi-bin/Tarea1_Seguridad/review_claims'\"> <input type='submit' value='Submit'></div>\n");
    cout << ("</form>\n");
    cout << ("</body>\n");
    cout << ("</html>\n");
    return EXIT_SUCCESS;
}