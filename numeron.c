#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void inputNum(char *player_num);
bool ruleNum(char *num);
void generateComputerNum(char *computer_num);

struct number{
    char num[4];
    char guess_num[4];
};

int main(void) {
    struct number player;
    struct number computer;

    // playerの数字決定
    inputNum(player.num);
    printf("%s\n", player.num);

    // computerの数字決定
    generateComputerNum(computer.num);
    printf("%s\n", computer.num);
    return 0;
}

void inputNum(char *player_num) {
    char tmp[10];
    bool rule = false;

    while (!rule) {
        printf("あなたの数字を入力してください：");
        scanf("%s", tmp);
        
        if (ruleNum(tmp)) {
            sprintf(player_num, "%s", tmp);
            rule = true;
        } else {
            printf("数字を入力してください。\n");
        }
    }
}

bool ruleNum(char *num) {
    int counter = 0;

    // 数字か判定
    if (isdigit(num[0])) {
        // intに変換
        int int_num = atoi(num);
        sprintf(num, "%d", int_num);
        int num_len = strlen(num);

        // 3桁でかつ同じ文字が入っていないかの比較
        if (num_len == 3) {
            for (int i = 0; i < num_len; i++) {
                for (int j = 0; j < num_len; j++) {
                    if (num[i] == num[j]) {
                        counter++;
                    }
                }
            }
            // 問題なかったらtrue
            if (counter == 3) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    // 数字でなかったらfalse
    } else {
        return false;
    }
}

void generateComputerNum(char *computer_num) {
    bool b = true;
    
    int min = 123;
    int Max = 987;

    int int_computer_num;
    char str_computer_num[4];

    // ランダムシード初期化
    srand((unsigned int)time(NULL));

    // 適正数字になるまで3桁のランダムな数字を作成
    while(b) {
        // 3桁作成
        int_computer_num = min + rand() % (Max - min + 1);
        // int to str
        sprintf(str_computer_num, "%d", int_computer_num);
        if (ruleNum(str_computer_num)) {b = false;}
    }
    printf("コンピュータの数字が決まりました\n");
    strcpy(computer_num, str_computer_num);
}

// void guessNum(int mode, char *who_guess) {
//     // mode 0 = player guess
//     // mode 1 = computer guess

//     int guess_num;

//     if (mode == 0) {
//         printf("コンピュータの数字を予想してください：");
//         scanf("%d\n", guess_num);




//     }
// }

// void judgeEatBite(int from_num, int to_num, int *eat, int *bite) {
//     *eat = 0;
//     *bite = 0;

//     char str_from_num[4];
//     char str_to_num[4];

//     sprintf(str_from_num, "%d", from_num);
//     sprintf(str_to_num, "%d", to_num);

//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             // eat
//             if (str_from_num[i] == str_to_num[j] && i == j) {
//                 *eat++;
//             // bite
//             } else if (str_from_num[i] == str_to_num[j] && i != j) {
//                 *bite++;
//             }
//         }
//     }
// }