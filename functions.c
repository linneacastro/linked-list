// FUNCTIONS //

/* PA1 A Linked List Program Written in C */
// NAME: Linnea P. Castro
// DATE: 12 JAN 2023
// COURSE: CSE 222
// ASSIGNMENT #: PA1
// SYNOPSIS:
/*
This functions.c file contains all function contents used by the main program and prototyped in main.h.  More detailed explanations
follow underneath each function title in all caps.
*/

#include "main.h"

// INIT FUNCTION //
/*
The init function is called once at the beginning of the main program.  The init function is responsible for creating a brand new empty
list with a single sentinel node and it does this by calling malloc to allocate memory.  I used strcpy to store the word "SENTINEL"
as the sentinel node's data contents.  Starting off, the sentinel points to NULL as it is the only node in the list.  As we populate 
the list, the sentinel will instead point to the next node, with the last node in the list pointing to NULL to signify the end of
the list (more on this later).  The init function returns a pointer to the sentinel node.  Within the main program, I call the init 
function and then assign it the handle, myList.
*/
struct DataNode *init()
{
  struct DataNode *sentinel;
  sentinel=malloc(sizeof(struct DataNode)); // Allocating memory for the sentinel node, big enough to hold struct DataNode (variable type)
  strcpy(sentinel->data, "SENTINEL"); // Copying the word "SENTINEL" into the sentinel's data using strcpy
  sentinel->next=NULL; // Sentinel node points to NULL, which means this is the one and only node in our list
  return(sentinel); // This function returns a pointer to an empty list
}

// ADD FUNCTION //
/*
The add function is one of two functions in this program that uses malloc to allocate new memory (the other function being init).  The
add function begins by creating a pointer called new and mallocing memory for it.  Similar to the delete and cleanup functions, two
pointers called current and previous are initiated to serve as markers for traversing the list as node contents are evaluated for 
alphabetical insertion.  This was the trickiest function for me to write because of the handling of the edge cases.  There were two
scenarios that would return a 1 to the main function for a successful add: adding somewhere in the middle of the list, and adding the 
first/last item in list (when new->next=NULL).  As long as memory is available in the malloc, we move into the second part of the 
function using strcpy to copy data into new->data.  While current != NULL we have two options: 1. Using strcmp we found the thing AFTER our
word alphabetically and update pointers to insert the word, returning 1 and exiting function. 2. Updating pointers because we did NOT find 
the word alphabetically after our word and we're still not at the end.  If nothing was found in the list that came alphabetically after our 
word (or if we are adding the very first thing), then our word placement is right at the end.  We update the new->next pointer to be NULL 
and return 1 to our main function for successful add. 
*/
int add(struct DataNode *list, char *data)
{
  struct DataNode *new=malloc(sizeof(struct DataNode)); // Adding a new node so we need to malloc memory for it
  struct DataNode *current; // Initializing current pointer
  struct DataNode *previous; // Initializing previous pointer

  previous=list; // Initially previous will be the sentinel node (list)
  current=list->next; // Current will initially be the node that sentinel points to, ie. the first non-sentinel node in list

  if(new == NULL){ // if new == NULL, we have no memory to create a new node
    return(0); // Return 0 to main function, no memory avail
  }

  else{ // Memory IS available and malloc was successful
    strcpy(new->data, data); // Use strcpy to add data into new->data, new data node just created

    while(current != NULL){ // As long as current node isn't holding NULL(the list is more than 1 item long), iterate the following
      if(strcmp(current->data, new->data) > 0){ // Comparing contents of current node to new node to alphabetize.  We found word that comes AFTER our word.
        previous->next=new; // Spot to insert our word found!  Previous will now point to new
        new->next=current; // And our new node will point to what was current
        return(1); // Function returns 1 to main function following successful add
      }
        previous=previous->next; // Current is still not NULL but we didn't find the word after our word yet, so we will traverse list
        current=current->next; // Previous and current pointers updated
    }
    previous->next=new; // These next 3 lines of code happen if we are inserting the last or first item in list (first after sentinel), ie current == NULL
    new->next=NULL; // For first or last item in list, new->next will be NULL
    return(1); // Function still returns 1 to main function for successful add!
  }
}

// PRINT FUNCTION //
/*
The print function traverses the list, starting at the sentinel node (but not printing it), and then hopping to the next node, printing it, and
moving along to the next one.  We initiate this function by creating a pointer called temp, that refers to the sentinel node initially, 
and then the thing right after it.  I used a while loop with the condition (temp != NULL) to iterate.  As long as temp does not equal NULL,
the item in the list will print followed by a space, and temp will be set to equal temp->next.  The function will stop once it reaches the 
last item in the list, when temp == NULL.  Having exited the while loop when temp == NULL, the function prints a newline and returns nothing
to the main function.
*/
void print(struct DataNode *list)
{
  struct DataNode *temp; // Creating a pointer called temp to help us traverse list
  temp=list; // This is the sentinel node that we do not want to print
  temp=temp->next; // Real first node in our list (the one after sentinel node)

  while (temp != NULL){ // Until we reach the very last node with NULL stored in it, do this:
    printf("%s ", temp->data); // Print first node followed by a space
    temp=temp->next; // Traverse to next node in the list by making temp the thing that temp->next points to
  }
  printf("\n"); // Print newline at the end so command prompt '>' in main prog shows up on next line
  return; // Print function returns nothing to main function.
}

// SEARCH FUNCTION //
/*
The search function is used within the main program for the 's' search command, and prior to executing the delete and insert/add commands.
Search takes a pointer to a node and a character string.  We establish a pointer wtihin the function called current which refers to the 
node right after the sentinel node (1st real item in our list).  Using a while current != NULL loop, strcmp checks user data input against 
current node contents for a match.  Strcmp returning a 0 means that a match was found and the item inputted by user was located within the 
list.  If a match was found, the search function will return 1 to the main program.  If the condition is fals (no match found), current gets 
set to the next thing current points to, thus traversing the list.  
*/
int search(struct DataNode *list, char *data)
{
  struct DataNode *current; // Initializing *current pointer

  current=list->next; // This is the first node to check (the one after the sentinel)
  
  while(current != NULL){ // As long as current != NULL
    if(strcmp(current->data, data) == 0){ // Strcmp checks if current->data matches the data inputted by user. == 0 means match found
      return(1); // Match was found, function will return 1 to main program
      break; // Match was found, so we can leave the while loop
    }
    current=current->next; // Traverse the list by changing current to point to the thing AFTER current, so we can go back to top of loop to check strcmp again.
  }
  return(0); // Function returns a 0 to main program if no match is found
}

// DELETE FUNCTION //
/*
In the delete function, we will initialize two pointers to be our placeholders as we traverse the list, because we will want to keep
track of the node we are currently on and the one directly before it (which we will need to link up the node AFTER the current node once
we delete something).  The function begins with an infinite loop which first seeks to find the word the user is requesting to delete. 
The match is confirmed using strcmp.  When a match is found, we use previous->next=current->next to redirect the pointer before found node
to point to the node after it, essentially skipping over it.  Once the previous and next nodes are linked up to skip over the node we
are deleting, that node's memory can be freed.  Successful deletion will return 1 to the main program.  If no match was found (strcmp
returned something other than 0) and we are on the last node (everything has been checked), the function will return 0 to the main program, 
signifying that the item was not found.  This function then traverses by setting previous=current and current=current->next.
*/
int delete(struct DataNode *list, char *data)
{
  struct DataNode *current; // Initializing current pointer
  struct DataNode *previous; // Initializing a previous pointer

  current=list->next; // First node to check is the one after the sentinel, current
  previous=list; // This is the node before the one we are checking, or the sentinel node to begin

  while(1){
    if(strcmp(current->data, data) == 0){ // Something matching what we want to delete has been found
    previous->next=current->next; // Skip over current and changes previous to point to the thing AFTER current
    free(current); // Free up the memory that we initially malloced to contain the data
    return(1); // Return 1 to the main program, successful deletion
    break; 
    }
    if((strcmp(current->data, data) != 0) && (current->next == NULL)){ // No match was found and we are at the end of the list
      return(0); // Return 0 to main function
      break; 
    }
  previous=current; // No match found, but we're not at the last node yet.  Traverse list to check the next node by updating the following pointers.
  current=current->next;
  }
}

// CLEANUP FUNCTION //
/*
Similar to the delete and add function, the cleanup function makes use of two pointers, current and previous, to traverse the list and free
memory.  First, we check if the node we are calling current is the last node in the list (is current != NULL?)  As long as it is not the last 
node in the list, we free the previous node and then update our pointers so that previous becomes the old current, and new current becomes
the thing old current was pointing to.  We keep iterating through this until we reach the last node.  When the function reaches the last and 
only node in the list, previous, we free that and leave the function, having freed all memory that was used by the program.  This function works
by deleting the sentinel node first and the node farthest from the sentinel node last. 
*/
void cleanup(struct DataNode *list)
{
  struct DataNode *current; // Initialize current pointer
  struct DataNode *previous; // Initialize previous pointer
  
  current=list->next; // First node to check is one after sentinel, current node
  previous=list; // Node before the one we are checking, the sentinel node

  while(1){ // Infinite loop
    if(current != NULL){ // As long as we're not at the last node, do the following:
    free(previous); // Free memory of previous node, first one freed will be sentinel
    previous=current; // Update pointers so previous becomes current
    current=current->next; // Update pointers so new current becomes the thing old current was pointing to
    }
    else{
      break; // Otherwise, if current is null and we are on the last node, break out of this loop and...
    }
  }
  free(previous); // Free previous memory allocation to release memory of last/only node
}

