#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <ctime>
#include <sstream>

using namespace std;

class Transaction 
{
    private:
        time_t _time;
        string _fromAddress; // Dia chi bi mat cua nguoi gui
        string _toAddress; // Dia chi cong khai cua nguoi nhan
        double _amount;
        string _content;

        // Kiem tra nguoi dung co tham gia giao dich hay khong
        bool _IsParticipant(string userPrivateKey);

        // Tra ve dia chi cong khai cua nguoi gui
        string _GetPublicAddressOfSender();
    
    public:
        Transaction(string fromAddress, string toAddress, double amount, string content);
        string CalculateHash() const;
        string GetTransactionInfo(string userPrivateKey);
};

#endif