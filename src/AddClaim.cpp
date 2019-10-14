#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Layout.cpp"
#include "CookieHandler.cpp"
#include "Utils.cpp"
#include "RequestHandler.cpp"
// Include the Connector/C++ headers
using namespace std;
using namespace sql::mysql;

bool checkFields(string title, string msg, string type){
    regex type_regex ("1|2|3");
    if(get_string_without_char(' ', '\0', title) == "" || regex_match(title,get_generic_regex())){
        return false;
    }

    if(get_string_without_char(' ', '\0', msg) == "" || regex_match(msg,get_generic_regex())){
        return false;
    }

    if(get_string_without_char(' ', '\0', type) == "" || regex_match(type,type_regex)){
        return false;
    }

    return true;
}

/*
    Claim type:
        0 = Query
        1 = feedback
        2 = claim
*/
bool addClaim(string post){
    vector<string> postData = getTokenPairs('&', post);
    int indexIfLogged = (postData.size() <= 3)?1:2;
    string title = getKeyOrValue(postData[0],1);
    string msg = getKeyOrValue(postData[indexIfLogged+1],1);
    string type = getKeyOrValue(postData[indexIfLogged],1);
    if(checkFields(title, msg, type)){
        addClaimToTable(title, msg, type, (postData.size() <= 3)?1:0,
                    getCookieKeyValue("SessionId"));
        return true;
    } else {
        return false;
    }
}

int main(int argc, char** argv, char** envp){
    string post = getPostData();
    string userId = "";
    bool session = sessionStatus();
    int error_adding_claim = 0;
    bool rst = true;
    if(!session){
        cout << "Location: Home\r\n\r\n";
    }
    try{//Try to add the user to the database.
        if(post != ""){//Call the user registry.
            rst = addClaim(post);
            if(rst) {
                cout << "Location: review_claims\r\n\r\n";
            } else {
                error_adding_claim = 2;
            }
        }
    } catch (exception e){//If a value from the form is not unique in the db (except fullname), it will fail and set the error.
        error_adding_claim = 1;
    }
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<body>\n";
    printOptions(sessionStatus());
    cout << ("<form action='add_claim' METHOD='POST'>\n");
    cout << ("<h2><b>Thanks for the Feedback!</b></h2>\n");
    if(error_adding_claim == 1 ){
        cout << "<h4>There was an error submitting your claim.</h4>";
    } else if(error_adding_claim == 2){
        cout << "<h4>Invalid character found in a form field.</h4>";
    }
    cout << ("<div><label>Title:</label><br><input name='title' required></div><br>\n");
    if(session){
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