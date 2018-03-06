#include <iostream>
#include "transaction.h"
#include "sha256.h"

using namespace std;

int transaction_test();

int main()
{
    transaction_test();
    return 0;
}

int transaction_test()
{
    string senderPrivateAddress = "asfasfasasfa";
    string senderPublicAddress = sha256(senderPrivateAddress);
    string receiverPrivateAddress = "asfaaoiekksfas";
    string receiverPublicAddress = sha256(receiverPrivateAddress);

    Transaction transaction(senderPrivateAddress, receiverPublicAddress, 1000, "Hello");
    
    cout << "Hash: " << transaction.CalculateHash() << endl << endl;
    cout << "Sender get transaction info: " << transaction.GetTransactionInfo(senderPrivateAddress) << endl;
    cout << "Receiver get transaction info: " << transaction.GetTransactionInfo(receiverPrivateAddress) << endl;
    cout << "Guess get transaction info: " << transaction.GetTransactionInfo(sha256("askfhaasfqiweup")) << endl;
    
    return 0;
}