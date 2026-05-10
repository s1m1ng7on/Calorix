#include <iostream>
#include "Calorix.h"
#include "UserProfile.h"

int main()
{
    Calorix calorix;

    //Successful register
    calorix.registerUser("s1m1ng7on", "simeon20", 20, 96.3, 178, UserProfile::Gender::Male);

    //Unsuccessful register (logout required)
    calorix.registerUser("babatunde", "lava_bear", 20, 96.3, 178, UserProfile::Gender::Male);

    //Successful logout
    calorix.logout();

    //Failed logout
    calorix.logout();

    //Failed login (inexisting user)
    calorix.login("zdravka_dimitrova", "koputri");

    //Failed login (wrong password)
    calorix.login("s1m1ng7on", "simeon19");

    //Successful login
    calorix.login("s1m1ng7on", "simeon20");

    //Unsuccessful login (logout required)
    calorix.login("babatunde", "lava_bear");

    //Successful logout
    calorix.logout();

    //Successful register
    calorix.registerUser("babatunde", "lava_bear", 20, 96.3, 178, UserProfile::Gender::Male);

    //Successful logout
    calorix.logout();

    //Failed register (user with this username already exists)
    calorix.registerUser("babatunde", "lava_bear", 20, 96.3, 178, UserProfile::Gender::Male);

    return 0;
}