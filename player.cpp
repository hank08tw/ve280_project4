#include "player.h"

class simple_player : public Player{
public:
    int bet(unsigned int bankroll, unsigned int minimum){
        return minimum;
    }
    bool draw(Card dealer,const Hand &player){
        if(!player.handValue ().soft){
            if(player.handValue ().count<=11){
                return true;
            }else if(player.handValue ().count==12){
                if(dealer.spot==FOUR||dealer.spot==FIVE||dealer.spot==SIX){
                    return false;
                }
                return true;
            }else if(player.handValue ().count>=13&&player.handValue ().count<=16){
                if(0<=dealer.spot&&dealer.spot<=4){
                    return false;
                }
                return true;
            }else{
                return false;
            }
        }else{
            if(player.handValue ().count<=17){
                return true;
            }else if(player.handValue ().count==18){
                if(dealer.spot==TWO||dealer.spot==SEVEN||dealer.spot==EIGHT){
                    return false;
                }
                return true;
            }else{
                return false;
            }
        }
    }
};