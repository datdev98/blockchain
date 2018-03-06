#include "transaction.h"
#include "sha256.h"

Transaction::Transaction(string fromAddress, string toAddress, double amount, string content) 
{
    time(&_time);
    _fromAddress = fromAddress;
    _toAddress = toAddress;
    _amount = amount;
    _content = content;
}

string Transaction::CalculateHash() const
{
    stringstream ss;
    ss << _time << _fromAddress << _toAddress << _amount << _content;

    return sha256(ss.str());
}

string Transaction::GetTransactionInfo(string userPrivateKey)
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

bool Transaction::_IsParticipant(string userPrivateKey)
{
    return (userPrivateKey.compare(_fromAddress) == 0) || (sha256(userPrivateKey).compare(_toAddress) == 0);
}


string Transaction::_GetPublicAddressOfSender() {
    return sha256(_fromAddress);
}