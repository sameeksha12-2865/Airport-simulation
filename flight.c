#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"

int boardId = 12813;

void ticket_details(TICKET *t) {
    printf("Enter name: ");
    scanf(" %[^\n]s", t->name);
    printf("Enter airways: ");
    scanf(" %[^\n]s", t->Airways);
    printf("Enter flight number: ");
    scanf(" %[^\n]s", t->flightNumber);
    printf("Enter source: ");
    scanf(" %[^\n]s", t->source);
    printf("Enter destination: ");
    scanf(" %[^\n]s", t->destination);
    printf("Enter type (E/B): ");
    scanf(" %c", &t->type);
    printf("Enter category (D/I): ");
    scanf(" %c", &t->category);
    printf("Enter departure date (dd:mm:yyyy): ");
    scanf(" %[^\n]s", t->D_Date);
    printf("Enter departure time (hh:mm): ");
    scanf(" %[^\n]s", t->DepartureTime);
}

void generate_boarding_pass(TICKET *ticket, int seat_number, FILE *file) {
    fprintf(file, "\nBoarding Pass Details:\n");
    fprintf(file, "Boarding ID: %d\n", (boardId)++);
    fprintf(file, "Name: %s\n", ticket->name);
    fprintf(file, "Airways: %s\n", ticket->Airways);
    fprintf(file, "Flight Number: %s\n", ticket->flightNumber);
    fprintf(file, "Source: %s\n", ticket->source);
    fprintf(file, "Destination: %s\n", ticket->destination);
    fprintf(file, "Type: %c\n", ticket->type);
    fprintf(file, "Category: %c\n", ticket->category);
    fprintf(file, "Departure Date: %s\n", ticket->D_Date);
    fprintf(file, "Departure Time: %s\n", ticket->DepartureTime);
    fprintf(file, "Seat Number: %d\n", seat_number);
    fprintf(file, "Gate: 1\n");
}

void generate_ticket(int n) {
    FILE *file = fopen("filename1.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }

    TICKET* tickets = (TICKET*)malloc(n * sizeof(TICKET));
    if (tickets == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for ticket %d:\n", i + 1);
        ticket_details(&tickets[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("\nTicket %d\n", i + 1);
        printf("Name: %s\n", tickets[i].name);
        printf("Airways: %s\n", tickets[i].Airways);
        printf("Flight Number: %s\n", tickets[i].flightNumber);
        printf("Source: %s\n", tickets[i].source);
        printf("Destination: %s\n", tickets[i].destination);
        printf("Type: %c\n", tickets[i].type);
        printf("Category: %c\n", tickets[i].category);
        printf("Departure Date: %s\n", tickets[i].D_Date);
        printf("Departure Time: %s\n", tickets[i].DepartureTime);

        printf("\nBoarding pass generated for ticket %d:\n", i + 1);
        generate_boarding_pass(&tickets[i], i + 1, file);
    }

    fclose(file);
    free(tickets);
}


void generate_flight_details(int n) {
    FLIGHT f;
    FILE *fp = fopen("filename2.txt", "w+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter Airway: ");
        scanf(" %[^\n]", f.Airways);
        printf("Enter flight number: ");
        scanf("%s", f.flightNumber);
        printf("Enter source: ");
        scanf("%s", f.source);
        printf("Enter destination: ");
        scanf("%s", f.destination);
        printf("Enter arrival or departure (A/D): ");
        scanf(" %c", &f.ArrDepart);
        while (getchar() != '\n'); // Clear the newline character from the buffer
        printf("Enter time of arrival or departure: ");
        scanf("%s", f.ArrDepartTime);
        printf("Enter status: ");
        scanf("%s", f.status);
        fprintf(fp, "%s,%s,%s,%s,%c,%s,%s\n", f.Airways, f.flightNumber, f.source, f.destination, f.ArrDepart, f.ArrDepartTime, f.status);
    }
    
    fclose(fp);
}



FLIGHTLIST *head = NULL;
void create_flight_list(FILE *fptr) {
    FLIGHT f1;
    char Airways[50], FlightNumber[50], source[50], destination[50], ArrDepartTime[6], status[20];char ArrDepart;
    while (fscanf(fptr, "%49[^,],%49[^,],%49[^,],%49[^,],%c,%5[^,],%19[^\n]\n", 
                  Airways, FlightNumber, source, destination, &ArrDepart, ArrDepartTime, status) == 7) {
        strcpy(f1.Airways, Airways);
        strcpy(f1.flightNumber, FlightNumber);
        strcpy(f1.source, source);
        strcpy(f1.destination, destination);
        f1.ArrDepart = ArrDepart;
        strcpy(f1.ArrDepartTime, ArrDepartTime);
        strcpy(f1.status, status);
        
        FLIGHTLIST *newNode = (FLIGHTLIST *)malloc(sizeof(FLIGHTLIST));
        newNode->oneflight = f1;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
        } else {
            FLIGHTLIST *fi = head;
            while (fi->next != NULL) {
                fi = fi->next;
            }
            fi->next = newNode;
        }
    }
}

void display_flight_list() {
    int i = 1;
    for (FLIGHTLIST *fi = head; fi != NULL; fi = fi->next) {
        printf("Flight %d:\n\n", i++);
        printf("Airways: %s\nFlight Number: %s\nSource: %s\nDestination: %s\nType: %c\nTime: %s\nStatus: %s\n\n",
               fi->oneflight.Airways,
               fi->oneflight.flightNumber,
               fi->oneflight.source,
               fi->oneflight.destination,
               fi->oneflight.ArrDepart,
               fi->oneflight.ArrDepartTime,
               fi->oneflight.status);
    }
}



void update_flight_status() {
    FILE *fp = fopen("filename2.txt", "r");
    FILE *temp_fp = fopen("tempfile.txt", "w+");
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    FLIGHT f;
    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        // Parse the line to extract flight details
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%c,%[^,],%s", f.Airways, f.flightNumber, f.source, f.destination, &f.ArrDepart, f.ArrDepartTime, f.status);

        // Print the current flight details
        printf("Current Flight Details: %s", line);

        // Ask the user if they want to change the status
        char choice;
printf("\n");
        printf("Do you want to change the status for flight %s? (y/n): ", f.flightNumber);
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clear the newline character from the buffer

        if (choice == 'y' || choice == 'Y') {
            printf("Enter new status: ");
            scanf("%s", f.status);
            while (getchar() != '\n'); // Clear the newline character from the buffer
        }

        // Write the (potentially updated) flight details to the temp file
        fprintf(temp_fp, "%s,%s,%s,%s,%c,%s,%s\n", f.Airways, f.flightNumber, f.source, f.destination, f.ArrDepart, f.ArrDepartTime, f.status);
    }

    fclose(fp);
    fclose(temp_fp);

    // Replace the original file with the updated file
    remove("filename2.txt");
    rename("tempfile.txt", "filename2.txt");
}


void print_passengers() {
    FILE *file = fopen("filename1.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[1000];
    const char *prefix = "Name: ";
    size_t len = strlen(prefix);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, prefix, len) == 0) {
            printf("%s", line);
        }
    }

    fclose(file);
}



void source_dest_check() {
    FILE *file = fopen("filename2.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[100];
    char s[100], d[100];

    printf("Enter source: ");
    scanf("%99s", s); // Limit input to prevent buffer overflow
    printf("Enter destination: ");
    scanf(" %99s", d); // Limit input to prevent buffer overflow

    printf("Searching for flights from %s to %s...\n", s, d);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        char *Airways = strtok(line, ",");
        char *flightNumber = strtok(NULL, ",");
        char *source = strtok(NULL, ",");
        char *destination = strtok(NULL, ",");
            if (!strcmp(s, source) && !strcmp(d, destination)) 
	   {
                 printf(" %s\n", line);
            }
        
    }

    fclose(file);
}



void display_status() {
    FILE *file = fopen("filename2.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *copy = strdup(line);
        char *Airways = strtok(copy, ",");
        char *flightNumber = strtok(NULL, ",");
        char *source = strtok(NULL, ",");
        char *destination = strtok(NULL, ",");
        char *ArrDept = strtok(NULL, ",");
        char *time = strtok(NULL, ",");
        char *status = strtok(NULL, ",");

        if (flightNumber != NULL && status != NULL) {
            printf("Flight %s is %s\n", flightNumber, status);
        }
        free(copy);
    }

    fclose(file);
}


int main(void) {
    char x;
    int n;
const char *filename = "filename2.txt"; 
    FLIGHTLIST *flightList = NULL;
    do {
        printf("A - Generate ticket and boarding pass\n");
        printf("G - Generate flight details\n");
        printf("C - Create flight info\n");
        printf("D - Display flight info\n");
        printf("U - Update flight status\n");
        printf("P - Print passenger names\n");
        printf("S - Check all flights with same source and destination\n");
        printf("F - Display status\n");
        printf("Q - Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &x);
        switch (x) {
            case 'A':
                printf("Enter the number of tickets: ");
                scanf("%d", &n);
                generate_ticket(n);
                break;
            case 'G':
                printf("Enter how many flights? ");
                scanf("%d", &n);
                generate_flight_details(n);
                break;
	    case 'C': {
            FILE *fptr = fopen("filename2.txt", "r");
            if (fptr == NULL) {
                perror("Failed to open file");
                exit(EXIT_FAILURE);  // Use exit() instead of return if this is not in main
            }
            create_flight_list(fptr);
            fclose(fptr);
            break;
        }
        case 'D':
            display_flight_list();
            break;
            case 'U':
    		update_flight_status(flightList);
    		break;
            case 'P':
                print_passengers();
                break;
            case 'S':
                source_dest_check();
                break;
            case 'F':
                display_status();
                break;
            case 'Q':
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        // Free memory if flightList was created
        if (flightList) {
            FLIGHTLIST *temp;
            while (flightList != NULL) {
                temp = flightList;
                flightList = flightList->next;
                free(temp);
            }
        }
    } while (x != 'Q');

    return 0;
}
