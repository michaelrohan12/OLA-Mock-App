#include "ola.c"
#include "locals.h"

void welcome(){

   system("color 1E"); //Setting The Color Of Console
   putchar('\n');
   fflush(stdout);
   printf("\t******************************\n");
   printf("\t*          WELCOME           *\n");
   printf("\t*            To              *\n");
   printf("\t*           OLA              *\n");
   printf("\t*  Book a City Taxi to your  *\n");
   printf("\t*   destination in town      *\n");
   printf("\t******************************\n");
   printf("\n\n\n");
   printf("\tLOADING ");
   for(int i=0;i<7;i++){
      Sleep(200);//For Pause
      printf("<");
      Sleep(200);//For Pause
      printf(">");
   }

   Sleep(200);//For Pause
   printf("\n\n\tSUCCESSFUL\n");

   Sleep(2000);//For Pause
   system("CLS");//To Clear The Screen

}

void menu(){
      printf("\t************************\n");
      printf("\t*      OLA CABS        *\n");
      printf("\t************************\n\n");

      printf("\t************************\n");
      printf("\t*<1>  USER SIGNUP      *\n");
      printf("\t************************\n\n");

      printf("\t************************\n");
      printf("\t*<2>  USER LOGIN       *\n");
      printf("\t************************\n\n");

      printf("\t************************\n");
      printf("\t*<3>     EXIT          *\n");
      printf("\t************************\n\n");

}

void login_menu(){
   flag3=1;
   while(flag3){
      printf("\t*****************************\n");
      printf("\t*        OLA CABS           *\n");
      printf("\t*****************************\n\n");
      printf("\t*****************************\n");
      printf("\t*WELCOME,%s                *\n",CURR_USER.name);
      printf("\t*****************************\n\n");
      printf("1.Profile Details\n");
      printf("2.Ride History\n");
      printf("3.Book a ride\n");
      printf("4.Tour through all the locations\n");
      printf("5.Log Out\n");
      printf("Enter your choice:");
      scanf("%d",&choice4);
      printf("\n\n");
      switch(choice4){
         case 1:print_profile_details();
                system("CLS");
                break;
         case 2:status=print_ride_history();
               if(status!=1){
                  printf("NO ride history found\n\n");
               }
               system("CLS");
               break;
         case 3:print_locations();
                re_enter2:
                pickup = (char*)malloc(40*sizeof(char));
                printf("Enter the pickup location(Case-sensitive):");
                scanf("%s",pickup);
                pickup=location_validation(pickup);
                if(pickup==NULL){
                  goto re_enter2;
                }
                re_enter3:
                destination = (char*)malloc(40*sizeof(char));
                printf("\nEnter the destination location(Case-sensitive):");
                scanf("%s",destination);
                destination=location_validation(destination);
                if(destination==NULL){
                  goto re_enter3;
                }
                print_cabs();
                printf("\nEnter vehicle type:");
                scanf("%s",vehicle_type);
                load_driver_eta(pickup,vehicle_type);
                printf("Journey starts\n\n");
                Sleep(200);
                cost=ride_journey(pickup,destination);
                fare = search_fare(vehicle_type);
                cost = cost*fare;
                printf("\n The Total Cost is %0.2f\n",cost);
                re__enter:
                printf("Do you have coupon code?\n");
                printf("1.Yes\n2.No\n");
                printf("Enter your choice:");
                scanf("%d",&fare_choice);
                if(fare_choice==1){
                   print_coupons_code();
                   printf("Enter coupon code:");
                   scanf("%s",coupon_temp);
                   dis = search_coupon(coupon_temp);
                   cost = cost - dis;
                   amt_enter:
                   printf("Enter %0.2f amount:",cost);
                   scanf("%f",&amt);
                   if(amt==cost){
                      update_ride_history(pickup,destination,cost);
                      system("CLS");
                   }
                   else
                     goto amt_enter;
                }
                else if(fare_choice==2){
                   printf("Enter %0.2f amount:",cost);
                   scanf("%f",&amt);
                   if(amt==cost){
                      update_ride_history(pickup,destination,cost);
                      system("CLS");
                  }
                }
                else
                   goto re__enter;
                break;
         case 4:char* final_dest = malloc(40*sizeof(char));
                print_locations();
                re_enter:
                pickup = (char*)malloc(40*sizeof(char));
                printf("Enter the pickup location(Case-sensitive):");
                scanf("%s",pickup);
                pickup=location_validation(pickup);
                if(pickup==NULL){
                  goto re_enter;
                }
                print_cabs();
                printf("\nEnter vehicle type:");
                scanf("%s",vehicle_type);
                load_driver_eta(pickup,vehicle_type);
                final_dest=tour_journey(pickup);
                cost = tour_cost();
                fare = search_fare(vehicle_type);
                cost = cost*fare;
                printf("\n The Total Cost is %0.2f\n",cost);
                re__enter1:
                printf("Do you have coupon code?");
                printf("1.Yes\n2.No\n");
                printf("Enter your choice:");
                scanf("%d",&fare_choice);
                if(fare_choice==1){
                   print_coupons_code();
                   printf("Enter coupon code:");
                   scanf("%s",coupon_temp);
                   dis = search_coupon(coupon_temp);
                   cost = cost - dis;
                   amt_enter2:
                   printf("Enter %0.2f amount:",cost);
                   scanf("%f",&amt);
                   if(amt==cost){
                      update_ride_history(pickup,final_dest,cost);
                      system("CLS");
                   }
                   else
                     goto amt_enter2;
                }
                else if(fare_choice==2){
                   printf("Enter %0.2f amount:",cost);
                   scanf("%f",&amt);
                   if(amt==cost){
                      update_ride_history(pickup,final_dest,cost);
                      system("CLS");
                  }
                }
                else
                   goto re__enter1;
                break;
         case 5:logout_dump();
                flag3=0;
                break;
         default:system("CLS");
                 printf("Invalid choice!! Re-enter your choice\n\n");
                 
      }
   }
}

int user_login(){
   system("CLS");
   flag2=1;
   while(flag2){
      printf("\t************************\n");
      printf("\t*     USER LOGIN       *\n");
      printf("\t************************\n\n");
      printf("Login using\n");
      printf("1.Phone Number\n");
      printf("2.Email and password\n");
      printf("3.To go to main menu\n");
      printf("Enter your choice:");
      scanf("%d",&choice3);
      switch(choice3){
         case 1:mobile_no:
                printf("\n\nENTER\n\n");
                printf("Mobile Number:");
                scanf("%s",mobile_no);
                status = login_validation1(mobile_no);
                if(status != 1){
                   system("CLS");
                   printf("Please enter a valid 10-digit mobile number / Not signed up yet.\n");
                   printf("If not signed up yet,go to signup page.\n\n");
                   goto mobile_no;
                }
                else{
                   re_enter:
                   char* otp = malloc(4*sizeof(char));
                   otp = generateotp();
                   printf("(Mock)Enter otp sent to your mobile (Enter this %s):",otp);
                   scanf("%s",temp);
                   if(!strcmp(temp,otp)){
                      system("CLS");
                      printf("LOGIN SUCCESSFUL!!\n\n");
                      Sleep(1000);
                      system("CLS");
                      status=load_user1(mobile_no);
                      if(status!=1)
                         printf("Check memory allocation\n\n");
                      login_menu();
                      flag2=0;
                      system("CLS");
                   }
                   else{
                      printf("\nIncorrect OTP.\n\n\n");
                      free(otp);
                      goto re_enter;
                   }
                }
                break;
         case 2:email:
                printf("\n\nENTER\n\n");
                printf("Email ID:");
                scanf("%s",email_id);
                printf("Password:");
                scanf("%s",password);
                status=login_validation2(email_id,password);
                if(status!=1){
                   printf("Incorrect EmailID/Password. (OR) Not signed up yet.\n");
                   printf("If not signed up yet,go to signup page.\n\n");
                   goto email;
                }
                else{
                   login_menu();
                   flag2=0;
                   system("CLS");
                }
                break;
         case 3:flag2=0;
                system("CLS");
                break;
         default:system("CLS");
                 printf("Invalid choice.Please input again!!\n\n");
      }
   }
}

void user_signup(){
   system("CLS");
   flag2=1;
   while(flag2){
      printf("\t************************\n");
      printf("\t*     USER SIGNUP      *\n");
      printf("\t************************\n\n");
      printf("SELECT\n");
      printf("1.Enter your 10-digit mobile number\n");
      printf("2.To go to main menu.\n");
      printf("Enter your choice:");
      scanf("%d",&choice2);
      switch(choice2){
         case 1:printf("Mobile Number:");
                scanf("%s",mobile_no);
                status = signup_validation(mobile_no);
                if(status != 1){
                   system("CLS");
                   printf("Please enter a valid 10-digit mobile number or login if signed up already.\n\n");
                }
                else{
                   re_enter:
                   char* otp = malloc(4*sizeof(char));
                   otp = generateotp();
                   printf("(Mock)Enter otp sent to your mobile (Enter this %s):",otp);
                   scanf("%s",temp);
                   if(!strcmp(temp,otp)){
                      system("CLS");
                      printf("SIGNUP SUCCESSFUL.\n\n");
                      Sleep(500);
                      status=user_profile_details(mobile_no);
                      if(status!=1)
                         printf("Check memory allocation\n\n");
                   }
                   else{
                      printf("\nIncorrect OTP.\n\n\n");
                      free(otp);
                      goto re_enter;
                   }
                   printf("\n\nRedirecting to login page");
                   for(int i=0;i<4;i++){
                      printf(".");
                      Sleep(500);
                   }
                   signup=user_login();
                   
                   flag2=0;
                }
                break;
         case 2:flag2=0;
                system("CLS");
                break;
         default:system("CLS");
                 printf("Invalid choice.Please input again!!\n\n");
      }
   }
}


int main()
{
   srand(time(NULL));
   status = load();
   if(status != 1){
        printf("Load has Failed.Check log file and the other files.\n");
        return 0;
   }

   welcome();

   while(flag1)
   {
      menu();
      printf("Enter your choice:");
      scanf("%d",&choice1);
      switch(choice1){
         case 1:user_signup();
               Sleep(200);
               system("CLS");
                break;
         case 2:user_login();
               Sleep(200);
               system("CLS");
                break;
         case 3:printf("\nThank you for using ola cabs. Have a nice day\n\n\n");
                status = dump();
                if(status != 1)
                     printf("Exit Failed\n. Please see the files related to project\n");
                return 0;
         default:system("CLS");
                 printf("Invalid choice!! Re-enter\n\n");
      }
   }

   return 0;
}

