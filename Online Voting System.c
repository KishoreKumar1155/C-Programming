#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_CANDIDATES 5
#define MAX_VOTES 100

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char username[50];
    char voted_candidate[50];
} Vote;

User users[MAX_USERS];
Vote votes[MAX_VOTES];

int user_count = 0;
int vote_count = 0;

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    
    printf("Enter username: ");
    scanf("%s", users[user_count].username);
    printf("Enter password: ");
    scanf("%s", users[user_count].password);
    
    user_count++;
    printf("Registration successful!\n");
}

int login_user(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

const char *candidates[MAX_CANDIDATES] = {"Alice", "Bob", "Charlie", "David", "Eve"};

void display_ballot() {
    printf("Candidates:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, candidates[i]);
    }
}

void cast_vote(char *username) {
    display_ballot();
    
    int choice;
    printf("Enter your choice (number): ");
    scanf("%d", &choice);
    
    if (choice < 1 || choice > MAX_CANDIDATES) {
        printf("Invalid choice!\n");
        return;
    }
    
    strcpy(votes[vote_count].username, username);
    strcpy(votes[vote_count].voted_candidate, candidates[choice - 1]);
    vote_count++;
    
    printf("Vote cast successfully!\n");
}

void tally_votes() {
    int vote_tally[MAX_CANDIDATES] = {0};
    
    for (int i = 0; i < vote_count; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            if (strcmp(votes[i].voted_candidate, candidates[j]) == 0) {
                vote_tally[j]++;
            }
        }
    }
    
    printf("Election Results:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s: %d votes\n", candidates[i], vote_tally[i]);
    }
}

int main() {
    int choice;
    char username[50], password[50];

    while (1) {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Vote\n");
        printf("4. Tally Votes\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (login_user(username, password)) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid credentials!\n");
                }
                break;
            case 3:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (login_user(username, password)) {
                    cast_vote(username);
                } else {
                    printf("You need to log in to vote!\n");
                }
                break;
            case 4:
                tally_votes();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

