#include "blockchain.h"

Blockchain::Blockchain(uint16_t dificulty)
{
    _dificulty = dificulty;

    Block * genesisBlock = new Block("kklsjfaslfa");
    genesisBlock->Mine(_dificulty);
    _chain.emplace_back(*genesisBlock);
    
    _pendingBlock = new Block(GetLastBlock()->GetHash());
}

void Blockchain::AddPendingBlockToChain()
{
    _pendingBlock->Mine(_dificulty);
    _chain.push_back(*_pendingBlock);
    
    _pendingBlock = new Block(GetLastBlock()->GetHash());
}

void Blockchain::AddTransactionToPendingBlock(Transaction &transaction)
{
    _pendingBlock -> AddTransaction(transaction);
}

const Block * Blockchain::GetLastBlock()
{
    return &_chain.back();
}

const Block * Blockchain::GetBlock(string blockHash)
{
    for (uint32_t i = 0; i < _chain.size(); i++)
        if (_chain[i].GetHash().compare(blockHash) == 0)
            return &_chain[i];
}

const Block * Blockchain::GetBlock(uint32_t index)
{
    return &_chain[index];
}

const Transaction * Blockchain::GetTransaction(const string transactionHash) const
{
    for (uint32_t i = 0; i < _chain.size(); i++)
    {
        const Transaction * transaction = _chain[i].GetTransaction(transactionHash);
        if (transaction)
            return transaction;
    }
}