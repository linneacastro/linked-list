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
