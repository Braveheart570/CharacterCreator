#include <iostream>
#include <string>
#include <vector>
#include <array>

using std::vector;
using std::string;

#pragma region definitions

/* this variable exists because I can't find 
a way to get the size of a const int array.*/
const int numberOfStats = 6; 

    const string availableStats[numberOfStats] = {
        "STRENGTH",
        "DEXTERITY",
        "CONSTITUTION",
        "WISDOM",
        "INTELLIGENCE",
        "CHARISMA"
    };

    const string availableRaces[5] = {
        "human",
        "dwarf",
        "elf",
        "orc",
        "halfling"
    };

    const string availableClasses[5] = {
        "fighter",
        "rouge",
        "mage",
        "ranger",
        "cleric"
    };

    const int humanStats[] = {
        0, //str
        0, //dex
        1, //const
        2, //wis
        0, //int
        0, //charm
    };

    const int dwarfStats[] = {
        2, //str
        0, //dex
        1, //const
        0, //wis
        0, //int
        0, //charm
    };

    const int elfStats[] = {
        0, //str
        2, //dex
        0, //const
        0, //wis
        1, //int
        0, //charm
    };

    const int orcStats[] = {
        2, //str
        0, //dex
        1, //const
        0, //wis
        0, //int
        0, //charm
    };

    const int halflingStats[] = {
        0, //str
        1, //dex
        0, //const
        0, //wis
        0, //int
        2, //charm
    };

#pragma endregion



class Stat {
public:
    
    Stat(string statIn, int levelIn) {
        mStatType = statIn;
        mLevel = levelIn;
    }
    void printStat() {
        int spaces = 16;
        std::cout << mStatType << ":" << string(spaces - mStatType.length()+1, ' ') << mLevel << std::endl;
    }

    int getLevel() const {
        return mLevel;
    }

    void setLevel(int inLevel) {
        mLevel = inLevel;
    }

    string getStatType() const {
        return mStatType;
    }

private:
    string mStatType = "None";
    int mLevel = 0;
};



class Player {
public:
    Player(string& inName, string& inRace, string& inClass) {
        mName = inName;
        mRace = inRace;
        mCharacterClass = inClass;

        // getting race stat modifiers
        if (mRace == availableRaces[0]) {
            std::copy(std::begin(humanStats), std::end(humanStats), std::begin(mStatBonuses));
        }
        else if (mRace == availableRaces[1]) {
            std::copy(std::begin(dwarfStats), std::end(dwarfStats), std::begin(mStatBonuses));
        }
        else if (mRace == availableRaces[2]) {
            std::copy(std::begin(elfStats), std::end(elfStats), std::begin(mStatBonuses));
        }
        else if (mRace == availableRaces[3]) {
            std::copy(std::begin(orcStats), std::end(orcStats), std::begin(mStatBonuses));
        }
        else if (mRace == availableRaces[4]) {
            std::copy(std::begin(halflingStats), std::end(halflingStats), std::begin(mStatBonuses));
        }


    }

    void PrintStats() {

        string title = mName + " the " + mRace + " " + mCharacterClass + "!";

        std::cout << "\n" << string(title.size(), '-') << std::endl;
        std::cout << title << std::endl;
        std::cout << string(title.size(), '-') << "\n" << std::endl;


        for (int c = 0; c < std::end(mBaseStats) - std::begin(mBaseStats); c++) {

            string toPrint = mBaseStats[c].getStatType() + ":" + string(16 - mBaseStats[c].getStatType().length() + 1, ' ') + std::to_string(mBaseStats[c].getLevel() + mStatBonuses[c]) ;
            std::cout << toPrint << std::endl;
        }
    }


    void setStat(int index, int level) {
        mBaseStats[index].setLevel(level);
    }

    Stat getStat(int index) const {
        return mBaseStats[index];
    }


private:

    string mName = "none";
    string mRace = "none";
    string mCharacterClass = "none";

    Stat mBaseStats[6] = {
        Stat(availableStats[0], 0),
        Stat(availableStats[1], 0),
        Stat(availableStats[2], 0),
        Stat(availableStats[3], 0),
        Stat(availableStats[4], 0),
        Stat(availableStats[5], 0),
    };

    int mStatBonuses[6] = { 0,0,0,0,0,0 };

};




void printRaceBonuses(const int raceStats[]);





int main()
{

    string nameTemp = "";
    string raceTemp = "";
    string classTemp = "";

    while (true) {


        string intro = "Create your Character!";
        std::cout << string(intro.size(), '-') << std::endl;
        std::cout << intro << std::endl;
        std::cout << string(intro.size(), '-') << std::endl;


        // --- Name --- //
        while (true) {
            std::cout << "\n Name:\t";
            
            //std::getline(std::cin, nameTemp); // this line was being weird on the second time the program loops
            std::cin >> nameTemp;
            if (nameTemp != "" && nameTemp.size() < 10) {
                break;
            }
            else {
                std::cout << "\n Invalid Name\n" << std::endl;
            }
        }

        // --- Race --- //
        bool validRace = false;

        std::cout << "\nChoose your race:\n\n";
        for (int c = 0; c < std::size(availableRaces); c++) {
            std::cout << availableRaces[c] << string(20-availableRaces[c].length(), ' ');
            //get related race atributes
            switch (c) {
            case 0:
                printRaceBonuses(humanStats);
                break;
            case 1:
                printRaceBonuses(dwarfStats);
                break;
            case 2:
                printRaceBonuses(elfStats);
                break;
            case 3:
                printRaceBonuses(orcStats);
                break;
            case 4:
                printRaceBonuses(halflingStats);
                break;
            }
            std::cout << "\n";
            

        }

        while (!validRace) {

            
            std::cout << "\nInput your race:    ";

            std::cin >> raceTemp;

            if (raceTemp == "") {
                std::cout << "Please input a valid Race" << std::endl;
                continue;
            }

            for (int c = 0; c < std::size(availableRaces); c++) {
                if (raceTemp == availableRaces[c]) {
                    validRace = true;
                    break;
                }
            }

            if (validRace == false) {
                std::cout << "Please input a valid Race" << std::endl;
            }


        }

        // --- Class --- //
        bool validClass = false;

        std::cout << "\nChoose your class:\n\n";
        for (int c = 0; c < std::size(availableClasses); c++) {
            std::cout << availableClasses[c] << std::endl;
        }

        while (!validClass) {

            
            std::cout << "\nInput your class:   ";

            std::cin >> classTemp;
            

            if (classTemp == "") {
                std::cout << "Please input a valid class" << std::endl;
                continue;
            }

            for (int c = 0; c < std::size(availableClasses); c++) {
                if (classTemp == availableClasses[c]) {
                    validClass = true;
                    break;
                }
            }

            if (validClass == false) {
                std::cout << "Please input a valid class" << std::endl;
            }


        }
        std::cout << "\n";


        //--- create player object ---//
        Player player(nameTemp, raceTemp, classTemp);

        
        //--- get player stats ---//
        for (int c = 0; c < numberOfStats; c++) {
            int level = 0;
            int StatInputSpace = 15;
            while (true) {

                std::cout << "Input your " << player.getStat(c).getStatType() << " stat:" << string(StatInputSpace - player.getStat(c).getStatType().length(), ' ');
                std::cin >> level;

                while (!std::cin.good()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "\nInvalid Input.\n Input your " << player.getStat(c).getStatType() << " stat:" << string(StatInputSpace- player.getStat(c).getStatType().length(), ' ');
                    std::cin >> level;

                }

                if (level <= 18 && level >= 8) {
                    break;
                }

                std::cout << "\nLevel must be between 8-18.\n";

            }

            player.setStat(c, level);
        }

        //---final output---//

        system("CLS");
        player.PrintStats();

        std::cout << "\n" << std::endl;

        //create new character prompt
        string response = "";
        while (true) {
            std::cout << "create another character? y/n" << std::endl;
            
            std::cin >> response;

            if (response == "n" || response == "y") {
                break;
            }
        }
        
        //exit condition
        if (response == "n") {
            break;
        }

        system("CLS");

    }
}

void printRaceBonuses(const int raceStats[]) {

    for (int c = 0; c < numberOfStats; c++) {
        if (raceStats[c] == 0) {
            continue;
        }

        std::cout << availableStats[c] << " +" << raceStats[c] << string(16 - availableStats[c].length(), ' ');


    }
}