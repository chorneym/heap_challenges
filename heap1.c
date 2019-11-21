#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct account{
char name[6];
char * card;
int needToBeFreed;
};

void clrInBuf(){
        while(getchar()!='\n'){};
}

void addCreditCard(struct account * current){
	if(current->needToBeFreed==0){
		current->card = malloc(17);
		(current->card)[16] = '\0';
		current->needToBeFreed = 1;
	}
	else{
		puts("The previous credit card needs to be removed first");
	}
}

void printCreditCard(struct account * current){
	if(current->card!=NULL){
		printf("%s\n", current->card);
	}
	else{
		puts("There is no credit card available to print");
	}
}

void removeCreditCard(struct account * current){
	if(current->card!=NULL){
		memset(current->card, 0, 16);
		free(current->card);
		current->needToBeFreed = 0;
	}
	else{
		puts("A card needs to be added first");
	}
}

void changeCreditCard(struct account * current){
	if(current->card!=NULL){
		fgets(current->card,17,stdin);
		clrInBuf();
	}
	else{
		puts("A card needs to be added first");
	}
}

int login(){
	char account[6] = {0};
	char pass[6] = {0};
	printf("Enter the account name: \n");
	fgets(account,6, stdin);
	clrInBuf();
	account[5] = '\0';
	printf("Enter the password: \n");
	fgets(pass, 6, stdin);
	clrInBuf();
	pass[5] = '\0';
	if(strcmp(account, "admin")==0){
		if(strcmp(pass, "67890")==0){
			return 1;
		}
		else{
			puts("Password was incorrect");
		}
	}
	else{
		if(strcmp(account, "guest\0")==0){
			if(strcmp(pass, "12345\0")==0){
				return 2;
			}
			else{
				puts("Password was incorrect");
			}
		}
		else{
			printf("The username %s is not a registered account\n", account);
		}
	}
	return 0;
}

int homePrompt(){
	int choice = 0;
	printf("--------------------------------------------\nPlease select your option:\n[1] Log in to an account\n[2] Clear data and exit\n");
	scanf("%d", &choice);
	clrInBuf();
	return choice;
}

int prompt(char * account){
	int option = 0;
	printf("---------------------------------------------\nSigned in as %s\nPlease select your option:\n[1] Add a credit card to the account\n[2] Print credit card\n[3] Change credit card\n[4] Remove credit card\n[5] Log out\n", account);
	scanf("%d", &option);
	clrInBuf();
	return option;
}

int main(int argc, char ** argv){
//--------------Start init-----------------
	struct account * guest = malloc(sizeof(struct account));
	struct account * admin = malloc(sizeof(struct account));
	strcpy(guest->name, "guest\0");
	strcpy(admin->name, "admin\0");
	guest->card = NULL;
	admin->card = NULL;
	guest->needToBeFreed = 0;
	admin->needToBeFreed = 0;
//--------------End init-------------------
	struct account * current = NULL;
	int choice = homePrompt();
	while(choice!=2){
		if(choice==1){
			int user = 0;
			while(user==0){
				user = login();
			};
			if(user==1){
				current = admin;
			}
			if(user==2){
				current = guest;
			}
			int option = 0;
			option = prompt(current->name);
			while(option!=5){
				switch(option){
					case 1:
						addCreditCard(current);
						break;
					case 2:
						printCreditCard(current);
						break;
					case 3:
						changeCreditCard(current);
						break;
					case 4:
						removeCreditCard(current);
						break;
					default:
						puts("Invalid choice");
				}
				option = prompt(current->name);
			}
			puts("Logging out");
		}
		else{
			puts("Invalid choice");
		}
		choice = homePrompt();
	}
	printf("Clearing data and exiting...\n");
}
