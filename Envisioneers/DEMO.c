#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User {
    char username[100];
    char password[50];
    char address[100];
    char phoneNumber[15];
    char pickupAddress[100];
    int collectionFrequency;
    float payment;
    int numHouseholds;
};
void showMainMenu();
void showUserInterface();
void handleUserSignUp();
struct User handleUserLogin();
void promptUserForFrequency(struct User *user);
void cancelPickup();
void recycle();
int selectFrequency();
void handlePackageAndInvoice(struct User *user);
void showAdminInterface();
void showTruckDriverInterface();
void viewPickupSchedule();
void markPickupCompleted();
void updateTruckStatus();
void manageUsers();
void viewPickupStatistics();
void calculateRouting();
void returnToMainMenu();
void contactUs();
void handleUserEditRequest(const char* username);
void cancelUserRequest(const char* username);
void showAdminOptions();
void showTruckDriverOptions();

//**************************************************** Md Hasibul Islam -- 1469 ***********************************************************

int main() {
    printf("\n\n");
    printf("\t\t\t\t#######################################################\n");
    printf("\t\t\t\t#                      Welcome to                     #\n");
    printf("\t\t\t\t#                Waste Management System              #\n");
    printf("\t\t\t\t#######################################################\n");

    showMainMenu();
    returnToMainMenu();
    return 0;
}

void showMainMenu() {
    int choice;

    printf("\n\tMain Menu:                                   \n");
    printf("\t----------                                  \n");
    printf("\t1. Request Pickup                              \n");
    printf("\t2. Request Recycle                             \n");
    printf("\t3. Administrator Interface                     \n");
    printf("\t4. Vehicle Management                          \n");
    printf("\t5. Contact Us                                  \n");
    printf("\t6. Exit                                        \n");
    printf("\n");

    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("pause");
            system("cls");
            showUserInterface();
            break;
        case 2:
            system("pause");
            system("cls");
            recycle();
            break;
        case 3:
            system("pause");
            system("cls");
            showAdminInterface();
            break;
        case 4:
            system("pause");
            system("cls");
            showTruckDriverInterface();
            break;
        case 5:
         contactUs();
            break;
        case 6:
         printf("\tExiting the system, Goodbye!\n");
            break;
        default:
            printf("\tInvalid choice. Exiting the system.\n");
            break;

    }
}
void returnToMainMenu() {
    int choice;
    printf("\n\tReturn to Main Menu:");
    printf(" [1 - Yes] / [0 - No-Exit]\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        system("pause");
        system("cls");
        showMainMenu();
    } else if (choice == 0) {
        printf("Goodbye!\n");
        exit(0);
    } else {
        printf("\tInvalid choice. Exiting the system.\n");
        exit(0);
    }
}
void showUserInterface() {
    int choice;
    struct User user;
    printf("\n\tUser Interface\n");
    printf("\t-----------------\n");
    printf("\t1 - Sign Up\n");
    printf("\t2 - Login\n");
    printf("\t3 - Cancel/Edit Pickup\n");
    printf("\t4 - Return to Main Menu\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            handleUserSignUp();
            break;
        case 2:
            user = handleUserLogin();
            printf("\n");
            user.collectionFrequency = selectFrequency();
            handlePackageAndInvoice(&user);
            break;
        case 3:
            cancelPickup();
            break;
        case 4:
            showMainMenu();
            break;
        default:
            printf("\tInvalid choice.\n");
            break;
    }returnToMainMenu();
}
void handleUserSignUp() {
    struct User user;
    printf("\n\tSign Up\n");
    printf("\tEnter your Name: ");
    scanf("%s", user.username);
    printf("\tEnter your Address: ");
    scanf("%s", user.address);
    printf("\tEnter your Phone Number: ");
    scanf("%s", user.phoneNumber);
    printf("\tEnter a Password (At least 8 characters): ");
    scanf("%s", user.password);
    printf("\tEnter your pickup place: ");
    scanf("%s", user.pickupAddress);
    user.collectionFrequency = selectFrequency();
    handlePackageAndInvoice(&user);
    returnToMainMenu();
}
struct User handleUserLogin() {
    char phoneNumber[15], password[50], storedUsername[50], storedPassword[50], storedAddress[100], storedPhoneNumber[15], pickupAddress[100];
    printf("\tEnter your Phone Number: ");
    scanf("%s", phoneNumber);
    printf("\tEnter your Password: ");
    scanf("%s", password);
    FILE *file = fopen("userinfo.txt", "r");
    if (file == NULL) {
        printf("\tError: Unable to open user database.\n");
        exit(1);
    }
    int found = 0;
    struct User user;
    while (fscanf(file, "%s %s %s %s %s", storedUsername, storedPassword, storedAddress, storedPhoneNumber, pickupAddress) != EOF) {
        if (strcmp(phoneNumber, storedPhoneNumber) == 0 && strcmp(password, storedPassword) == 0) {
            found = 1;
            strcpy(user.username, storedUsername);
            strcpy(user.address, storedAddress);
            strcpy(user.phoneNumber, storedPhoneNumber);
            strcpy(user.pickupAddress, pickupAddress);
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("\tLogin failed. Invalid credentials.\n");
        exit(1);
    }printf("\tLogin successful...\n");
    return user;
    returnToMainMenu();
}
void handleUserEditRequest(const char* username) {
    printf("Editing request for user: %s\n", username);
    printf("Request edited successfully.\n");
    returnToMainMenu();
}

void cancelUserRequest(const char* username) {
    FILE *invoiceFile = fopen("invoices.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (invoiceFile == NULL || tempFile == NULL) {
        printf("Error: Unable to open invoice file.\n");
        if (invoiceFile) fclose(invoiceFile);
        if (tempFile) fclose(tempFile);
        returnToMainMenu();
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), invoiceFile)) {
        if (strstr(line, username) != NULL) {
            found = 1;
            for (int i = 0; i < 3; i++) {
                fgets(line, sizeof(line), invoiceFile);
            }
            continue;
        }
        fputs(line, tempFile);}
    fclose(invoiceFile);
    fclose(tempFile);

    if (found) {
        remove("invoices.txt");
        rename("temp.txt", "invoices.txt");
        printf("Request canceled successfully.\n");
    } else {
        remove("temp.txt");
        printf("No request found for user: %s\n", username);
    }

    returnToMainMenu();
}

void cancelPickup() {
    char username[50];
    int choice;

    printf("\nCancel or Edit Pickup Request\n");
    printf("Enter your username: ");
    scanf("%s", username);

    printf("\nOptions:\n");
    printf("\t1 - Edit Request\n");
    printf("\t2 - Cancel Request\n");
    printf("\t0 - Return to Main Menu\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Editing request for user: %s\n", username);
            printf("Request edited successfully.\n");
            returnToMainMenu();
            break;
        case 2: {
            FILE *invoiceFile = fopen("invoices.txt", "r");
            FILE *tempFile = fopen("temp.txt", "w");
            if (invoiceFile == NULL || tempFile == NULL) {
                printf("Error: Unable to open invoice file.\n");
                if (invoiceFile) fclose(invoiceFile);
                if (tempFile) fclose(tempFile);
                returnToMainMenu();
                return;
            }
            char line[256];
            int found = 0;
            while (fgets(line, sizeof(line), invoiceFile)) {
                if (strstr(line, username) != NULL) {
                    found = 1;
                    for (int i = 0; i < 3; i++) {
                        fgets(line, sizeof(line), invoiceFile);
                    }
                    continue;
                }
                fputs(line, tempFile);
            }

            fclose(invoiceFile);
            fclose(tempFile);

            if (found) {
                remove("invoices.txt");
                rename("temp.txt", "invoices.txt");
                printf("Request canceled successfully.\n");
            } else {
                remove("temp.txt");
                printf("No request found for user: %s\n", username);
            }

            returnToMainMenu();
            break;
        }
        case 0:
            returnToMainMenu();
            break;
        default:
            printf("Invalid choice.\n");
            returnToMainMenu();
            break;
    }
}
//***************************************************** MD. ASHRAFUL ALAM HRIDOY - 1459 ******************************************
void recycle() {
    int choice;
    float amountPlastic, amountGlass, amountOrganic;

    printf("\n\tRecycle Options\n");
    printf("\t---------------\n");
    printf("\t1 - Sign Up\n");
    printf("\t2 - Login\n");
    printf("\t3 - Return to Main Menu\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
        handleUserSignUp();
            break;
        case 2:
            handleUserLogin();
            system("pause");
            system("cls");
            break;
        case 3:
            showMainMenu();
            break;
        default:
            printf("Invalid choice.\n");

            break;
    }
    if (choice == 1 || choice == 2) {
        printf("\n\tRecycling Options\n");
        printf("\t--------------------\n");
        printf("\t1 - Plastic\n");
        printf("\t2 - Glass\n");
        printf("\t3 - Organic Waste\n");
        printf("\t4 - Return to Main Menu\n\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

switch (choice) {
    case 1:
        printf("\nRecycling Plastic:\n");
        printf("Plastic recycling helps reduce environmental pollution and saves energy.\n");
        printf("Please enter the amount of plastic waste you want to recycle (in kg): ");
        scanf("%f", &amountPlastic);
        printf("\nThank you for contributing to a cleaner environment!\n");
        printf("Your request to recycle %.2f kg of plastic waste is now in process.\n", amountPlastic);
        printf("\nDid you know? Recycled plastic can be used to create various products such as clothing, furniture, and even playground equipment.\n");
        break;
    case 2:
        printf("\nRecycling Glass:\n");
        printf("Recycling glass helps conserve natural resources and reduce landfill waste.\n");
        printf("Please enter the amount of glass waste you want to recycle (in kg): ");
        scanf("%f", &amountGlass);
        printf("\nThank you for choosing to recycle glass!\n");
        printf("Your request to recycle %.2f kg of glass waste is now in process.\n", amountGlass);
        printf("\nFun fact: Recycled glass can be transformed into new glass containers, fiberglass insulation, or even decorative glassware.\n");
        break;
    case 3:
        printf("\nRecycling Organic Waste:\n");
        printf("Organic waste recycling reduces methane emissions and produces valuable compost.\n");
        printf("Please enter the amount of organic waste you want to recycle (in kg): ");
        scanf("%f", &amountOrganic);
        printf("\nThank you for composting your organic waste!\n");
        printf("Your request to recycle %.2f kg of organic waste is now in process.\n", amountOrganic);
        printf("\nInteresting fact: Composting organic waste creates nutrient-rich soil amendments that improve soil structure and fertility, promoting healthy plant growth.\n");
        break;
    case 4:
        printf("\nReturning to Main Menu.\n");
        break;
    default:
        printf("\nInvalid choice. Please select a valid option.\n");
        break;
}}}
int selectFrequency() {
    int choice;
    printf("\tSelect pickup frequency:\n");
    printf("\t1 - Weekly\n");
    printf("\t2 - Biweekly\n");
    printf("\t3 - Monthly\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void handlePackageAndInvoice(struct User *user) {
    int collectionCharge;
    switch (user->collectionFrequency) {
        case 1: collectionCharge = 100; break;
        case 2: collectionCharge = 500; break;
        case 3: collectionCharge = 1000; break;
        default: printf("\tInvalid frequency selection.\n"); return;
    }
    printf("Your Total Frequency Charge is: $%d\n", collectionCharge);

    FILE *file = fopen("userinfo.txt", "a");
    if (file == NULL) { printf("Error opening file!\n"); exit(1); }
    fprintf(file, "%s %s %s %s %s %d\n", user->username, user->password, user->address, user->phoneNumber, user->pickupAddress, user->collectionFrequency);
    fclose(file);

    printf("Sign up successful!\n\n\t------ Invoice ------\n\tUsername: %s\n\tAddress: %s\n\tPayment: $%d\n\t---------------------\n", user->username, user->address, collectionCharge);

    FILE *invoiceFile = fopen("invoices.txt", "a");
    if (invoiceFile == NULL) { printf("Error opening file!\n"); return; }
    fprintf(invoiceFile, "------ Invoice ------\nUsername: %s\nAddress: %s\nPayment: $%d\n---------------------\n", user->username, user->address, collectionCharge);
    fclose(invoiceFile);
        printf("\tPayment will be Cash on delivery\n");
}
void calculateRouting() {
    int numPlaces, shortestDistance = -1, totalDistance = 0, vehicleRange, wasteHistory;

    printf("\nCalculate Routing\n");

    printf("Enter the number of places to collect waste: ");
    scanf("%d", &numPlaces);

    printf("Enter distances between places (enter -1 if unreachable):\n");
    for (int i = 0; i < numPlaces; ++i) {
        for (int j = i + 1; j < numPlaces; ++j) {
            int distance;
            printf("Distance from place %d to place %d: ", i + 1, j + 1);
            scanf("%d", &distance);
            if (shortestDistance == -1 || (distance > 0 && distance < shortestDistance)) {
                shortestDistance = distance;
            }
            if (distance != -1) {
                totalDistance += distance;
            }}}
    printf("Enter the vehicle's range: ");
    scanf("%d", &vehicleRange);

    printf("Enter the waste history (in tons): ");
    scanf("%d", &wasteHistory);

    printf("-------------------------------------------------------\n");
    printf("Shortest distance between places: %d\n", shortestDistance);
    printf("Vehicle's range: %d\n", vehicleRange);
    printf("Waste history: %d tons\n", wasteHistory);

    double vehicleSpeed = 30;
    double estimatedTime = (double)shortestDistance / vehicleSpeed;
    printf("Estimated time to cover the shortest distance: %.2f hours\n", estimatedTime);

    printf("Total distance covered for waste collection: %d\n", totalDistance);

    if (numPlaces > 3 && shortestDistance > 10 && vehicleRange > 50) {
        printf("Recommendation: Optimize the route for efficient waste collection.\n");
    }
    printf("-------------------------------------------------------\n");   returnToMainMenu();}
void showAdminInterface() {
    int choice;

    printf("\n\tAdministrator Interface\n");
    printf("\t-----------------------\n");
    printf("\t1 - Sign Up\n");
    printf("\t2 - Login\n");
    printf("\t0 - Exit\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            handleUserSignUp();
            showAdminOptions();
            break;
        case 2:
            handleUserLogin();
            showAdminOptions();
            break;
        case 0:
            printf("Exiting.\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
    }
}

//************************************************************ MD MOLLA GOLAM MOSTAFA - 1464 **********************************************************
void showTruckDriverInterface() {
    int choice;

    printf("\n\tVehicle Management\n");
    printf("\t------------------\n");
    printf("\t1 - Sign Up\n");
    printf("\t2 - Login\n");
    printf("\t0 - Exit\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            handleUserSignUp();
            showTruckDriverOptions();
            system("pause");
            system("cls");
            break;
        case 2:
            handleUserLogin();
            system("pause");
            system("cls");
            showTruckDriverOptions();
            break;
        case 0:
            printf("Exiting.\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void showTruckDriverOptions() {
    int choice;
    printf("\n\tVehicle Management\n");
    printf("\t-----------------------\n");
    printf("\t1 - View Pickup Requests\n");
    printf("\t2 - Mark Pickup Completed\n");
    printf("\t3 - Update Truck Status\n");
    printf("\t4 - Logout\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            viewPickupSchedule();
            break;
        case 2:
            markPickupCompleted();
            break;
        case 3:
            updateTruckStatus();
            break;
        case 4:
            printf("Logging out.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }}

void viewPickupSchedule() {
    printf("\nView Pickup Schedule\n");

    FILE *invoiceFile = fopen("invoices.txt", "r");
    if (invoiceFile == NULL) {
        printf("No pickup requests found.\n");
        returnToMainMenu();
        return;
    }

    printf("-------------------------------------------------------\n");
    printf("Pickup Requests:\n");
    printf("-------------------------------------------------------\n");
    printf("Username\t\tAddress\t\t\t\tPayment\n");
    printf("-------------------------------------------------------\n");
    char username[50];
    char address[100];
    float payment;
    int found = 0;
    char line[256];

    while (fgets(line, sizeof(line), invoiceFile)) {
        if (sscanf(line, "------ Invoice ------\n") == 0) {
            fgets(username, sizeof(username), invoiceFile);
            fgets(address, sizeof(address), invoiceFile);
            fgets(line, sizeof(line), invoiceFile);
            sscanf(line, "Payment: $%f\n", &payment);

            username[strcspn(username, "\n")] = '\0';
            address[strcspn(address, "\n")] = '\0';

            printf("%-15s\t%-30s\t$%.2f\n", username, address, payment);
            found = 1;
        }
    }

    if (!found) {
        printf("No pickup requests found.\n");
    }

    printf("-------------------------------------------------------\n");

    fclose(invoiceFile);
    returnToMainMenu();
}

void markPickupCompleted() {
        time_t t;
    time (&t);

    printf("\n %s",ctime (&t));
    printf("\n\tMark Pickup Completed\n");

    FILE *invoiceFile = fopen("invoices.txt", "r+");
    if (invoiceFile == NULL) {
        printf("Error: Unable to open invoice file.\n");
        return;
    }

    char username[50], address[100], date[20];
    int index = 1, choice;

    printf("\tPending Pickup Requests:\n");
    while (fscanf(invoiceFile, "------ Invoice ------\nUsername: %[^\n]\nAddress: %[^\n]\nPayment: $*f\nDate: %[^\n]\n---------------------\n", username, address, date) != EOF) {
        printf("%d. %s at %s (Date: %s)\n", index++, username, address, date);
        break;
    }

    if (index == 1) {
        printf("\tNo pending pickup requests.\n");
        fclose(invoiceFile);
        return;
    }

    printf("\tDo you want to mark this pickup as completed? (1 for Yes / 0 for No): ");
    scanf("%d", &choice);

    if (choice != 1) {
        printf("\tCancelled marking pickup as completed.\n");
        fclose(invoiceFile);
        return;
    }
    rewind(invoiceFile);
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file for writing.\n");
        fclose(invoiceFile);
        return;
    }
    index = 1;
    while (fscanf(invoiceFile, "------ Invoice ------\nUsername: %[^\n]\nAddress: %[^\n]\nPayment: $*f\nDate: %[^\n]\n---------------------\n", username, address, date) != EOF) {
        if (index++ == 1) {
            printf("Marked pickup request for %s at %s as completed.\n", username, address);
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            strftime(date, sizeof(date), "%Y-%m-%d", tm);
            fprintf(tempFile, "------ Invoice ------\nUsername: %s\nAddress: %s\nPayment: $0.00\nDate: %s\n---------------------\n", username, address, date);
            break;
        } else {
            fprintf(tempFile, "------ Invoice ------\nUsername: %s\nAddress: %s\nPayment: $0.00\nDate: %s\n---------------------\n", username, address, date);
        }
    }

    fclose(invoiceFile);
    fclose(tempFile);

    remove("invoices.txt");
    rename("temp.txt", "invoices.txt");

    getchar();
}
void updateTruckStatus() {
    printf("\n\tAll vehicles are checked and they ready to work...\n");}

//***************************************************** MD ATIKUJJAMAN TUTUL - 1103 *****************************************************************
void showAdminOptions() {
    int choice;
            system("pause");
            system("cls");
    printf("\n\tAdministrator Options\n");
    printf("\t-----------------------\n");
    printf("\t1 - Manage Users\n");
    printf("\t2 - View Pickup Statistics\n");
    printf("\t3 - Calculate Routing\n");
    printf("\t4 - Logout\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            manageUsers();
            break;
        case 2:
            viewPickupStatistics();
            break;
        case 3:
            calculateRouting();
            break;
        case 4:
            printf("Logging out.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
void manageUsers() {
    int choice;
    printf("\n\tManage Users\n");
    printf("\n\t-------------\n");
    printf("\t1. View Users\n");
    printf("\t2. Return to Main Menu\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            viewUsers();
            break;
        case 2:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
void viewUsers() {
    const char *filename = "userinfo.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening user file");
        return;
    }

    struct User user;
    printf("\nList of Users:\n");
    while (fscanf(file, "%49s %99s %14s %49s %99s %d",
                  user.username, user.address, user.phoneNumber,
                  user.password, user.pickupAddress,
                  &user.collectionFrequency) == 6) {
        printf("Username: %s\n", user.username);
        printf("Address: %s\n", user.address);
        printf("Phone Number: %s\n", user.phoneNumber);
        printf("Pickup Address: %s\n", user.pickupAddress);
        printf("Collection Frequency: %d\n\n", user.collectionFrequency);
    }

    fclose(file);
}

void viewPickupStatistics() {
    printf("\nView Pickup Statistics\n");

    FILE *invoiceFile = fopen("invoices.txt", "r");
    if (invoiceFile == NULL) {
        printf("Error: Unable to open invoice file.\n");
        return;
    }

    int totalPickups = 0;
    float totalPayment = 0.0;
    float maxPayment = 0.0;
    float minPayment = -1;
    char maxPaymentUsername[50] = "";
    char minPaymentUsername[50] = "";
    char username[50], address[100];
    float payment;

    char line[256];
    while (fgets(line, sizeof(line), invoiceFile)) {
        if (sscanf(line, "Username: %[^\n]", username) == 1) {
            fgets(line, sizeof(line), invoiceFile); // Read the address line
            sscanf(line, "Address: %[^\n]", address);
            fgets(line, sizeof(line), invoiceFile); // Read the payment line
            sscanf(line, "Payment: $%f", &payment);
            fgets(line, sizeof(line), invoiceFile); // Read the separator line

            totalPickups++;
            totalPayment += payment;

            if (payment > maxPayment) {
                maxPayment = payment;
                strcpy(maxPaymentUsername, username);
            }

            if (minPayment == -1 || payment < minPayment) {
                minPayment = payment;
                strcpy(minPaymentUsername, username);
            }
        }
    }

    fclose(invoiceFile);

    if (totalPickups == 0) {
        printf("\tNo pickup statistics available.\n");
        return;
    }

    float averagePayment = totalPayment / totalPickups;

    printf("Total number of pickups: %d\n", totalPickups);
    printf("Total payment received: $%.2f\n", totalPayment);
    printf("Average payment per pickup: $%.2f\n", averagePayment);
    printf("Maximum payment received: $%.2f by %s\n", maxPayment, maxPaymentUsername);
    printf("Minimum payment received: $%.2f by %s\n", minPayment, minPaymentUsername);
    showMainMenu();
}


void contactUs() {
    printf("\n\n\tContact Us\n");
    printf("\t----------\n");
    printf("\tFor any inquiries or Review, please reach out to us at:\n");
    printf("\tEmail: support@wastemanagement.com\n");
    printf("\tPhone: +8801305458548\n");
    printf("\tAddress: Ashulia model Town, Dhaka, Bangladesh\n");
    printf("\tWe are here to help you with any questions or concerns you may have.\n");
}
