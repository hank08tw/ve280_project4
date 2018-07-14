#include "hand.h"

Hand::Hand() {
    discardAll ();
}

void Hand::discardAll() {
    curValue.count=0;
    curValue.soft=false;
}

void Hand::addCard(Card c) {
    if(c.spot==ACE){
        if(curValue.count<=10){
            curValue.soft=true;
            curValue.count+=11;
        }else{
            curValue.count+=1;
        }
    }else{
        if(c.spot==TEN||c.spot==JACK||c.spot==QUEEN||c.spot==KING){
            if(curValue.count>11&&curValue.soft){
                curValue.soft=false;
            }else{
                curValue.count+=10;
            }
        }else{
            if(curValue.count+(c.spot+2)>21&&curValue.soft){
                curValue.soft=false;
                curValue.count-=10;
                curValue.count+=(c.spot+2);
            }else{
                curValue.count+=((int)c.spot+2);
            }
        }
    }
}

HandValue Hand::handValue() const {
    return curValue;
}
