#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rewards.h"

#define MAX_CUSTOMERS 1000
#define CUSTOMER_DOES_NOT_EXIST -1

Customer* customerDatabase = NULL;
static int customerCount = 0;
static int customerIndex;
static int multiplier;


void initCustomerDatabase() {
    customerDatabase = (Customer*)malloc(MAX_CUSTOMERS * sizeof(Customer));
    if (customerDatabase == NULL) {
        fprintf (stderr, "Failed to allocate memory for customer database. \n");
        exit(1);
    }

    customerCount = 0;
}

void addCustomer(int id, int rewardHistory, const char* rewardTier) {
    if (customerCount >= MAX_CUSTOMERS) {
        fprintf (stderr, "Customer database is full. Unable to add more customers. \n");
        return;
    }

    // Save the customer data (ID, history of rewards points, and reward tier)
    customerDatabase[customerCount].id = id;
    customerDatabase[customerCount].rewardHistory = rewardHistory;
    strncpy(customerDatabase[customerCount].rewardTier, rewardTier, sizeof(customerDatabase[customerCount].rewardTier) - 1);
    customerDatabase[customerCount].rewardTier[sizeof(customerDatabase[customerCount].rewardTier) - 1] = '\0';

    customerCount++;
}

void printCustomerDatabase() {
    for (int i = 0; i < customerCount; ++i) {
        printf("Customer ID: %d\n", customerDatabase[i].id);
        printf("Reward Points: %d\n", customerDatabase[i].rewardHistory);
        printf("Reward Tier: %s\n\n", customerDatabase[i].rewardTier);
    }

    printf("No. of customers: %d\n", customerCount);
}

int findCustomer(int id) {
    for (int i = 0; i < customerCount; ++i) {
        if (customerDatabase[i].id == id) {
            return i;
        }
    }

    fprintf(stderr, "Invalid customer ID.\n");
    return CUSTOMER_DOES_NOT_EXIST;
}

void addPoints(int id, int amountSpent) {
    if (amountSpent > 10000) {
        fprintf (stderr, "Cannot exceed $10000 in one transaction.\n");
        return;
    }

    customerIndex = findCustomer(id);

    if (strcmp(customerDatabase[customerIndex].rewardTier, "Gold") == 0) {
        multiplier = 3;
    }
    else if (strcmp(customerDatabase[customerIndex].rewardTier, "Silver") == 0) {
        multiplier = 2;
    }
    else {
        multiplier = 1;
    }

    customerDatabase[customerIndex].rewardHistory += amountSpent * multiplier;
}

RewardsTracker testRewardsTracker = {
    .init = initCustomerDatabase,
    .addCustomer = addCustomer,
    .print = printCustomerDatabase,
    .find = findCustomer,
    .addPoints = addPoints,
};

void initRewardsTracker() {
    testRewardsTracker.customerDatabase = customerDatabase;
    testRewardsTracker.customerCount = &customerCount;
}