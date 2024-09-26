#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void inputNum(char *player_num);
bool ruleNum(char *num);
int generateRandomNum(int mode, int min, int Max, char *computer_num);
void guessNum(int mode, char *who_guess);
void judgeEatBite(int mode, char *from_num, char *to_num, int *EAT);
bool isWin(int eat);
void saveNumArray(char *num, int eat, int bite);
void computerGuessNum(char *computer_guess_num);
bool check_history(int target);

struct number{
    char num[4];
    char guess_num[4];
};

//  0-9までの値を保持する配列 for computer
char str_num_array[11] = "0123456789";
int num_array[10] = {0};

// guess_numの履歴
int guess_history[100];

int round_count = 1;

int main(void) {
    struct number player;
    struct number computer;

    int eat; //勝利確認用

    // round 1,2,3は固定のため初期化
    guess_history[1] = 123;
    guess_history[2] = 456;
    guess_history[3] = 789;

    // ランダムシード初期化
    srand((unsigned int)time(NULL));

    // playerの数字決定
    puts("----------------------------------------------------");
    inputNum(player.num);
    puts("----------------------------------------------------");

    // computerの数字決定
    generateRandomNum(1, 123, 987, computer.num);
    printf("コンピュータの数字が決まりました\n");
    puts("----------------------------------------------------");

    while (true) {
        // player　予想
        guessNum(0, player.guess_num);
        judgeEatBite(0, player.guess_num, computer.num, &eat);
        
        if (isWin(eat)) {
            printf("Player Win!!\n");
            exit(0);
        }
        puts("----------------------------------------------------");

        // computer 予想
        guessNum(1, computer.guess_num);
        judgeEatBite(1, computer.guess_num, player.num, &eat);
        if (isWin(eat)) {
            printf("Player Lose;;\n");
            exit(0);
        }
        puts("----------------------------------------------------");

        round_count ++;
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

// in rule == true, not in rule == false
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

    // 適正数字になるまで3桁のランダムな数字を作成
    while(loop) {
        // 3桁作成
        int_num = min + rand() % (Max - min + 1);
        if (mode == 1) {
            sprintf(str_num, "%d", int_num);
            if (ruleNum(str_num)) {loop = false;}
        }
        else {loop = false;}
    }

    if (mode == 1) {
        strcpy(computer_num, str_num);
        return 0;
    } else {
        return int_num;
    }
}

void guessNum(int mode, char *who_guess) {
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

        if (round_count == 1) {
            sprintf(who_guess, "123");
        } else if (round_count == 2) {
            sprintf(who_guess, "456");
        } else if (round_count == 3) {
            sprintf(who_guess, "789");
        } else {
            computerGuessNum(who_guess);
        }
    }
}

void judgeEatBite(int mode, char *from_num, char *to_num, int *EAT) {
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
    if (mode == 1) {saveNumArray(from_num, eat, bite);}

    *EAT = eat;
    printf("%s ： %deat %dbite\n", from_num, eat, bite);
}

void saveNumArray(char *num, int eat, int bite) {
    int tmp_sum = 0;

    // 可能性がある数字をtrueにする
    if ((eat + bite > 0) && (eat + bite < 3)) {
        for (int i = 0; i < 3; i++) {
            int int_a_num = num[i] - '0';
            num_array[int_a_num] = 1;
        }
    } else if (eat + bite == 3) { //数字が確定したら他の数を0にする
        memset(num_array, 0, sizeof(num_array)); //num_array リセット
        
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
    if (round_count == 3) {
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

// is existed == false,  is not existed == true
bool check_history(int target) {
    for (int i = 1; i <= round_count; i++) {
        if (target == guess_history[i]) {
            return false;
        }
    }
    return true;
}

// round >= 4の時のコンピュータ予想番号
void computerGuessNum(char *computer_guess_num) {
    
    int int_tmp_num = 0;
    int random_num1;
    int random_num2;
    int random_num3;
    char str_tmp_num[11];
    int array_count = 0;
    char return_tmp_num[4];

    // 可能性のある数字達を一つの文字列に
    for (int i = 9; i >= 0; i--) {
        if (num_array[i]) {
            int_tmp_num *= 10;
            int_tmp_num += i;
            array_count++;
        }
    }
    sprintf(str_tmp_num, "%d", int_tmp_num);

    // 3桁の数字作成
    bool flag = true;
    while (flag) {
        random_num1 = generateRandomNum(0, 0, array_count - 1, NULL);
        random_num2 = generateRandomNum(0, 0, array_count - 1, NULL);
        random_num3 = generateRandomNum(0, 0, array_count - 1, NULL);
    
        sprintf(return_tmp_num, "%c%c%c", str_tmp_num[random_num1], str_tmp_num[random_num2], str_tmp_num[random_num3]);
        
        // 前に試したことがない数字 && ルール通りの数字
        if (check_history(atoi(return_tmp_num)) && ruleNum(return_tmp_num)) {flag = false;}
    }
    strcpy(computer_guess_num, return_tmp_num);
    guess_history[round_count] = atoi(computer_guess_num);
}
