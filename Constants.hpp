#pragma once

#include <string>

typedef std::string str;

const str USERS_DATABASE_FILE =
"users.db";

const str APP_NAME =
"Traveller's App";

const str HELP_COMMAND =
"help";

const str EXIT_COMMAND =
"exit";

const str REGISTER_COMMAND =
"register";

const str LOGIN_COMMAND =
"login";

const str LOGOUT_COMMAND =
"logout";

const str WELCOME_MESSAGE =
"\nHello! Welcome to " + APP_NAME + "!\n"
"Type \"" + HELP_COMMAND + "\" if you don't know how to use it.\n";

const str HELP_MESSAGE =
"\nHi! I will show you how to use " + APP_NAME + ".\n"
"You can execute commands by typing them and pressing enter.\n"
"At any moment you can type \"" + EXIT_COMMAND + "\" to exit the app.\n"
"First you need to register, or log in if you already have an account.\n"
"   *To register type \"" + REGISTER_COMMAND + "\"\n"
"   *To log in type \"" + LOGIN_COMMAND + "\"\n";

const str INVALID_COMMAND_MESSAGE =
"Not a valid command.\n"
"Type \"" + HELP_COMMAND + "\" for more info.\n";

const str ENTER_USERNAME =
"Enter username: ";

const str ENTER_PASSWORD =
"Enter password: ";

const str ENTER_EMAIL =
"Enter email: ";

const int MIN_USERNAME_LEN = 4;
const int MAX_USERNAME_LEN = 30;

const str INVALID_USERNAME =
"Not a valid username.\n"
"Usernames should be between " + 
std::to_string(MIN_USERNAME_LEN) + " and " + std::to_string(MAX_USERNAME_LEN) + " characters long\n"
"and contain no spaces.\n";

const int MIN_PASSWORD_LEN = 6;
const int MAX_PASSWORD_LEN = 40;

const str INVALID_PASSWORD =
"Not a valid password.\n"
"Passwords should be between " +
std::to_string(MIN_PASSWORD_LEN) + " and " + std::to_string(MAX_PASSWORD_LEN) + " characters long\n"
"and contain at least one letter and at least one digit.\n";

const int MIN_EMAIL_NAME_LEN = 1;
const int MIN_EMAIL_DOMAIN_LEN = 2;
const int MIN_EMAIL_DOMAIN_NETWORK_LEN = 2;
const int MIN_EMAIL_LEN = MIN_EMAIL_NAME_LEN + 1 + MIN_EMAIL_DOMAIN_LEN + 1 + MIN_EMAIL_DOMAIN_NETWORK_LEN;
const int MAX_EMAIL_LEN = 40;

const str INVALID_EMAIL =
"Not a valid email.\n";

const str USER_NOT_FOUND =
"There is no user with this username.\n";

const int USER_INDEX_INVALID = -1;

const str PASSWORD_WRONG =
"Wrong password.\n";

const str REGISTER_SUCCESSFUL =
"You registered successfully.\n";

const str LOGIN_SUCCESSFUL =
"You logged in successfully.\n";

const str NOT_LOGGED_IN =
"You are not logged in.\n";

const str LOGOUT_SUCCESSFUL =
"You logged out successfully.\n";

#define VALIDATE(condition, invalidMsg, oninvalid) \
if (!(condition)) { \
    std::cout << invalidMsg << std::endl; \
    oninvalid; \
}

#define CHECK_FILE_OPENED(file, filename, onerror) \
if (!file.is_open()) { \
    std::cout << "Error: Cannot open file: " << filename << "\n\n"; \
    onerror; \
}

#define CHECK_FILE_CLOSED(file, filename, onerror) \
if (file.is_open()) { \
    std::cout << "Error: Cannot close file: " << filename << "\n\n"; \
    onerror; \
}

const str FILE_SEPARATOR =
"\n";

const str CANT_REGISTER_WHILE_LOGGEDIN =
"Error: You cannot register while logged in.\n";

const str ALREADY_LOGGEDIN = 
"You are already logged in.\n";

const str USERNAME_TAKEN =
"Error: A user with this username already exists.\n";

const str EMAIL_TAKEN =
"Error: A user with this email already exists.\n";

#define ITERATE_AND_FIND(begin, end, condition, onfind, ondidntfind) \
for (int i = begin; i < end; i++) \
{ \
    if (condition) \
    { \
        onfind; \
    } \
} \
ondidntfind;

#define ITERATE_AND_DO(begin, end, do) \
for (int i = begin; i < end; i++) \
{ \
    do; \
}

#define IN_INTERVAL(x, a, b) ((x) >= (a) && (x) <= (b))