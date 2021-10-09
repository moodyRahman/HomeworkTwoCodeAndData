#include <iostream>
#include <fstream>
#include "sequence_map.h"

int main(int argc, char const *argv[])
{

    std::string line;
    std::ifstream db("rebase210.txt");

    if (db.is_open())
    {
        while (std::getline(db, line))
        {
            std::size_t pos = 0;
            
            bool first = true; 
            std::string enz_acro;
            std::string reco_seq;

            while ((pos = line.find("/")) != std::string::npos)
            {
                std::string token = line.substr(0, pos);
                if (token.length() > 0 && first)
                {
                    enz_acro = token;
                    first = false;
                }
                else if (token.length() > 0)
                {
                    SequenceMap(enz_acro, token);
                    std::cout << enz_acro << "    " << token << std::endl;
                }
                line.erase(0, pos + 1);
            }
        }
    }
    return 0;
}
