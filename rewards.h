#ifndef REWARDS_H
#define REWARDS_H

typedef struct {
    int id;
    int rewardHistory;
    char rewardTier[10];
} Customer;

typedef struct {
    void(*init)();
    void(*addCustomer)(int id, int rewardHistory, const char* rewardTier);
    void(*print)();
    int(*find)(int id);
    void(*addPoints)(int id, int amountSpent);
    Customer* customerDatabase;
    int* customerCount;
} RewardsTracker;

extern RewardsTracker testRewardsTracker;
void initRewardsTracker();

#endif //REWARDS_H