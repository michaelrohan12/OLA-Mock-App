#include "ola.h"
#include "settings.h"


//Function:     open_log
//Description:  opens the log file to write the success or failure status
//Input param:  NULL
//Return Type:  NULL
void open_log()
{
    // Open the file
    flog = fopen("log_txt","a+");

    // If unable to open the file, alert the user
    if(flog == NULL)
        printf("LOG File not found. No log status will be captured.");
    else
        fprintf(flog,"%s","_________________START OF PROCESS_________________");
    
    
    fprintf(flog,"%s","\n\n");
}

//Function:     close_log
//Description:  closes the log file if opened
//Input param:  NULL
//Return Type:  NULL
void close_log()
{
    if(flog!=NULL){

        // Add a message to indicate end of a iteration
        fprintf(flog,"%s","_________________END OF PROCESS_________________");
        fprintf(flog,"%s","\n\n");

        // Close the file pointer
        fclose(flog);
    }
}

//Function:     write_log
//Description:  logs the status with success or failure message
//Input param:  function name, status and message to display
//Return Type:  NULL
void write_log(char *function_name,char *status,char *message)
{
    // Write the appropriate log message with associated run time
    mytime = time(NULL);
    fprintf(flog,"%s %s : %s --->%s\n\n",ctime(&mytime),function_name,status,message);
}

//Function:     file_empty_check
//Description:  Check whether file has content or not
//Input param:  name of the file
//Return Type:  integer
//              success state is returned if file has content
//              FILE_EMPTY_ERROR otherwise
int file_empty_check(char *filename)
{

    // Declaring "stat" a system call to know about content of file.
    struct stat filestat;
    stat(filename,&filestat);

    // Variables to hold messages
    char message_failure[40];
    char message_success[40];

    strcpy(message_failure, filename);
    strcat(message_failure, "is empty. No data available");

    strcpy(message_success,filename);
    strcat(message_success," has content.");

    //check size of file and return appropriate status.
    if(filestat.st_size == 0){
        write_log("file_empty_check","FILE_EMPTY_ERROR",message_failure);
        return FILE_EMPTY_ERROR;
    }
    else{
        write_log("file_empty_check","SUCCESS",message_success);
        return SUCCESS;
    }
}

//Function:     users_memory_allocation
//Description:  dynamically allocates the memory to the for the users list
//Input param:  NULL
//Return Type:  USER_PROFILE *
//              success status on successful memory allocation
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
USER_PROFILE* users_memory_allocation(){
    
    //Local node created
    USER_PROFILE *newnode;

    //Allocate memory of the structure to the node and initialise next to Null and return the node
    newnode = (USER_PROFILE*)malloc(sizeof(USER_PROFILE));
    if(newnode==NULL)
        printf("Memory Allocation Failed.");
    else{
        newnode->next=NULL;
        write_log("users_memory_allocation", "SUCCESS", "Memory allocation Successful");
    }
    return newnode;
}

//Function:     users_insert
//Description:  insert the nodes at the end of USERS list
//Input param:  temp of type USER_PROFILE*
//Return Type:  void
//              success status on successful insertion to the log file
void user_insert(USER_PROFILE* temp){
    //If the list is empty, assign to the head node
    if(USER==NULL){
        USER=temp;
    }
    else{
        //Traverse till the last node using curr pointer and insert the node at the end
        USER_PROFILE* curr=USER;
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=temp;
    }

    write_log("user_insert", "SUCCESS", "Insertion of node at the end of USERS List Successful");
}

//Function:     user_load
//Description:  Transferring the data from secondary memory to primary memory using singly-linked list of users list
//Input param:  NULL
//Return Type:  void
//              success status on successful creation of list
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
void user_load(){
    FILE *fp;
    USER_PROFILE *temp;
    fp = fopen("users.txt","r");
    while(!feof(fp)){
        //calling function for memory allocation
        temp=users_memory_allocation();
        if(temp==NULL){
            write_log("user_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return;
        }

        //Data is transferred from secondary memory to primary memory via linked lists
        fscanf(fp,"%d %s %s %s %s ",&temp->user_id,temp->mobile_number,temp->name,temp->email,temp->password);

        //Insert the node
        user_insert(temp);
    }
    fclose(fp);
    write_log("user_load", "SUCCESS", "User List successfully created");
}


//Function:     drivers_memory_allocation
//Description:  dynamically allocates the memory to the for the drivers list
//Input param:  NULL
//Return Type:  DRIVERS_PROFILE *
//              success status on successful memory allocation
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
DRIVERS_PROFILE* drivers_memory_allocation(){
    //Local node created
    DRIVERS_PROFILE *newnode;

    //Allocate memory of the structure to the node and initialise next to Null and return the node
    newnode = (DRIVERS_PROFILE*)malloc(sizeof(DRIVERS_PROFILE));
    if(newnode==NULL)
        printf("Memory Allocation Failed.");
    else{
        newnode->next=NULL;
        write_log("drivers_memory_allocation", "SUCCESS", "Memory allocation Successful");
    }
    return newnode;
}

//Function:     drivers_insert
//Description:  insert the nodes at the end of DRIVERS list
//Input param:  temp of type DRIVERS_PROFILE*
//Return Type:  void
//              success status on successful insertion to the log file
void drivers_insert(DRIVERS_PROFILE* temp){
    //If the list is empty, assign to the head node
    if(DRIVERS==NULL){
        DRIVERS=temp;
    }
    else{
        //Traverse till the last node using curr pointer and insert the node at the end
        DRIVERS_PROFILE* curr=DRIVERS;
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=temp;
    }

    write_log("drivers_insert", "SUCCESS", "Insertion of node at the end of DRIVERS List Successful");
}

//Function:     drivers_load
//Description:  Transferring the data from secondary memory to primary memory using singly-linked list of drivers list
//Input param:  NULL
//Return Type:  void
//              success status on successful creation of list
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
void drivers_load(){
    FILE *fp;
    DRIVERS_PROFILE *temp;
    fp = fopen("drivers.txt","r");
    while(!feof(fp)){
        //calling function for memory allocation
        temp=drivers_memory_allocation();
        if(temp==NULL){
            write_log("drivers_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return;
        }

        //Data is transferred from secondary memory to primary memory via linked lists
        fscanf(fp,"%s %s %s %s %s %d ",temp->name,temp->location,temp->vehicle_type,temp->vehicle_name,temp->phone_number,&temp->status);
        
        //Insert the node
        drivers_insert(temp);
    }
    fclose(fp);
    write_log("drivers_load", "SUCCESS", "Drivers List successfully created");
}

//Function:     print_users
//Description:  Display the contents of users list(admin priveleges)
//Input param:  NULL
//Return Type:  void
//              success status on successful display of list
//              EMPTY Response if list is empty(by indicating through null node)
void print_users(){
    if(USER==NULL){
        printf("USERS list is empty\n\n");
        write_log("print_users", "USERS_LIST_EMPTY", "Users List is empty");
    }
    //Traverse the list using curr pointer and display the details till curr reaches NULL
    USER_PROFILE* curr=USER;
    while(curr!=NULL){
        printf("%d\t%s\t%s\t%s\t%s\n",curr->user_id,curr->mobile_number,curr->name,curr->email,curr->password);
        curr=curr->next;
    }
    printf("\n");

    write_log("print_users", "SUCCESS", "Users List Displayed successfully.");
}

//Function:     print_drivers
//Description:  Display the contents of drivers list(admin priveleges)
//Input param:  NULL
//Return Type:  void
//              success status on successful display of list
//              EMPTY Response if list is empty(by indicating through null node)
void print_drivers(){
    if(DRIVERS==NULL){
        printf("DRIVERS list is empty\n\n");
        write_log("print_drivers", "DRIVERS_LIST_EMPTY", "Drivers List is empty");
    }
    DRIVERS_PROFILE* curr=DRIVERS;
    //Traverse the list using curr pointer and display the details till curr reaches NULL
    while(curr!=NULL){
        printf("%s\t%s\t%s\t%s\t%s\t%d\n",curr->name,curr->location,curr->vehicle_type,curr->vehicle_name,curr->phone_number,curr->status);
        curr=curr->next;
    }
    printf("\n");

    write_log("print_drivers", "SUCCESS", "Drivers List Displayed successfully.");
}

void print_coupons_code(){
    COUPON_CODE *curr=CODES;
    while(curr!=NULL){
        printf("%s\t%d\n",curr->code,curr->discount);
        curr=curr->next;
    }
}

//Function:     locations_load
//Description:  Transferring the data from secondary memory to primary memory using dynamic array of type char* for locations list
//Input param:  NULL
//Return Type:  void
//              success status on successful allocation of array
//              MEMORY_ALLOCATION_ERROR on failure
void locations_load(){
    FILE *fp;
    int i=0;
    //Column Dynamic allocation of locations using char* array
    locations = (char**)malloc(locations_count*sizeof(char*));

    if(locations == NULL){
        write_log("locations_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
        return ;
    }
    fp = fopen("locations.txt","r");
    while(!feof(fp)){
        //Each row dynamic allocation of array
        locations[i] = (char*)malloc(locations_length*sizeof(char*));
        if(locations[i] == NULL){
            write_log("locations_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return;
        }

        //Transfer of string from secondary memory to primary memory
        fscanf(fp,"%s ",locations[i]);
        i++;
    }
    fclose(fp);

    write_log("locations_load", "SUCCESS", "Locations succssfully loaded to array.");
}

//Function:     coupon_memory_allocation
//Description:  Transferring the data from secondary memory to primary memory using linked lists for coupons list
//Input param:  COUPON_CODE*
//Return Type:  void
//              success status on successful allocation of array
//              MEMORY_ALLOCATION_ERROR on failure(via NULL node)
COUPON_CODE* coupon_memory_allocation(){
    //local node of type COUPON_CODE*
    COUPON_CODE* newnode;

    //Dynamic allocation of memory to node-
    newnode = (COUPON_CODE*)malloc(sizeof(COUPON_CODE));
    if(newnode==NULL)
        printf("Memory Allocation Failed\n");
    else{
        newnode->next = NULL;
        write_log("Coupon_memory_allocation", "SUCCESS", "Coupon NODE Succefully created.");
    }
    return newnode;

    
}

//Function:     coupon_insert
//Description:  insert the nodes at the end of coupons list
//Input param:  temp of type COUPON_CODE*
//Return Type:  void
//              success status on successful insertion to the log file
void coupon_insert(COUPON_CODE *temp){
    //If list is empty, assign to head node
    if(CODES==NULL){
        CODES=temp;
    }
    else{
        //Traverse till the last node using curr pointer and insert the node at the end
        COUPON_CODE *curr=CODES;
        while(curr->next!=NULL)
            curr = curr->next;
        curr->next = temp;
    }

    write_log("coupon_insert", "SUCCESS", "Coupon NODE Succefully inserted at the end of coupons list.");
}

//Function:     coupon_codes_load
//Description:  Transferring the data from secondary memory to primary memory using singly-linked list of coupons list
//Input param:  NULL
//Return Type:  void
//              success status on successful creation of list
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
void coupon_codes_load()
{
    FILE *fp;
    COUPON_CODE *temp;
    fp = fopen("coupon_codes.txt","r");
    while(!feof(fp)){
        //calling function for memory allocation
        temp = coupon_memory_allocation();
        if(temp == NULL){
            write_log("drivers_load", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return;
        }
        //Data is transferred from secondary memory to primary memory via linked lists
        fscanf(fp,"%s %d ",temp->code,&temp->discount);

        //Insert the node
        coupon_insert(temp);
    }
    fclose(fp);
    write_log("coupon_codes_load", "SUCCESS", "Coupons Code List successfully created");
}

//Function:     cabs_memory_allocation
//Description:  Transferring the data from secondary memory to primary memory using linked lists for cabs list
//Input param:  CABS*
//Return Type:  void
//              success status on successful allocation of array
//              MEMORY_ALLOCATION_ERROR on failure(via NULL node)
CABS* cabs_memory_allocation(){
    //local node of type COUPON_CODE*
    CABS* newnode;

    //Dynamic allocation of memory to node-
    newnode = (CABS*)malloc(sizeof(CABS));
    if(newnode==NULL)
        printf("Memory Allocation Failed\n");
    else{
        newnode->next = NULL;
        write_log("Cabs_memory_allocation", "SUCCESS", "Cabs NODE Succefully created.");
    }
    return newnode;

    
}

//Function:     cabs_insert
//Description:  insert the nodes at the end of cabs list
//Input param:  temp of type CABS*
//Return Type:  void
//              success status on successful insertion to the log file
void cabs_insert(CABS *temp){
    //If list is empty, assign to head node
    if(CAB==NULL){
        CAB=temp;
    }
    else{
        //Traverse till the last node using curr pointer and insert the node at the end
        CABS *curr=CAB;
        while(curr->next!=NULL)
            curr = curr->next;
        curr->next = temp;
    }

    write_log("cabs_insert", "SUCCESS", "Cabs NODE Succefully inserted at the end of Cabs list.");
}

//Function:     cabs_load
//Description:  Transferring the data from secondary memory to primary memory using singly-linked list of cabs list
//Input param:  NULL
//Return Type:  void
//              success status on successful creation of list
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
void cabs_load(){
    FILE *fp;
    CABS *temp;
    fp = fopen("cabs.txt","r");
    while(!feof(fp)){
        //calling function for memory allocation
        temp = cabs_memory_allocation();
        if(temp == NULL){
            write_log("cabs_load()", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
            return;
        }
        //Data is transferred from secondary memory to primary memory via linked lists
        fscanf(fp,"%s %d ",temp->vehicle_type,&temp->fare);

        //Insert the node
        cabs_insert(temp);
    }
    fclose(fp);
    write_log("cabs_load", "SUCCESS", " List successfully created"); 
}

//Function:     print_cabs
//Description:  Display the contents of cabs list
//Input param:  NULL
//Return Type:  void
//              success status on successful display of list
//              EMPTY Response if list is empty(by indicating through null node)
void print_cabs(){
    if(CAB==NULL){
        printf("CABS list is empty\n\n");
        write_log("print_cabs", "Cabs_LIST_EMPTY", "Cabs List is empty");
    }
    CABS* curr=CAB;
    //Traverse the list using curr pointer and display the details till curr reaches NULL
    while(curr!=NULL){
        printf("%s\t%d\n",curr->vehicle_type,curr->fare);
        curr=curr->next;
    }
    printf("\n");

    write_log("print_cabs()", "SUCCESS", "Cabs List Displayed successfully.");
}

//Function:     load
//Description:  loads the count and is a gateway for loading all the respective file
//              loads the data from secondary memory to primary
//Input param:  NULL
//Return Type:  integer
//              success status on successful operation
//              respective error status code otherwise
int load()
{
    // Start the log file
    open_log();

    // Use a file pointer to open various files to load the values
    FILE *fp;

    //Local variables
    int status      = 0;
    int file_status = 0;


    //check whether users_count.txt file is empty or not.
    file_status = file_empty_check("users_count.txt");
    if (file_status == 1006)
        return FAILURE;

    //check whether users.txt file is empty or not.
    file_status = file_empty_check("users.txt");
    if (file_status == 1006)
        return FAILURE; 

    //check whether drivers_count.txt file is empty or not.
    file_status = file_empty_check("drivers_count.txt");
    if (file_status == 1006)
        return FAILURE; 

    //check whether drivers.txt file is empty or not.
    file_status = file_empty_check("drivers.txt");
    if (file_status == 1006)
        return FAILURE;

    //check whether locations_count.txt file is empty or not.
    file_status = file_empty_check("locations_count.txt");
    if (file_status == 1006)
        return FAILURE; 

    //check whether locations.txt file is empty or not.
    file_status = file_empty_check("locations.txt");
    if (file_status == 1006)
        return FAILURE; 

    //check whether coupon_codes_count.txt file is empty or not.
    file_status = file_empty_check("coupon_codes_count.txt");
    if (file_status == 1006)
        return FAILURE;    

    //check whether coupon_codes.txt file is empty or not.
    file_status = file_empty_check("coupon_codes.txt");
    if (file_status == 1006)
        return FAILURE;
    
    //check whether time_data.txt file is empty or not.
    file_status = file_empty_check("time_data.txt");
    if (file_status == 1006)
        return FAILURE;

    //check whether distance_data.txt file is empty or not.
    file_status = file_empty_check("distance_data.txt");
    if (file_status == 1006)
        return FAILURE;
    
    //check whether cabs_count.txt file is empty or not.
    file_status = file_empty_check("cabs_count.txt");
    if (file_status == 1006)
        return FAILURE;

    //check whether cabs.txt file is empty or not.
    file_status = file_empty_check("cabs.txt");
    if (file_status == 1006)
        return FAILURE;

    //Loading of USERS List
    user_load();

    //Loading of drivers list
    drivers_load();

    //Loading of coupon_codes list
    coupon_codes_load();

    //Open the locations_count file to read the number of locations
    fp = fopen("locations_count.txt","r");
    if(fp == NULL) {
        write_log("load", "FILE_OPEN_ERROR", "Unable to open the locations_count file");
        return FAILURE;
    }
    fscanf(fp,"%d ",&locations_count);
    fclose(fp);

    //Loading of locations list
    locations_load();

    cabs_load();

    //Open the users_count file to read the number of users
    fp = fopen("users_count.txt","r");
    if(fp == NULL) {
        write_log("load", "FILE_OPEN_ERROR", "Unable to open the users_count file");
        return FAILURE;
    }
    fscanf(fp,"%d ",&users_count);
    fclose(fp);

    //Open the drivers_count file to read the number of drivers
    fp = fopen("drivers_count.txt","r");
    if(fp == NULL) {
        write_log("load", "FILE_OPEN_ERROR", "Unable to open the drivers_count file");
        return FAILURE;
    }
    fscanf(fp,"%d ",&drivers_count);
    fclose(fp);

    //Open the cabs_count file to read the number of cabs
    fp = fopen("cabs_count.txt","r");
    if(fp == NULL) {
        write_log("load", "FILE_OPEN_ERROR", "Unable to open the cabs_count file");
        return FAILURE;
    }
    fscanf(fp,"%d ",&cabs_count);
    fclose(fp);

    //Open the coupon_codes_count file to read the number of coupon codes
    fp = fopen("coupon_codes_count.txt","r");
    if(fp == NULL) {
        write_log("load", "FILE_OPEN_ERROR", "Unable to open the coupon_codes_count file");
        return FAILURE;
    }
    fscanf(fp,"%d ",&coupon_codes_count);
    fclose(fp);

    

    write_log("load", "SUCCESS", "Load Successful");
    return SUCCESS;
}

//Function:     signup_validation
//Description:  Checks if the given credentials i.e., Mobile number is valid
//              and checks if the user has an account already
//Input param:  mobile_no of type char*
//Return Type:  integer
//              success status on successful operation
//              otherwise FAILURE with appropriate message
int signup_validation(char *mobile_no){
    
    //Check if the mobile number is 10 digits long(input has to be in digits)
    if(strlen(mobile_no)==10){
        //Traverse the list to check for any dupliicates exist
        USER_PROFILE *curr=USER;
        while(curr!=NULL){
            if(!strcmp(mobile_no,curr->mobile_number)){
                write_log("signup_validation", "FAILURE", "Mobile NUMBER IS PRE-EXISTING");
                return FAILURE;
            }
            curr=curr->next;
        }
        write_log("signup_validation", "SUCCESS", "Successfully signed up");
        return SUCCESS;
    }
    else{
        write_log("signup_validation", "FAILURE", "Mobile NUMBER IS Invalid");
        return FAILURE;
    }
}

//Function:     generateotp
//Description:  A mock applicationf of A One-Time-Password(otp)
//Input param:  NULL
//Return Type:  CHAR*
//              success status on successful operation
//              Failure if memory is not allocated
char* generateotp(){
    int n = strlen(str);
    //Dynamic allocation of variable
    char* otp = malloc(7*sizeof(char));
    if(otp == NULL){
        printf("Memory Allocation Failed\n");
        write_log("generateotp", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
    }
    //Using rand() function for a random otp to be generated modulus the string length
    for(int i=0;i<6;i++){
        otp[i] = str[rand()%n];
    }

    write_log("generateotp", "SUCCESS", "OTP is successfully created");
    
    return otp;
}

//Function:     passsword_validation
//Description:  Checks if the given password is according to the given specifications
//Input param:  password of type char*
//Return Type:  integer
//              success status on successful operation
//              otherwise FAILURE with appropriate message
int password_validation(char* password){
    if(strlen(password)>=6){
        for(int i=0;i<strlen(password);i++){
            //Check for a digit in the password,alphabets and special character
            if((isdigit(password[i])!=0)){
                digit=1;
            }
            else if((password[i] >= 97 && password[i] <= 122) || (password[i] >= 65 && password[i] <= 90)){
                alphabet=1;
            }
            else{
                spe_char=1;
            }
            if(alphabet==1 && digit==1 && spe_char==1){
                write_log("password_validation", "SUCCESS", "Password is affirmed.");
                return SUCCESS;
            }
        }
        write_log("password_validation", "FAILURE", "Password is not affirmed.");
        return FAILURE;
    }
    else{
        write_log("password_validation", "FAILURE", "Password is of appropriate length.");
        return FAILURE;
    }
}

//Function:     user_profile_details
//Description:  Checks if the given password is according to the given specifications
//Input param:  password of type char*
//Return Type:  integer
//              success status on successful operation
//              otherwise FAILURE with appropriate message
int user_profile_details(char* mobile){
    //creation of node to store the details
    USER_PROFILE *temp;
    temp = users_memory_allocation();
    if(temp==NULL){
        write_log("user_profile_details", "MEMORY_ALLOCATION_ERROR", "Memory allocation failed");
        return MEMORY_ALLOCATION_ERROR;
    }
    //transfer of data to the temp node
    strcpy(temp->mobile_number,mobile);
    temp->user_id=users_count+1;
    char buf[40];

    //Creation of ride_history file
    sprintf(buf,"ride_history_user%d.txt",temp->user_id);
    FILE *fp;
    fp = fopen(buf,"a+");
    fclose(fp);
    printf("Enter your profile details\n\n");
    printf("Name:");
    scanf(" %s",temp->name);
    printf("Email ID:");
    scanf("%s",temp->email);
    re_enter:
    printf("Password\n");
    printf("Should have a length of 6 (max 40),consisting at least one number,one alphabet and one special character\n");
    scanf("%s",passwd1);

    //Calling of password_validation function, goto label to complete the process properly
    status=password_validation(passwd1);
    if(status!=1){
        printf("\n\nIncorrect format of password!!\n\n");
        goto re_enter;
    }
    printf("Re-enter your password\n");
    scanf("%s",passwd2);
    if(!strcmp(passwd1,passwd2)){
        strcpy(temp->password,passwd1);

        //Insertion of node to the end of the users file
        user_insert(temp);
        users_count++;
        printf("\n\nPROFILE DETAILS COMPLETED!!");

        write_log("user_profile_details", "SUCCESS", "User details updated successfully.");
        Sleep(1000);
        return SUCCESS;
    }
    printf("\n\nPasswords do not match\n\n");
    goto re_enter;
}

//Function:     login_validation1
//Description:  Checks if the given mobile_no is an existing user of ola
//Input param:  mobile number of type char*
//Return Type:  integer
//              success status on successful operation
//              otherwise FAILURE with appropriate message
int login_validation1(char *mobile_no){
    //Check for 10 digit mobile number
    if(strlen(mobile_no)==10){
        USER_PROFILE *curr=USER;
        while(curr!=NULL){
            //check is user is existing in users list
            if(!strcmp(mobile_no,curr->mobile_number)){
                write_log("login_validation1", "SUCCESS", "Login Sucessful.");
                return SUCCESS;
            }
            curr=curr->next;
        }
        write_log("login_validation1", "FAILURE", "Login UnSucessful/not signed up.");
        return FAILURE;
    }
    else{
        write_log("login_validation1", "FAILURE", "Login UnSucessful/Incorrect MOBILE number.");
        return FAILURE;  
    }
}

//Function:     login_validation2
//Description:  Checks if the given email_id and password is of an existing user of ola
//Input param:  email and password of type char*
//Return Type:  integer
//              success status on successful operation
//              otherwise FAILURE with appropriate message
int login_validation2(char* email,char *password){
    USER_PROFILE *curr=USER;
    while(curr!=NULL){
        //Traverse to the list and check for compatibility
        if(!strcmp(email,curr->email) && !strcmp(password,curr->password)){
            write_log("login_validation1", "SUCCESS", "Login Sucessful.");
            return SUCCESS;
        }
        curr=curr->next;
    }
    write_log("login_validation1", "FAILURE", "Login UnSucessful/not signed up/Incorrect details.");
    return FAILURE;
}

//Function:     rides_memory_allocation
//Description:  Allocation of memory for Rides history list
//Input param:  NULL
//Return Type:  RIDE_HISTORY*
//              success status on successful creation of list
//              MEMORY_ALLOCATION_ERROR on failure(by indicating through null node)
RIDE_HISTORY* rides_memory_allocation(){
    //Local node created
    RIDE_HISTORY *newnode;

    //Allocate memory of the structure to the node and initialise next to Null and return the node
    newnode = (RIDE_HISTORY*)malloc(sizeof(RIDE_HISTORY));
    if(newnode==NULL)
        printf("Memory Allocation Failed.");
    else{
        newnode->next=NULL;
        write_log("rides_memory_allocation", "SUCCESS", "Memory allocation Successful");
    }
    return newnode;
}

//Function:     ride_insert
//Description:  Insertion of node at the end of the rides linked list
//Input param:  temp of type RIDE_HISTORY *
//Return Type:  void
//              success status on successful insertion of node at the end of the list
void ride_insert(RIDE_HISTORY *temp){
    //If list is empty assign node to head
    if(RIDES==NULL){
        RIDES=temp;
    }
    else{
        //Traverse the last node and attach the node to it
        RIDE_HISTORY *curr=RIDES;
        while(curr->next!=NULL)
            curr=curr->next;
        curr->next=temp;
    }
    write_log("ride_insert", "SUCCESS", "NOde Successfully inserted at th end of rides list.");
}

//Function:     load_ride_history
//Description:  Load the ride history of a user from secondary memory to primary memory
//Input param:  id of type int
//Return Type:  int
//              success status on successful load of the file
int load_ride_history(int id){
    int file_status = 0;
    //Use a buffer to store the user id and access the appropriate user ride history file
    char buf[40];
    sprintf(buf,"ride_history_user%d.txt",id);
    FILE *fp;
    fp = fopen(buf,"r");

    //check if the file is empty
    file_status = file_empty_check(buf);
    if (file_status == 1006){
        write_log("load_ride_history", "FAILURE", "User Ride history is empty.");
        return FAILURE;
    }
    
    RIDE_HISTORY *temp;
    //Transfer of data from secondary memory to primary memory
    while(!feof(fp)){
        temp = rides_memory_allocation();
        if(temp==NULL)
            return MEMORY_ALLOCATION_ERROR;
        fscanf(fp,"%s %s %s %s %s %0.2f ",temp->pickup,temp->destination,temp->driver_name,temp->vehicle_type,temp->vehicle_name,&temp->fare);
        ride_insert(temp);
    }
    fclose(fp);
    write_log("load_ride_history", "SUCCESS", "Ride history of user succefully loaded");
    return SUCCESS;
}

//Function:     print_ride_history
//Description:  Display the ride history of the user
//Input param:  NULL
//Return Type:  int
//              success status on successful DISPLAY of the file
int print_ride_history(){
    if(RIDES==NULL){
        write_log("print_ride_history", "FAILURE", "Ride history of user is empty");
        return FAILURE;
    }
    RIDE_HISTORY* curr=RIDES;

    //Traverse through the list and display the data
    while(curr!=NULL){
        printf("%s\t%s\t%s\t%s\t%s\t%0.2f\n",curr->pickup,curr->destination,curr->driver_name,curr->vehicle_type,curr->vehicle_name,curr->fare);
        curr=curr->next;
    }
    Sleep(10000);

    write_log("print_ride_history", "SUCCESS", "Displayed the data succesfully.");
    return SUCCESS;
}

//Function:     load_user1
//Description:  After login, to hold the current user details in a separate structure
//Input param:  mobile number of type char*
//Return Type:  int
//              success status on successful LOAD of the data
//              FAILURE if data is not found
int load_user1(char *mobile){
    USER_PROFILE* curr=USER;
    //Traverse through the list and search for mobile number of registered user
    while(curr!=NULL){
        if(!strcmp(mobile,curr->mobile_number)){
            break;
        }
        curr=curr->next;
    }

    //If user is not found
    if(curr==NULL){
        printf("Error in user file\n\n");
        write_log("load_user1", "FAILURE", "User not found check users file.");
        return FAILURE;
    }

    //Transfer of data to a new structure (temporary)
    CURR_USER.user_id=curr->user_id;
    strcpy(CURR_USER.name,curr->name);
    strcpy(CURR_USER.mobile_number,curr->mobile_number);
    strcpy(CURR_USER.email,curr->email);
    strcpy(CURR_USER.password,curr->password);
    load_ride_history(curr->user_id);

    write_log("load_user1", "SUCCESS", "Successfully loaded the data into new structure.");
    return SUCCESS;
}

//Function:     load_user1
//Description:  After login, to hold the current user details in a separate structure
//Input param:  email and password of type char*
//Return Type:  int
//              success status on successful LOAD of the data
//              FAILURE if data is not found
int load_user2(char *email,char* password){
    USER_PROFILE* curr=USER;
    //Traverse through the list and search for email and password of registered user
    while(curr!=NULL){
        if(!strcmp(email,curr->email) && !strcmp(password,curr->password)){
            break;
        }
        curr=curr->next;
    }

    //If user is not found
    if(curr==NULL){
        write_log("load_user2", "FAILURE", "User not found check users file.");
        printf("Error in user file\n\n");
        return FAILURE;
    }

    //Transfer of data to a new structure (temporary)
    CURR_USER.user_id=curr->user_id;
    strcpy(CURR_USER.name,curr->name);
    strcpy(CURR_USER.mobile_number,curr->mobile_number);
    strcpy(CURR_USER.email,curr->email);
    strcpy(CURR_USER.password,curr->password);
    load_ride_history(curr->user_id);

    write_log("load_user2", "SUCCESS", "Successfully loaded the data into new structure.");
    return SUCCESS;
}

//Function:     print_locations
//Description:  Display the locations that can be used for pickup and destination
//Input param:  email and password of type char*
//Return Type:  int
//              success status on successful LOAD of the data
//              FAILURE if data is not found
void print_locations(){
    //Display locations
    printf("The Locations are\n");
    for(int i=0;i<locations_count;i++){
        printf("%s\n",locations[i]);
    }
    printf("\n");

    write_log("print_locations", "SUCCESS", "Successfully displayed the locations.");
}

//Function:     print_profile_details
//Description:  Display the profile details of the user 
//Input param:  NULL
//Return Type:  int
//              success status on successful LOAD of the data
//              FAILURE if data is not found
void print_profile_details(){
    //User details displayed using the temporary structure
    printf("Name:%s\n",CURR_USER.name);
    printf("Mobile_No:%s\n",CURR_USER.mobile_number);
    printf("Email ID:%s\n",CURR_USER.email);
    printf("Password:******\n");
    re_enter:

    //To check and go back
    printf("Press 0 to go back\n");
    scanf("%d",&choice);
    if(choice==0){

        write_log("print_profile_details", "SUCCESS", "Successfully displayed the profile details.");
        return;
    }
    else{
        goto re_enter;
    }
}

//Function:     location_validation
//Description:  Using brute force string search, to search for the pickup and destination
//Input param:  pick_dest of type char* (both pickup and destination)
//Return Type:  char*
//              success status on successful find of data
//              FAILURE if data is not found
char* location_validation(char* pick_dest){
    int i,j,k,n,m;
    count = 0;

    //array of indexes with matches
    indexes = malloc(locations_count*sizeof(int));
    m = strlen(pick_dest);

    //Check for matching string in the given locations
    for(i=0;i<locations_count;i++){
        n = strlen(locations[i]);
        for(j=0;j<=(n-m);j++){
            k = 0;

            //Cotinue the loop till match is found
            while(k<m && pick_dest[k]==locations[i][j+k]){
                k = k+1;
            }

            //If match is found load it to the indexes array 
            if(k==m){
                indexes[count] = i;
                count++;
                break;
            }
        }
    }
    
    //No matching sub-strings found
    if(count==0){
        printf("No matching locations found!! Re-enter the pickup location.\n");

        write_log("location_validation", "FAILURE", "No matching locations found.");
        return NULL;
    }
    //If there is only one match, ask for confirmation
    else if(count == 1){
        re_enter:
        printf("Pickup Location chosen is:%s\n",locations[indexes[0]]);
        printf("Press 1 to confirm\n");
        printf("Press 2 to Re-enter\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:strcpy(pick_dest,locations[indexes[0]]);
                   write_log("location_validation", "SUCCESS", "matching locations found and approved.");
                   return pick_dest;
                   break;
            case 2:write_log("location_validation", "SUCCESS", "matching locations found but not approved.");
                    return NULL;
                   break;
            default:printf("Invalid choice please re-enter!!\n");
                    goto re_enter;
        }
    }
    //Multiple matches, display the strings and ask for confirmation
    else{
        re_enter1:
        printf("Possible Locations to choose from\n");
        for(i=0;i<count;i++){
            printf("%d.%s\n",i+1,locations[indexes[i]]);
        }
        printf("\nPress 1 to choose from above locations\n");
        printf("Press 2 to Re-enter\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:re_enter2:
                   printf("Enter your location choice:");
                   scanf("%d",&ans);
                   if(ans>count){
                       printf("Incorrect choice!! Re-enter\n");
                       goto re_enter2;
                   }
                   strcpy(pick_dest,locations[indexes[ans-1]]);
                   write_log("location_validation", "SUCCESS", "matching locations found and approved.");
                   return pick_dest;
                   break;
            case 2:write_log("location_validation", "SUCCESS", "matching locations found but not approved.");
                    return NULL;
                   break;
            default:printf("Invalid choice please re-enter!!\n");
                    goto re_enter1;
        }
    }
}

//Function:     floyd
//Description:  Search for the shortest paths for all locations to all locations for ease in finding ETA of the driver
//Input param:  NULL
//Return Type:  void
//              success status on successful find of data
//              FAILURE if data is not found
void floyd()
{
    for(int k=0;k<locations_count;k++){
        for(int i=0;i<locations_count;i++){
            for(int j=0;j<locations_count;j++)
            {
                if((time_estimate[i][k]+time_estimate[k][j])<time_estimate[i][j])
                    time_estimate[i][j]=time_estimate[i][k]+time_estimate[k][j];
            }
        }
    }
}

int search_location(char* loc){
    for(int i=0;i<locations_count;i++){
        if(!strcmp(loc,locations[i])){
            return i;
        }
    }
}

void load_driver_eta(char* pickup,char* vehicle_type){
    time_estimate = malloc(locations_count*sizeof(*time_estimate));
    for(int i=0;i<locations_count;i++)
    {
        time_estimate[i] = malloc(locations_count*sizeof(*time_estimate[i]));
    }
    for(int i=0;i<locations_count;i++){
        for(int j=0;j<locations_count;j++){
            if(i==j)
                time_estimate[i][j]=0;
            else
                time_estimate[i][j]=MAX;
        }
    }
    FILE *fp;
    fp = fopen("time_data.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d %d %f ",&u,&v,&t);
        time_estimate[u][v]=t;
        time_estimate[v][u]=t;
    }
    fclose(fp);
    floyd();
    DRIVERS_PROFILE *curr=DRIVERS;
    float min=MAX;
    index2 = search_location(pickup);
    while(curr!=NULL)
    {
        index1 = search_location(curr->location);
        if(min>time_estimate[index1][index2]){
            if(curr->status==0 && (!strcmp(curr->vehicle_type,vehicle_type)))
            {
                strcpy(temp_driver.name,curr->name);
                strcpy(temp_driver.location,curr->location);
                strcpy(temp_driver.vehicle_type,curr->vehicle_type);
                strcpy(temp_driver.vehicle_name,curr->vehicle_name);
                strcpy(temp_driver.phone_number,curr->phone_number);
                min=time_estimate[index1][index2];
            }
        }
        curr=curr->next;
    }
    printf("Driver Details\n");
    printf("Name:%s\n",temp_driver.name);
    printf("Location:%s\n",temp_driver.location);
    printf("Vehicle_type:%s\n",temp_driver.vehicle_type);
    printf("Vehicle_name:%s\n",temp_driver.vehicle_name);
    printf("Phone Number:%s\n\n",temp_driver.phone_number);
    printf("ETA IN:%0.2f minutes\n",min);
    printf("Press 0 TO CONTINUE\n");
    scanf("%d",&choice);
    if(choice==0){
        return;
    }
}

void swap(MST *a,MST *b)
{
    MST temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int Partition(MST *M,int l,int r)
{
    float p = M[l].w;
    int i = l;
    int j = r+1;
    do
    {
        do
        {
            ++i;
        }while(M[i].w<p);
        do
        {
            --j;
        }while(M[j].w>p);
        swap(&M[i],&M[j]);
    }while(i<j);
    swap(&M[i],&M[j]);
    swap(&M[l],&M[j]);
    return j;
}

void quicksort(MST *M,int l,int r)
{
    if(l<r)
    {
        int s = Partition(M,l,r);
        quicksort(M,l,s-1);
        quicksort(M,s+1,r);
    }
}

void union_find(int *a,int i,int j,int n)
{
    int k;
    for(k=0;k<n;k++)
    {
        if(a[k]==i)
        {
            a[k]=j;
        }
    }
}

float minimum_spanning_tree(int *a,MST *M,int n)
{
    int i,j,step=0,count=0;
    float cost = 0.0;
    while(count<n-1)
    {
        i=a[M[step].u];
        j=a[M[step].v];
        if(i!=j)
        {
            cost+=M[step].w;
            count++;
        }
        step++;
    }
    return cost;
}

float tour_cost(){
    int* a = malloc(locations_count*sizeof(int));
    for(int i=0;i<locations_count;i++){
        a[i]=i;
    }
    int i=0;
    FILE *fp;
    fp = fopen("distance_data.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d %d %f ",&M[i].u,&M[i].v,&M[i].w);
        i++;
    }
    fclose(fp);
    quicksort(M,0,i-1);
    float cost=minimum_spanning_tree(a,M,locations_count);
    return cost;
}

int min2(int a,int b,int* path,int source,int i)
{
    if(a<b)
        return a;
    else{
        path[i]=source;
        return b;
    }
}

void path_trace(int destination,int *path){
    if(path[destination]==destination){
         printf("%s",locations[destination]);
         printf("-");
         Sleep(1000);
         printf("-");
         Sleep(1000);
         printf("-");
         Sleep(1000);
         printf(">");
         return;
    }
    path_trace(path[destination],path);
    printf("%s",locations[destination]);
    printf("-");
    Sleep(1000);
    printf("-");
    Sleep(1000);
    printf("-");
    Sleep(1000);
    printf(">");
    return;

}

float ride_journey(char* pickup,char* destination){
    time_estimate = malloc(locations_count*sizeof(*time_estimate));
    for(int i=0;i<locations_count;i++)
    {
        time_estimate[i] = malloc(locations_count*sizeof(*time_estimate[i]));
    }
    for(int i=0;i<locations_count;i++){
        for(int j=0;j<locations_count;j++){
            if(i==j)
                time_estimate[i][j]=0;
            else
                time_estimate[i][j]=MAX;
        }
    }
    FILE *fp;
    fp = fopen("time_data.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d %d %f",&u,&v,&t);
        time_estimate[u][v]=t;
        time_estimate[v][u]=t;
    }
    
    int source = search_location(pickup);
    int destinations = search_location(destination);
    int min_wt,min_index,flag1=1,flag2=1;
    int* path = malloc(locations_count*sizeof(int));
    int*  visited = malloc(locations_count*sizeof(int));
    float* dist = malloc(locations_count*sizeof(float));

    float total = 0.0;
    memset(visited,0,locations_count*sizeof(int));
    for(int i=0;i<locations_count;i++)
        path[i] = source;
    for(int i=0;i<locations_count;i++){
        dist[i] = time_estimate[source][i];
    }
    visited[source]=1;
    while(flag1)
    {
        flag1=0;
        flag2=1;
        for(int i=0;i<locations_count;i++)
        {
            if(visited[i] == 0){
                flag1 = 1;
                if(flag2){
                    flag2=0;
                    dist[i]=min2(dist[i],total+time_estimate[source][i],path,source,i);
                    min_wt=dist[i];
                    min_index=i;
                }
                else{
                    dist[i]=min2(dist[i],total+time_estimate[source][i],path,source,i);
                    if(min_wt>dist[i]){
                        min_wt=dist[i];
                        min_index=i;
                    }
                }

            }
        }
        if(flag1==0){
            break;
        }
        visited[min_index]=1;
        source=min_index;
        total=min_wt;
    }
    path_trace(destinations,path);
    printf("You have Reached your Destination!!\n\n");
    printf("Total time taken:%0.2f minutes\n\n",dist[destinations]);
    Sleep(2000);
    return dist[destinations];
}

char* tour_journey(char* pickup){
    time_estimate = malloc(locations_count*sizeof(*time_estimate));
    for(int i=0;i<locations_count;i++)
    {
        time_estimate[i] = malloc(locations_count*sizeof(*time_estimate[i]));
    }
    for(int i=0;i<locations_count;i++){
        for(int j=0;j<locations_count;j++){
            if(i==j)
                time_estimate[i][j]=0;
            else
                time_estimate[i][j]=MAX;
        }
    }
    FILE *fp;
    fp = fopen("time_data.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d %d %f",&u,&v,&t);
        time_estimate[u][v]=t;
        time_estimate[v][u]=t;
    }
    int source = search_location(pickup);
    int min_wt,min_index,flag1=1,flag2=1;
    int* path = malloc(locations_count*sizeof(int));
    int*  visited = malloc(locations_count*sizeof(int));
    float* dist = malloc(locations_count*sizeof(float));
    memset(visited,0,locations_count*sizeof(int));
    for(int i=0;i<locations_count;i++)
        path[i] = source;
    for(int i=0;i<locations_count;i++){
        dist[i] = time_estimate[source][i];
    }
    visited[source]=1;
    while(flag1)
    {
        flag1=0;
        flag2=1;
        for(int i=0;i<locations_count;i++)
        {
            if(visited[i]==0){
                flag1=1;
                if(flag2){
                    flag2=0;
                    dist[i]=min2(dist[i],time_estimate[source][i],path,source,i);
                    min_wt=dist[i];
                    min_index=i;
                }
                else{
                    dist[i]=min2(dist[i],time_estimate[source][i],path,source,i);
                    if(min_wt>dist[i]){
                        min_wt=dist[i];
                        min_index=i;
                    }
                }

            }
        }
        if(flag1==0){
            break;
        }
        printf("%s",locations[source]);
        printf("-");
        Sleep(1000);
        printf("-");
        Sleep(1000);
        printf("-");
        Sleep(1000);
        printf(">");
        visited[min_index]=1;
        source=min_index;
    }
    printf("%s",locations[min_index]);
    printf("\n\nTour Completed\n\n");
    return locations[min_index];
    Sleep(5000);
}


//Function:     update_ride_history
//Description:  
//Input para:   name of type char*
//Return Type:  float
//              Success status on successful operation
int update_ride_history(char* pickup,char* destination,float fare){
    RIDE_HISTORY *temp;
    temp = rides_memory_allocation();
    strcpy(temp->pickup,pickup);
    strcpy(temp->destination,destination);
    temp->fare=fare;
    strcpy(temp->driver_name,temp_driver.name);
    strcpy(temp->vehicle_type,temp_driver.vehicle_type);
    strcpy(temp->vehicle_name,temp_driver.vehicle_name);
    ride_insert(temp);
    return SUCCESS;
}

//Function:     search_fare
//Description:  search the index of the fare for which amouint will be deducted
//Input para:   name of type char*
//Return Type:  float
//              Success status on successful operation
float search_fare(char *name){
    CABS *curr=CAB;
    //Traverse through cabs list and find the apporpriate fare of cab
    while(curr!=NULL){
        if(!strcmp(name,curr->vehicle_type)){
            write_log("search_fare", "SUCCESS", "Fare of Cab found.");
            return curr->fare;
        }
        curr=curr->next;
    }

    write_log("search_fare", "FAILURE", "Fare of cab NOT found.");
    return FAILURE;
}

//Function:     search_coupon
//Description:  search the index of the coupon for which dicount will be applied
//Input para:   name of type char*
//Return Type:  float
//              Success status on successful operation
float search_coupon(char* name){
    COUPON_CODE *curr=CODES;
    //Traverse through coupons list and find the apporpriate coupon
    while(curr!=NULL){
        if(!strcmp(name,curr->code)){
            write_log("search_coupon", "SUCCESS", "Coupon code found.");
            return curr->discount;
        }
        curr=curr->next;
    }

    write_log("search_coupon", "FAILURE", "Coupon code NOT found.");
    return FAILURE;
}

//Function:     logout_dump
//Description:  dumps the RIDE history of respective user,from main memory to secondary memory
//Input para:   NULL
//Return Type:  void
//              Success status on successful operation
void logout_dump(){
    //Buffer to holf the user filename 
    char buf[40];
    sprintf(buf,"ride_history_user%d.txt",CURR_USER.user_id);
    FILE *fp;
    //Open file for writing
    fp = fopen(buf,"w+");
    RIDE_HISTORY *curr=RIDES;
    //Transfer of data from main memory to secondary memory
    while(curr!=NULL){
        fprintf(fp,"%s %s %s %s %s %0.2f\n",curr->pickup,curr->destination,curr->driver_name,curr->vehicle_type,curr->vehicle_name,curr->fare);
        curr=curr->next;
    }
    fclose(fp);

    //De-allocation of List
    RIDE_HISTORY *curr1=RIDES;
    while(curr1!=NULL){
        free(curr1);
        curr1=curr1->next;
    }
    RIDES = NULL;
    
    write_log("logout_dump", "SUCCESS", "Data Successfully placed in secondary memory(Rides_history).");
}


//Function:     dump
//Description:  dumps the counts and data of respective file,from main memory to secondary memory
//Input para:   NULL
//Return Type:  integer
//              Success status on successful operation
//              otherwise respective error status code
int dump()
{

    // File pointer
    FILE *fp;
    FILE *tfp;

    // Open the file in write mode and dump the latest data
    fp = fopen("users_count.txt","w+");
    if(fp == NULL) {
        write_log("dump", "FILE_OPEN_ERROR", "Unable to open the users_count file");
        tfp = fopen("tempfile.txt", "a+");
        fprintf(tfp, "%s","\nFollowing contents to be added in said file");
        fprintf(tfp, "%s", "users_count.txt\n");
        fprintf(tfp,"%d", users_count);
        fclose(tfp);
        return FAILURE;
    }
    fprintf(fp,"%d", users_count);
    write_log("dump", "SUCCESS", "users count dumped successfully");
    fclose(fp);

    // Open the file in write mode and dump the latest data
    fp = fopen("drivers_count.txt","w+");
    if(fp == NULL) {
        write_log("dump", "FILE_OPEN_ERROR", "Unable to open the drivers_count file");
        tfp = fopen("tempfile.txt", "a+");
        fprintf(tfp, "%s","\nFollowing contents to be added in said file");
        fprintf(tfp, "%s", "drivers_count.txt\n");
        fprintf(tfp,"%d", drivers_count);
        fclose(tfp);
        return FAILURE;
    }
    fprintf(fp,"%d", drivers_count);
    write_log("dump", "SUCCESS", "Drivers count dumped successfully");
    fclose(fp);

    fp = fopen("users.txt","w+");
    if(fp == NULL) {
        write_log("dump", "FILE_OPEN_ERROR", "Unable to open the users file");
        tfp = fopen("tempfile.txt", "a+");
        fprintf(tfp, "%s","\nFollowing contents to be added in said file");
        fprintf(tfp, "%s", "users.txt\n");
        fclose(tfp);
        return FAILURE;
    }
    USER_PROFILE *curr=USER;
    while(curr!=NULL){
        fprintf(fp,"%d\t%s\t%s\t%s\t%s\n",curr->user_id,curr->mobile_number,curr->name,curr->email,curr->password);
        curr=curr->next;
    }
    write_log("dump", "SUCCESS", "Users dumped successfully");
    fclose(fp);

    //De-allocation of List
    USER_PROFILE *curr1=USER;
    while(curr1!=NULL){
        free(curr1);
        curr1=curr1->next;
    }

    //De-allocation of List
    DRIVERS_PROFILE *curr2=DRIVERS;
    while(curr2!=NULL){
        free(curr2);
        curr2=curr2->next;
    }

    //De-allocation of List
    CABS *curr3=CAB;
    while(curr3!=NULL){
        free(curr3);
        curr3=curr3->next;
    }

    //De-allocation of List
    COUPON_CODE *curr4=CODES;
    while(curr4!=NULL){
        free(curr4);
        curr4=curr4->next;
    }

    write_log("dump", "SUCCESS", "Data dumped successfully");

    // Close the log file
    close_log();
    return SUCCESS;
}