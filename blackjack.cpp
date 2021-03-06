#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
using namespace std;
int main(int argc,char* argv[]) {
    Player* player= nullptr;
    Deck deck;
    int bankroll=(int)atoi(argv[1]);
    int min_bet=(int)atoi(argv[2]);
    int hands=(int)atoi(argv[3]);
    if(string(argv[4])=="simple"){
        player=get_Simple ();
    }else{
        player=get_Counting ();
    }
    cout << "# Shuffling the deck\n";
    if(argc>=6){
        ifstream iFile;
        iFile.open(argv[5]);
        string input;
        getline (iFile,input);
        istringstream istream;
        istream.str(input);
        while(istream){
            int tmp_shuffle;
            istream >> tmp_shuffle;
            if(!istream)break;
            deck.shuffle (tmp_shuffle);
            cout << "cut at " << tmp_shuffle << endl;
        }
        iFile.close ();
    }else{
        for(int i=0;i<7;i++){
            int num=get_cut ();
            deck.shuffle (num);
            cout << "cut at " << num << endl;
        }
    }
    player->shuffled ();
    if(bankroll <min_bet){
        cout << "# Player has " << bankroll << " after 0 hands\n";
        return 0;
    }
    bool lose=false;
    Hand player_hand=Hand();
    Hand dealer_hand=Hand();
    for(int i=1;i<=hands;i++) {
        player_hand.discardAll ();
        dealer_hand.discardAll ();
        cout << "# Hand " << i << " bankroll " << bankroll << endl;
        if (deck.cardsLeft () < 20) {
            cout << "# Shuffling the deck\n";
            for(int j=0;j<7;j++){
                int num=get_cut();
                deck.shuffle (num);
                cout << "cut at " << num << endl;
            }
            player->shuffled ();
        }
        int wage=player->bet ((unsigned int)bankroll, (unsigned int)min_bet);
        cout << "# Player bets " << wage << endl;
        Card playercard1 = deck.deal ();
        player_hand.addCard (playercard1);
        player->expose (playercard1);
        cout << "Player dealt " << SpotNames[playercard1.spot] << " of " << SuitNames[playercard1.suit] << endl;
        Card dealercard1 = deck.deal ();
        dealer_hand.addCard (dealercard1);
        player->expose (dealercard1);
        cout << "Dealer dealt " << SpotNames[dealercard1.spot] << " of " << SuitNames[dealercard1.suit] << endl;
        Card playercard2 = deck.deal ();
        player_hand.addCard (playercard2);
        player->expose (playercard2);
        cout << "Player dealt " << SpotNames[playercard2.spot] << " of " << SuitNames[playercard2.suit] << endl;
        Card dealer_holecard = deck.deal ();
        dealer_hand.addCard (dealer_holecard);
        if (player_hand.handValue ().count == 21) {
            cout << "# Player dealt natural 21\n";
            bankroll += (3 * wage / 2);
            continue;
        }
        while (player->draw (dealercard1, player_hand)) {
            Card tmp_playercard = deck.deal ();
            player_hand.addCard (tmp_playercard);
            player->expose (tmp_playercard);
            cout << "Player dealt " << SpotNames[tmp_playercard.spot] << " of " << SuitNames[tmp_playercard.suit] << endl;
        }
        cout << "Player's total is " << player_hand.handValue ().count << endl;
        if (player_hand.handValue ().count > 21) {
            cout << "# Player busts\n";
            bankroll -= wage;
            if(bankroll<min_bet){
                cout << "# Player has " << bankroll << " after " << i << " hands\n";
                lose=true;
                break;
            }
            continue;
        }
        cout << "Dealer's hole card is " << SpotNames[dealer_holecard.spot] << " of " << SuitNames[dealer_holecard.suit]
             << endl;
        player->expose (dealer_holecard);
        while (dealer_hand.handValue ().count < 17) {
            Card tmp_dealercard = deck.deal ();
            dealer_hand.addCard (tmp_dealercard);
            player->expose (tmp_dealercard);
            cout << "Dealer dealt " << SpotNames[tmp_dealercard.spot] << " of " << SuitNames[tmp_dealercard.suit] << endl;
        }
        cout << "Dealer's total is " << dealer_hand.handValue ().count << endl;
        if (dealer_hand.handValue ().count > 21) {
            cout << "# Dealer busts\n";
            bankroll += wage;
            continue;
        }
        if (player_hand.handValue ().count > dealer_hand.handValue ().count) {
            cout << "# Player wins\n";
            bankroll += wage;
        } else if (player_hand.handValue ().count < dealer_hand.handValue ().count) {
            cout << "# Dealer wins\n";
            bankroll -= wage;
        } else {
            cout << "# Push\n";
        }
        if (bankroll < min_bet) {
            cout << "# Player has " << bankroll << " after " << i << " hands\n";
            lose=true;
            break;
        }
    }

    if(!lose){
        cout << "# Player has " << bankroll << " after " << hands << " hands\n";
    }
    return 0;
}