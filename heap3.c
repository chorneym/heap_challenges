#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clrInBuf(){
        while(getchar()!='\n'){};
}

struct command{
struct command * next;
char name[8];
void (*function)();
};

struct value{
struct value * next;
char name[8];
int val;
};

struct command * cList = NULL;
struct command * cLast = NULL;
struct value * vList = NULL;
struct value * vLast = NULL;
struct  command * lastCommand = NULL;

void adminFunction(){
	system("/bin/sh");
}

void addition(){
	puts("This alias will do addition");
}

void subtraction(){
	puts("This alias will do subtraction");
}

void multiplication(){
	puts("This alias will do multiplication");
}

void division(){
	puts("This alias will do division");
}

void removeCommand(){
	char target[8] = {0};
        printf("Enter the name of the alias command to be removed: ");
        fgets(target, 8, stdin);
        struct command * currentCommand = cList;
	struct command * previous = NULL;
	int found = 0;
	while(currentCommand!=NULL){
		if(strcmp(currentCommand->name, target) == 0){
			if(currentCommand==cList){
				cList = currentCommand->next;
			}
			else{
				if(currentCommand==cLast){
					cLast = previous;
				}
				previous->next=currentCommand->next;
			}
			found = 1;
			free(currentCommand);
			puts("freed");
		}
		previous = currentCommand;
		currentCommand = currentCommand->next;
	}
	if(found==0){
		puts("No such alias was found");
	}
}

void listAll(){
	struct command * currentCommand = cList;
	printf("Commands:\n");
	while(currentCommand!=NULL){
		printf("%s", currentCommand->name);
		currentCommand = currentCommand->next;
	}
	struct value * currentValue = vList;
	printf("\nValues:\n");
	while(currentValue!=NULL){
		printf("%s", currentValue->name);
		currentValue = currentValue->next;
	}
	printf("\n");
}

void createValue(){
	struct value * newValue = malloc(sizeof(struct value));
	printf("Enter the name of the alias value ");
	fgets(newValue->name, 8, stdin);
	printf("Enter the number value to be aliased: ");
	scanf("%d", &(newValue->val));
	clrInBuf();
	if(vList == NULL){
		vList = newValue;
		vLast = newValue;
	}
	else{
		vLast->next = newValue;
		vLast = newValue;
	}
}

int aliasFuncPrompt(){
        int choice = 0;
        printf("--------------------------------------------\nPlease select your option:\n[1] Addition\n[2] Subtraction\n[3] Multiplication\n[4] Division\n");
	scanf("%d", &choice);
        clrInBuf();
        return choice;
}

void createCommand(){
	struct command * newCommand = calloc(sizeof(struct command),1);
	printf("Enter the name of the alias command: ");
	fgets(newCommand->name, 8, stdin);
	int funcSelection = aliasFuncPrompt();
	switch(funcSelection){
		case 1:
			newCommand->function = &addition;
			break;
		case 2:
			newCommand->function = &subtraction;
			break;
		case 3:
			newCommand->function = &multiplication;
			break;
		dafault:
			newCommand->function = &division;
			break;
	}
	lastCommand = newCommand;
	if(cList == NULL){
		cList = newCommand;
		cLast = newCommand;
	}
	else{
		cLast->next = newCommand;
		cLast = newCommand;
	}
}


int homePrompt(){
	int choice = 0;
	printf("--------------------------------------------\nPlease select your option:\n[1] Create a new alias command\n[2] Create a new alias value\n[3] List aliases\n[4] Delete an alias command\n[5] Test last alias function\n[6] Clear data and exit\n");
	scanf("%d", &choice);
	clrInBuf();
	return choice;
}

int main(int argc, char ** argv){
	int choice = homePrompt();
	while(choice!=6){
		if(choice==1){
			createCommand();
		}
		else{
			if(choice==2){
				createValue();
			}
			else{
				if(choice==3){
					listAll();
				}
				else{
					if(choice==4){
						removeCommand();
					}
					else{
						if(choice==5){
							(lastCommand->function)();
						}
						else{
							puts("Invalid choice");
						}
					}
				}
			}
		}
		choice = homePrompt();
	}
	printf("Clearing data and exiting...\n");
}
