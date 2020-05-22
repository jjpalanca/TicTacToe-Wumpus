#ifndef INC_382_TILE_HPP
#define INC_382_TILE_HPP

#include <iostream>
#include <vector>

/*Programmers: Ariel Villaseñor and Jessmer Palanca*/

/* The "Tile" class is has 4 private data members. "endgame", "HunterOn", "special" and "BeenHere"
 * Our "Board" in "Wumpus.hpp" will be a vector of vectors. Each index will have a "Tile" object.
 * The "BeenHere" data member will be set to true if the "Hunter" has been on this tile and false otherwise.
 * The "special" data member will either be "W", "S", "P", "G" or "B". There is no special for the Hunter.
 * The "HunterOn" data member will be set to true if the "Hunter" is currently on the "Tile" object.
 * The "endgame" data member will be set to true if the user lands on the Wumpus or Pit Tile.
 * */
class Tile {
private:
    std::string special;
    bool endgame;
    bool HunterOn;
    bool BeenHere;

public:
    Tile() {
        BeenHere = false;
        HunterOn = false;
        endgame = false;
        special = " ";
    }

    void SetBeenHere() {
        BeenHere = true;
    }

    void PrintSpecial() const {
        if (HunterOn) {
            std::cout << "O ";
        } else if (BeenHere) {
            std::cout << special << " ";
        } else if (!BeenHere) {
            std::cout << "X ";
        }
    }

    std::string getSpecial() const {
        return special;
    }

    void PrintMessage() {
        if (!BeenHere) {
            SetBeenHere();
            if (special == "S") {
                std::cout << "I can hear the wind." << std::endl;
            } else if (special == "B") {
                std::cout << "I smell a murder most foul." << std::endl;
            } else if (special == "G") {
                std::cout << "I smell a murder most foul AND I can hear the wind!!!" << std::endl;
            } else if (special == "P") {
                std::cout << "You fell down a bottomless pit. You lose!" << std::endl;
                endgame = true;
            } else if (special == "W") {
                std::cout << "You walked into the Wumpus. You lose!" << std::endl;
                endgame = true;
            }
        }
    }

    void SetSpecial(std::string &str) {
        special = str;
    }

    bool EndGame() const {
        return endgame;
    }

    void SetHunterOn(bool IsOn) {
        HunterOn = IsOn;
    }

    bool ReturnHunterOn() {
        return HunterOn;
    }


};

#endif //INC_382_TILE_HPP