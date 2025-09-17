#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include<unistd.h>

#include "contact.h"
#include "file.h"
#include "populate.h"
int val_name(AddressBook *addressBook,char *name);
int val_number(AddressBook *addressBook,char *num);
int val_email(AddressBook *addressBook,char *email);
//Function to list the valid contacts with name,phonenum & mail id
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++)
        {
            int compare;
            switch(sortCriteria)
            {
                case 1:
                compare=strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                break;
                case 2:
                compare=strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                break;
                case 3:
                compare=strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                break;
                default:  
                printf("\n\t<-----Invaild Sort Criteria----->\n");
                return ;
            }
            if(compare>0)
            {
                Contact temp=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=addressBook->contacts[j];
                addressBook->contacts[j]=temp;
            }
        }
        
    }
   int i;
    printf("\nThere are %d contacts :\n", addressBook->contactCount);
    printf("| %-3s | %-15s | %-12s | %-20s |\n", "No", "NAME", "NUMBER", "EMAIL");
    printf("+-----+-----------------+--------------+----------------------+\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("| %-3d | %-15s | %-12s | %-20s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("+-----+-----------------+--------------+----------------------+\n");
    printf("\n");
}
    


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);// Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int comp(int search,AddressBook *addressBook,char str[]);
void createContact(AddressBook *addressBook)
{
    while(1)
    {
        char name[100];
        printf("enter a name:");
        scanf(" %[^\n]",name);
        if(val_name(addressBook,name))
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,name);
            break;
        }
    }
     while(1)
    {
        char number[100];
        printf("enter a number:");
        scanf(" %s",number);
        if(strlen(number)<10)
        {
            printf("Given input is lessthan 10 digit\n");
        }
        else
        {
            if(val_number(addressBook,number))
            {
                if(!(comp(2,addressBook,number)))
                {
                  strcpy(addressBook->contacts[addressBook->contactCount].phone,number);
                break;  
                }
                else{
                    printf("Number already exists!\n");
                }
            }
        }
    }
    while(1)
    {
        char email[100];
        printf("enter a email:");
        scanf(" %s",email);
        if(val_email(addressBook,email))
        {
            if(!(comp(3,addressBook,email)))
            {
                strcpy(addressBook->contacts[addressBook->contactCount].email,email);
            break;
         }
         else{
            printf("E-mail already exists!\n");
         }

            
        }
    }
    addressBook->contactCount++;
}

void search_name(AddressBook *addressBook);
void search_number(AddressBook *addressBook);
void search_email(AddressBook *addressBook);
void searchContact(AddressBook *addressBook) 
{

    int choice=0;
    printf("Select the below the options to Search:\n");
    printf("1.Name\n");
    printf("2.Number\n");
    printf("3.Mail-id\n");
    printf("4.Back to Main menu\n");
    while(1)
    {
        printf("\nEnter your Choice: ");
        scanf("%d",&choice);
        if(choice<1)
        {
            printf("\nPlease enter the valid choice");
            
        }
        switch(choice)
        {
            case 1:
            search_name(addressBook);
            return;
            case 2:
            search_number(addressBook);
            return;
            case 3:
            search_email(addressBook);
            return;
            case 4:
            return;
            default:
            printf("\nInvalid Input !!Please verify your input");
            return;
        }
    }

}
void search_name(AddressBook *addressBook)
{
    int i, found = 0;
    char new_name[20];

    while(1)
    {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", new_name); 
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, new_name) == 0)
            {
                printf("\nContact %d:\n", found + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                found++;
                break;
            }
        }
        if (found == 0)
        {
            printf("Contact not found, enter correct name\n");

        }
        else{
            break;
        }
        
    }
}
void search_number(AddressBook *addressBook)
{
    int i, found = 0;
    char number[20];

    int ret = 0;
    while (!ret)
    {
        printf("Enter the contact number: ");
        scanf(" %[^\n]", number);

        ret = val_number(addressBook, number);  // Assuming this validates phone number format

        if (strlen(number) == 1 && isdigit(number[0]))
            ret = 1;

        if (ret)
        {
            if (strlen(number) == 1) // Search for all numbers starting with this digit
            {
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (addressBook->contacts[i].phone[0] == number[0])
                    {
                        printf("\nContact %d:\n", found + 1);
                        printf("Name     : %s\n", addressBook->contacts[i].name);
                        printf("Contact  : %s\n", addressBook->contacts[i].phone);
                        printf("Email-ID : %s\n", addressBook->contacts[i].email);
                        found++;
                    }
                }
            }
            else
            {
                for (i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, number) == 0)
                    {
                        printf("\nContact %d:\n", found + 1);
                        printf("Name     : %s\n", addressBook->contacts[i].name);
                        printf("Contact  : %s\n", addressBook->contacts[i].phone);
                        printf("Email-ID : %s\n", addressBook->contacts[i].email);
                        found++;
                        break;
                    }
                }
            }
        }

        if (!ret)
            printf("Invalid number!\n");
    }

    if (found == 0)
    {
        printf("Contact not found\n");
    }
}

void search_email(AddressBook *addressBook)
{
    int i, found = 0;
    char mail[50];

    int ret = 0;
    while (!ret)
    {
        printf("Enter the Email-ID: ");
        scanf(" %[^\n]", mail);
        ret =val_email(addressBook, mail); 
        if (ret)
        {
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, mail) == 0)
                {
                printf("\nContact %d:\n", found + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                found++;
                break;
                }
            }
        }
        if (!ret)
            printf("Invalid Email-ID!\n");
    }
    if (found == 0)
    {
        printf("Contact not found\n");
    }
}
int search();
// compare function



void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    switch(search())
    {
        case 1:
          while(1)
            {
                char name[100];
                printf("Enter the name: ");
                scanf(" %[^\n]",name);
                if(val_name(addressBook,name))
                {
                    int res=comp(1,addressBook,name);
                    if(res) 
                    {
                        printf("Entered name is found\n");
                        while(1)
                        {
                            printf("enter a new name: ");
                            char str[100];
                            scanf(" %s",str);
                            if(val_name(addressBook,str))
                            {
                                strcpy(addressBook->contacts[res].name,str);
                                printf("Name is updated Successfully!!\n");
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        printf("Entered name is not found\n");
                    }
                }
                
            }
            break;
        case 2:
          while(1)
            {
                char phone[100];
                printf("Enter the phone: ");
                scanf(" %s",phone);
                if(val_number(addressBook,phone))
                {
                    int res=comp(2,addressBook,phone);
                    if(res) 
                    {
                        printf("Entered number is found\n");
                        while(1)
                        {
                            printf("enter a new number: ");
                            char str[100];
                            scanf(" %s",str);
                            if(val_number(addressBook,str))
                            {
                                strcpy(addressBook->contacts[res].phone,str);
                                printf("Number is Updated Successfully!!\n");
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        printf("Entered number is not found\n");
                    }
                }
                
            }
            break;
        case 3:
          while(1)
            {
                char email[100];
                printf("Enter the email: ");
                scanf(" %s",email);
                if(val_email(addressBook,email))
                {
                    int res=comp(3,addressBook,email);
                    if(res) 
                    {
                        printf("Entered email is found\n");
                        while(1)
                        {
                            printf("enter a new email: ");
                            char str[100];
                            scanf(" %s",str);
                            if(val_email(addressBook,str))
                            {
                                strcpy(addressBook->contacts[res].email,str);
                                printf("Email is  Updated Successfully!!\n");
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        printf("Entered email is  not found\n");
                    }
                }
                
            }
            break;
        default:
            printf("Search invalid!!.\n");
            return;
    }
}
void swap(int index,AddressBook *addressBook);
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
     printf("-------------------------------\n");
     while(1)
{
 switch(search())
 {
 case 1:
 while(1)
 {
 char name[100];
 printf(" Enter Name: "); 
 scanf(" %[^\n]",name);
 if(val_name(addressBook,name))
 {
 int res=comp(1,addressBook,name);
 if(res) 
 {
 printf("\n Are you sure you want to delete this contact?\n");
 printf("\t1 Confirm\n"); 
 printf("\t2 Cancel\n"); 
 printf("Enter your choice: ");
 int num;
 scanf("%d",&num);
 printf("\n");
 if(num==2)
 {
 break;
 }
 swap(res,addressBook);
 printf("\n\t<----- Contact successfully deleted ----->\n");
 break;
 }
 else
 {
 printf("\n\t<----- Name is not found in address book----->\n");
 }
 }
 
 }
 break;
 case 2:
 while(1)
 {
 char phone[100];
 printf(" Enter Phone: "); 
 scanf(" %s",phone);
 if(val_number(addressBook,phone))
 {
 int res=comp(2,addressBook,phone);
 if(res) 
 {
 printf("\n Are you sure you want to delete this contact?\n");
 printf("\t1 Confirm\n"); 
 printf("\t2 Cancel\n"); 
 printf("Enter your choice: ");
 int num;
 scanf("%d",&num);
 printf("\n");
 if(num==2)
 {
 break;
 }
 swap(res,addressBook);
 printf("\n\t<----- Contact successfully deleted----->\n");
 break;
 }
 else
 {
 printf("\n\t<----- Number is not found in addressbook----->\n");
 }
 }
 
 }
 break;
 case 3:
 while(1)
 {
 char email[100];
 printf(" Enter Email: "); 
 scanf(" %s",email);
 if(val_email(addressBook,email))
 {
 int res=comp(3,addressBook,email);
 if(res) 
 {
 printf("\n Are you sure you want to delete this contact?\n");
 printf("\t1 Confirm\n"); 
 printf("\t2 Cancel\n"); 
 printf("Enter your choice: ");
 int num;
 scanf("%d",&num);
 printf("\n");
 if(num==2)
 {
 break;
 }
 swap(res,addressBook);
 printf("\n\t<----- Contact successfully deleted----->\n");
 break;
 }
 else
 {
 printf("\n\t<----- Email is not found in address book----->\n");
 }
 }
 
 }
 break;
 default:
 printf("\n\t<----- Invalid search criteria ----->\n"); 
 return ;
 }
 printf("\n Delete another contact?\n\t 1 Yes\n\t 2 No\nEnter choice: "); 
 int num;
 scanf("%d",&num);
 printf("\n");
 if(num==2)
 {
 printf("\n\t<----- Returning to main menu ----->\n"); 
 break;
 }
}
}
   
