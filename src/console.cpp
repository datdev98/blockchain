#include "console.h"

Console::Console(): _blockchain(DIFICULTY, REWARD), _wallet("", &_blockchain)
{
    _isWorking = true;

    _mainMenu.SetMenuName("Main");
    _mainMenu.AddCommand("Login Wallet", this, &Console::Login);
    _mainMenu.AddCommand("Show Transactions of a Block", this, &Console::ListTransaction);
    _mainMenu.AddCommand("Show Transaction information", this, &Console::ShowTransactionInfo);    
    _mainMenu.AddCommand("Exit", this, &Console::Exit);    

    _userMenu.SetMenuName("User Wallet");
    _userMenu.AddCommand("Mine Block", this, &Console::MineBlock);
    _userMenu.AddCommand("Make Transaction", this, &Console::MakeTransaction);
    _userMenu.AddCommand("Check Balance", this, &Console::CheckBalance);
    _userMenu.AddCommand("Show public address", this, &Console::GetUserAddress);
    _userMenu.AddCommand("Logout Wallet", this, &Console::Logout);    

    _listTransactionMenu.SetMenuName("List Transactiontions");
    _listTransactionMenu.AddCommand("By Block hash", this, &Console::ByBlockHash);
    _listTransactionMenu.AddCommand("By Block index", this, &Console::ByBlockIndex);
    _listTransactionMenu.AddCommand("Back", this, Console::Back);

    _transactionInfoMenu.SetMenuName("Transaction info");
    _transactionInfoMenu.AddCommand("By hash", this, &Console::InfoByHash);
    _transactionInfoMenu.AddCommand("By index", this, &Console::InfoByIndex);
    _transactionInfoMenu.AddCommand("Back", this, &Console::Back);

    _currentMenu = & _mainMenu;

    system("color 0a");
    system("title Blockchain");
    system("mode con:cols=90 lines=20");
}

void Console::Exit()
{
    _isWorking = false;
}

void Console::Back()
{
    _currentMenu = &_mainMenu;
}

void Console::Login()
{
    string privateKey;
    PrivateKeyPrompt(&privateKey);
    if (privateKey == "")
    {
        cout << "Private key cannot empty!" << endl;
        return;
    }
    _wallet = Wallet(privateKey, &_blockchain);
    _currentMenu = & _userMenu;
}

void Console::MineBlock()
{
    _wallet.AddPendingBlockToChain();
}

void Console::MakeTransaction()
{
    string toAddress;
    double amount;
    string content;

    cout << "Enter to address: "; cin.clear(); fflush(stdin); getline(cin, toAddress);
    cout << "Enter amount: "; cin >> amount;
    cout << "Enter content: "; cin.clear(); fflush(stdin); getline(cin, content);

    _wallet.MakeTransaction(toAddress, amount, content);
}

void Console::CheckBalance()
{
    cout << "Your balance is: " << _wallet.GetBalance() << endl;
}

void Console::GetUserAddress()
{
    cout << "User public address is: " << _wallet.GetAddress() << endl;
}

void Console::ListTransaction()
{
    _currentMenu = &_listTransactionMenu;
}

void Console::ByBlockHash()
{
    string blockHash;
    cout << "Enter Block hash: "; cin.clear(); fflush(stdin); getline(cin, blockHash);
    const Block * block = _blockchain.GetBlock(blockHash);
    if (block) 
    {
        block -> ListTransactions();
    }
    else 
    {
        cout << "Block does not exsist" << endl;
    }
}

void Console::ByBlockIndex()
{
    uint32_t blockIndex;
    cout << "Enter Block index: "; cin >> blockIndex;
    const Block * block = _blockchain.GetBlock(blockIndex);
    if (block) 
    {
        block -> ListTransactions();
    }
    else 
    {
        cout << "Block does not exsist" << endl;
    }
}

void Console::ShowTransactionInfo()
{
    _currentMenu = &_transactionInfoMenu;
}

void Console::InfoByHash()
{
    string transactionHash;
    string privateKey;
    cout << "Enter transaction hash: "; cin.clear(); fflush(stdin); getline(cin, transactionHash);
    PrivateKeyPrompt(&privateKey);
    const Transaction * transaction = _blockchain.GetTransaction(transactionHash);
    if (transaction)
    {
        cout <<  transaction -> GetTransactionInfo(privateKey);
    }
    else
    {
        cout << "Transaction does not exsist" << endl;
    }
}

void Console::InfoByIndex()
{
    string privateKey;
    PrivateKeyPrompt(&privateKey);

    uint32_t blockIndex;
    cout << "Enter block index: "; cin >> blockIndex;
    const Block * block = _blockchain.GetBlock(blockIndex);
    if (block)
    {
        uint32_t transactionIndex;
        cout << "Enter transaction index: "; cin >> transactionIndex;
        const Transaction * transaction = block -> GetTransaction(transactionIndex);
        if (transaction)
        {
            cout <<  transaction -> GetTransactionInfo(privateKey);
        }
        else
        {
            cout << "Transaction does not exsist" << endl;
        }
    }
    else
    {
        cout << "Block does not exsist!" << endl;
    }
}

void Console::Logout()
{
    _wallet = Wallet("", &_blockchain);
    _currentMenu = & _mainMenu;
}

void Console::PrivateKeyPrompt(string *privateKey)
{
    cout << "Enter private key: ";
    *privateKey = "";
    char ch;
    ch = getch();
    while (ch != ENTER)
    {
        if (ch == BACKSPACE)
        {
            if (privateKey -> length() != 0)
            {
                cout << "\b \b";
                privateKey -> resize(privateKey -> length() - 1);
            }
        }
        else 
        {
            privateKey -> push_back(ch);
            cout << "*";
        }
        ch = getch();
    }
    cout << endl;
}

bool Console::IsWorking()
{     
    return _isWorking;
}

void Console::ShowCurrentMenu()
{
    _currentMenu -> Show();
}

void Console::EnterCommand(uint16_t * command)
{
    *command = -1;
    uint16_t temp = 0;
    cout << "Enter your command: ";
    cin >> temp;
    if (cin.fail())
    {
        cin.clear();
        fflush(stdin);
    }
    else
    {
        *command = temp;
    }   
}

void Console::ExecuteCommand(uint16_t command)
{
    _currentMenu -> ExecuteCommand(command);
}