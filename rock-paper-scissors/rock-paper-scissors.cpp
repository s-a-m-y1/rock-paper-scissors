#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;

// ================= Enums =================
enum En_Choice_User_Computer { Stone = 1, Paper = 2, Scissors = 3 };
enum En_Winner_User_OR_Computer { player_One_winner = 1, computer_winner = 2, draw = 3 };

// ================= Structs =================
struct St_Game_Rounds
{
    En_Choice_User_Computer Player_One;
    En_Choice_User_Computer Computer;
    En_Winner_User_OR_Computer Drawing;
};

struct Game_Result
{
    short Player_One = 0;
    short Computer = 0;
    short Drawing = 0;
    short GameRound = 0;
    string Final_Winner;
};

// ================= Helpers =================
int Random_Computer(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

En_Choice_User_Computer Choose_a_computer()
{
    return (En_Choice_User_Computer)Random_Computer(1, 3);
}

int Read_player()
{
    int number;
    do
    {
        cout << "How many rounds (1 to 10)? ";
        cin >> number;
    } while (number < 1 || number > 10);
    return number;
}

En_Choice_User_Computer choice_player_one()
{
    int player_One;
    do
    {
        cout << "Stone[1] Paper[2] Scissors[3]? ";
        cin >> player_One;
    } while (player_One < 1 || player_One > 3);

    return (En_Choice_User_Computer)player_One;
}

string choiceToString(En_Choice_User_Computer choice)
{
    switch (choice)
    {
    case Stone: return "Stone";
    case Paper: return "Paper";
    case Scissors: return "Scissors";
    default: return "Unknown";
    }
}

// ================= Game Logic =================
En_Winner_User_OR_Computer Check_PlayerOne_Vs_Computer(St_Game_Rounds Games_Winners, Game_Result& result)
{
    if (Games_Winners.Player_One == Games_Winners.Computer)
    {
        system("color 6f");
        result.Drawing++;
        return draw;
    }

    if (
        (Games_Winners.Player_One == Paper && Games_Winners.Computer == Stone) ||
        (Games_Winners.Player_One == Stone && Games_Winners.Computer == Scissors) ||
        (Games_Winners.Player_One == Scissors && Games_Winners.Computer == Paper)
    )
    {
        system("color 2f");
        Beep(1000, 200);
        result.Player_One++;
        return player_One_winner;
    }
    else
    {
        system("color 4f");
        Beep(400, 400);
        result.Computer++;
        return computer_winner;
    }
}

void Print_Round(int roundNum)
{
    cout << "_____________ Round [" << roundNum << "] ________________\n";
}

void print_the_game_rounds_1gmae(const St_Game_Rounds& round)
{
    cout << "Player One Choice : " << choiceToString(round.Player_One) << endl;
    cout << "Computer Choice   : " << choiceToString(round.Computer) << endl;
    cout << "Round Winner      : ";

    switch (round.Drawing)
    {
    case En_Winner_User_OR_Computer::player_One_winner:
        cout << "Player One (Winner)";
        break;
    case En_Winner_User_OR_Computer::computer_winner:
        cout << "Computer (Winner)";
        break;
    case En_Winner_User_OR_Computer::draw:
        cout << "Draw";
        break;
    }

    cout << endl << "______________________________________________________" << endl;
}

void Print_result(Game_Result result)
{
    cout << "\n___________________________________________________\n";
    cout << "\t\t+++ GAME OVER +++\n";
    cout << "___________________________________________________\n";
    cout << "[__________________[GAME RESULT]_____________________]\n";
    cout << "Total Rounds     : " << result.GameRound << endl;
    cout << "Player Wins      : " << result.Player_One << endl;
    cout << "Computer Wins    : " << result.Computer << endl;
    cout << "Draws            : " << result.Drawing << endl;
    cout << "Final Winner     : " << result.Final_Winner << endl;
    cout << "_____________________________________________________\n\n";
}

bool checkPLater_Aganie()
{
    char Again;
    do
    {
        cout << "Do you want to play again (Y/N)? ";
        cin >> Again;
    } while (Again != 'y' && Again != 'Y' && Again != 'n' && Again != 'N');
    return (Again == 'y' || Again == 'Y');
}

// ================= Game Flow =================
void play_game()
{
    do
    {
        int roundsCount = Read_player();
        Game_Result result = {};

        for (int i = 1; i <= roundsCount; i++)
        {
            Print_Round(i);

            St_Game_Rounds round;
            round.Player_One = choice_player_one();
            round.Computer = Choose_a_computer();
            round.Drawing = Check_PlayerOne_Vs_Computer(round, result);
            result.GameRound++;

            print_the_game_rounds_1gmae(round);
        }

        if (result.Player_One > result.Computer)
            result.Final_Winner = "Player One";
        else if (result.Player_One < result.Computer)
            result.Final_Winner = "Computer";
        else
            result.Final_Winner = "Draw";

        Print_result(result);

    } while (checkPLater_Aganie());
}

// ================= MAIN =================
int main()
{
    srand((unsigned)time(NULL)); // تهيئة العشوائية
    play_game();                 // تشغيل اللعبة
    return 0;
}
