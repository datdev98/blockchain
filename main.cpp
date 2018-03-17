#include <iostream>
#include <cstdlib>
#include "transaction.h"
#include "block.h"
#include "blockchain.h"
#include "wallet.h"
#include "sha256.h"

using namespace std;

void wallet_test();

int main()
{
    wallet_test();
    return 0;
}

void wallet_test()
{
    Blockchain blockchain(4, 100);
    
    Wallet walletDat(sha256("Nguyen Van Dat"), &blockchain);
    Wallet walletTuanAnh(sha256("Trinh Tuan Anh"), &blockchain);
    Wallet walletMo(sha256("Tong Thi Mo"), &blockchain);

    walletDat.AddPendingBlockToChain();
    walletDat.MakeTransaction(walletTuanAnh.GetAddress(), 20, "Hello");
    walletTuanAnh.MakeTransaction(walletMo.GetAddress(), 30, "How are you today");

    walletMo.AddPendingBlockToChain();

    cout << walletDat.GetBalance() << endl;
    cout << walletTuanAnh.GetBalance() << endl;
    cout << walletMo.GetBalance() << endl;

    // string transactionHash;
    // cout << "Enter transaction hash: " << endl;
    // cin >> transactionHash;
    // const Transaction * transaction = blockchain.GetTransaction(transactionHash);
    // if (transaction)
    //     cout << transaction -> GetTransactionInfo(sha256("Nguyen Van Dat"));
    // else
    //     cout << "Transaction not found";

    const Block * block = blockchain.GetBlock(3);
    cout << "GetBlock" << block -> GetHash() << endl;
    const Transaction * transaction = block -> GetTransaction(1);
    cout << "GetTransaction" << transaction -> GetHash() << endl;
    cout << "GetTransactionInfo: " << transaction -> GetTransactionInfo(sha256("Nguyen Van Dat"));
}