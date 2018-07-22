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
    next=0;
    Card tmp_deck[DeckSize];
    int left_start=0;
    int right_start=n;
    int i=0;
    while(left_start<n&&right_start<DeckSize){
        tmp_deck[i++]=deck[right_start++];
        tmp_deck[i++]=deck[left_start++];
    }
    while(left_start<n){
        tmp_deck[i++]=deck[left_start++];
    }
    while(right_start<DeckSize){
        tmp_deck[i++]=deck[right_start++];
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