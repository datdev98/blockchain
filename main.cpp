#include <iostream>
#include "transaction.h"
#include "block.h"
#include "sha256.h"

using namespace std;

int transaction_test();
int block_test();

int main()
{
    block_test();
    return 0;
}

int transaction_test()
{
    string senderPrivateAddress = "asfasfasasfa";
    string senderPublicAddress = sha256(senderPrivateAddress);
    string receiverPrivateAddress = "asfaaoiekksfas";
    string receiverPublicAddress = sha256(receiverPrivateAddress);

    Transaction transaction(senderPrivateAddress, receiverPublicAddress, 1000, "Hello");
    
    cout << "Hash: " << transaction.GetHash() << endl << endl;
    cout << "Sender get transaction info: " << transaction.GetTransactionInfo(senderPrivateAddress) << endl;
    cout << "Receiver get transaction info: " << transaction.GetTransactionInfo(receiverPrivateAddress) << endl;
    cout << "Guess get transaction info: " << transaction.GetTransactionInfo(sha256("askfhaasfqiweup")) << endl;
    
    return 0;
}

int block_test()
{
    Block block(sha256("iouaopsifa9fuasfasfasf"));
    Transaction transaction1("asdfasdfaasfasdfa", sha256("qwuerhrewerasdfas"), 1000, "First Transaction");
    Transaction transaction2("asdfwewqr", sha256("sdwaasdfsaf"), 1300, "Second Transaction");
    Transaction transaction3("llelleklnlz", sha256("sdwaasdqwewaf"), 2000, "Third Transaction");

    block.AddTransaction(transaction1);
    block.AddTransaction(transaction2);

    cout << "Before mining hash: " << block.GetHash() << endl;
    
    block.Mine(3);

    cout << "After mining hash: " << block.GetHash() << endl;

    block.AddTransaction(transaction3);  

    Transaction * aTransaction = block.GetTransaction(transaction1.GetHash());
    cout << "Transaction 1 info" << aTransaction->GetTransactionInfo("");

    Transaction * anotherTransaction = block.GetTransaction(transaction3.GetHash());
    if (!anotherTransaction)
    {
        cout << "Transaction does not exsist" << endl;
    }

    return 0;  
}