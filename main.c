#include <stdio.h>
#include <string.h>
#define MAX 100
#define IsNum(c) ('0' <= (c) && (c) <= '9')
#define IsOp(c) ('A' <= (c) && (c) <= 'D')
#define Rate(x) ((float)(x) / all * 100)

int all;
int true;
int each[4];

char FindOp(char []);
char FindAns(char []);

int main() {
    FILE *input = fopen("questions.txt", "r"); //路径不能含中文字符
    if(input == NULL) {
        printf("error");
        return -1;
    }
    char c, op;
    char s[MAX];
    int len[4];
    int i;
    while((c = fgetc(input)) != EOF) { 
        if(IsNum(c) == 0) continue;
        if((c = fgetc(input)) == '.') { //找到题目
            all++;
            //归零
            for(i = 1; i < 4; i++) 
                len[i] = 0;
            while((fgets(s, MAX, input)) != NULL && strstr(s, "答案") == NULL) { //还没有出现答案
                if(strchr(s, '.')) { //找到选项
                    op = FindOp(s);
                    len[op - 'A'] = strlen(s);
                }   
            }  
            //找到最大长度
            int max = 0;
            for(i = 1; i < 4; i++) {
                if(len[i] > len[max] || (len[i] == len[max] && i == 1))
                    max = i;
            }
            //找到答案
            char ans = FindAns(s);
            if(ans - 'A' == max)
                true++;
            each[ans - 'A']++;
        }
        else 
            ungetc(c, input);
    }
    printf("all:%d\ntrue:%d\ntrue rate:%.2f%%\n", all, true, Rate(true));
    printf("A:%d(%.2f%%)\nB:%d(%.2f%%)\nC:%d(%.2f%%)\nD:%d(%.2f%%)\n", each[0], Rate(each[0]), each[1], Rate(each[1]), each[2], Rate(each[2]), each[3], Rate(each[3]));
    return 0;
}

char FindOp(char s[]) {
    unsigned int i;
    for(i = 0; i < strlen(s); i++) 
        if(IsOp(s[i]) && s[i + 1] == '.')
            return s[i];
    return 0;
}

char FindAns(char s[]) {
    unsigned int i;
    for(i = 0; i < strlen(s); i++) 
        if(IsOp(s[i]))
            return s[i];
    return 0;
}