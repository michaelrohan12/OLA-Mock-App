#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

//Count variables and the appropriate error codes
int users_count;

int locations_count;

int drivers_count;

int cabs_count;

int coupon_codes_count;

#define SUCCESS                     1
#define FAILURE                    -1
#define FILE_OPEN_ERROR             1001
#define MEMORY_ALLOCATION_ERROR     1002
#define FILE_DELETE_ERROR           1003
#define COUNT_EXCEED_ERROR          1004
#define FILE_EMPTY_ERROR            1006
#define RESULT_NOT_FOUND            1005


#endif // SETTINGS_H_INCLUDED
