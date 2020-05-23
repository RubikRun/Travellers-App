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

        //Returns user's username
        const str& GetUsername() const;

        //Checks if the given password is the same as the user's password
        bool PasswordCheck(const str& password);

        //Reads a username and makes sure it's valid
        static str ReadUsername();

        //Reads a password and makes sure it's valid
        static str ReadPassword();

        //Reads an email and makes sure it's valid
        static str ReadEmail();
    
    private:

        //Checks if a username is valid
        static bool UsernameIsValid(const str& username);

        //Checks if a password is valid
        static bool PasswordIsValid(const str& passowrd);

        //Checks if an email is valid
        static bool EmailIsValid(const str& email);

        //Reads user from stream
        friend std::istream& operator>>(std::istream& stream, User& user);

        //Writes user to stream
        friend std::ostream& operator<<(std::ostream& stream, const User& user);
};


std::istream& operator>>(std::istream& stream, User& user);
std::ostream& operator<<(std::ostream& stream, const User& user);