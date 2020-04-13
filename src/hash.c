/* 	I have assembled in this program an hash_table, which consist's array of 29 linked list instance
		the program reads input file names in the command line,
		each file contain integers from 0 to 28.
		the program reads the integers from the files,
		and prints the integer occurrences in certain file as well the matching file name.
		if an integer wont occur in a file,
		nothing will be printed out.
		if there is an error with the input of the input files by the user,
		there will be an error printed to the stderr file.
*/


#include "hash.h"

typedef struct node* ptr; /* node pointer */
typedef struct node
{
	int data; /* the number of occurences for specific number in a file */
	char fname[MAX_FILE_NAME]; /* the name of the specific file */
	ptr next;
}node;


ptr hash_table[HASH_SIZE]; /* the linked list array */



/* function declerations */
int addtolist(ptr *hptr,int n,char *fname);
void printlist(ptr h, int n);
void countInteger(FILE* fd,int n, char *fname);

int main(int argc, char *argv[])
{
	FILE* fd;
	int fnum, i,k,j,p;
	fnum = argc-1; /* number of files inserted by the user */
	if(argc < 2)
	{
		fprintf(stderr,"%s","You need to enter atleast one file name when executing the program\n");
		exit(0);
	}/*end of if*/
	/* initializing the hash_table to null */
	for(j = 0; j < HASH_SIZE; j++)
	{
		hash_table[j] = 0;
	} /* end of for */
	for(i = fnum; i>=1; i--) /* looping through the files backwards */
	{
		fd = fopen(argv[i], "r");
	if(fd == NULL) /* if the file didn't open correctly */
	{
		fprintf(stderr,"%s","Error, cannot open one of the files which has been inserted. Either the file name is incorrect or you dont have the right previleges.\n");
		exit(0);
	} /* end of if */
	else /* we managed to open the file */
	{
		for(k = 0; k < HASH_SIZE; k++)
		{
			countInteger(fd,k,argv[i]);
	  }/* end of for*/
	 fclose(fd);
	}/* end of else */
}/* end of for */
	for(p = 0; p < HASH_SIZE; p++) /* looping through each number linked list */
	{
		if(hash_table[p] == NULL)
			continue;
		else
		printlist(hash_table[p],p);
	}/*end of for*/
	return 0;
}/*end of main*/


/* linked list functions */

/* Function : countInteger
		the function get as input the current file which i'm working on, the number to look for in the file,
		and the file name. the function will scan throught the file until it reaches the end, with a while loop.
		if we have found a match between the current number, and the number from the file, i will add to the counter.
		in the end, i will add to the matching linked list using my addtolist function, only integers which appear atleast
		once in the file, otherwise, i wont add any node to the matching linked list.
*/

void countInteger(FILE* fd,int n, char *fname)
{
	int tmp;
	int counter[HASH_SIZE] = { 0 }; /* initializing the array elements to 0 */
	fscanf(fd, "%d", &tmp);
	while(!feof(fd))
		{
			if(tmp == n)
				counter[n]+=1;
			fscanf(fd, "%d", &tmp);
		} /* end of while */
		if(counter[n] > 0)
			addtolist(&hash_table[n],counter[n],fname); /* adding the data to the array of linked lists */
		rewind(fd);
}	

/* Function: printlist
		the function get as input a pointer to the required linked list, and the current integer value and scanning through the list.
		while there are still nodes, i have created a counter integer, in order to determine if i'm printing
		for the first time, if so, i will print the beginning as required in the question, i have inserted checks
		to determine if the value is 1, or greater than 1, in order to check if ("times/time") is needed.
		if there is more than 1 node, i will print comma for the next input.
		after i finish with the linked list, i will print \n between different lists outputs.
*/

void printlist(ptr h,int n)
{
	int counter = 0;
		while(h)
		{
		if(counter == 0)
			printf("%d appears in ",n);
		if(counter > 0)
			printf(", ");
		if(h->data == 0)
				h = h -> next;
			else
			{
				if(h->data == 1)
					{
						printf("file %s - %d time",h->fname,h->data);
						h = h -> next;
						counter+=1;
					}/*end of if */
				else
				{
					printf("file %s - %d times",h->fname,h->data);
					h = h -> next;
					counter+=1;
				}/*end of second else*/
			}/*end of first else*/
		}/*end of while*/
	printf("\n");
}/* end of function */



/*Function: addtolist
	the function get as input a pointer to the list, the number of occurnces of an integer in the file, and the file name.
	the function allocates memory for the new node. the function will check when we reach the end of the list inserted,
	in order to add the node in the end of the list. I will add the value of occurences of the integer, aswell as the filename.
*/


int addtolist(ptr *hptr,int n,char *fname)
{
	ptr head,p2,t;
	t = malloc(sizeof(node));
	if(!t)
	{
	printf("\ncannot allocate memory\n");
	exit(0);
	}/* end of if */
	t -> data = n;
	strncpy(t -> fname, fname, MAX_FILE_NAME);
	if(!(*hptr))
	{
		t -> next = NULL;
		*hptr = t;
		return 0;
	}/* end of if */
	head = *hptr;
	while((head) && (head->data < n))
	{
		p2 = head;
		head = head -> next;
	}/* end of while */
	if(head == *hptr)
	{
		t -> next = head;
		*hptr = t;
		return 0;
	}/* end of if */
	t->next = head;
	p2->next = t;
	return 0;
}/* end of function */
