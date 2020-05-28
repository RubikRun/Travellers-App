//User is a class representing a user of the app.
//It contains all the user's data,
//and the functionality needed to manage that data

#pragma once

#include "../Trip/Trip.hpp"
#include "../Database/Serializable.hpp"

#include <vector>
#include <string>
typedef std::string str;

class User : public Serializable
{
    //User's username
    str m_username;
    //User's password
    str m_password;
    //User's email
    str m_email;

    //User's trips
    std::vector<Trip> m_trips;

  public:

    //Creates a default user
    User();

    //Creates a user with the given info
    User(const str& username, const str& password, const str& email);

    //Returns user's username
    const str& GetUsername() const;

    //Checks if a password matches user's password
    bool PasswordsMatch(const str& password) const;

    //Returns user's email
    const str& GetEmail() const;

    //Adds a new trip to user's trips
    void AddTrip(const Trip&);

    //Serializes the user
    str Serialize() const;

    //Deserializes the user
    void Deserialize(const str&);
};