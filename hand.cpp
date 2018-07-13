#include "hand.h"
Hand::Hand() {
    discardAll ();
}

void Hand::discardAll() {
    curValue.count=0;
    soft=false;
}

void Hand::addCard(Card c) {
    if(c.spot==ACE){
        if(curValue.count<=10){
            soft=true;
            curValue.count+=11;
        }else{
            curValue.count+=1;
        }
    }else{
        if(c.spot==TEN||c.spot==JACK||c.spot==QUEEN||c.spot==KING){
            curValue.count+=10;
        }else{
            curValue.count+=(c.spot+2);
        }
    }
}

HandValue Hand::handValue() const {
    return curValue;
}