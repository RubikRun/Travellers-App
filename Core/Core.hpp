//A core represents the memory of the app.
//All the data is stored in the core,
//and it has all the functionality needed to manage that data

#pragma once

#include "User/User.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>
typedef std::string str;

//A pair of a user (their username) and a grade
//indicating that the user gave this grade
struct UserGrade { str username; int grade; };

//A pair of users' indecies
struct UsersPair { int firstInd, secondInd;};

class Core
{
    //App's registered users
    std::vector<User> m_users;

    //App's destinations,
    //and for each destination keeping a list of grades received by users
    std::map< str, std::vector<UserGrade> > m_destUserGrades;

    //Each user's set of friends.
    //This kind of structure allows for one-way and two-way friendships
    //so we will consider the two-way friendship to be the real friendship,
    //and the one-way friendship will indicate a non-answered friend request.
    //Meaning that when user A sends a request to user B, B becomes a friend of A,
    //but A does not become a friend of B, until B confirms the request.
    std::map<int, std::set<int>> m_friends;

    //The currently logged in user (their index)
    int m_currUserInd;

  public:

    //Creates an empty core with no current user
    Core();

    //Loads the core from the database
    void Load();

    //Saves the core to the database
    void Save();

    //Adds a new user with the given info to app's users
    void AddUser(const str& username, const str& password, const str& email);

    //Checks if there is a registered user with this username
    bool UsernameExists(const str& username) const;

    //Checks if there is a registered user with this email
    bool EmailExists(const str& email) const;

    //Checks if there is a destination with this name
    bool DestExists(const str& dest) const;

    //Checks if this is the password of the user with this username
    bool UserPasswordMatch(const str& username, const str& password) const;

    //Checks if there is a current user
    bool IsThereCurrUser() const;

    //Sets the current user to the user with this username
    void SetCurrUser(const str& username);

    //Returns the username of the current user
    const str& GetCurrUser() const;

    //Sets the current user to null, indicating that there is no current user
    void LogOutCurrUser();

    //Adds a new trip to the current user's trips
    void CurrUserAddTrip(const str& dest, const Date& begin, const Date& end,
        int grade, const str& comment, const std::vector<str>& photos);

    //Returns a list of all the destinations
    std::vector<str> GetDests() const;

    //Returns a list of all the grades received by users for this destination
    const std::vector<UserGrade>& GetUsersGrades(const str& dest) const;

    //Checks if two users are friends
    bool AreFr(const str& user1, const str& user2) const;

    //Checks if a user has a friend request from another user
    bool HasFrReqFrom(const str& user1, const str& user2) const;

    //Sends a friend request from one user to another
    void SendFrReq(const str& user1, const str& user2);

    //Unsends a friend request from one user to anoter
    void UnsendFrReq(const str& user1, const str& user2);

    //Confirms a friend request from the second user to the first one
    void ConfirmFrReq(const str& user1, const str& user2);

    //Declines a friend request from the second user to the first one
    void DeclineFrReq(const str& user1, const str& user2);

    //Unfriends the two users
    void RmFr(const str& user1, const str& user2);

    //Returns a list of the trips of the user with this username
    const std::vector<Trip>& GetUserTrips(const str& username) const;

    //Returns a list of friend requests that the current user has (list of usernames)
    std::vector<str> GetCurrUserFrReqs() const;

  private:

    //Loads users from a database
    void LoadUsers(const str& usersDb);

    //Loads destinations from a database
    void LoadDests(const str& destsDb);

    //Saves user to a database
    void SaveUsers(const str& usersDb) const;

    //Saves destinations to a database
    void SaveDests(const str& destsDb) const;

    //Reads users from a database
    void ReadUsers(std::ifstream& db);

    //Reads friendships from a database
    void ReadFriendships(std::ifstream& db);

    //Writes users to a database
    void WriteUsers(std::ofstream& db) const;

    //Writes friendships to a database
    void WriteFriendships(std::ofstream& db) const;

    //Finds the user with this username, returns its index
    int FindUser(const str& username) const;

    //Checks if the second user is in the friends of the first one
    bool UserFrsContain(int user1, int user2) const;

    //Adds the second user to the friends of the first one
    void UserFrsAdd(int user1, int user2);

    //Removes the second user from the friends of the first one
    void UserFrsRm(int user1, int user2);
};