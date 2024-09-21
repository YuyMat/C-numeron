#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int inputNum(void);
bool ruleNum(int num);
int generateComputerNum(void);

struct number{
    int num;
    int guess_num;
};

int main(void) {
    struct number player;
    struct number computer;

    // playerの数字決定
    player.num = inputNum();
    printf("%d\n", player.num);

    // computerの数字決定
    computer.num = generateComputerNum();
    printf("%d\n", computer.num);
    return 0;
}

int inputNum(void) {
    char tmp[10];
    int num;
    bool rule = false;

    while (!rule) {
        printf("あなたの数字を入力してください：");
        scanf("%s", tmp);

        if (isdigit(tmp[0])) {   
            num = atoi(tmp);
            rule = ruleNum(num);
        } else {
            printf("数字を入力してください。\n");
        }
    }

    return num;
}

bool ruleNum(int num) {
    char number[10];
    sprintf(number, "%d", num);
    int num_len = strlen(number);
    int counter = 0;

    // 3桁でかつ同じ文字が入っていないかの比較
    if (num_len == 3) {
        for (int i = 0; i < num_len; i++) {
            for (int j = 0; j < num_len; j++) {
                if (number[i] == number[j]) {
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
}

int generateComputerNum(void) {
    bool init = true;
    bool b = true;
    
    int min = 123;
    int Max = 987;

    int computer_num;

    // ランダムシード初期化
    srand((unsigned int)time(NULL));

    // 適正数字になるまで3桁のランダムな数字を作成
    while(b) {
        computer_num = min + rand() % (Max - min + 1);
        if (ruleNum(computer_num)) {b = false;}
    }
    printf("コンピュータの数字が決まりました\n");
    return computer_num;
}

int guessNum(int mode) {
    // mode 0 = player guess
    // mode 1 = computer guess

    int guess_num;

    if (mode == 0) {
        printf("コンピュータの数字を予想してください：");
        scanf("%d", &guess_num);


    }
}

void judgeEatBite(int from_num, int to_num, int *eat, int *bite) {
    *eat = 0;
    *bite = 0;

    char str_from_num[4];
    char str_to_num[4];

    sprintf(str_from_num, "%d", from_num);
    sprintf(str_to_num, "%d", to_num);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // eat
            if (str_from_num[i] == str_to_num[j] && i == j) {
                *eat++;
            // bite
            } else if (str_from_num[i] == str_to_num[j] && i != j) {
                *bite++;
            }
        }
    }
}