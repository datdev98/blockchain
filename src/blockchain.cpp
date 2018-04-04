#include "wallet.h"
#include "blockchain.h"

Blockchain::Blockchain(uint16_t dificulty, double reward)
{
    _dificulty = dificulty;
    _reward = reward;

    cout << "Create genesis Block" << endl;
    Block * genesisBlock = new Block("");
    cout << "Mine genesis Block" << endl;
    genesisBlock->Mine(_dificulty);
    _chain.emplace_back(*genesisBlock);
    
    _pendingBlock = new Block(GetLastBlock()->GetHash());
}

const Block * Blockchain::GetLastBlock()
{
    return &_chain.back();
}

const Block * Blockchain::GetBlock(const string blockHash) const
{
    for (uint32_t i = 0; i < _chain.size(); i++)
        if (_chain[i].GetHash().compare(blockHash) == 0)
            return &_chain[i];
    return 0;
}

const Block * Blockchain::GetBlock(const uint32_t index) const
{
    if (index >= 0 && index < _chain.size())
        return &_chain.at(index);

    return 0;
}

const Transaction * Blockchain::GetTransaction(const string transactionHash) const
{
    for (uint32_t i = 0; i < _chain.size(); i++)
    {
        const Transaction * transaction = _chain[i].GetTransaction(transactionHash);
        if (transaction)
            return transaction;
    }
    const Transaction * transaction = _pendingBlock -> GetTransaction(transactionHash);
    if (transaction)
        return transaction;
    return 0;
}

double Wallet::GetBalance()
{
    double balance = 0;
    for (uint32_t i = 0; i < _blockchain -> _chain.size(); i++)
    {
        balance += _blockchain -> _chain[i].GetBlockAmount(_privateKey);
    }
    balance += _blockchain -> _pendingBlock -> GetBlockAmount(_privateKey);
    return balance;
}

void Wallet::MakeTransaction(string toAddress, double amount, string content)
{
    double balance = GetBalance();
    if (amount > balance)
    {
        cout << "Invalid transaction" << endl;
        return;
    } 
    else
    {
        cout << "Making transaction and adding it to Blockchain" << endl;
        Transaction transaction(_privateKey, toAddress, amount, content);
        _blockchain -> _pendingBlock -> AddTransaction(transaction);
        cout << "Transaction added: " << transaction.GetHash() << endl;
    }
}

void Wallet::AddPendingBlockToChain()
{
    cout << "Adding pending Block to Blockchain" << endl;
    cout << "Mine this Block..." << endl;
    _blockchain -> _pendingBlock -> Mine(_blockchain -> _dificulty);
    _blockchain -> _chain.push_back(*_blockchain -> _pendingBlock);

    cout  << "Pending Block added" << endl;
    cout << "Create new Block..." << endl;
    _blockchain -> _pendingBlock = new Block(_blockchain -> GetLastBlock()->GetHash());
    cout << "Adding reward for Miner..." << endl;
    Transaction rewardTransaction("", GetAddress(), _blockchain -> _reward, "Reward for mining Blockchain");
    _blockchain -> _pendingBlock -> AddTransaction(rewardTransaction);
    cout << "Reward transaction added: " << rewardTransaction.GetHash() << endl; 
    cout << "New Block is ready for adding Transactions" << endl;
}