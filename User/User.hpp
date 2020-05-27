#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"
#include "../Trip/Trip.hpp"

#include <string>
#include <vector>
typedef std::string str;

class User : public Serializable, public Printable
{
    //User's info
    str m_username, m_password, m_email;
    //User's trips
    std::vector<Trip> m_trips;
    //User's friends (their indecies)
    std::vector<int> m_frsInd;
    //User's friend requests (senders' indecies)
    std::vector<int> m_frReqsInd;

    public:

        //Creates an empty user
        User();

        //Creates a user with the given info
        User(const str& username, const str& password, const str& email);

        //Returns user's username
        const str& GetUsername() const;

        //Checks if a password is the same as user's password
        bool PasswordsMatch(const str& password);

        //Adds a new trip to user's trips
        void AddTrip(const Trip&);

        //Check if a username is valid
        static bool UsernameIsValid(const str&);
        
        //Checks if a password is valid
        static bool PasswordIsValid(const str&);

        //Checks if an email is valid
        static bool EmailIsValid(const str&);

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};