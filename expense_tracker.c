#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSE_SIZE 100
#define MAX_INPUT_SIZE 100

struct Expense {
	char name[30];
	char category[20];
	char amount[10];
	char date[15];
};

int load_expenses (struct Expense [], int);
void display_expenses (struct Expense [], int, int);
void add_expense (struct Expense[], int, int*);
void edit_expense (struct Expense[], int, int);
void delete_expense (struct Expense[], int, int*);
void save_changes (struct Expense[], int, int);

int main ()
{
	struct Expense expenses[MAX_EXPENSE_SIZE];
	int num_of_expenses;
	int selected_option = 0;
	char selection_input[MAX_INPUT_SIZE];

	num_of_expenses = load_expenses(expenses, MAX_EXPENSE_SIZE);
	display_expenses(expenses, MAX_EXPENSE_SIZE, num_of_expenses);

	do {
		printf("\nDo you want to...\n1) Add Expense\n2) Edit Expense\n3) Delete Expense\n4) Exit Application\n");
		if (fgets(selection_input, sizeof(selection_input), stdin) != NULL) {
			if (sscanf(selection_input, "%i", &selected_option) != 1) {
				selected_option = 0;
			}
		}

		switch (selected_option) {
			case 1: 
				add_expense (expenses, MAX_EXPENSE_SIZE, &num_of_expenses);
				save_changes(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				display_expenses(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				break;
			case 2:
				edit_expense(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				save_changes(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				display_expenses(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				break;
			case 3:
				delete_expense(expenses, MAX_EXPENSE_SIZE, &num_of_expenses);
				save_changes(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				display_expenses(expenses, MAX_EXPENSE_SIZE, num_of_expenses);
				break;
			case 4:
				break;
			default:
				printf("Invalid Input, Please Try Again.");
				break;
		}

	} while (selected_option != 4);

	printf("Program exited. Have a lovely day.");

	return 0;

}

int load_expenses (struct Expense expenses[], int size) {
	FILE* fp;
	fp = fopen("expenses.txt", "r");

	if (fp == NULL) {
		printf("Error opening file for loading.\n");
		return 0;
	}


	char line[MAX_INPUT_SIZE];
	int expense_count = 0;
	char* token;

	while (fgets(line, sizeof(line), fp) != NULL && expense_count < size) {
		line[strcspn(line, "\n")] = '\0';

		if ((token = strtok(line, "|")) != NULL) {
			strcpy(expenses[expense_count].name, token);
		}

		if (token = strtok(NULL, "|")) {
			strcpy(expenses[expense_count].category, token);
		}

		if (token = strtok(NULL, "|")) {
			strcpy(expenses[expense_count].amount, token);
		}

		if (token = strtok(NULL, "|")) {
			strcpy(expenses[expense_count].date, token);
		}

		expense_count++;
	}

	fclose(fp);

	return expense_count;
}

void display_expenses (struct Expense expenses[], int size, int num_of_expenses) {

	if (num_of_expenses == 0) {
		printf("\nNo Expenses Recorded.\n");
	}
	else {
		printf("\n| ID  ");
		printf("| %-35s", "Name");
		printf("| %-25s", "Category");
		printf("| %-16s", "Amount");
		printf("| %-20s", "Date");
		printf("|\n");

		for (int expense_count = 0; expense_count < num_of_expenses; expense_count++) {
			printf("| %-3i ", expense_count + 1);
			printf("| %-35s", expenses[expense_count].name);
			printf("| %-25s", expenses[expense_count].category);
			printf("| $%-15s", expenses[expense_count].amount);
			printf("| %-20s", expenses[expense_count].date);
			printf("|\n");
		}
	}
}

void add_expense (struct Expense expenses[], int size, int* num_of_expenses) {
	char input[MAX_INPUT_SIZE];

	if (*num_of_expenses == size) {
		printf("Maximum number of entries reached.\n");
	}
	else {
		printf("\nPlease enter expense name (max 30 characters): ");
		if (fgets(input, sizeof(char) * 30, stdin) != NULL){
			input[strcspn(input, "\n")] = '\0';
			strcpy(expenses[*num_of_expenses].name, input);
		}
		printf("Please enter expense category (max 20 characters): ");
		if (fgets(input, sizeof(char) * 20, stdin) != NULL) {
			input[strcspn(input, "\n")] = '\0';
			strcpy(expenses[*num_of_expenses].category, input);
		}
		printf("Please enter expense amount (max 10 characters): $");
		if (fgets(input, sizeof(char) * 10, stdin) != NULL) {
			input[strcspn(input, "\n")] = '\0';
			strcpy(expenses[*num_of_expenses].amount, input);
		}
		printf("Please enter expense date (max 15 characters): ");
		if (fgets(input, sizeof(char) * 15, stdin) != NULL) {
			input[strcspn(input, "\n")] = '\0';
			strcpy(expenses[*num_of_expenses].date, input);
		}

		(*num_of_expenses)++;
	}
}

void edit_expense (struct Expense expenses[], int size, int num_of_expenses) {
	char selection_input[MAX_INPUT_SIZE];
	char input[MAX_INPUT_SIZE];
	int selected_expense = -1;

	printf("Enter expense ID: ");
	if (fgets(selection_input, sizeof(selection_input), stdin) != NULL) {
			if (sscanf(selection_input, "%i", &selected_expense) != 1) {
				selected_expense = -1;
			}
		}

	if (selected_expense != -1) {
		if (selected_expense > num_of_expenses || selected_expense < 1) {
			printf("Invalid Input\n");
		}
		else {
			selected_expense--;
			printf("\nPlease enter expense name (max 30 characters): ");
			if (fgets(input, sizeof(char) * 30, stdin) != NULL) {
				input[strcspn(input, "\n")] = '\0';
				strcpy(expenses[selected_expense].name, input);
			}
			printf("Please enter expense category (max 20 characters): ");
			if (fgets(input, sizeof(char) * 20, stdin) != NULL) {
				input[strcspn(input, "\n")] = '\0';
				strcpy(expenses[selected_expense].category, input);
			}
			printf("Please enter expense amount (max 10 characters): ");
			if (fgets(input, sizeof(char) * 10, stdin) != NULL) {
				input[strcspn(input, "\n")] = '\0';
				strcpy(expenses[selected_expense].amount, input);
			}
			printf("Please enter expense date (max 10 characters): ");
			if (fgets(input, sizeof(char) * 25, stdin) != NULL) {
				input[strcspn(input, "\n")] = '\0';
				strcpy(expenses[selected_expense].date, input);
			}
		}
	}
	else printf("Invalid Input");
}

void delete_expense (struct Expense expenses[], int size, int* num_of_expenses) {
	char selection_input[MAX_INPUT_SIZE];
	int selected_expense = -1;

	printf("\nEnter expense ID: ");
	if (fgets(selection_input, sizeof(selection_input), stdin) != NULL) {
		if (sscanf(selection_input, "%i", &selected_expense) != 1) {
			selected_expense = -1;
		}
	}

	if (selected_expense != -1) {
		if (selected_expense > *num_of_expenses || selected_expense < 1) {
			printf("Invalid Input\n");
		}
		else {
			for (int expense_position = selected_expense; expense_position < *num_of_expenses; expense_position++) {
				strcpy(expenses[expense_position - 1].name, expenses[expense_position].name);
				strcpy(expenses[expense_position - 1].category, expenses[expense_position].category);
				strcpy(expenses[expense_position - 1].amount, expenses[expense_position].amount);
				strcpy(expenses[expense_position - 1].date, expenses[expense_position].date);
			}
		
			(*num_of_expenses)--;
		}
	}
	else printf("\nInvalid Input");

}

void save_changes(struct Expense expenses[], int size, int num_of_expenses) {
	FILE* fp = fopen("expenses.txt", "w");

	if (fp == NULL) {
		printf("Error opening file for saving.\n");
		return;
	}

	for (int expense_count = 0; expense_count < num_of_expenses; expense_count++) {
		fprintf(fp, "%s|%s|%s|%s\n", expenses[expense_count].name, expenses[expense_count].category, expenses[expense_count].amount,expenses[expense_count].date);
	}

	fclose(fp);
	printf("Changes saved successfully!\n");
}
