#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <cstdint>
#include <vector>
#include "block.h"
#include "transaction.h"


class Blockchain
{
    private:
        vector<Block> _chain;
        uint16_t _dificulty;
        Block * _pendingBlock;

    public:
        Blockchain(uint16_t dificulty);
        void AddPendingBlockToChain();
        void AddTransactionToPendingBlock(Transaction &transaction);
        const Block * GetLastBlock();
        const Block * GetBlock(string blockHash);
        const Block * GetBlock(uint32_t index);
        const Transaction * GetTransaction(const string transactionHash) const;
};

#endif