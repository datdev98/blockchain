#include "block.h"

Block::Block(string previousHash)
{
    time(&_time);
    _transacstions.clear();
    _previousHash = previousHash;
    _nonce = -1;
    _isMined = false;
    _hash = "";
}

void Block::AddTransaction(Transaction &transaction)
{
    if (!this->_isMined)
    {
        _transacstions.push_back(transaction);
        cout << "Transaction Added" << endl;
    } 
    else
    {
        cout << "Cannot add transaction to mined Block" << endl;
    }
}

string Block::GetHash() const
{
    return _hash;
}

void Block::Mine(uint16_t dificulty)
{
    if (!this->_isMined)
    {
        string zeroString = _CreateZeroString(dificulty);

        string currentHash;
        do
        {
            _nonce++;
            currentHash = this->_CalculateHash();
        } while (currentHash.substr(0, dificulty).compare(zeroString) != 0);

        this->_isMined = true;
        _hash = currentHash;

        cout << "Block mined: " << _hash << endl;
    }
}

string Block::_CreateZeroString(uint16_t numberOfZeros)
{
    stringstream ss;
    for (int i = 0; i < numberOfZeros; i++)
        ss << "0";
    return ss.str();
}

string Block::_CalculateHash()
{
    stringstream ss;
    ss << _nonce  << _time << _TransactionHashes() << _previousHash;
    return sha256(ss.str());
}

string Block::_TransactionHashes()
{
    stringstream ss;
    for (uint32_t i = 0; i < _transacstions.size(); i++)
    {
        ss << _transacstions[i].GetHash();
    }
    return ss.str();
}

const Transaction * Block::GetTransaction(const string transactionHash) const
{
    for (uint32_t i = 0; i < _transacstions.size(); i++)
    {
        if (_transacstions[i].GetHash().compare(transactionHash) == 0)
        {
            return &_transacstions[i];
        }
    }
}

