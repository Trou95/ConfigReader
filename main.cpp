#include <iostream>
#include <string>
#include "ConfigReader.h"

using namespace std;

int main()
{
    ConfigReader configreader("Settings.ini");
    configreader.ReadConfig();
   
    for (auto str : configreader.getConfig())
        cout << str->name << " - " << str->value << endl;

    configreader.addValue(string("FontFamily=Arial"));
    configreader.setValue("FontSize", 20);

    configreader.SaveFile();

    for (auto str : configreader.getConfig())
        cout << str->name << " - " << str->value << endl;

}

