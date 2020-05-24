#pragma once

#include "../Trip/Trip.hpp"

#include <string>

typedef std::string str;

class User
{
    //User's info
    str m_username;
    str m_password;
    str m_email;

    //User's trips
    std::vector<Trip> trips;

    public:

        //Creates a user with no info
        User();

        //Creates a user with the given info
        User(const str& username, const str& password, const str& email);

        //Returns user's username
        const str& GetUsername() const;

        //Returns user's email
        const str& GetEmail() const;

        //Checks if the given password is the same as the user's password
        bool PasswordCheck(const str& password);

        //Checks if a username is valid
        static bool UsernameIsValid(const str& username);

        //Checks if a password is valid
        static bool PasswordIsValid(const str& passowrd);

        //Checks if an email is valid
        static bool EmailIsValid(const str& email);

    
    private:

        //Reads user from stream
        friend std::istream& operator>>(std::istream& stream, User& user);

        //Writes user to stream
        friend std::ostream& operator<<(std::ostream& stream, const User& user);
};