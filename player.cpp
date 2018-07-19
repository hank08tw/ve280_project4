#include "player.h"

class simple_player : public Player{
public:
    simple_player(){}
    int bet(unsigned int bankroll, unsigned int minimum){
        return minimum;
    }
    bool draw(Card dealer,const Hand &player) {
        if(!player.handValue ().soft){
            if(player.handValue ().count<=11){
                return true;
            }
            if(player.handValue ().count==12){
                if(dealer.spot==FOUR||dealer.spot==FIVE||dealer.spot==SIX){
                    return false;
                }
                return true;
            }
            if(player.handValue ().count>=13&&player.handValue ().count<=16){
                if(TWO<=dealer.spot&&dealer.spot<=SIX){
                    return false;
                }
                return true;
            }
            return false;
        }
        if(player.handValue ().count<=17){
            return true;
        }
        if(player.handValue ().count==18){
            if(dealer.spot==TWO||dealer.spot==SEVEN||dealer.spot==EIGHT){
                return false;
            }
            return true;
        }
        return false;
    }
    void expose(Card c){}
    void shuffled(){}

};
class counting_player : public Player{
    int count;
public:
    counting_player(){
        count=0;
    }
    int bet(unsigned int bankroll, unsigned int minimum){
        if(count>=2&&bankroll>=2*minimum){
            return 2*minimum;
        }
        return minimum;
    }

    bool draw(Card dealer,const Hand &player){
        if(!player.handValue ().soft){
            if(player.handValue ().count<=11){
                return true;
            }
            if(player.handValue ().count==12){
                if(dealer.spot==FOUR||dealer.spot==FIVE||dealer.spot==SIX){
                    return false;
                }
                return true;
            }
            if(player.handValue ().count>=13&&player.handValue ().count<=16){
                if(TWO<=dealer.spot&&dealer.spot<=SIX){
                    return false;
                }
                return true;
            }
            return false;
        }
        if(player.handValue ().count<=17){
            return true;
        }
        if(player.handValue ().count==18){
            if(dealer.spot==TWO||dealer.spot==SEVEN||dealer.spot==EIGHT){
                return false;
            }
            return true;
        }
        return false;
    }
    void expose(Card c){
        if(c.spot<=ACE&&c.spot>=TEN){
            count--;
        }else if(TWO<=c.spot&&c.spot<=SIX){
            count++;
        }
    }
    void shuffled(){
        count=0;
    }
};

extern Player *get_Simple(){
    simple_player* simplePlayer=new simple_player;
    return simplePlayer;
}

extern Player *get_Counting(){
    counting_player* countingPlayer=new counting_player;
    return countingPlayer;
}