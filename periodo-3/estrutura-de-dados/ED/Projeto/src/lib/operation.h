#include "graph.h"

#define STANDARD_USER_NAME_LENGTH 20
#define EQUAL_NAMES 0

typedef char* user;

void userGetFollowers(graph *grp, user user_name);
void userGetFollowing(graph *grp, user user_name);

void userListNoFollowers(graph *grp);
void userListNoFollowing(graph *grp);
void userListByFollowersAmount(graph *grp);

void userCreate(graph *grp);

void userFollow(graph *grp, user first_user, user second_user);
void userUnfollow(graph *grp, user first_user, user second_user);
