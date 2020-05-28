//A core represents the memory of the app.
//All the data is stored in the core,
//and it has all the functionality needed to manage that data

#pragma once

#include "User/User.hpp"

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
typedef std::string str;

//A pair of a user's index and a grade,
//indicating that the user gave this grade
struct UserGrade { int userInd, grade; };

//A pair of users' indecies
struct UsersPair { int firstInd, secondInd; };

class Core
{
    //App's registered users
    std::vector<User> m_users;

    //App's destinations,
    //and for each destination keeping a list of grades received by users
    std::map< str, std::vector<UserGrade> > m_destUserGrades;

    //Friendships between the users.
    //If two users with indecies A and B are friends, we will have (A,B) and (B,A) in the set
    std::unordered_set<UsersPair> m_friendships;

    //Friend requests between users.
    //For each user we will keep a list of their received friend requests.
    std::unordered_map<int, std::vector<int>> m_frReqs;

    //The currently logged in user (their index)
    int m_currUserInd;

  public:

    //Loads the core from the database
    void Load();

    //Adds a new user to app's users
    void AddUser(const User&);

    //Checks if there is a registered user with this username
    bool UsernameExists(const str& username) const;

    //Checks if there is a registered user with this email
    bool EmailExists(const str& email) const;

    //Checks if there is a destination with this name
    bool DestExists(const str& dest) const;

    //Checks if this is the password of the user with this username
    bool UserPasswordMatch(const str& username, const str& password) const;

    //Sets the current user to the user with this username
    void SetCurrUser(const str& username);

    //Returns the username of the current user
    const str& GetCurrUser() const;

    //Adds a new trip to the current user's trips
    void CurrUserAddTrip(const Trip&);

    //Returns a list of all the destinations
    const std::vector<str>& GetDests() const;

    //Returns a list of all the grades received by users for this destination
    const std::vector<UserGrade>& GetUserGrades(const str& dest) const;

    //Checks if the user with this username is a friend of the current user
    bool IsFrToCurr(const str& username) const;

    //Checks if the current user has a friend request from the user with this username
    bool CurrHasFrReqFrom(const str& username) const;

    //The current user sends a friend request to the user with this username
    void CurrSendFrReqTo(const str& username) const;

    //The current user confirms the friend request he received from the user with this username
    void CurrConfirmFrReqFrom(const str& username) const;

    //The current user removes from friends the user with this username
    void CurrRmFr(const str& username) const;

    //The current user declines the friend request he received from the user with this username
    void CurrDeclineFrReqFrom(const str& username) const;

    //Returns a list of the trips of the user with this username
    void GetTripsOf(const str& username) const;
};