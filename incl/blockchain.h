#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <cstdint>
#include <vector>
#include "block.h"
#include "transaction.h"
#include "wallet.h"

class Wallet;

class Blockchain
{
    private:
        vector<Block> _chain;
        uint16_t _dificulty;
        Block * _pendingBlock;
        double _reward;

    public:
        Blockchain(uint16_t dificulty, double reward);
        const Block * GetLastBlock();
        const Block * GetBlock(const string blockHash) const;
        const Block * GetBlock(const uint32_t index) const;
        const Transaction * GetTransaction(const string transactionHash) const;
        friend double Wallet::GetBalance();
        friend void Wallet::MakeTransaction(string toAddress, double amount, string content);
        friend void Wallet::AddPendingBlockToChain();        
};

#endif