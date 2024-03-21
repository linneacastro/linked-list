// MAIN PROGRAM //

/* PA1 A Linked List Program Written in C */
// NAME: Linnea P. Castro
// DATE: 12 JAN 2023
// COURSE: CSE 222
// ASSIGNMENT #: PA1
// SYNOPSIS:
/*
The main program provides an interface for the user to interact with functions wrapped around a linked list. The 6 functions are:
init, add, print, delete, search, and cleanup.  The init function is foundational, as it creates the linked list and sentinel
node, yet it is also the most passive, as the user doesn't interact with this command via the prompt menu.  The prompt menu is 
built around an infinite while loop that keeps circling back to the '>' asking for a command until the user exits with 'x'.  

Using the command 'i' followed by a string, the user can insert a word into the linked list, provided that it does not already exist in the list and 
that there is memory available for it.  Prior to inserting a word, the search function checks to see that the word doesn't already
exist in the list. Words are placed into the linked list in alphabetical order, which requires the pointers of the nodes surrounding the new node,
and the pointers of the new node itself to be updated once correct placement is confirmed.  More detailed explanations of each function
can be found within the functions.c file itself. 

The 'p' command will print the contents of the list, with each word separated by a space.  Words will print in alphabetical order
because that is the way they are stored inside the list.  More detail on this function in functions.c file.

The command 'd' followed by a word will search for that word within the list, and if found, delete it by rerouting pointers surrounding that
node.  Like insert, the delete command will first call the search function and only call the delete function if the search function returned
a 1, indicating that the word was found.  

The 's' command searches for a given word within the list and depending on what it returns to the main function, the main function prints
confirmation that the word was found or not found.  The s command is useful as a gatekeeper before executing other functions, namely delete and 
add functions, as discussed above.  

The final command a user can provide this program is the cleanup function, called with a single 'x'.  The cleanup function traverses the linked
list and frees memory associated with the previous node, until it at last, frees the memory of the final current node.  

This program runs with no memory leaks, as confirmed by Valgrind following various test cases.  

The main ideas this program explores are the makings of a linked list and how to add to and delete from one in ways which are mindful of memory
allocation and freeing.  Initiating pointers to be able to insert and delete nodes and understanding how to update pointers within a loop were crucial
for this assignment.  Another concept that this assignment explored was encapsulating code within various functions inside a larger functions file 
that let the user interact with the main program, with the main program then calling the functions.  Beyond the first init call, the main
program did not handle any of the node creation/deletion.  Concepts reviewed include: while loops, if/else conditionals, fgets, sscanf, infinite loops,
makefiles.  New concepts explored: pointers, malloc, freeing memory, using gdb to confirm/look at memory location and node contents, linked lists.
*/

#include "main.h"

void main()
{

char temp[120]; // Char array for user input with fgets to be passed to sscanf
char command; // Varible to store command for menu interface and fgets/sscanf
char data[16]; // Char array variable to store the data from fgets/sscanf we will copy into the linked list as its "data" field

struct DataNode *myList; // Beginning of linked list

myList=init(); // Uses init function to create an empty linked list with only a sentinel node.  myList references empty linked list.

while(1){ // Enter infinite loop prompting user for command (will only exit with 'x', call of cleanup func)
  printf("> "); // Prompts user for command and string
  fgets(temp, 120, stdin); // Keyboard input from user gets stored in temp
  sscanf(temp, "%c %s", &command, data); // Using sscanf to parse temp and store command and data in variables

// INSERT COMMAND
  if (command == 'i'){ 
    int searchresult=search(myList,data); // To avoid adding a duplicate, we want to first search for data's presence in list 
    if(searchresult == 1){ // Search function has returned 1 (item already exists in list)
      printf("NODE ALREADY IN LIST\n"); // Notify user that node already exist w/in list
    }
    else{ // Search function was called and returned 0, no match found, item not present in list
      int addresult=add(myList,data);
      if(addresult == 1){ // So we can go ahead and call the add function
        printf("SUCCESS\n"); // Item was successfully added to list
      }
      else{
        printf("OUT OF MEMORY\n"); // If no match was found, but the add function returned something other than 1 (a 0)
      }
    }
  }

// PRINT COMMAND
  else if (command == 'p'){
    print(myList); // Call print function
 }

// SEARCH FUNCTION
  else if (command == 's'){
    if(search(myList, data) == 1){ // Calls search function and match was found, function returns 1
      printf("FOUND\n"); // Main program prints FOUND
    }
    else{ // Search function was called and it returned NOT 1 (0), no match was found
      printf("NOT FOUND\n"); // Main program prints NOT FOUND
    }
  }

// DELETE COMMAND
  else if (command == 'd'){
    int deletesearchresult=search(myList, data); // Call search function and assign result to a variable
    while(deletesearchresult==1){ // Search function returned 1, item exists in list and therefore we can delete it
      delete(myList, data); // Call delete function (we're only calling it because a match was found)
      printf("SUCCESS\n"); // Main function prints confirmation that word was deleted
      break; // Exit this while loop
    }
    if(deletesearchresult==0){ // Search function was called and no match found
      printf("NODE NOT FOUND\n"); // Word doesn't exist in list and therefore can't be deleted, main pgm prints
    }
  }

// CLEANUP COMMAND
  else if (command == 'x'){
    cleanup(myList); // Cleanup function called to delete nodes and free all memory
    exit(0); // Exits program completely
  }
  
// COMMAND MENU
  else{ // User has entered an illegitimate command and needs to be reminded of instructions:
    printf("\nPlease enter one of the following commands:\n");
    printf("i string    to insert your string into the alphabetized list\n");
    printf("p           to print the list in alphabetical order\n");
    printf("s string    to see if this string exists within the list\n");
    printf("d string    to delete string from the list\n");
    printf("x           to exit the program\n");
  }

}

}
