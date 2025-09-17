#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "file.h"
#include "populate.h"
#include "contact.h"
// check name:::
//Function to validate the name [Except alphabets any special characters(except space) present in the given input itb returns invalid input]
int val_name(AddressBook *addressBook,char *name)
{
    for (int i = 0; name[i]; i++) 
    {
        if ( ! ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
        {
            printf("Invalid input format ( Enter only the alphabet and space)\n");
            return 0;
        }
    }
    return 1;
}
//Function to validate the mobile number [except numbers if any alphabets or special characters present in the given input it prints as invalid input]
int val_number(AddressBook *addressBook,char *num)
{
    for(int i=0;num[i];i++)
    {
        if(!isdigit(num[i]))
        {
            printf("[\033[1;37m Invalid:please give correct format (only 0 to 9)\033[0m\n");
            return 0;
        }
    }
    return 1;
}

//check email:
//Function to check the valid mail if the given mail is without 1)'@',"com" 2)'@'& ".com" present more than one time it prints that the entered mail is invalid
int val_email(AddressBook *addressBook,char *email)
{
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    int atcount=0;
    int dotcount=0;
    int comcount=0;
    for(char *ptr=email;*ptr;ptr++)
    {
        if(*ptr=='@')atcount++;
        if(*ptr=='.')dotcount++;
        if(strncmp(ptr, ".com", 4) == 0)comcount++;
    }

    if (!(at && dot && at < dot  && strcmp(dot, ".com") == 0 && atcount==1 && dotcount==1 && comcount==1) )
    {
        printf("Invalid email. Please enter a valid email (example: abc@gmail.com / abc23@gmail.com)\n");
        return 0;
    } 
    return 1;
}
int comp(int search,AddressBook *addressBook,char str[])
{   
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        int compare;
        switch(search)
        {
            case 1:
             compare=strcmp(addressBook->contacts[i].name,str);
             break;
            case 2:
             compare=strcmp(addressBook->contacts[i].phone,str);
             break;
            case 3:
             compare=strcmp(addressBook->contacts[i].email,str);
             break;
        }
        if(compare==0)
        {
            printf("%s\t",addressBook->contacts[i].name);
            printf("%s\t",addressBook->contacts[i].phone);
            printf("%s\n",addressBook->contacts[i].email);
            index=i;
        }
    }
    return index;
}
//[Function to define the search creteria]
int search()
{

    printf("Select Search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("\033[1;31mEnter your choice: ");
     printf("\033[0m");
    int search;
    scanf("%d", &search);
    return search;
}
void swap(int index,AddressBook *addressBook)
{
 if(index== addressBook->contactCount-1)
 {
 Contact temp={"\0","\0","\0"};
 addressBook->contacts[index]=temp;
 }
 for(int i=index+1;i<addressBook->contactCount-1;i++)
 {
 Contact temp=addressBook->contacts[i];
 addressBook->contacts[i]=addressBook->contacts[i+1];
 addressBook->contacts[i+1]=temp;
 }
}
