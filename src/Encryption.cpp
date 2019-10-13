#include <iostream>
#include "string.h"
#include <openssl/sha.h>
using namespace std;

string hash_password(string password, string salt){//Salt should be username
    string salted_pass = (password + salt);
    const char *password_hash = salted_pass.c_str();

    unsigned char digest[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char*)&password_hash, strlen(password_hash), (unsigned char*)&digest);
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++){
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    password_hash = mdString;
    return password_hash;
}