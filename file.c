#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
     FILE *fp=fopen("contacts.txt","w+");
    if(fp==NULL)
    {
        fprintf(stderr,"Cannot open the file\n");
        return;
    }
    //writing all contacts by one by one 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,  
                addressBook->contacts[i].phone,  
                addressBook->contacts[i].email); 
    }
    //CLOSING THE FILE
    fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    
}
