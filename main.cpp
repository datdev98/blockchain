#include <iostream>
#include "console.h"

using namespace std;

int main()
{
    Console console;

    system("pause");
    system("cls");

    uint16_t command;

    while (console.IsWorking())
    {
        console.ShowCurrentMenu();
        cout  << "_______________________________" << endl;
        console.EnterCommand(&command);
        console.ExecuteCommand(command);
        system("pause");
        system("cls");
    }

    return 0;
}