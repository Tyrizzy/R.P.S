#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

string player_selection, computer_selection, choice;
int rps, player_win, computer_win, Tie, player_win_total, computer_win_total, player_computer_tie;
const int m = 2, n = 5;
string Tally[m][n];

int player_1(){
    cout << "Player 1: Enter your choice (1=paper, 2=scissors, 3=rock): ";
    cin >> rps;
}

void player_RPS(){
    if(rps == 1){
        choice = "paper";
    }  
    else if (rps == 2){
        choice = "scissor";
    } 
    else if (rps == 3){
        choice = "rock";
    }
    player_selection = choice;
    cout << "Player 1 entered " << player_selection << " as the choice.\n";
}

void RPS_comparison(){
    player_win = 0;
    computer_win = 0;
    Tie = 0;

    if (player_selection == "paper" && computer_selection == "rock"){
        player_win += 1;
        cout << "PLAYER 1 WINS\n";
    }
    else if (player_selection == "scissor" && computer_selection == "paper"){
        player_win += 1;
        cout << "PLAYER 1 WINS\n";
    }
    else if (player_selection == "rock" && computer_selection == "scissor"){
        player_win += 1;
        cout << "PLAYER 1 WINS\n";
    }

    if (computer_selection == "paper" && player_selection == "rock"){
        computer_win += 1;
        cout << "COMPUTER WINS\n";
    }
    else if (computer_selection == "scissor" && player_selection == "paper"){
        computer_win += 1;
        cout << "COMPUTER WINS\n";
    }
    else if (computer_selection == "rock" && player_selection == "scissor"){
        computer_win += 1;
        cout << "COMPUTER WINS\n";
    }
    else if (computer_selection == player_selection || player_selection == computer_selection){
        Tie += 1;
        cout << "IT'S A TIE\n";
    }
}

void refresh(){
    fstream refresh;

    refresh.open("rps.txt", ios::out);
    if (refresh.is_open()){
        refresh.close();
    }
}

void winner_tally_to_file(){
    fstream dataFile_append;

    dataFile_append.open("rps.txt", ios::app);
    if (dataFile_append.is_open()){
        if (player_win == 1){
            dataFile_append << "PLAYER1-WINS!!!" << endl; ;
        }
        else if (computer_win == 1){
            dataFile_append << "COMPUTER-WINS!!!" << endl;
        }
        else if (Tie == 1){
            dataFile_append << "TIE!!!" << endl;
        }
        dataFile_append.close();
    }    
    else{
        cout << "CANNOT READ FILE" << endl;
    }
}

void official_tally_from_file(){
    fstream dataFile_read;

    dataFile_read.open("rps.txt", ios::in);
    if (dataFile_read.is_open()){
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                dataFile_read >> Tally[i][j];
            }
        }
        dataFile_read.close();
    }
    else{
        cout << "CANNOT READ FILE" << endl;
    }

    player_win_total = 0;
    computer_win_total = 0;
    player_computer_tie = 0;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (Tally[i][j] == "PLAYER1-WINS!!!"){
                player_win_total += 1;
            }
            else if (Tally[i][j] == "COMPUTER-WINS!!!"){
                computer_win_total += 1;
            }
            else if (Tally[i][j] == "TIE!!!"){
                player_computer_tie += 1;
            }
        }
    }

    if ((player_win_total > computer_win_total) && (player_win_total > player_computer_tie)){
        cout << "THE PLAYER HAS THE MOST WINS IN THE SERIES";
    }
    else if ((computer_win_total > player_win_total) && (computer_win_total > player_computer_tie)){
        cout << "THE COMPUTER HAS THE MOST WINS IN THE SERIES";
    }
    else if ((player_computer_tie >= player_win_total) || (player_computer_tie >= computer_win_total) || (player_win_total == computer_win_total)){
        cout << "THE SERIES IS A TIE";
    }
}

void close(){
    string C;
    cout << "Enter any key and press enter to close" << endl;
    cin >> C;


}

int main(){
    refresh();

    for (int x = 1; x < 11; x++){
        cout << "\n ROCK, PAPER, SCISSORS GAME  (MATCH #" << x << ")";
        cout << "\n=========================================\n";
        player_1();
        player_RPS();
        
        srand(time(0)); 
        int comp_selection = rand() % 3 + 1; 
        if (comp_selection == 1){ 
            choice = "paper"; 
        } 
        else if (comp_selection == 2){ 
            choice = "scissor"; 
        } 
        else if (comp_selection == 3){ 
            choice = "rock"; 
        } 
        computer_selection = choice;
        cout << "Computer selected " << computer_selection << " as the choice.\n";

        RPS_comparison();

        winner_tally_to_file();
    }
    cout << "\n";
    official_tally_from_file();

    cout << "" << endl;
    close();
    return 0;
}
