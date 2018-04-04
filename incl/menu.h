#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>

using namespace std;

template<class Commands>
class Menu
{
    typedef void (Commands::*Function)(void);

    private:
        string _menuName;
        vector<string> _functionName;
        vector<Function> _function;
        vector<Commands*> _instances;
        bool _IncorrectCommand(uint16_t command);
    public:
        Menu();
        void SetMenuName(string menuName);
        void AddCommand(string functionName, Commands * instance, Function function);
        void Show();
        void ExecuteCommand(uint16_t command);     
};

template<class Commands>
Menu<Commands>::Menu()
{
    
}

template<class Commands>
void Menu<Commands>::SetMenuName(string menuName)
{
    _menuName = menuName;
}

template<class Commands>
void Menu<Commands>::AddCommand(string functionName, Commands *instance, Function function)
{
    _functionName.push_back(functionName);
    _instances.push_back(instance);
    _function.push_back(function);
}

template<class Commands>
void Menu<Commands>::Show()
{
    cout << "\t" << _menuName << endl;
    for (uint16_t i = 0; i < _functionName.size(); i++)
    {
        cout << i << ". " << _functionName[i] << endl;
    }
}

template<class Commands>
void Menu<Commands>::ExecuteCommand(uint16_t command)
{
    if (_IncorrectCommand(command))
    {
        cout << "Incorrect command" << endl;
        return;
    }
    (_instances[command]->*_function[command])();
}

template<class Commands>
bool Menu<Commands>::_IncorrectCommand(uint16_t command)
{
    return command < 0 || command >= _functionName.size();
}

#endif