#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char renk[10];
    char isim[13];
    int deger;
} Kart;

Kart deste[52];
int cekilenIndex = 0;

void make_deste() {
    char *renkler[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char *isimler[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int degerler[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strcpy(deste[index].renk, renkler[i]);
            strcpy(deste[index].isim, isimler[j]);
            deste[index].deger = degerler[j];
            index++;
        }
    }
}

void deste_karma() {
    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        int random = rand() % 52;
        Kart temp = deste[i];
        deste[i] = deste[random];
        deste[random] = temp;
    }
}

Kart kartcek() {
    if (cekilenIndex >= 52) {
        printf("Deck is empty! Shuffling a new deck...\n");
        deste_karma();
        cekilenIndex = 0;
    }
    return deste[cekilenIndex++];
}

int asdegeri(int score, int assayi) {
    while (score > 21 && assayi > 0) {
        score -= 10;
        assayi--;
    }
    return score;
}

int kalankart() {
    return 52 - cekilenIndex;
}

int main() {
    int choise = 0, your_score = 0, pc_score = 0, pc_as = 0, your_as = 0;
    char devam;
    make_deste();
    deste_karma();
    while (choise != 2) {
        printf("\nShall we start the game? (yes 1-no 2): ");
        scanf("%d", &choise);
        if (choise == 1) {
            if (kalankart() < 3) {
                printf("Not enough cards left in the deck! Shuffling a new deck...\n");
                deste_karma();
            }

            your_as = 0;
            your_score = 0;
            pc_as = 0;
            pc_score = 0;

            printf("\nPlayer's cards:\n");
            for (int i = 0; i < 2; i++) {
                Kart kart = kartcek();
                if (kart.deger == 11) {
                    your_as++;
                }
                your_score += kart.deger;
                printf("  - %s %s\n", kart.renk, kart.isim);
            }

            printf("\nDealer's cards:\n");
            Kart pc_open = kartcek();
            if (pc_open.deger == 11) {
                pc_as++;
            }
            pc_score += pc_open.deger;
            printf("  - %s %s (Face Up)\n", pc_open.renk, pc_open.isim);

            Kart pc_close = kartcek();
            if (pc_close.deger == 11) {
                pc_as++;
            }
            pc_score += pc_close.deger;
            printf("  - Face Down Card\n");

            your_score = asdegeri(your_score, your_as);
            pc_score = asdegeri(pc_score, pc_as);

            printf("\nYour score: %d\n", your_score);
            printf("Dealer's face-up card: %s %s\n", pc_open.renk, pc_open.isim);

            printf("Do you want to draw another card? (y/n): ");
            scanf(" %c", &devam);
            while (devam == 'y' || devam == 'Y') {
                Kart kart = kartcek();
                if (kart.deger == 11) {
                    your_as++;
                }
                your_score += kart.deger;
                your_score = asdegeri(your_score, your_as);

                printf("\nDrawn card: %s %s\n", kart.renk, kart.isim);
                printf("Your score: %d\n", your_score);

                if (your_score > 21) {
                    printf("Bust! You lose.\n");
                    break;
                }

                printf("Do you want to draw another card? (y/n): ");
                scanf(" %c", &devam);
            }

            if (your_score <= 21) {
                printf("\nDealer's face-down card: %s %s\n", pc_close.renk, pc_close.isim);
                while (pc_score < 17) {
                    Kart kart = kartcek();
                    if (kart.deger == 11) {
                        pc_as++;
                    }
                    pc_score += kart.deger;
                    pc_score = asdegeri(pc_score, pc_as);
                    printf("Dealer draws: %s %s\n", kart.renk, kart.isim);
                }

                printf("\nYour final score: %d\n", your_score);
                printf("Dealer's final score: %d\n", pc_score);

                if (pc_score > 21 || your_score > pc_score) {
                    printf("You win!\n");
                } else if (your_score == pc_score) {
                    printf("It's a tie!\n");
                } else {
                    printf("You lose!\n");
                }
            }
        }
    }

    printf("\nThank you for playing!\n");
    return 0;
}