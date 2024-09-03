#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rewards.h"
#include "unitTest.h"

extern RewardsTracker testRewardsTracker;

void validateTest(int actual, int expected, const char* testName) {
    if (actual == expected) {
        printf ("Test: %s PASSED (expected %d, got %d)\n\n", testName, expected, actual);
        fflush(stdout);
    }

    else {
        printf ("%s FAILED. Expected %d, got %d\n", testName, expected, actual);
        fflush(stdout);
    }
}

void runUnitTests() {
    testRewardsTracker.init();
    initRewardsTracker();

    printf("\nA customer should be able to be added to the database and their index in the database searchable by ID:\n");
    testRewardsTracker.addCustomer(1234, 10, "Gold");
    validateTest(testRewardsTracker.find(1234), 0, "Add first customer and search by ID");

    printf("After adding 4 more customers, the total number of customers should be counted accurately:\n");
    testRewardsTracker.addCustomer(1235, 10, "Silver");
    testRewardsTracker.addCustomer(1236, 10, "Bronze");
    testRewardsTracker.addCustomer(1237, 10, "Gold");
    testRewardsTracker.addCustomer(1238, 5, "Bronze");
    validateTest(*testRewardsTracker.customerCount, 5, "Total number of customers");

    printf("When making a $10 purchase, a Gold member with 10 points initially should end up with a total of 40 points:\n");
    testRewardsTracker.addPoints(1234, 10);
    validateTest(testRewardsTracker.customerDatabase[testRewardsTracker.find(1234)].rewardHistory, 10+10*3, "Total points for Gold member");

    printf("When making a $10 purchase, a Silver member with 10 points initially should end up with a total of 30 points:\n");
    testRewardsTracker.addPoints(1235, 10);
    validateTest(testRewardsTracker.customerDatabase[testRewardsTracker.find(1235)].rewardHistory, 10+10*2, "Total points for Silver member");

    printf("When making a $10 purchase, a Bronze member with 10 points initially should end up with a total of 20 points:\n");
    testRewardsTracker.addPoints(1236, 10);
    validateTest(testRewardsTracker.customerDatabase[testRewardsTracker.find(1236)].rewardHistory, 10+10*1, "Total points for Bronze member");

    printf("Processing a transaction greater than $10000 should produce an error. Reward history should remain unchanged:\n");
    testRewardsTracker.addPoints(1237, 10001);
    validateTest(testRewardsTracker.customerDatabase[testRewardsTracker.find(1237)].rewardHistory, 10, "Cannot exceed $10000 in one transaction");

    printf("Inputting an incorrect customer ID should produce an error. Reward history should remain unchanged:\n");
    testRewardsTracker.addPoints(9999, 10);
    validateTest(testRewardsTracker.customerDatabase[testRewardsTracker.find(1238)].rewardHistory, 5, "ID not found");
}