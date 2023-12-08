#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

class Player{
public:
    Player() {

    }

    string name;
    int score;
    int gamesplayed;
    int easywin;
    int hardwin;

    Player(const string& playerName): name(playerName),score(0),gamesplayed(0),easywin(0),hardwin(0) {}

    void displaystats()const{
        cout<<"\nPlayer: "<<name<<endl;
        cout<<"\nTotal games played: "<<gamesplayed<<endl;
        cout<<"\nTotal Score: "<<score<<endl;
        cout<<"\nEasy Games won: "<<easywin<<endl;
        cout<<"\nHard Games won: "<<hardwin<<endl;


    }


};

void Menu() {
    cout << "\n--Welcome--";
    cout << "\n1. Start Game (easy)";
    cout << "\n2. Start Game (hard)";
    cout << "\n3. View Stats";
    cout<<"\n4. Enter New Player";
    cout<<"\n5. Quit";
    cout << "\nPlease select an option (1,2,3,4,5): ";

}

void savePlayer(const vector<Player>&players){
    ofstream file("player_data.txt");
    if(file.is_open()){
        for(const Player& player: players) {
            file << player.name << " " <<player.gamesplayed<<" "<< player.score << " " << player.easywin << " " << player.hardwin << "\n";
        }
        file.close();
    }
    else{
        cout<<"unable to open file";
    }

}

void loadPlayer(vector<Player>&players){
    players.clear();
    ifstream file("player_data.txt");
    if(file.is_open()){
        while(file>>ws && !file.eof()){
            Player player;
            file>> player.name >> player.gamesplayed>>player.score>> player.easywin>> player.hardwin;
            players.push_back(player);
        }
        file.close();
    }else{
        cout<<"unable to open file";
    }
}




int main() {
    int playerchoice;
    vector<Player> players;
    loadPlayer(players);


    do {
        Menu();
        cin >> playerchoice;
        string playerName;

        switch (playerchoice) {
            case 1: {
                cout << "\nYou have selected the easy mode";
                cout << "\nYou will have three chances to guess a number 1-10";
                cout << "\nThe quicker you guess the more points you will receive";
                cout << "\nIf you do not guess the number you will receive no points";

                cout << "\nEnter player name: ";
                cin >> playerName;


                int guess, numb, basescore;
                basescore = 4;
                numb = (rand() % 10) + 1;

                for (Player &player: players)
                    if (player.name == playerName) {
                        player.gamesplayed++;
                    }



                for (int i = 1; i <= 3; i++) {
                    cout << "\nenter a number 1-10: ";
                    cin >> guess;

                    if (guess == numb) {
                        cout << "\nCongrats! you guessed correctly";
                        cout << "\nyou earned " << basescore << " points";
                        for (Player &player: players)
                            if (player.name == playerName) {
                                player.score += basescore;
                                player.easywin++;
                            }

                        break;
                    } else {
                        cout << "\nThe number was not correct";
                        basescore -= 1;

                    }
                    if (guess < numb) {
                        cout << "\nThe correct number is higher";
                    } else {
                        cout << "\nThe correct number is lower";
                    }
                    cout << "\nYou have " << 3 - i << " attempts left";


                }
                cout<<"\nthe correct answer was "<<numb;
                break;
            }

                case 2: {
                    cout << "You have selected the hard mode";
                    cout << "\nYou will have three chances to guess a number 1-20";
                    cout << "\nThe quicker you guess the more points you will receive";
                    cout << "\nIf you do not guess the number you will receive no points";
                    cout << "\nEnter player name: ";
                    cin >> playerName;


                    int guess, numb;
                    int basescore;
                    basescore = 7;
                    numb = (rand() % 10) + 1;

                    for (Player &player: players)
                        if (player.name == playerName) {
                            player.gamesplayed++;
                        }

                    for (int i = 1; i <= 3; i++) {
                        cout << "\nenter a number 1-20: ";
                        cin >> guess;

                        if (guess == numb) {
                            cout << "\nCongrats! you guessed correctly";
                            cout << "\nyou earned" << basescore << "points";
                            for (Player &player: players) {
                                if (player.name == playerName) {
                                    player.score += basescore;
                                    player.hardwin++;
                                }
                            }

                            break;
                        } else {
                            cout << "\nThe number was not correct";
                            basescore -= 2;

                        }
                        if (guess < numb) {
                            cout << "\nThe correct number is higher";
                        } else {
                            cout << "\nThe correct number is lower";
                        }
                        cout << "\nYou have " << 3 - i << " attempts left";


                    }
                    cout<<"\nthe correct answer was "<<numb;
                    break;
                }

                case 3: {
                    cout << "--Player Statistics--\n";
                    for (const Player &player: players) {
                        player.displaystats();
                        cout << "-----------------------\n";
                    }

                }
                break;

                case 4: {
                    Player newPlayer;
                    cout << "\nEnter player name: ";
                    cin >> newPlayer.name;
                    newPlayer.score = 0;
                    newPlayer.gamesplayed=0;
                    newPlayer.easywin=0;
                    newPlayer.hardwin=0;
                    players.push_back(newPlayer);
                    cout << "you have added a new player\n";

                    savePlayer(players);
                    break;
                }

                case 5: {
                    savePlayer(players);
                    break;
                }

                default:
                    cout << "what you entered does not match any of the options. Please try again";
                break;
            }
        }
    while (playerchoice != 5);
    }


