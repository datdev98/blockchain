#include "wallet.h"

Wallet::Wallet(string privateKey, Blockchain * blockchain)
{
    _privateKey = privateKey;
    _address = sha256(_privateKey);
    _blockchain = blockchain;
}

const string Wallet::GetAddress()
{
    return _address;
}