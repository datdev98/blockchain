#ifndef WALLET_H
#define WALLET_H

#include "sha256.h"
#include "transaction.h"

using namespace std;

class Blockchain;

class Wallet
{
    private:
        string _privateKey;
        string _address;
        Blockchain * _blockchain;
    public:
        Wallet(string privateKey, Blockchain *blockchain);
        const string GetAddress();
        double GetBalance();
        void MakeTransaction(string toAddress, double amount, string content);
        void AddPendingBlockToChain();
};

#endif