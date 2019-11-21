#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct list_elem{
struct list_elem * next;
char * data;
};

void adminFunc(){
	write(1, "You did it!\n", 12);
}

int main(int argc, char * argv){
	struct list_elem * one = malloc(sizeof(struct list_elem));
	one->data = malloc(8);
	struct list_elem * two = malloc(sizeof(struct list_elem));
	two->data = malloc(8);
	one->next = two;

	puts("Enter the first data element");
	gets(one->data);
	puts("Enter the second data element");
	gets(two->data);

	puts("Ending Program!\n");
}
