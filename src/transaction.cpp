#include "transaction.h"

Transaction::Transaction(string fromAddress, string toAddress, double amount, string content) 
{
    time(&_time);
    _fromAddress = fromAddress;
    _toAddress = toAddress;
    _amount = amount;
    _content = content;
    _hash = _CalculateHash();
}

string Transaction::_CalculateHash()
{
    stringstream ss;
    ss << _time << _fromAddress << _toAddress << _amount << _content;

    return sha256(ss.str());
}

string Transaction::GetHash() const
{
    return _hash;
}

string Transaction::GetTransactionInfo(string userPrivateKey) const
{
    stringstream ss;
    ss << asctime(gmtime(&_time))
        << "From: " << _GetPublicAddressOfSender() << endl 
        << "To: " << _toAddress << endl
        << "Amount: " << _amount << endl;
    if (_IsParticipant(userPrivateKey))
    {
        ss << "Content: " << _content << endl;
    }

    return ss.str();
}

bool Transaction::_IsParticipant(string userPrivateKey) const
{
    return (userPrivateKey.compare(_fromAddress) == 0) || (sha256(userPrivateKey).compare(_toAddress) == 0);
}


string Transaction::_GetPublicAddressOfSender() const
{
    return sha256(_fromAddress);
}

double Transaction::GetTransactionAmount(string userPrivateKey) const
{
    if (_IsSender(userPrivateKey))
        return - _amount;
    if (_IsReceiver(userPrivateKey))
        return + _amount;
    return 0;
}

bool Transaction::_IsSender(string userPrivateKey) const
{
    return _fromAddress.compare(userPrivateKey) == 0;
}

bool Transaction::_IsReceiver(string userPrivateKey) const
{
    return _toAddress.compare(sha256(userPrivateKey)) == 0;
}