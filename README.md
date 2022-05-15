 **ConfigReader for read/write configurations to files**

How to use
-

Create an instance with filepath argument

 

    ConfigReader configreader("filepath/filename");
   Example:
   

    ConfigReader configreader("C:\\Users\user\\Desktop\\Settings.ini");

**Reading File**

    configreader.ReadConfig();

**Saving File**

    configreader.SaveFile();
   
   **Get Value**
   

    const char* ptr = configreader.getValue("value");

**Set Value**

    configreader.setValue("FontSize", 20);

**Add Value**

    configreader.addValue(string("FontFamily=Arial"));

You can check main file for details

**Comment Line**
Its also supports comments (# Default check header file to change it) line in config file you can leave comment with it above 

> #Its comment line
> 
> FontSize=20
