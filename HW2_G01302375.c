 /*

  Name : Preeti Bhattacharya
  G-Number : G01302375

  */
   
  
  #include <stdio.h>
  #include <stdlib.h>
  #include<ctype.h>
  #include<string.h>
  
  //Declaring all the user defined function.
  struct address_t *string_tokenize(char *, char *); 
  void add_address(char *, char *,struct address_t *); //For Option 1 "Add address"
  int lookup_address(); //For Option 2 "Looking up at address"
  int update_address(struct address_t *); //For Option 3 "Updating address"
  void delete_address(); //For Option 4 "Delete Address"
  void display(struct address_t * head); //For Option 5 "Display List"
  int alias_location(struct address_t *); //For Option6 "Display aliases for location"
  void save_to_file(struct address_t *); //For Option7 "Save to a new file"
  void insertAtEnd(char *, char *); //For adding IP at the end

  //creating structure type for four components and alias name
   struct address_t
    {
      int  first_component;
      int  second_component;
      int  third_component;
      int  fourth_component;
      char *name;
      struct address_t *next; 
     };
    struct address_t *head = NULL;
    struct address_t *temp = NULL;
    
  //creating the linked list
  void insertAtEnd(char *ip, char *alias)
  {
      struct address_t *new_node = (struct address_t*)malloc(sizeof(struct address_t));
      new_node=NULL;
      new_node = string_tokenize(ip,alias);
      if (head == NULL)
      {
        head = new_node;
        return;
      }
      else
      {
        temp = head;
        while(temp->next != NULL){
        temp = temp->next;
        }
        temp->next = new_node; 
      }   
}

  // This function is used to display IP address and alias name
  void display(struct address_t * head)
  {
      
    struct address_t *temp = malloc(sizeof(struct address_t));
    temp=NULL;
    temp=head;
    int count=0;
    while(temp != NULL)
    {
      printf("%d.%d.%d.%d %s \n",temp->first_component,temp->second_component,temp->third_component,temp->fourth_component,temp->name);
      temp = temp->next;
      count++;
    }
    if(count==0){
        printf("List is empty \n");
    }else{
        printf("Total node count: %d \n", count);
    }
 }

//tokenizing the strings
  struct address_t *string_tokenize(char *IP, char *alias)
  {
    int octets[4];
    char *p_tok;

    p_tok = strtok(IP, ".");

    int i =0;
    while(p_tok != NULL)
    {
      octets[i] = atoi(p_tok);
      i++;
      p_tok = strtok(NULL, ".");
    } 
     
  struct address_t *new_node = (struct address_t*)malloc(sizeof(struct address_t));
  
    new_node->name=malloc(sizeof(char*));
    new_node->first_component= octets[0];
    new_node->second_component= octets[1];
    new_node->third_component=  octets[2];
    new_node->fourth_component= octets[3];
    strcpy(new_node->name,alias);
    return new_node;
    }

//This function is used to add address
 void add_address(char *name, char *address,struct address_t *head)
  { 
    int flag = 0;
    char new_address_component[20];
    char new_address[20];
    char new_name[10];
    printf("\nEnter the alias: ");
    scanf("%s",new_name);
    struct address_t *temp = head;
    while(temp->next!=NULL)
   {
     if(strcasecmp(temp->name,new_name)==0)
     {
     printf("\n %s already exists \n",new_name);
     flag = 1;
     return;
     }
    temp = temp->next;
   }
    printf("\n Enter address for %s: ",new_name);
    scanf("%s",new_address);

    if(strlen(new_address)==0 && strlen(new_name)==0)
    {
    printf("\nError! Empty input not allowed");
    }
    else
    {
    int octets[4];
    char *p = strtok(new_address, ".");
    int i = 0;
    while (p != NULL) {
        octets[i] = atoi(p);
        i++;
        p = strtok(NULL, ".");
    }

    

    struct address_t *new_node = (struct address_t*)malloc(sizeof(struct address_t));

//checking the range of IP address
if((octets[0]>=0 && octets[0]<255)&& (octets[1]>=0 && octets[1]<255)&& (octets[2]>=0 && octets[2]<255)&& (octets[3]>=0 && octets[3]<255)){
     new_node->first_component= (long)malloc(sizeof(int));
     new_node->second_component=(long)malloc(sizeof(int));
     new_node->third_component= (long)malloc(sizeof(int));
     new_node->fourth_component= (long)malloc(sizeof(int));
     new_node->name=malloc(sizeof(char *));
   new_node->first_component = octets[0];
   new_node->second_component= octets[1];
   new_node->third_component = octets[2];
   new_node->fourth_component= octets[3];
   strcpy(new_node->name,new_name);

   struct address_t *temp = head;
   while(temp->next!=NULL)
   {
     if(octets[0] == temp->first_component && octets[1] == temp->second_component && octets[2] == temp->third_component && octets[3] == temp->fourth_component)
     {
     printf("\n Address already exists \n");
     flag = 1;
     break;
     }
    temp = temp->next;
   }
   if(flag != 1)
   temp->next = new_node;
}
else
{
  printf("\n Improper IP \n");
}
}
  }

// This function is used to look up for an address if alias name is given
  int lookup_address()
  {
      int flag = 0;
      char nam [20];
      printf("Enter alias: ");
      scanf("%s",nam);

      struct address_t *temp = head;
      while(temp!= NULL)
      {
        if(strcasecmp(temp->name,nam)==0)
        {
          
          printf("\nThe Address for %s :- %d.%d.%d.%d \n", temp->name, temp->first_component, temp -> second_component, temp -> third_component, temp -> fourth_component);
          flag = 1;
          return 0;
        }
      
        temp = temp->next; 

      }
      
     
              printf("\n %s does not exist \n", nam);
     return flag;      

  }

  // This function is used to update the address
  int update_address(struct address_t *head)
  {
    char address[20];
    char new_name[10];
    int octets[4];
    int flag = -1;
    int res = strcasecmp(temp->name,new_name);
    printf("Enter alias: ");
    scanf("%s",new_name);
    struct address_t *temp = head;
    while(temp!=NULL)
   {
     if(strcasecmp(temp->name,new_name)==0)
     {
     flag = 1;
     break;
     }
    temp = temp->next;
   }
   if(flag==-1){
       printf("%s doesn't exist \n", new_name);
       return 0;
   }
   else{
          printf("Update address for %s: %d.%d.%d.%d \n",new_name,temp->first_component, temp -> second_component, temp -> third_component, temp -> fourth_component);

   }
   int location1[4];
   
   for(int i=0; i<4; i++){
    printf("Enter location value #%d (0-255): ",i+1);
    scanf("%d",location1+i);
    
    while(location1[i]>255 || location1[i]<0){
        
            printf("Illegal Entry: \n");
            printf("Enter location value #%d (0-255): ",i+1);
            scanf("%d",location1+i);
        
    }
   }
    // printf("Update address for %s: %d.%d.%d.%d \n",new_name,temp->first_component, temp -> second_component, temp -> third_component, temp -> fourth_component);
    
    struct address_t *temp1 = head;
      
    while(temp1->next!=NULL)
   {
     if(location1[0] == temp1->first_component && location1[1] == temp1->second_component && location1[2] == temp1->third_component && location1[3] == temp1->fourth_component)
     {
     printf("\n Address already exists \n");
     flag = 1;
     return 0;
     }
    temp1 = temp1->next;
   }
   
   temp->first_component = location1[0];
   temp->second_component = location1[1];
   temp->third_component = location1[2];
   temp->fourth_component = location1[3];
   

    return flag;

  }

  //This function is used to delete the address
  void delete_address()
  {
    char name[10];
    char ch[5];
    int flag=-1;
    printf("Enter the alias: ");
    scanf("%s",name);
    struct address_t *temp = head;
    struct address_t *reaper =NULL;
    while(temp!=NULL)
    {
     if(strcasecmp(temp->name,name)==0)
     {
     flag=1;
     break;
     }
     reaper = temp;
     temp = temp->next;
     
    }
    if(flag==-1){
           printf("%s doesn't exist \n", name);
           return ;
    }
       
    printf("\n Delete %s: %d.%d.%d.%d ? (y/n):", name, temp->first_component, temp -> second_component, temp -> third_component, temp -> fourth_component);
    scanf("%s",ch);
    if(strcmp(ch,"Y")==0 || strcmp(ch,"y") == 0){
        if(temp==head){
            head= temp->next; 
        }else{
            reaper->next = temp->next;
        }
        
    }


  }

  //This function is used to display aliases at the given location
  int alias_location(struct address_t *head)
  {
    int location1=999;
    int location2=999;
    int flag = 0;
    
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
    

    struct address_t *temp = head;
    while(temp!=NULL)
    {
      if(temp->first_component ==location1  && temp->second_component == location2)

      {
        flag = 1;
        printf("%d.%d.%d.%d %s \n",temp->first_component,temp->second_component,temp->third_component,temp->fourth_component,temp->name);
      }
      temp = temp->next;
    }
   
      

  return flag;
  }


  //This function is used to save the contents in another file
  void save_to_file(struct address_t *head)
  {

    FILE *fp;
    char filename[10];
    printf("Enter a file name: ");
    scanf("%s", filename);
    fp = fopen(filename, "w"); 
    struct address_t *temp = head;
    while(temp!=NULL)
    {
     fprintf(fp,"%d.%d.%d.%d %s \n",temp->first_component,temp->second_component,temp->third_component,temp->fourth_component,temp->name);

     temp = temp->next; 
    }
    printf("File Saved! \n"); 
fclose(fp);
  }
 
  
  int main(void) {
    
      FILE *fp = fopen("CS531_Inet.txt", "r");    //test data file "CS531_Inet.txt" which contains IP address and alias names
      char chunk[120];
      if(fp == NULL) {
          perror("Unable to open file!");
          exit(1);
     }

      char *IP;
      char *alias;

     head = NULL;
    
     while(fgets(chunk,sizeof(chunk),fp)!=NULL)
     {
       IP=strtok(chunk," ");
       alias=strtok(NULL,"");
       char* back = alias + strlen(alias);
          while(isspace(*--back));
             *(back+1) = '\0';
       insertAtEnd(IP,alias);

     }
     
  fclose(fp);
  
    
    char nam[10];
    char address[16];
    int choice = 0;
    char *res_add;
    int res;
    int val;
    int val2;
    

   while(choice!=8)
   {
    printf("********************************* \n");
    printf(" 1 - Add address \n");
    printf(" 2 - Look up address\n");
    printf(" 3 - Update address \n");
    printf(" 4 - Delete address\n");
    printf(" 5 - Display list\n");
    printf(" 6 - Display aliases for location \n");
    printf(" 7 - Save to file \n");
    printf(" 8 - Quit \n \n");
    printf("********************************* \n");
    printf("Enter Option: ");
    scanf("%d",&choice); 

// Creating the menu options and their functionality
    switch(choice)
    {
      
      case 1: add_address(nam,address,head);
              continue;

      case 2: lookup_address();
              
              continue;

      case 3:  val = update_address(head);
              if(val == 1)
                printf("address updated successfully \n");
              continue;
      case 4: delete_address();
              continue;
      case 5: display(head);
              continue;
      case 6: val2 = alias_location(head);
              if(val2 != 1)
              {
                printf("\n Address does not exist within the list \n");
              }
              
              continue;
      case 7: save_to_file(head);
              continue;
      case 8: printf("Good Bye!");
                exit(-1);
              continue;        
      
      default:
      printf("Invalid option");
              continue;
    }
    int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
  }
  
    
 
    fclose(fp);
 }
