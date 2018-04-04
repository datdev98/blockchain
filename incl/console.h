#ifndef CONSOLE_H
#define CONSOLE_H

#include <conio.h>
#include <cstdint>
#include "menu.h"
#include "blockchain.h"
#include "wallet.h"

using namespace std;

const uint16_t DIFICULTY = 4;
const double REWARD = 100;
const char ENTER = 13;
const char BACKSPACE = 8;

class Console
{
    private:
        bool _isWorking;
        Menu<Console> * _currentMenu;
        Menu<Console> _mainMenu;
        Menu<Console> _userMenu;
        Menu<Console> _listTransactionMenu;
        Menu<Console> _transactionInfoMenu;

        Blockchain _blockchain;
        Wallet _wallet;
    public:
        Console();
        bool IsWorking();
        void ShowCurrentMenu();
        void EnterCommand(uint16_t * command);
        void ExecuteCommand(uint16_t command);

        void Login();
            void MineBlock();
            void MakeTransaction();
            void CheckBalance();
            void GetUserAddress();
            void Logout();

        void ListTransaction();
            void ByBlockHash();
            void ByBlockIndex();

        void ShowTransactionInfo(); 
            void InfoByHash();
            void InfoByIndex();

        void Exit();
        void Back();

        void PrivateKeyPrompt(string *privateKey);        
};

#endif