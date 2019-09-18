#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "hacking.h"

#define DATAFILE "chance.data" //file for users data

struct      user {
    int     uid;
    int     credits;
    int     hightscore;
    char    name[100]; 
    int     (*current_game) ();
};

int     get_player_data();
void    register_new_player();
void    show_highscore();
void    jackpot();
void    print_cards(char *, char *, int);
int     take_wager(int, int);
void    play_the_game();
int     pick_a_number();
int     dealer_no_match();
int     find_the_ace(); 
void    fatal(char *);
void    input_name();
void    update_player_data();

struct user player;

int main() {
    int choice, last_game;

    srand(time(0));
/*if data file is empty, we register new player */
    if (get_player_data() == -1)
        register_new_player();

    while (choice != 7) {
        printf("-=[ Menu ]=-\n");
        printf("1 - Game guess a number\n");
        printf("2 - Game no coincidence\n");
        printf("3 - Game Find ace\n");
        printf("4 - Top score\n");
        printf("5 - Change player\n");
        printf("6 - Renew money\n");
        printf("7 - Quit\n");
        printf("[Name: %s]\n", player.name);
        printf("[Your scores: %u] -> ", player.credits);
        scanf("%d", &choice);

        if ((choice < 1) || (choice > 7))
            printf("\n[!!] Number %d unavalible.\n\n", choice);
        else if (choice < 4) {
            if (choice != last_game) {
                if (choice == 1)
                    player.current_game = pick_a_number;
                else if (choice == 2)
                    player.current_game =dealer_no_match;
                else
                    player.current_game = find_the_ace;
                last_game = choice;
            }
            play_the_game();
        }
        else if (choice == 4)
            show_highscore();
        else if (choice == 5) {
            printf("\nOther player\n");
            printf("Enter new name: ");
            input_name();
            printf("Name was changed.\n\n");
        }
        else if (choice == 6) {
            printf("\nYour money has been renew.\n\n");
            player.credits = 100;
        }
    }
    update_player_data();
    printf("\nThanks for playing!\n");
}

/*
read from file players data with right uid
return -1 if can't find uid
*/

int get_player_data() {
    int fd, uid, read_bytes;
    struct user entry;
    
    uid = getuid();

    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        return -1;
    read_bytes = read(fd, &entry, sizeof(struct user));
    while (entry.uid != uid && read_bytes > 0) {
        read_bytes = read(fd, &entry, sizeof(struct user));
    }
    close(fd);
    if (read_bytes < sizeof(struct user))
            return -1;
    else
        player = entry;
    return 1;
}

void register_new_player() {
    int fd;

    printf("-=-={ Register new player }=-=-\n");
    printf("Enter your name: ");
    input_name();

    player.uid = getuid();
    player.hightscore = player.credits = 100;

    fd = open(DATAFILE, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fatal("can't open file in register_new_player");
    write(fd, &player, sizeof(struct user));
    close(fd);

    printf("\nYou are welcome %s.\n", player.name);
    printf("You have %u credits.\n", player.credits);
}

void update_player_data() {
    int fd, i, read_uid;
    char burned_byte;

    fd = open(DATAFILE, O_RDWR);
    if (fd == -1)
        fatal("can't open file update_player_data\n");
    read(fd, &read_uid, 4);
    while (read_uid != player.uid) {
        for (i = 0; i < sizeof(struct user) - 4; i++)
            read(fd, &burned_byte, 1);
        read(fd, &read_uid, 4);
    }
    write(fd, &(player.credits), 4);
    write(fd, &(player.hightscore), 4);
    write(fd, &(player.name), 4);
    close(fd);
}

void show_highscore() {
    unsigned int top_score = 0;
    char top_name[100];
    struct user entry;
    int fd;

    printf("\n====================== [Top score] =========================\n");
    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        fatal("can't open file in show_hightscore");
    while (read(fd, &entry, sizeof(struct user)) > 0) {
        if (entry.hightscore > top_score)
            top_score = entry.hightscore;
        strcpy(top_name, entry.name);
    }
    close(fd);
    if (top_score > player.hightscore)
        printf("%s achive top score %u\n", top_name, top_score);
    else
        printf("You have top %u credits\n", player.hightscore);
    printf("\n============================================================\n");
}

void jackpot() {
    printf("*+*+*+*+*+* JACPOT *+*+*+*+*\n");
    printf("You WON jacpot and earn 100 credits\n");
    player.credits += 100;
}

void input_name() {
    char *name_ptr, input_char = '\n';
    while (input_char == '\n')
        scanf("%c", &input_char);

    name_ptr = (char *) &(player.name);
    while (input_char != '\n') {
        *name_ptr = input_char;
        scanf("%c", &input_char);
        name_ptr++;
    }
    *name_ptr = '\0';
}

void print_cards(char *msg, char *cards, int user_pick) {
    int i;

    printf("\n\t*** %s ***\n", msg);
    printf("\t\t._.\t._.\t._.\n");
    printf("Cards:\t|%c|\t|%c|\t|%c|\n\t", cards[0], cards[1], cards[2]);
    if (user_pick == -1)
        printf(" 1 \t 2 \t 3\n");
    else {
        for (i = 0; i < user_pick; i++)
            printf("\t");
        printf("^-- you choice\n");
    }
}

int take_wager(int avaliable_credits, int previous_wager) {
    int wager, total_wager;

    printf("What is your bet? Avalible: %d\n", avaliable_credits);
    scanf("%d", &wager);
    if (wager < 1) {
        printf("Bet shoud be positive number\n");
        return -1;
    }
    total_wager = previous_wager + wager;
    if (total_wager > avaliable_credits) {
        printf("You bet %d more then you have\n", total_wager);
        printf("You have %d credits, try again.\n", avaliable_credits);
        return -1;
    }
    return wager;
}

void play_the_game() {
    int play_again = 1;
    int (*game) ();
    char selection;

    while (play_again) {
        printf("\n[DEBUG] pointer current_game @ %p\n",
                player.current_game);
        if (player.current_game() != -1) {
            if (player.credits > player.hightscore)
                player.hightscore = player.credits;
            printf("\nYou have %u credits\n", player.credits);
            update_player_data();

            printf("Play again? (y/n) ");
            selection = '\n';
            while (selection == '\n')//missing spaces

            scanf("%c", &selection);
            if(selection == 'n')
                play_again = 0;
        }
        else
            play_again = 0;
    }
}

int pick_a_number() {
    int pick, winning_number;

    printf("\n###### Choose a number ########\n");
    printf("This game costs 10 credits. Just pick a number\n");
    printf("from 1 to 20, and you pick a number\n");
    printf("you win 100 credits\n");
    winning_number = (rand() % 20) + 1;
    if (player.credits < 10) {
        printf("You have %d credits. Not enough credits to play game!\n\n",
        player.credits);
        return -1;
    }
    player.credits -= 10;
    printf("You paid 10 credits.\n");
    printf("Pick a number from 1 to 20: ");
    scanf("%d", &pick);

    printf("Winning number is %d\n", winning_number);
    if (pick == winning_number)
        jackpot();
    else
        printf("You lost\n");
    return 0;
}

int dealer_no_match() {
    int i, j, numbers[16], wager = -1, match = -1;

    printf("\n:::::::: No matches ::::::::\n");
    printf("You can bet all your credits\n");
    printf("Dealer chouse 16 random numbers from 0 to 99.\n");
    printf("If ther are no matches, you win double bet!\n");

    if (player.credits == 0) {
        printf("You haven't got credits to make bet.\n");
        return -1;
    }
    while (wager == -1)
        wager = take_wager(player.credits, 0);

    printf("\t\t::: Choosing 16 random numbers :::\n");
    for (i = 0; i < 16; i++) {
        numbers[i] = rand() % 100;
        printf("%2d\t", numbers[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    for (i = 0; i < 15; i++) {
        j = i + 1;
        while (j < 16) {
            if (numbers[j] == numbers[i])
                    match = numbers[i];
            j++;
        }
    }
    if (match != -1) {
        printf("Number %d have matched!\n", match);
        printf("You lost %d credits.\n", wager);
        player.credits -= wager;
    } else {
        printf("No matches. You won %d credits.\n", wager);
        player.credits += wager;
    }
    return 0;
}

int find_the_ace() {
    int i, ace, total_wager;
    int invalid_choice, pick = -1, wager_one = -1, wager_two = -1;
    char choice_two, cards[3] = "XXX";

    ace = rand() % 3;

    printf("******** Find ace ********\n");
    printf("You can bet all your credit.\n");
    printf("We choosing 3 cards, 2 queens and 1 ace.\n");
    printf("Find ace and you will win.\n");
    printf("After your choice we open 1 queen.\n");
    printf("And you can change your choice or raise a bet.\n");

    if (player.credits == 0) {
        printf("You have no credits to make bet.\n");
        return -1;
    }

    while (wager_one == -1)
        wager_one = take_wager(player.credits, 0);

    print_cards("Choosing cards", cards, -1);
    pick = -1;
    while ((pick < 1) || (pick > 3)) {
        printf("Choose a card: 1, 2 and 3 ");
        scanf("%d", &pick);
    }
    pick--;
    i = 0;
    while (i == ace || i == pick)
        i++;
    cards[i] = 'Q';
    print_cards("Open queen", cards, pick);
    invalid_choice = 1;
    while (invalid_choice) {
        printf("Do you want to raise[b] or change choice[y]?\n");
        printf("Choose b or y: ");
        choice_two = '\n';
        while (choice_two == '\n')
            scanf("%c", &choice_two);
        if (choice_two == 'y') {
            invalid_choice = 0;
            while (wager_two == -1)
                wager_two = take_wager(player.credits, wager_one);
        }
        if (choice_two == 'b') {
            i = invalid_choice = 0;
            while (i == pick || cards[i] == 'Q')
                i++;
            pick = i;
            printf("You have changed your choice.\n");
        }
    }

    for (i = 0; i < 3; i++) {
        if (ace == i)
            cards[i] = 'A';
        else
            cards[i] = 'Q';
    }
    print_cards("Result", cards, pick);

    if (pick == ace) {
        printf("Your first bet give you %d credits\n", wager_one);
        player.credits += wager_one;
        if (wager_two != -1) {
            printf("Your second bet give you %d credits\n", wager_two);
            player.credits += wager_two;
        }
    } else {
        printf("You lost %d credits with first bet\n", wager_one);
        player.credits -= wager_one;
        if (wager_two != -1) {
            printf("You lost %d credits with second bet\n", wager_two);
            player.credits -= wager_two;
        }
    }
    return 0;
}
