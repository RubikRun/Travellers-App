#pragma once

#include <string>

typedef std::string str;

class User
{
    //User's info
    str m_username;
    str m_password;
    str m_email;

    public:

        //Creates a user with no info
        User();

        //Creates a user with the given info
        User(const str& username, const str& password, const str& email);

        //Reads a username and makes sure it's valid
        static str ReadUsername();

        //Reads a password and makes sure it's valid
        static str ReadPassword();

        //Reads an email and makes sure it's valid
        static str ReadEmail();
    
    private:

        //Used to read a field of user's info (username, password or email)
        static str ReadInfoField(bool (*FieldIsValid)(const str&),
            const str& enterFieldMsg, const str& invalidFieldMsg);

        //Checks if a username is valid
        static bool UsernameIsValid(const str& username);

        //Checks if a password is valid
        static bool PasswordIsValid(const str& passowrd);

        //Checks if an email is valid
        static bool EmailIsValid(const str& email);
};