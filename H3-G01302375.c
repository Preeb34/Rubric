/*

 NAME: Preeti Bhattacharya
 G ID: G01302375

*/


#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>

//declaring structure type for four components, alias, leftChild and rightChild
struct address_t {
    int first_component;
    int second_component;
    int third_component;
    int fourth_component;
    char alias[10];
    struct address_t *leftChild, *rightChild;
};

//Declaring the functions
void add_address();//For Option 1 "Add address"
bool duplicate_check(char *ip, char *name, struct address_t *main_node); //For checking duplicated aliases
bool duplicate_check_IP(int a[4], struct address_t *main_node); //For checking duplicated address
struct address_t *insert(struct address_t *main_node, char *IP, char *alias); //This function is used to add address
struct address_t *validate_address(char *IP, char *alias); // To check the range of the IP
bool address_searcher(char *alias, struct address_t *main_node); //This function is used to look up for an address if alias name is given
struct address_t *delete_address(struct address_t *main_node, char *alias); //For Option 4 "Delete Address"
struct address_t *minValueNode(struct address_t *node); //This function is used to return the node with the minimum key value found in the tree
bool alias_location(int loc1, int loc2, struct address_t *root); //This function is used to give alias name for given two address components
void display_tree(struct address_t *main_node); //This function is used to display the list
void save(); //This function is used to prompt the user to save the file or not and error-checking
void save_file(FILE *fq, struct address_t *main_node); //This function is used to save the contents in file
int flushes(); //flushes out the new-line character

//Declaring global variables
struct address_t *root = NULL;
struct address_t *rootTmp = NULL;

bool temp = false;

//flushes out the new-line character
int flushes() {
    while (getchar() != '\n');
    return 1;
}


//This function is used to look up for an address if alias name is given 
bool address_searcher(char *alias, struct address_t *main_node) {

    int flag = 0;
    if (main_node == NULL) {
        return NULL;
    }

    address_searcher(alias, main_node->leftChild);

    if (strlen(alias) == strlen(main_node->alias)) {
        flag = 0;
        int i;
        for (i = 0; i < strlen(alias); i++) {
            if (alias[i] == main_node->alias[i]) {
                flag++;
            }
        }
    }

    if (flag == strlen(alias)) {

        printf("\nFound address for alias %s :- %d.%d.%d.%d ", main_node->alias, main_node->first_component,
               main_node->second_component, main_node->third_component, main_node->fourth_component);
        temp = true;
        return true;
    }

    address_searcher(alias, main_node->rightChild);

    return false;

}



//This function is used to return the node with the minimum key value found in the tree
struct address_t *minValueNode(struct address_t *node) {
    struct address_t *present = node;

    while (present && present->leftChild != NULL) {
        present = present->leftChild;
    }
    return present;
}

//This function is used to delete node
struct address_t *delete_address(struct address_t *main_node, char *alias) {

    //base case
    if (main_node == NULL) return main_node;

    if (strcmp(alias, main_node->alias) < 0) {
        main_node->leftChild = delete_address(main_node->leftChild, alias);
    } else if (strcmp(alias, main_node->alias) > 0) {
        main_node->rightChild = delete_address(main_node->rightChild, alias);
    } else {

        if (main_node->leftChild == NULL) {     //node with one child or no child
            struct address_t *temp = main_node->rightChild;
            free(main_node);
            return temp;
        } else if (main_node->rightChild == NULL) {
            struct address_t *temp = main_node->leftChild;
            free(main_node);
            return temp;
        }

        struct address_t *temp = minValueNode(
                main_node->rightChild); //node with two children, getting inorder successor

        strcpy(main_node->alias, temp->alias);
        main_node->first_component = temp->first_component;
        main_node->second_component = temp->second_component;
        main_node->third_component = temp->third_component;
        main_node->fourth_component = temp->fourth_component;

        main_node->rightChild = delete_address(main_node->rightChild, temp->alias);

    }
    return main_node;
}

//This function is used to display the list
void display_tree(struct address_t *main_node) {

    if (main_node == NULL) {
        return;
    }

    display_tree(main_node->leftChild);
    printf("\n%s  %d.%d.%d.%d", main_node->alias, main_node->first_component, main_node->second_component,
           main_node->third_component, main_node->fourth_component);
    display_tree(main_node->rightChild);
}

//This function is used to prompt the user to save the file or not and error-checking
void save() {
    char filename[100] = "";
    char c[5];
    printf("\nDo you want to save the file : Y/N \n");
    scanf(" %s", c);
    getchar();
    if(strcmp(c,"Y")==0 || strcmp(c,"y") == 0){
        printf("Enter the name of the file \n");
        fgets(filename, 200, stdin);

        while (strlen(filename) == 1) {
            printf("\nError! Empty input not allowed, please re-enter \n");
            fgets(filename, 200, stdin);
        }

        strcpy(filename, strtok(filename, "\n"));
        strcat(filename, ".txt");

        FILE *fq;
        fq = fopen(filename, "w+");
        save_file(fq, root);
        printf("\nFile saved with BST succesfully! \n");
        fclose(fq);

    }
}

//This function is used to save the contents in file
void save_file(FILE *fq, struct address_t *main_node) {
    if (main_node != NULL) {
        save_file(fq, main_node->leftChild);
        fprintf(fq, "%d.%d.%d.%d %s \n", main_node->first_component, main_node->second_component,
                main_node->third_component, main_node->fourth_component, main_node->alias);
        save_file(fq, main_node->rightChild);
    }
}

//This function is used to give alias name for given two address components
bool alias_location(int loc1, int loc2, struct address_t *root) {

    if (root == NULL) {
        return NULL;
    }

    alias_location(loc1, loc2, root->leftChild);

    if (root->first_component == loc1 && root->second_component == loc2) {
        temp = true;
        printf("\n%s", root->alias);
    }

    alias_location(loc1, loc2, root->rightChild);
    return false;

}

//This function is used to check the IP address range
struct address_t *validate_address(char *IP, char *alias) {

    struct address_t *ptr = (struct address_t *) malloc(sizeof(struct address_t));
    int octets[4];
    char *p;
    strcpy(ptr->alias, alias);
    p = strtok(IP, ".");
    int i = 0;

    while (p != NULL) {
        octets[i] = atoi(p);
        i++;
        p = strtok(NULL, ".");
    }

    ptr->first_component = octets[0];
    ptr->second_component = octets[1];
    ptr->third_component = octets[2];
    ptr->fourth_component = octets[3];


    if ((0 <= ptr->first_component && ptr->first_component <= 255) &&
        (0 <= ptr->second_component && ptr->second_component <= 255) &&
        (0 <= ptr->third_component && ptr->third_component <= 255) &&
        (0 <= ptr->fourth_component && ptr->fourth_component <= 255) &&
        (strlen(alias) <= 10)) {      //Checking for the VALID IP ADRESS
        return ptr;

    } else {
        printf("\nError! There is a problem with your IP or alias! Please choose again \n");
        fflush(stdin);

    }

}

//This function is used to update address for the given alias
void update_address(char *new_name, char *new_address, struct address_t *main_node) {

    int flip = 0;
    if (main_node == NULL) {
        return;
    }

    update_address(new_name, new_address, main_node->leftChild);

    if (strcmp(new_name, main_node->alias) == 0) {
        int a[4];
        char *p;
        int flag2 = 0;
        p = strtok(new_address, ".");
        int i = 0;
        while (p != NULL) {
            a[i] = atoi(p);
            if (a[i] < 0 || a[i] > 255) {
                flag2 = 1;
            }
            i++;
            p = strtok(NULL, ".");
        }

        if (flag2 == 1) {
            printf("\nError! There is a problem with your IP! Please choose again \n");
            return;
        }
        
        temp=false;
         bool check_d = duplicate_check_IP(a, rootTmp);

        if (!temp) {
            
                main_node->first_component = a[0];
                main_node->second_component = a[1];
                main_node->third_component = a[2];
                main_node->fourth_component = a[3];
            
            printf("IP of %s is successfully updated to %d.%d.%d.%d \n", main_node->alias, main_node->first_component,
               main_node->second_component, main_node->third_component, main_node->fourth_component);
        }

       

        
        temp = true;
    }

    update_address(new_name, new_address, main_node->rightChild);
    return;
}
//This function is used to check duplicate alias
bool duplicate_check_IP(int a[4] , struct address_t *main_node) {
    
    
    
    if (main_node != NULL)
    {
    duplicate_check_IP(a, main_node->leftChild);
    if(main_node->first_component ==a[0] && main_node->second_component ==a[1] && main_node->third_component ==a[2] && main_node->fourth_component ==a[3])
        {
        printf("%d.%d.%d.%d already	exists\n",a[0],a[1],a[2],a[3]);
        temp = true;
        return false;
                
    }
    duplicate_check_IP(a, main_node->rightChild);
    }



}

//This function is used to check duplicate alias
bool duplicate_check(char *ip, char *name, struct address_t *main_node) {

    struct address_t *node1 = (struct address_t *) malloc(sizeof(struct address_t));
    int a[4];
    char *p;
    strcpy(node1->alias, name);

    p = strtok(ip, ".");
    int i = 0;
    while (p != NULL) {
        a[i] = atoi(p);
        i++;
        p = strtok(NULL, ".");
    }

    node1->first_component = a[0];
    node1->second_component = a[1];
    node1->third_component = a[2];
    node1->fourth_component = a[3];

    int flag = 0;

    if (main_node == NULL) {
        return NULL;
    }

    duplicate_check(ip, name, main_node->leftChild);
    if( main_node->first_component ==a[0] && main_node->second_component ==a[1] && main_node->third_component ==a[2] && main_node->fourth_component ==a[3])
        {
            printf("%d.%d.%d.%d already	exists\n",a[0],a[1],a[2],a[3]);
            temp = true;
            return false;
        }

    if (strlen(node1->alias) == strlen(main_node->alias)) {
        flag = 0;
        int i = 0;
        for (i = 0; i <
                    strlen(node1->alias); i++) { //Comparing the character by character values of each of the alias and incrementing the flag value if characters match
            if (node1->alias[i] == main_node->alias[i]) {
                flag++;
            }
        }
    }

    if (flag ==
        strlen(node1->alias)) {           //If flag value equals the strlen(ptr->alias), then it means that we have got a match for alias in the LinkedList
        printf("\nError! The alias %s already exists in the BST", node1->alias);
        temp = true;
        return false;
    }

    duplicate_check(ip, name, main_node->rightChild);

    return true;
}

//This function is used to add address
struct address_t *insert(struct address_t *main_node, char *IP, char *alias) {

    if (main_node == NULL) {
        return validate_address(IP, alias);
    } else {
        if (strcmp(main_node->alias, alias) > 0) {
            main_node->leftChild = insert(main_node->leftChild, IP, alias);
        } else {
            main_node->rightChild = insert(main_node->rightChild, IP, alias);
        }

    }

    return main_node;

}

//This function is used to prompt user for IP address and alias for insertion and error checking
void add_address() {

    char a[100] = "";
    char e[100] = "";
    char b[100] = "";
    char c[100] = "";

    printf("\nEnter the IPV4 address: ");
    int flag = 0;
    fgets(a, 200, stdin);

    while (strlen(a) == 1) {          //Checks for empty-input
        printf("\n Empty input is not allowed! Please re-enter \n");
        fgets(a, 200, stdin);
    }

    strcpy(a, strtok(a, "\n"));

    printf("\nEnter the alias: ");
    fgets(e, 200, stdin);

    while (strlen(e) == 1) {          //Checks for empty-input
        printf("\n Empty input is not allowed! Please re-enter \n");
        fgets(e, 200, stdin);
    }

    strcpy(e, strtok(e, "\n"));

    if (strcmp(a, "...") == 0) {
        printf("\nError! There is a problem with your input! Please choose again! \n");
        flag = 1;
    }

    if (strlen(a) == 0) {
        printf("\nWrong Input! Choose Again \n");
        flag = 1;
    } else if (strlen(e) == 0) {
        printf("\nWrong Input! Choose Again \n");
        flag = 1;
    }

    char dotter[100] = "";

    int dot_count = 0;
    strcpy(dotter, a);
    int v;
    for (v = 0; v < strlen(dotter); v++) {
        if (dotter[v] == '.') {
            dot_count++;
        }
    }


    if (dot_count != 3 && flag == 0) {
        printf("\nWrong Input! Choose again!");
        flag = 1;
    }

    if (flag == 0) {
        strcpy(b, a);
        strcpy(c, e);

        bool check_d = duplicate_check(a, e, root);

        if (!temp) {
            
                root = insert(root, b, c);
            
            
        }
    }

    temp = false;
    fflush(stdin);

}

int main() {

    int choice = 0;

    //Reading contents of data file CS531_Inet.txt
    FILE *fp = fopen("CS531_Inet.txt", "r");
    char chunk[120];
    if (fp == NULL) {
        perror("Unable to open file! \n");
        exit(1);
    }

    char IP[100];
    char alias[100];
    char a[100] = "";
    char new_address[100] = "";

    bool isEmpty = true;

    //Creation of root node
    while (fscanf(fp, " %s %s", IP, alias) == 2) {
        if (isEmpty) {
            root = insert(root, IP, alias);
            isEmpty = false;
        } else {
            root = insert(root, IP, alias);
            if (feof(fp)) {
                break;
            }
        }
    }

    fclose(fp);

    rootTmp = root;
    //Creating the menu options and their functionality
    while (choice !=8) {
        printf(" \n\n 1 - Add address \n");
        printf(" 2 - Look up address \n");
        printf(" 3 - Update address \n");
        printf(" 4 - Delete address \n");
        printf(" 5 - Display list \n");
        printf(" 6 - Display aliases for location \n");
        printf(" 7 - Save to file \n");
        printf(" 8 - Quit \n \n");
        printf("********************************* \n");

        do {
            printf("\nEnter menu option (Numeric) :");
        } while (((scanf("%d", &choice) != 1)) && flushes());

        getchar();
        int location1, location2;

        switch (choice) {

            case 1:
                add_address();
                continue;

            case 2:
                printf("\nEnter the alias:\n");
                scanf("%s", a);

                while (strlen(a) == 1) {
                    printf("\nEmpty input! Please re-enter");
                    scanf("%s", a);
                }

                address_searcher(a, root);

                if (!temp) {
                    printf("\nNo address for given alias! \n");
                }
                temp = false;
                continue;

            case 3:
                printf("\nEnter the alias for which you want to update the address: \n");
                scanf("%s", a);

                while (strlen(a) == 1) {
                    printf("\nEmpty input! Please re-enter \n");
                    fgets(a, 200, stdin);
                }

                strcpy(a, strtok(a, "\n"));
                char c[5];

                address_searcher(a, root);

                if (temp) {

                    printf("\n Do you want to update the address for this alias? Y/N? \n");
                    scanf(" %s", c);
                    getchar();
                    if(strcmp(c,"Y")==0 || strcmp(c,"y") == 0){
                        int s = 0;
                        printf("\nEnter the new address \n");

                        fgets(new_address, 200, stdin);

                        while (strlen(new_address) == 1) {
                            printf("\nEmpty input! Please re-enter \n");
                            fgets(new_address, 200, stdin);
                        }

                        strcpy(new_address, strtok(new_address, "\n"));

                        char dot_counter[100] = "";
                        int iterator = 0, v = 0;
                        strcpy(dot_counter, new_address);
                        for (v = 0; v < strlen(dot_counter); v++) {
                            if (dot_counter[v] == '.') {
                                iterator++;
                            }
                        }

                        if (iterator != 3) {
                            printf("\nError! There is a problem with your input! Please choose again! \n");
                            s = 1;
                        }

                        if (s == 0) {
                            update_address(a, new_address, root);
                        }

                    }
                } else {
                    printf("\n Oops! Given alias is not found \n");
                }
                temp = false;
                continue;

            case 4:
                printf("\nEnter the alias  :");
                scanf("%s", a);
                strcpy(a, strtok(a, "\n"));
                bool q = address_searcher(a, root);

                if (!temp) {
                    printf("\nError! Relevant address not found! \n");
                } else {
                    printf("\nDo you want to delete the address for this alias?Y/N ");
                    scanf(" %s", c);
                    getchar();
                    if(strcmp(c,"Y")==0 || strcmp(c,"y") == 0){
                        delete_address(root, a);
                        printf("\n%s is Deleted from the BST \n", a);
                    }
                }

                temp = false;
                fflush(stdin);
                continue;

            case 5:
                display_tree(root);
                continue;

            case 6:
            
                 printf("Enter location value #1 (0-255): ");
                    scanf("%d",&location1);
                    
                    while(location1>255 || location1<0){
                        
                            printf("Illegal Entry : \n");
                            printf("Enter location value #1 (0-255): ");
                            scanf("%d",&location1);
                        
                    }
                    
                    printf("Enter location value #2 (0-255): ");
                    scanf("%d",&location2);
                    
                    while(location2>255 || location2<0 ){
                        
                            printf("Illegal Entry : \n");
                            printf("Enter location value #2 (0-255): ");
                            scanf("%d",&location2);
                       
                        
                    }
                
                temp = false;
                 bool xx = alias_location(location1, location2, root);

                    if (!temp) {
                        printf("\nNo alias is present for the entered value\n");
                    }
                continue;

            case 7:
                save();
                continue;

            case 8:
                printf("Goodbye!\n");
                exit(-1);
                continue; 

            default:
                printf("\nPlease enter a valid choice!");

        }

    }
    return 0;

}






