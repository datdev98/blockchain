#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <ctime>
#include "transaction.h"
#include "sha256.h"

using namespace std;


class Block
{
    private:
        uint64_t _nonce;
        vector<Transaction> _transacstions; // Danh sach cac giao dich
        time_t _time; // Thoi gian doi tuong duoc tao ra
        string _hash;
        string _previousHash;
        bool _isMined; // Da thuc hien thanh con phuong thuc MineBlock hay chua

        string _CalculateHash();
        string _TransactionHashes();

        static string _CreateZeroString(uint16_t numberOfZeros);

    public:
        Block(string previousHash);
        void AddTransaction(Transaction &transacstion);
        string GetHash() const;
        void Mine(uint16_t dificulty);
        const Transaction * GetTransaction(const string transactionHash) const;
};

#endif