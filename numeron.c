#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void inputNum(char *player_num);
bool ruleNum(char *num);
int generateRandomNum(int mode, int min, int Max, char *computer_num);
void guessNum(int mode, int round, char *who_guess, int *num_array);
void judgeEatBite(int mode, char *from_num, char *to_num, int *EAT, int round, int *num_array);
bool isWin(int eat);
void saveNumArray(int round, int *num_array, char *num, int eat, int bite);
void computerGuessNum(int *num_array, char *computer_guess_num);

struct number{
    char num[4];
    char guess_num[4];
};

char str_num_array[11] = "0123456789";

int main(void) {
    struct number player;
    struct number computer;

    int eat; //勝利確認用
    int round = 1;

    //  0-9までの値を保持する配列 for computer
    int num_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // playerの数字決定
    inputNum(player.num);
    puts("----------------------------------------------------");

    // computerの数字決定
    generateRandomNum(1, 123, 987, computer.num);
    printf("コンピュータの数字が決まりました\n");
    printf("%s\n", computer.num);
    puts("----------------------------------------------------");

    while (true) {
        // player　予想
        guessNum(0, round, player.guess_num, NULL);
        judgeEatBite(0, player.guess_num, computer.num, &eat, round, NULL);
        
        if (isWin(eat)) {
            printf("Player Win!!\n");
            exit(0);
        }
        puts("----------------------------------------------------");

        // computer 予想
        guessNum(1, round, computer.guess_num, num_array);
        judgeEatBite(1, computer.guess_num, player.num, &eat, round, num_array);
        if (isWin(eat)) {
            printf("Player Lose;;\n");
            exit(0);
        }
        puts("----------------------------------------------------");

        // debug
        for (int i = 0; i < 10; i++) {
            printf("%d", num_array[i]);
        }

        round ++;
    }

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
            printf("正しい数字を入力してください\n");
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

// mode == 1:for computer, else mode:just for generate num(likes 0);
int generateRandomNum(int mode, int min, int Max, char *computer_num) {
    bool loop = true;
    int int_num;
    char str_num[4];

    // ランダムシード初期化
    srand((unsigned int)time(NULL));

    // 適正数字になるまで3桁のランダムな数字を作成
    while(loop) {
        // 3桁作成
        int_num = min + rand() % (Max - min + 1);
        // int to str
        sprintf(str_num, "%d", int_num);
        if (ruleNum(str_num)) {loop = false;}
    }

    if (mode == 1) {
        strcpy(computer_num, str_num);
        return 0;
    } else {
        return int_num;
    }
}

void guessNum(int mode, int round, char *who_guess, int *num_array) {
    // mode 0 = player guess
    // mode 1 = computer guess
    
    char tmp[10];
    bool loop = true;

    if (mode == 0) {
        while (loop) {
            printf("あなたの番です。\nコンピュータの数字を予想してください：");
            scanf("%s", tmp);

            if (ruleNum(tmp)) {
                strcpy(who_guess, tmp);
                loop = false;
            } else {
                printf("正しい数字を入力してください\n");
            }
        }
    } else if (mode == 1) {
        printf("コンピュータの予想の番です\n");

        if (round == 1) {
            sprintf(who_guess, "123");
        } else if (round == 2) {
            sprintf(who_guess, "456");
        } else if (round == 3) {
            sprintf(who_guess, "789");
        } else {
            computerGuessNum(num_array, who_guess);
        }
        
    }
    
}

void judgeEatBite(int mode, char *from_num, char *to_num, int *EAT, int round, int *num_array) {
    int eat = 0, bite = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // eat
            if (from_num[i] == to_num[j] && i == j) {
                eat++;
            // bite
            } else if (from_num[i] == to_num[j] && i != j) {
                bite++;
            }
        }
    }
    
    // computerの場合、num_arrayの処理
    if (mode == 1 && num_array != NULL) {saveNumArray(round, num_array, from_num, eat, bite);}

    *EAT = eat;
    printf("%s ： %deat %dbite\n", from_num, eat, bite);
}

void saveNumArray(int round, int *num_array, char *num, int eat, int bite) {
    int tmp_sum = 0;

    // 可能性がある数字をtrueにする
    if (eat + bite > 0) {
        for (int i = 0; i < 3; i++) {
            int int_a_num = num[i] - '0';
            num_array[int_a_num] = 1;
        }
    } else { //可能性がない時
        for (int i = 0; i < 3; i++) {
            int int_a_num = num[i] - '0';
            num_array[int_a_num] = 0;
        }
    }

    // ラウンド3の時に可能性のある数字の個数が9個なかったら0をtrueにする
    if (round == 3) {
        // 可能性のある数字の個数を調べる
        for (int i = 1; i < 10; i++) {
            tmp_sum += num_array[i];
        }
        if (tmp_sum != 9) {num_array[0] = 1;}
    }
}

bool isWin(int eat) {
    if (eat == 3) {
        return true;
    }
    return false;
}

// round >= 4の時のコンピュータ予想番号
void computerGuessNum(int *num_array, char *computer_guess_num) {
    
    int int_tmp_num;
    int random_num1;
    int random_num2;
    int random_num3;
    char str_tmp_num[10];
    int array_count = 0;
    char return_tmp_num[4];

    for (int i = 0; i < 10; i++) {
        if (num_array[i]) {
            int_tmp_num *= 10;
            int_tmp_num += atoi(&str_num_array[i]);
            array_count++;
        }
    }

    
    sprintf(str_tmp_num, "%d", int_tmp_num);
    int len_num_array = strlen(str_tmp_num);

    for (int i = 0; i < 3; i++) {
        random_num1 = generateRandomNum(0, 0, len_num_array, NULL);
        random_num2 = generateRandomNum(0, 0, len_num_array, NULL);
        random_num3 = generateRandomNum(0, 0, len_num_array, NULL);
    }

    sprintf(return_tmp_num, "%c%c%c", str_tmp_num[random_num1], str_tmp_num[random_num2], str_tmp_num[random_num3]);
    ruleNum(return_tmp_num);

    strcpy(computer_guess_num, return_tmp_num);
}