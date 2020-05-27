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

        //Returns a string containing the notifications of the user.
        str GetNotificationsStr() const;

        //Adds a new trip to user's trips
        void AddTrip(const Trip&);

        //Returns user's trips
        const std::vector<Trip>& GetTrips() const;

        //Checks if the other user is a friend
        bool IsFriend(int userInd) const;

        //Checks if user has a friend request from the other user
        bool HasFriendRequest(int userInd) const;

        //User accepts a friend request, adds the other user to friends
        void AcceptFriendRequest(int userInd);

        //The other user has sent a friend request to this user
        void ReceiveFriendRequest(int userInd);

        //Removes the other user from this user's friends
        void RemoveFriend(int userInd);

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