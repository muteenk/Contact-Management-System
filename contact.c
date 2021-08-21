#include <stdio.h>
#include <stdlib.h>
#include <string.h>






/////////////////////////
// Contact Structures
/////////////////////////

typedef struct contact{
    char name[50];
    char phone[20];
} Contact;








////////////////////////
// Function Prototypes
////////////////////////




// Contact Managing Functions
/////////////////////////////

// To add a contact detail
void addContact();

// To remove a contact detail
void deleteContact();

// To display all contact details
void displayContact();

// To Update a Contact Detail
void editContact();

// To search a contact detail
void searchContact();











//////////////////////
// Main Function
//////////////////////


int main(){

    char choice;

    while (1)
    {

        system("clear");
        
        printf("\n\n########################################\n\n");
        printf("         Contact Management System              ");
        printf("\n\n########################################\n\n");


        printf("\n\n[#] What would you like to do : \n\n\t[1] Display Contacts\n\t[2] Add Contact(s)\n\t[3] Delete Contact(s)\n\t[4] Edit Contact(s)\n\t[5] Search Contact(s)\n\t[0] Exit\n\n");
        printf("[*] Enter Your Choice (0/1/2/3/4/5) : ");
        scanf("%c", &choice);
        getchar();

        switch (choice)
        {
        case '0':
            system("clear");
            printf("\n\n############################\n\n");
            printf("Thank You For Being A User !");
            printf("\n\n############################\n\n");
            return 0;

        case '1':
            displayContact();
            break;

        case '2':
            addContact();
            break;

        case '3':
            deleteContact();
            break;

        case '4':
            editContact();
            break;

        case '5':
            searchContact();
            break;
        
        default:
            break;
        }
        

    }
    


    return 0;
}


















/////////////////////////////
// CRUD Function Definitions
/////////////////////////////



//  To display all contacts
////////////////////////////

void displayContact(){

    system("clear");

    // Temporary Contact Information
    Contact temp;

    // No of Contacts Found
    int noOfEntries = 0;

    FILE *contacts = fopen("contact.dat", "rb");

    if (contacts != NULL){

        while (fread(&temp, sizeof(Contact), 1, contacts)){

            // Displaying Contacts
            printf("\n#########################################\n\n");
            printf("\t[#] Name : %s\n\t[#] Phone no. : %s\n", temp.name, temp.phone);

            // Empty temp Contact
            strcpy(temp.name, "");
            strcpy(temp.phone, "");

            // Increment No of Contacts Found
            noOfEntries++;
        }

        if (noOfEntries <= 0){

            printf("\n############################\n\n");
            printf("THERE ARE NO ENTRIES !");
            printf("\n\n############################\n");
            
        }
        else{
            printf("\n#########################################\n\n");
        }

        fclose(contacts);

        printf("\n\t[#] Press 'Enter' to Continue > ");
        getchar();
    }
    else{
        printf("\n############################\n\n");
        printf("THERE ARE NO ENTRIES !");
        printf("\n\n############################\n");
    }
}






// Add Contacts
/////////////////

void addContact(){

    // Temporary Contact Information
    Contact temp;

    FILE *contacts = fopen("contact.dat", "ab+");

    // To keep track of wether to add another entry
    char another = 'y';
    while (another == 'y'){

        // clear the screen
        system("clear");

        fflush(stdin);

        // Input Name of Contact
        printf("\n\n\t[*] Enter Name of Contact : ");
        scanf("%[^\n]*c", temp.name);
        getchar();

        // Input Phone Number of Contact
        fflush(stdin);
        printf("\n\t[*] Enter Phone Number for '%s' : ", temp.name);
        scanf("%[^\n]*c", temp.phone);
        getchar();

        // writing to contact.dat file
        fwrite(&temp, sizeof(Contact), 1, contacts);

        printf("\n\n######################################\n\n");
        printf("NEW CONTACT ENTRY ADDED SUCCESSFULLY !");
        printf("\n\n######################################\n\n");

        // To make sure if to enter another entry
        printf("\n\n\t[#] Would you like to add another contact (y/n) : ");
        another = getchar();
        getchar();

        // Empty the temp Contact
        strcpy(temp.name, "");
        strcpy(temp.phone, "");

    }

    fclose(contacts);

} 






// Delete Contact
////////////////////

void deleteContact(){

    // Temporary Contact Details
    Contact temp;

    // Temporary Contact Information
    char tempName[50];

    // No of Entries
    int noOfEntries = 0;

    // Main Contact File
    FILE *contacts, *tempFile;

    // To check wether to delete another entry or not
    char another = 'y';
    while (another == 'y'){

        // Main Contact File
        contacts = fopen("contact.dat", "rb");

        if (contacts != NULL){

            // Temporary File
            FILE *tempFile = fopen("temp.dat", "wb");

            system("clear");

            printf("\n\n\t[*] Enter the Name or Phone Number of Contact to be Deleted : ");
            scanf("%[^\n]*c", tempName);
            getchar();

            // Transfering all the data from contact.dat file to temp.dat file except the one to delete
            while (fread(&temp, sizeof(Contact), 1, contacts))
            {
                
                // Checking if given name or number matches any of the data from contact.dat
                if (strcmp(tempName, temp.name) != 0 && strcmp(tempName, temp.phone) != 0){
                    fwrite(&temp, sizeof(Contact), 1, tempFile);
                }

                // Empty temp Info
                strcpy(temp.name, "");
                strcpy(temp.phone, "");

                // Increment No of Contacts
                noOfEntries++;
            }

            // Empty the tempName
            strcpy(tempName, "");

            // Closing Files
            fclose(contacts);
            fclose(tempFile);

            // Checking if no entries were found
            if (noOfEntries <= 0){

                printf("\n############################\n\n");
                printf("THERE ARE NO ENTRIES !");
                printf("\n\n############################\n");

                remove("temp.dat");
                
            }
            else{

                // Deleting the original contact.dat file and renaming temp.dat to contact.dat
                remove("contact.dat");
                rename("temp.dat", "contact.dat");
                
                printf("\n############################\n\n");
                printf("ENTRY DELETED SUCCESSFULLY !");
                printf("\n\n############################\n");
            }
        
            // Asking if to delete another entry
            printf("\n\n\t[#] Would you like to Delete Another Entry (y/n) : ");
            another = getchar();
            getchar();
        
        }
        else{
            printf("\n############################\n\n");
            printf("THERE ARE NO ENTRIES !");
            printf("\n\n############################\n");
        }

    }

}




// Edit Contact
/////////////////

void editContact(){

    // Temporary Contact Details and Details to be modified
    Contact temp, edit;

    // Whom to modify
    char userDetail[50];

    // No of Entries Found
    int noOfEntries = 0;

    // Main Contact File
    FILE *contacts, *tempFile;

    // To check wether to Edit another entry or not
    char another = 'y';
    while (another == 'y'){

        // Main Contact File
        contacts = fopen("contact.dat", "rb");

        if (contacts != NULL){

            // Given User Detail Found
            int isFound = 0;

            // Temporary File
            FILE *tempFile = fopen("temp.dat", "wb");

            system("clear");

            printf("\n\n\t[*] Enter the Name or Phone Number of Contact to be Modified (Edited) : ");
            scanf("%[^\n]*c", userDetail);
            getchar();

            // Transfering all the data from contact.dat file to temp.dat file while Editing the one Entered
            while (fread(&temp, sizeof(Contact), 1, contacts))
            {
                
                // Checking if given name or number matches any of the data from contact.dat
                if (strcmp(userDetail, temp.name) != 0 && strcmp(userDetail, temp.phone) != 0){
                    fwrite(&temp, sizeof(Contact), 1, tempFile);
                }
                else{

                    printf("\n\n\t[*] Enter New Name of Contact (%s) : ", temp.name);
                    scanf("%[^\n]*c", edit.name);
                    getchar();

                    printf("\n\t[*] Enter New Phone Number of Contact (%s) : ", temp.name);
                    scanf("%[^\n]*c", edit.phone);
                    getchar();

                    fwrite(&edit, sizeof(Contact), 1, tempFile);

                    isFound = 1;
                }

                // Empty temp and edit Info
                strcpy(temp.name, "");
                strcpy(temp.phone, "");
                strcpy(edit.name, "");
                strcpy(edit.phone, "");

                // Increment No of Contacts
                noOfEntries++;
            }

            // Empty the User Detail
            strcpy(userDetail, "");

            // Closing Files
            fclose(contacts);
            fclose(tempFile);

            // Checking if no entries were found
            if (noOfEntries <= 0){

                printf("\n############################\n\n");
                printf("THERE ARE NO ENTRIES !");
                printf("\n\n############################\n");

                remove("temp.dat");
                
            }
            else{

                if (isFound == 1){
                    // Deleting the original contact.dat file and renaming temp.dat to contact.dat
                    remove("contact.dat");
                    rename("temp.dat", "contact.dat");
                    
                    printf("\n################################\n\n");
                    printf("ENTRY MODIFIED SUCCESSFULLY !");
                    printf("\n\n################################\n");
                }
                else{
                    remove("temp.dat");

                    printf("\n######################################\n\n");
                    printf("CONTACT TO BE MODIFIED NOT FOUND !");
                    printf("\n\n######################################\n");

                }
            }
        
            // Asking if to edit another entry
            printf("\n\n\t[#] Would you like to Edit (Modified) Another Entry (y/n) : ");
            another = getchar();
            getchar();
        
        }
        else{
            printf("\n############################\n\n");
            printf("THERE ARE NO ENTRIES !");
            printf("\n\n############################\n");
        }

    }
}





// Search Contact
//////////////////

void searchContact(){


    // Temporary Contact Details
    Contact temp;

    // Temporary Contact Information
    char UserDetail[50];

    // Contact Found
    int isFound = 0;

    // Main Contact File
    FILE *contacts;

    // To check wether to search another entry or not
    char another = 'y';
    while (another == 'y'){

        // Main Contact File
        contacts = fopen("contact.dat", "rb");

        if (contacts != NULL){

            system("clear");

            printf("\n\n\t[*] Enter the Name or Phone Number of Contact you want to Search : ");
            scanf("%[^\n]*c", UserDetail);
            getchar();

            // Finding the User Detail
            while (fread(&temp, sizeof(Contact), 1, contacts))
            {
                
                // Checking if given name or number matches any of the data from contact.dat
                if (strcmp(UserDetail, temp.name) == 0 || strcmp(UserDetail, temp.phone) == 0){
                    
                    // Displaying Contacts
                    printf("\n#########################################\n\n");
                    printf("\t[#] Name : %s\n\t[#] Phone no. : %s\n", temp.name, temp.phone);
                    isFound = 1;

                }

                // Empty temp Info
                strcpy(temp.name, "");
                strcpy(temp.phone, "");

            }

            // Empty the tempName
            strcpy(UserDetail, "");

            // Closing Files
            fclose(contacts);

            // Checking if no contact was found
            if (isFound == 0){
                printf("\n############################\n\n");
                printf("CONTACT NOT FOUND !");
                printf("\n\n############################\n");
            }
            else{

                printf("\n#########################################\n\n");
                
                printf("\n############################\n\n");
                printf("ENTRY FOUND SUCCESSFULLY !");
                printf("\n\n############################\n");
            }
        
            // Asking if to search another entry
            printf("\n\n\t[#] Would you like to Search Another Entry (y/n) : ");
            another = getchar();
            getchar();
        
        }
        else{
            printf("\n############################\n\n");
            printf("THERE ARE NO ENTRIES !");
            printf("\n\n############################\n");
        }

    }

}