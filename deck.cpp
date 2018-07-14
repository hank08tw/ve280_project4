#include "deck.h"
Deck::Deck() {
    reset ();
}

void Deck::reset() {
    next=0;
    for(int i=0;i<SUIT_SIZE;i++){
        for(int j=0;j<SPOT_SIZE;j++){
            deck[i*13+j].suit=(enum Suit)i;
            deck[i*13+j].spot=(enum Spot)j;
        }
    }
}

void Deck::shuffle(int n) {
    Card tmp_deck[DeckSize];
    int leftstart=0;
    int rightstart=n;
    int i=0;
    while(leftstart<n&&rightstart<DeckSize){
        tmp_deck[i++]=deck[rightstart++];
        tmp_deck[i++]=deck[leftstart++];
    }
    if(leftstart<n){
        while(leftstart<n){
            tmp_deck[i++]=deck[leftstart++];
        }
    }else{
        while(rightstart<DeckSize){
            tmp_deck[i++]=deck[rightstart++];
        }
    }
    for(int j=0;j<DeckSize;j++){
        deck[j]=tmp_deck[j];
    }
}

Card Deck::deal() {
    if(cardsLeft ()==0){
        DeckEmpty deckEmpty;
        throw deckEmpty;
    }
    return deck[next++];
}

int Deck::cardsLeft() {
    return DeckSize-next;
}