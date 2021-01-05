//PROGRAM TO MANAGE MY COLLECTION OF BOOKS //
//SONIA MUBASHER // 20129528//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
#define MAXSIZE 100


//STRUCTURES USED IN THIS PROGRAM
struct book{     //structure to store book information
    char *title;    //book title
    char *author;   //book author
    char *subject;  //subject
};//end book structure

struct library {   //structure to store library information
    //structure within structure
    struct book collection; //book collection
    int num_books;          //num_books
    struct library *next;   //pointer to next of type struct library
}*start; //end library structure

//FUNCTIONS USED IN THIS PROGRAM

void copybook(struct book* dest,struct book *source);        //function prototype to copy contents of one book to another book
void addbook(struct library *thislib);                       //function prototype to add books to my collection
void deletebook(struct library *thislib);                    //function prototype to delete book from my collection
void searchbook(struct library *thislib);                    //function prototype to search book from my collection
void author(struct library *thislib);                        //function prototype to display list of books by a particular author
void subject(struct library *thislib);                       //function prototype to display list of books by a particular subject


//GLOBAL POINTERS so that I can use in all the functions
FILE *inputfile;  //pointer to input of type file for reading the data
FILE *outputfile; //pointer to output of type file for writing the data

//MAIN FUNCTION STARTS//
int main ()
{

    unsigned int updates;                      //unsigned integer indicating number of updates
    int instruction;                           //instruction variable of type integer indicating instructions
    inputfile = (fopen("library.txt","r"));    //opening input file for reading the data
    outputfile = (fopen("output.txt","w"));    //opening output file for writing the data
    start  = NULL;                             //start pointer indicating the starting point of library initializing it to null
    start = malloc(sizeof(struct library));     //allocating memory space for the starting point of library
    start -> collection.title  = NULL;          //indicating at the start the library is empty
    start -> num_books =0;                      //indicating there are zero number of books now
    start -> next = NULL;                       //indicating this is the end point/not linking to other node

    fscanf(inputfile,"%u",&updates);            //reading number of updates from input file
    while(updates>=0)                           //while it is greater than number of updates keep on checking
    {

        fscanf(inputfile,"%d",&instruction);    //reading instruction from file
        switch(instruction)                     //using switch case to check which operation to be performed
            {
            case 1:
            addbook(start);
            updates--;                           ////after doing each change in library decrement the update counter////
            break;
            case 2:
            deletebook(start);                   //if it is 2 then call the delete function to delete books from your collection.
            updates--;
            break;
            case 3:                              //if it is 3 then call the search function to search books from your collection.
            searchbook(start);
            updates--;
            break;
            case 4:                              //if it is 4 then call the author function to list all the books by particular author
            author(start);
            updates--;
            break;
            case 5:                              //if it is 5 then call the subject function to list all the books by particular subject
            subject(start);
            updates--;
            break;
            default:
            printf("INVALID INSTRUCTION!!!");     //if instructions are not from 1-5 then print invalid instruction
            break;
            }//end switch
           if(feof(inputfile))                   //if reached end of file then break
            {
                break;
            }
    }//end while
    fclose(inputfile);                          //close the input file
    fclose(outputfile);                         //close the output file

return 0;
}//end main



//FUNCTION TO ADD BOOKS TO MY COLLECTION//



void addbook(struct library *thislib)
{
    struct book *bookinfo;                           //declaring pointer book info of type structure book to store information of book
    struct library *newlib;                          //declaring pointer new library to add a new book to the collection
    struct library *start = thislib;                 //indicating the starting point of the library
    int value =1;                                    //initializing dummy value to variable to check whether two books are having same title or not
    newlib = malloc(sizeof(struct library));         //allocating space to add new book in the collection
    bookinfo = malloc(sizeof(struct book));          //allocating space to store information of new book
    bookinfo->title = malloc(SIZE);                  //restricting to 49 characters only for title
    bookinfo->author = malloc(SIZE);                 //restricting to 49 characters only for author
    bookinfo->subject = malloc(SIZE);                //restricting to 49 characters only for subject
    fscanf(inputfile,"%s %s %s",bookinfo->title,bookinfo->author,bookinfo->subject); //reading the information of book from file and storing it in book info pointer
    if(thislib -> collection.title == NULL)   //if the library is empty
    {
        thislib -> collection = *bookinfo; //add a new book into the collection
        printf("\nThe book %s has been added into the library\n\n",bookinfo -> title); //print the result in output screen
        fprintf(outputfile,"\nThe book %s has been added into the library\n\n",bookinfo -> title); //print the result in output file
        start -> num_books ++; //increment the number of books by 1
        return;
    }//end if
    else //if it is not empty
    {
        while(thislib->next!= NULL) //check the next position in the collection
        { //if two books are having same title
          if(strcasecmp(bookinfo -> title, thislib -> collection.title) == 0 || strcasecmp(bookinfo -> title, thislib -> next -> collection.title) == 0)
            {
               value = 0; //if any one of the above condition is true we will not add the book value will be zero
               break;     //come out of if
            }//end if
            thislib = thislib -> next; //link it to the next position in the collection
        }//end while
        if(value == 1 && start-> num_books <= MAXSIZE) //if none of the above condition meets we will add the book to the collection also by checking
        {                                              //library should not exceed 100
            thislib -> next = newlib; //add the new book to the end of list
            newlib -> collection = *bookinfo; //add the book information to the collection
            newlib -> next = NULL; //indicating this is the last position now
            printf("\nThe book %s has been added to the library.\n\n",bookinfo->title); //print the result in output screen
            fprintf(outputfile,"\nThe book %s has been added to the library.\n\n",bookinfo->title); //print the result in output file
            start -> num_books ++; //increment num_books by one
        }//end if
        else //otherwise
        {
            printf("Can't add %s because it has already been added.\n\n",bookinfo->title);  //printing to output screen that can't add
            fprintf(outputfile,"Can't add %s because it has already been added.\n\n",bookinfo->title); //writing to output file that can't add

        }//end else
    }//end else
} //end add function


//FUNCTION TO SEARCH BOOKS FROM MY COLLECTION//


void searchbook(struct library* thislib)
{
    char title[SIZE]; //declaring array of type char to store title of book
    int value = 0;    //initializing dummy variable to check whether the book is in library or not
    fscanf(inputfile,"%s",title); //reading input data from file
    while(thislib!= NULL)
    {
        if(strcmp(title, thislib -> collection.title) == 0) //comparing the book data read from file with the collection of library id true
        {
            value = 1; //assign it 1
            break;
        }//end if
        thislib = thislib -> next; //move to the next position in library
    }//end while

    if(value == 1) //if it is one
    {
        printf("\nThe book %s is currently in the library\n\n",title); //print result in output screen that book found
        fprintf(outputfile,"\nThe book %s is currently in the library\n\n",title);//print result in output file

    }//end if

    else//otherwise
    {
        printf("The book %s is NOT currently in the library\n",title); //print book not found at output screen
        fprintf(outputfile,"The book %s is NOT currently in the library\n",title);//print book not found at output file

    }//end else
}//end search function


//FUNCTION TO DELETE BOOK FROM MY COLLECTION//


void deletebook(struct library* thislib)
{

    char title[SIZE]; //declaring title array to store the title of book to be deleted
    struct library *last ,*destmatch; //declaring last node and destmatch node as last node is where the last book will be and at destmatch the position of deleted book
    struct library* match = thislib;//storing the thislib node to match node with the help of which we will match where our required book is to be deleted
    struct book *dest ,*source;//declaring dest and source variables to copy the contents of book from where it will be deleted
    last = destmatch = NULL; //initializing it to null
    fscanf(inputfile, "%s", title);//reading input from file
    while (match!=NULL){ //until it is null keep on looping and find the book to be deleted
        if(strcasecmp(title,match->collection.title)==0){ //using strcasecmp because its not case sensitive and matching the title with the title in library collection if true
            destmatch = match; //store it in destmatch node where the node to be deleted will be
            while (match!=NULL){//while match is not equal to null means until it reaches the complete list of collection find the last node
                last = match;//found last node
                match=match->next;//pointing to next position
            }//end while
                dest = malloc(sizeof(struct book)); //allocating memory for dest node in memory
                source = malloc(sizeof(struct book));//allocating memory for source node in memory
                 copybook(source,last);//copy the data of book in the last node to the source node
                 copybook(dest,destmatch);//copy the data of book to be deleted to dest node
                 copybook(dest,source); //copy source to dest
                 copybook(destmatch,dest);//and copy dest to the position where the book is deleted
            free(last);//delete the last node
            printf("\nThe book %s has been removed from the library.\n\n", title);//print on output screen that book removed
            fprintf(outputfile, "\nThe book %s has been removed from the library.\n\n", title);//print on output file that book removed
            thislib->num_books--;//decrement the counter by one each time the book is deleted
            return;
        }//end if
        last = match;//found last node
        match=match->next;//pointing to next position
    }//end while
    printf("Book not found!\n\n");//print book not found on output screen
    fprintf(outputfile, "Book not found!\n\n");//print book not found in output file
    return;
}//end delete function


//FUNCTION TO COPY CONTENTS OF ONE BOOK TO ANOTHER


void copybook(struct book *dest, struct book *source)
   {
    (dest->title)= strdup(source->title);     //copy title of book to other book also using strdup instead of strcpy because it will automatically malloc space
    (dest->author)= strdup(source->author);   //copy author of book to other book
    (dest->subject)= strdup(source->subject); //copy subject of book to other book
   }//end copy function



//FUNCTION TO DISPLAY BOOKS BY A PARTICULAR AUTHOR IN ASCENDING ORDER BASED ON TITLE


  void author(struct library *thislib)
  {
    int value=0; //initializing dummy value to indicate whether book found or not
    int i,j; //counter variables
    int k=0; //counter variable
    char title[thislib->num_books][SIZE]; //declaring 2D array to store titles of book
    char temp[thislib->num_books][SIZE];  //declaring 2D temporary array to store titles of book for sorting
    char author_name[SIZE]; //declaring author_name to store author name
    fscanf(inputfile,"%s",author_name); //reading the author name from file
    printf("\nList of all books by %s\n",author_name); //printing to output screen
    fprintf(outputfile,"\nList of all books by %s\n",author_name); //printing to output file
    while (thislib!=NULL) //loop until it reads the author of all books
    {
       if(strcasecmp(author_name,thislib->collection.author) == 0) //if author name matches with the one stored in library collection

         {
           value =1; //assign one
           strcpy(title[k],thislib->collection.title);//store the matched title in title array
           k++; //increment counter

        }
        thislib=thislib->next; //move to the next position
    }


           for (i=0;i<=k;i++)//for loop for sorting the array in ascending order based on title
           {
               for (j=0;j<k-i;j++)//for loop for sorting the array in ascending order
               {
                  if(strcmp(title[i],title[j])<0)//<0 for ascending order
                  {
                      strcpy(temp, title[i]);//swapping strings for sorting purpose
                      strcpy(title[i], title[j]); //swapping strings for sorting purpose
                      strcpy(title[j], temp);//swapping strings for sorting purpose
                  }//end if

               }//end for
           }//end for
           for(i=0;i<k;i++)//for loop for printing the sorted titles
           {
              printf("%s\n",title[i]);//printing in output screen
			  fprintf(outputfile,"%s\n",title[i]);//printing in output file
           }//end for

   if (value==0)//if value is zero
	{
		printf("No book from author %s\n",author_name);//print no book from author in output screen
		fprintf(outputfile,"No book from author %s\n",author_name);//print no book from author in output file
	}//end if
  }//end author function


//FUNCTION TO DISPLAY BOOKS BY A PARTICULAR SUBJECT IN DESCENDING ORDER BASED ON TITLE

void subject(struct library *thislib)
  {
    int i,j; //counter variables
    int k=0; //counter variable
    char title[thislib->num_books][SIZE]; //declaring 2D array  to store title of book
    char temp[thislib->num_books][SIZE];//declaring 2D temporary array to store titles of book for sorting
    int value=0;//initializing dummy value to indicate whether book found or not
    char subject_name[SIZE];//declaring author_name to store author name
    fscanf(inputfile,"%s",subject_name); //reading the author name from file
    printf("\nList of all books by %s\n",subject_name);//printing to output screen
    fprintf(outputfile,"\nList of all books by %s\n",subject_name); //printing to output file
    while (thislib!=NULL) //loop until it reads the title of all books
    {
	   if(strcasecmp(subject_name,thislib->collection.subject) == 0) //compare subject name with the subject name in library if true
        {
           value =1;//assign one
           strcpy(title[k],thislib->collection.title);//store the matched title in title array
           k++;//increment by one

        }//end if
        thislib=thislib->next;//move to the next position
    }
           for (i=0;i<=k;i++)//for loop for sorting the array in ascending order based on title
           {
               for (j=0;j<k-i;j++)//for loop for sorting the array in ascending order
               {
                  if(strcmp(title[i],title[j])>0)//>0 for descending order
                  {
                      strcpy(temp, title[i]);//swapping strings for sorting purpose
                      strcpy(title[i], title[j]);//swapping strings for sorting purpose
                      strcpy(title[j], temp);//swapping strings for sorting purpose
                  }//end if

               }//end for
           }//end for
           for(i=0;i<k;i++)//for loop for printing the sorted titles
           {
              printf("%s\n",title[i]);//printing in output screen
			  fprintf(outputfile,"%s\n",title[i]);//printing in output file
           }//end for

   if(value==0)//if no book found
	{
		printf("No related book for %s is found\n",subject_name);//printing on output screen
		fprintf(outputfile,"No related book for %s is found\n",subject_name);//printing on output file
	}//end if
}//end subject function































