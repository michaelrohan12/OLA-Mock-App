#ifndef OLA_H_INCLUDED
#define OLA_H_INCLUDED

// Including all the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <windows.h>

time_t mytime;

FILE *flog;

//string for generating otp
char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWQYZ0123456789";

//Structure definition of USERS List
struct USER_PROFILE{
    int user_id;
    char mobile_number[11];
    char name[40];
    char email[40];
    char password[12];
    struct USER_PROFILE *next;
};

//typecasting the users list
typedef struct USER_PROFILE USER_PROFILE;

//Declaration of users list head node
USER_PROFILE *USER=NULL;

//The current user structure variable to store his/her details when logged in
USER_PROFILE CURR_USER;

//Structure Defintion of Ride_History of a particular individual
struct RIDE_HISTORY{
    char pickup[40];
    char destination[40];
    char driver_name[40];
    char vehicle_type[40];
    char vehicle_name[40];
    float fare;
    struct RIDE_HISTORY *next;
};

//typecasting the ride history structure
typedef struct RIDE_HISTORY RIDE_HISTORY;

//Declaration of Rides history head node
RIDE_HISTORY *RIDES=NULL;

//Structure Definiton of the Drivers List
struct DRIVERS_PROFILE{
    char name[40];
    char location[40];
    char vehicle_type[40];
    char vehicle_name[40];
    char phone_number[10];
    int status;
    struct DRIVERS_PROFILE *next;
};

//typecasting the drivers profile list
typedef struct DRIVERS_PROFILE DRIVERS_PROFILE;

//Declaration of the Drivers list head node
DRIVERS_PROFILE *DRIVERS=NULL;

//Declaration of the current driver's details structure variable
DRIVERS_PROFILE temp_driver;

//Structure Definition of Coupon codes list
struct COUPON_CODE{
    char code[10];
    int discount;
    struct COUPON_CODE *next;
};

//typecasting the coupon codes list
typedef struct COUPON_CODE COUPON_CODE;

//Declaration of the Coupon codes head node
COUPON_CODE *CODES = NULL;

typedef struct CABS{
    char vehicle_type[40];
    int fare;
    struct CABS *next;
}CABS;

CABS *CAB=NULL;

//Structure definition of minimum spanning tree's cost to be found out(type-casted)
typedef struct Kruskal
{
    int u;
    int v;
    float w;
}MST;

//Structure variable of MST
MST M[50];

//character array to hold the locations
char** locations;

//character array to hold the traveeling time between two points
float** time_estimate;

//character array to hold the traveeling distance between two points
float** distance_estimate;  

//Local variables used in ola.c file
char passwd1[40];
char passwd2[40];

int status;

int digit=0;

int alphabet=0;

int spe_char=0;

int choice;

int count = 0;

int* indexes;

char* pick_dest;

int ans;

float MAX = 10000.00;

int u;

int v;

float t;

int index1;

int index2;

int locations_length=40;

int go_back;

//ALL the Function definitions in ola.c file
void open_log();
void close_log();
void write_log(char *,char *,char *);
int file_empty_check(char *);
int load();
USER_PROFILE* users_memory_allocation();
void user_load();
void user_insert();
USER_PROFILE* users_memory_allocation();
COUPON_CODE* coupon_memory_allocation();
void coupon_insert(COUPON_CODE*);
void coupon_codes_load();
void print_users();
void print_cabs();
CABS* cabs_memory_allocation();
void cabs_load();
void cabs_insert(CABS *temp);
int signup_validation(char*);
char* generateotp();
int user_profile_details(char*);
int password_validation(char*);
void print_locations();
int load_user2(char *,char* );
int load_user1(char *);
int print_ride_history();
int load_ride_history(int);
void ride_insert(RIDE_HISTORY *);
RIDE_HISTORY* rides_memory_allocation();
int login_validation2(char*,char *);
int login_validation1(char *);
void locations_load();
void print_drivers();
void print_users();
void drivers_load();
void drivers_insert(DRIVERS_PROFILE*);
DRIVERS_PROFILE* drivers_memory_allocation();
void print_profile_details();
char* location_validation(char*);
void floyd();
int search_location(char*);
void swap(MST *,MST *);
int Partition(MST *,int,int);
void quicksort(MST*,int,int);
void union_find(int *,int ,int ,int );
void load_driver_eta(char*,char*);
int dump();
void logout_dump();
float search_coupon(char*);
float search_fare(char *);
int update_ride_history(char*,char*,float);
char* tour_journey(char*);
float ride_journey(char*,char*);
void path_trace(int,int *);
int min2(int,int,int*,int,int );
float tour_cost();
float minimum_spanning_tree(int *,MST *,int );

#endif // OLA_H_INCLUDED