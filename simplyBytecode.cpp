// SimplyBytecode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>

namespace Bytecode
{
    namespace Lex
    {
        int isKey(std::string arg)
        {
            if (arg == "int")
            {
                return 1;
            }
            else if (arg == "long")
            {
                return 2;
            }
            return 0;
        }

        bool isSwitch(char arg)
        {
           /* if (strcmp(arg, "=") == 0 || strcmp(arg, "+") == 0)
            {
                return 1;
            }
            return 0;*/
            if (arg == '=' || arg == '+')
            {
                return 1;
            }
            return 0;
        }
       

        std::vector<std::string> sepKeys(std::string line)
        {
            std::vector<std::string> keys;
            int rightIndex = line.length();
            int leftIndex = 0;

            std::string loadedChars;
            while (leftIndex <= rightIndex)
            {
                char _key = line[leftIndex];    
                if (isSwitch(_key))
                {
                    keys.push_back(loadedChars);
                    loadedChars = "";
                }
                else if (isKey(loadedChars.c_str()))
                {
                    keys.push_back(loadedChars);
                    loadedChars = "";
                }
                else
                {
                    loadedChars += _key;
                }

                leftIndex++;
            }
            keys.push_back(loadedChars);
            loadedChars.clear();

  

            return keys;
        }

    }

    class stackItem
    {
    public:
        const char* type; //INT, LONG
        const char* value; //5, 5.2
    };

    namespace Stack
    {
        int returnTypeIndex(std::vector<stackItem> stack, const char* type)
        {
            int typeindex = 1;
            for (stackItem sI : stack)
            {
                if (strcmp(sI.type, type) == 0)
                {
                    typeindex++;
                }
            }
            return typeindex;
        }
    }
    int returnLType(std::string ltype)
    {
        if (ltype.find("INTSTORE") != std::string::npos)
        {
            return 1;
        }
        if (ltype.find("LONGSTORE") != std::string::npos)
        {
            return 2;
        }
        return 0;
    }
    void writeLine(std::ofstream& file, std::string line, std::vector<stackItem>& stack)
    {
        std::vector<std::string> bytes;
        std::vector<std::string> keys = Lex::sepKeys(line);

        for (int i = 0; i < keys.size(); i++)
        {
            std::string key = keys[i];
            std::string toPush;
            int last_type = 0;
            if (bytes.size() > 0)
            {
                last_type = returnLType(bytes[bytes.size() - 1]);
            }
            if (Lex::isKey(key))
            {
                switch (Lex::isKey(key))
                {
                case 1:
                    //int
                    /*toPush = (char*)malloc(1 + strlen("INTSTORE_") + strlen((char*)Stack::returnTypeIndex(stack, "INT")));
                    strcpy(toPush, "INTSTORE_");
                    strcat(toPush, (char*)Stack::returnTypeIndex(stack, "INT"));*/
                    toPush = "INTSTORE_" + std::to_string(Stack::returnTypeIndex(stack, "INT"));
                    bytes.push_back(toPush);
                    break;
                case 2:
                    //long
                    toPush = "LONGSTORE_" + std::to_string(Stack::returnTypeIndex(stack, "LONG"));
                    bytes.push_back(toPush);
                    break;
                }
            }
            else if (last_type)
            {
                switch (last_type)
                {
                case 1:
                    //int
                    toPush = "INTCONST_" + key + "_" + keys[i + 1];
                    bytes.push_back(toPush);
                    break;
                case 2:
                    toPush = "LONGCONST_" + key + "_" + keys[i + 1];
                    bytes.push_back(toPush);
                    break;
                }
            }
        }

        std::cout << "Bytes Size: " << bytes.size() << std::endl;
        for (std::string c : bytes)
        {
            std::cout << "Byte: " << c << std::endl;
        }
    }
}


int main()
{

    /*
    
    int a = 5

    INTSTORE_1
    INTCONST_a_5

    long b = 6
    
    */

    std::cout << "Filename?" << std::endl;
    std::string filename;
    std::cin >> filename; //cba rn
    std::ifstream myfile(filename);
    /*if (!myfile.is_open())
    {
        return 1;
    }*/

    std::string linex;
    std::vector<std::string> lines = { "int a = 5", "long b = 7"};
    /*while(std::getline(myfile, linex))
    {
        lines.push_back(linex);
    }*/

    std::ofstream bytc(filename + "_bytecode.sb");

    std::vector<Bytecode::stackItem> stack;
    for (std::string line : lines)
    {
        std::cout << "line: " << line;
        Bytecode::writeLine(bytc, line, stack);
    }
   

}
