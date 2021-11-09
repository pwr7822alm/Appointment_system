/*
Author : Judy910426
Date : 2021/11/9
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30
#define MAX_RECORD 10
#define SEARCH_LEN 15

// Record type
typedef struct {
	char who[MAX_SIZE];
	char what[MAX_SIZE];
	char when[MAX_SIZE];
	char where[MAX_SIZE];
} Record;

// Function prototype
void loadRecord(Record *, int *, char *);
void menu();
void enterRecord(Record *, int *);
void viewDay(Record *, int);
void viewWeek(Record *, int);
void modifyRecord(Record *, int);
void deleteRecord(Record *, int *);
void searchRecord(Record *, int);
void quit(Record *, int, char *);
void nowRecord(Record *, int);
char *readLine(char *, int, FILE *);

// main function
int main() {
	Record appointmentapp[MAX_RECORD];
	int flag = 1, choice, recordNumber = 0, i;
	char fileName[MAX_SIZE], load;
	
	loadRecord(appointmentapp, &recordNumber, fileName);		// load the record fron file
	printf("There are %d records in the file\n\n", recordNumber);

	while(flag) {
		menu();		// print system menu
		nowRecord(appointmentapp, recordNumber);		// show the current records
		printf("Please enter your choice (0 ~ 6) : ");
		scanf("%d", &choice);		// user enter the choice
		getchar();
		switch(choice) {
			case 1:
				enterRecord(appointmentapp, &recordNumber);
				break;
			case 2:	
				viewDay(appointmentapp, recordNumber);
				break;
			case 3:
				viewWeek(appointmentapp, recordNumber);
				break;
			case 4:
				modifyRecord(appointmentapp, recordNumber);
				break;
			case 5:
				deleteRecord(appointmentapp, &recordNumber);
				break;
			case 6:
				searchRecord(appointmentapp, recordNumber);
				break;
			case 0:
				quit(appointmentapp, recordNumber, fileName);
				flag = 0;
				break;
			default:
				printf("Range error, please try again\n");
				break;
		}
	}
}

// load the records from file and list the record, if file doesn't exist, create a new file
void loadRecord(Record *app, int *num, char fileName[]) {
	FILE *fp;
	int i;
	
	printf("Please enter file name to open or save : ");
	scanf("%[^\n]", fileName);
	
	if((fp = fopen(fileName, "r")) == NULL) {
		printf("File dose not exist, create a new file\n");
		return;
	}else
        while (readLine(app[*num].who, MAX_SIZE, fp) != NULL) {
            app[*num].who[strlen(app[*num].who)-1] = '\0';
            readLine(app[*num].what, MAX_SIZE, fp);
            app[*num].what[strlen(app[*num].what)-1] = '\0';
            readLine(app[*num].when, MAX_SIZE, fp);
            app[*num].when[strlen(app[*num].when)-1] = '\0';
            readLine(app[*num].where, MAX_SIZE, fp);
            app[*num].where[strlen(app[*num].where)-1] = '\0';
            (*num) ++ ;
        }
     printf("\n------ Load Record ------\n");
     for (i = 0 ; i < *num ; i++) 
        printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);
     fclose(fp);
}


// print the system menu
void menu() {
	printf("------ Appointment app System ------\n");
	printf("|         1. Enter Record          |\n");
	printf("|         2. View Day              |\n");
	printf("|         3. View Week             |\n");
	printf("|         4. Modify                |\n");
	printf("|         5. Delete                |\n");
	printf("|         6. Search                |\n");
	printf("|         0. Quit System           |\n");
	printf("------------------------------------\n\n");
}

// user can enter the who/what/when/where information
void enterRecord(Record app[], int *num) {  
	int i = 0, flag = 0;
	char check[MAX_SIZE]; 
	
	if((*num) == 10) {		// if the number of the records is 10, give error message and return menu
		printf("The record is full, please delete some record\n");
		return;
	}
	system("cls");
	printf("Please enter who : ");
	scanf("%[^\n]", app[*num].who);
	getchar();
	printf("Please enter what : ");
	scanf("%[^\n]", app[*num].what);
	getchar();
	printf("Please enter when (yyyy/mm/dd/hh/mm) : ");
	scanf("%[^\n]", check);
	getchar();
	
	while(i < *num) {		// give warnings if there is a record with the exact date and time exists.
		while(i < *num && strncmp(app[i].when, check, strlen(check)) == 0) {
			printf("There are other event in this time, please enter again : ");
			scanf("%[^\n]", check);
			getchar();
		}
		i++;
	}
	strcpy(app[*num].when, check);
	printf("Please enter where : ");
	scanf("%[^\n]", app[*num].where);
	getchar();
	(*num)++;
	system("cls");
}

// to show the appointments of a given day
void viewDay(Record app[], int num) {
	int i = 0, flag = 0;
	char date[MAX_SIZE];
	system("cls");
	printf("Please enter the date(yyyy/mm/dd) to view : ");
	scanf("%[^\n]", date);
	getchar();
	
	while(i < num) {
		while(i < num && (strncmp(app[i].when, date, strlen(date)) != 0))
			++i;
		if(i < num) {
			printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);
			flag = 1;
		}	
        i++;
	}
	if(flag == 0)
		printf("\nRecord not found\n");
	printf("\n");
} 

// to show the appointments of a given week
void viewWeek(Record app[], int num) {
	char date[MAX_SIZE];
	int i = 0, count = 0, flag = 0;
	system("cls");
	printf("Please enter the date(yyyy/mm/dd) to view : ");
	scanf("%[^\n]", date);

	while(count < 7) {
		i = 0;
		while(i < num) {
			while(i < num && (strncmp(date, app[i].when, strlen(date)) != 0))
				++i;
			if(i < num) {
				printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);
				flag = 1;
			}
			
     	   i++;
     	} 
        date[9] = date[9] + 1 ;
        if ((date[9] - '0') > 9) {
            date [8] = date[8] + 1;
            date [9] = date[9] - 10;
        }
        count++;	
	}
	if(flag == 0)
		printf("Record not found\n");
	printf("\n");
}

// user can modify record
void modifyRecord(Record app[], int num) {
	int recordNo, choice, i = 0;
	char check[MAX_SIZE];
	
	system("cls");		
	nowRecord(app, num);		// show the current records
	printf("Which record do you want to modify, please enter the number (1 ~ %d): ", num);
	scanf("%d", &recordNo);		// give record's number to modify
	getchar();
	while(recordNo < 1 || recordNo > num) {
		printf("Range error, please enter again : ");
		scanf("%d", &recordNo);
		getchar();
	}
	printf("\n------Which one do you want to modify ------\n");
	printf("|                  1. Who                    |\n");
	printf("|                  2. What                   |\n");
	printf("|                  3. When                   |\n");
	printf("|                  4. Where                  |\n");
	printf("|                  5. All                    |\n");
	printf("----------------------------------------------\n\n");
	printf("Please enter you choice : ");
	scanf("%d", &choice);
	getchar();
	switch(choice) {
		case 1:
			printf("please enter who : ");
			scanf("%[^\n]", app[recordNo - 1].who);
			getchar();
			break;
		case 2:
			printf("please enter what : ");
			scanf("%[^\n]", app[recordNo - 1].what);
			getchar();
			break;
		case 3:
			printf("please enter when (yyyy/mm/dd/hh/mm) : ");
			scanf("%[^\n]", check);
			getchar();
			while(i < num) {		// give warnings if there is a record with the exact date and time exists.
				while(i < num && strncmp(app[i].when, check, strlen(check)) == 0) {
					printf("There are other event in this time, please enter again : ");
					scanf("%[^\n]", check);
				}
				getchar();
				i++;
			}
			strcpy(app[recordNo - 1].when, check);
			break;
		case 4:
			printf("please enter where : ");
			scanf("%[^\n]", app[recordNo - 1].where);
			getchar();
			break;
		case 5:
			printf("Please enter who : ");
			scanf("%[^\n]", app[recordNo - 1].who);
			getchar();
			printf("Please enter what : ");
			scanf("%[^\n]", app[recordNo - 1].what);
			getchar();
			printf("Please enter when (yyyy/mm/dd/hh/mm) : ");
			scanf("%[^\n]", app[recordNo - 1].when);
			getchar();
			printf("Please enter where : ");
			scanf("%[^\n]", app[recordNo - 1].where);
			getchar();
		default:
			printf("Range error, please try again\n");
			break;	
	}
	system("cls");
}

// user can delete record
void deleteRecord(Record app[], int *num) { // ÁÙ¨S¼g§¹ 
	int recordNo, choice, i;
	Record temp;
	
	system("cls");
	nowRecord(app, *num);		// show the current record
	printf("Which record do you want to modify, please enter the number (1 ~ %d): ", *num);
	scanf("%d", &recordNo);		// give record's number to delete
	getchar();
	while(recordNo < 1 || recordNo > *num) {
		printf("Range error, please enter again : ");
		scanf("%d", &recordNo);
		getchar();
	}
	
	for(i = recordNo - 1; i < *num;i++) {
		strcpy(temp.who, app[i+1].who);
		strcpy(temp.what, app[i+1].what);
		strcpy(temp.when, app[i+1].when);
		strcpy(temp.where, app[i+1].where);
	
		strcpy(app[i+1].who, app[i].who);
		strcpy(app[i+1].what, app[i].what);
		strcpy(app[i+1].when, app[i].when);
		strcpy(app[i+1].where, app[i].where);
	
		strcpy(app[i].who, temp.who);
		strcpy(app[i].what, temp.what);
		strcpy(app[i].when, temp.when);
		strcpy(app[i].where, temp.where);
	}
	(*num)--;

	for (i = 0 ; i < *num ; i++) 
        printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);

}

// to search a record by one of when/what/who/where
void searchRecord(Record app[], int num) {
	char word[SEARCH_LEN];
	int length, i = 0;
	
	system("cls");
	printf("\nPlease enter a word to search (the word less than 15 characters) : ");
	scanf("%[^\n]", word);		// enter the word to search
	getchar();
	length = strlen(word);
	
	while(i < num) {
		while(i < num && (strncmp(word, app[i].who, length) != 0) 
					  && (strncmp(word, app[i].what, length) != 0)
					  && (strncmp(word, app[i].when, length) != 0) 
					  && (strncmp(word, app[i].where, length) != 0) )
		++i;
		if(i < num) 
			printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);
		++i;
	}
	return;
}

// quit system, provide a choice of save or discard file
void quit(Record app[], int num, char fileName[]) {
	int i, choice;
	FILE *fp;
	system("cls");
	printf("------ Quit the system, which do you want to do ? ------\n");
	printf("|                   1. Save & Quit                     |\n");
	printf("|                   2. Discard & Quit                  |\n");
	printf("--------------------------------------------------------\n\n");
	
	printf("Please enter your choice (1 or 2) : ");
	scanf("%d", &choice);		// give a choice to save or discard
	switch(choice) {
		case 1:
			fp = fopen(fileName, "w");
			for(i = 0; i < num; i++)
				fprintf(fp, "%s\n%s\n%s\n%s\n", app[i].who, app[i].what, app[i].when, app[i].where);
			printf("Save Successfully, system quit\n");
			fclose(fp);
		case 2:
			printf("system quit\n");
			break;
		default:
			printf("Range error, please try again\n");
			break;
	}
	
}

// show the current records
void nowRecord(Record app[], int num) {
	int i = 0;
	printf("------ Now Record ------\n");
	for(i = 0; i < num; i++)
				printf("[%d] Who: %s, What: %s, When: %s, Where: %s\n", i+1, app[i].who, app[i].what, app[i].when, app[i].where);
	printf("\n\n");
}

// load the data from file to struct
char *readLine(char str[], int size, FILE *fp) {
	int c;
	char *p;

	for (p = str, size--; size > 0; size--) {
		if ((c = fgetc (fp)) == EOF)
			break;
		*p++ = c;
		if (c == '\n')
			break;
	}
	*p = 0;
	if (p == str || c == EOF)
		return NULL;
	return (p);
}
