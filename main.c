#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

struct list{
    struct words* words;
    struct list* next;
    int number;
    char** command;
};
struct word{
    char* thatchar;
    int buff;
    int len;
};
struct words{
    struct word** word;
    int buff;
    int len;
};

void  addchar(struct word* thatword,int b,int* endofword){
    if (b == -1) {
        puts("\n");
        exit(0);
    }else{
        if ((*thatword).len < (*thatword).buff) {
            (*thatword).thatchar[(*thatword).len] = (char) b;
            (*thatword).len++;
        } else {
            char *helpingword = (char *) malloc((*thatword).buff * sizeof(char));
            for (int i = 0; i < (*thatword).buff; i++) {
                helpingword[i] = (*thatword).thatchar[i];
            }
            free((*thatword).thatchar);
            (*thatword).buff = (*thatword).buff * 2;
            (*thatword).thatchar = (char *) malloc((*thatword).buff * sizeof(char));
            for (int i = 0; i < ((*thatword).buff) / 2; i++) {
                (*thatword).thatchar[i] = helpingword[i];
            }
            free(helpingword);
            (*thatword).thatchar[(*thatword).len] = (char) b;
            (*thatword).len++;
        }
    }
}
struct word* inword(int* endofword) {
    struct word *thatword = (struct word *) malloc(sizeof(struct word));
    (*thatword).buff = 8;
    (*thatword).thatchar = (char *) malloc((*thatword).buff * sizeof(char));
    (*thatword).len = 0;
    int b = getchar();
    while (b == ' ') {
        b = getchar();
    }
    if (b == '\n') {
        *endofword = 1;
        free(thatword->thatchar);
        free(thatword);
        thatword = 0;
    } else {
        if (b == '|') {
            *endofword = -1;
            free(thatword->thatchar);
            free(thatword);
            thatword = 0;
        } else {
            if (b=='<'){
                *endofword = 3;
                free(thatword->thatchar);
                free(thatword);
                thatword = 0;
            } else {
                if (b == '>') {
                    *endofword = 4;
                    free(thatword->thatchar);
                    free(thatword);
                    thatword = 0;

                }else{
                    if (b == '&'){
                        *endofword = 2;
                        free(thatword->thatchar);
                        free(thatword);
                        thatword = 0;
                    }else {
                        while (b != ' ' && b != '\n' && b != '|' && b != '&' && b != '<' && b != '>') {
                            if (b == '\\') {
                                b = getchar();
                                if (b != '\n') {
                                    addchar(thatword, '\\', endofword);
                                    addchar(thatword, b, endofword);
                                }
                                b = getchar();
                            } else {
                                if (b == '\'') {
                                    b = getchar();
                                    while (b != '\'') {
                                        addchar(thatword, b, endofword);
                                        b = getchar();
                                    }
                                    b = getchar();
                                } else {
                                    if (b == '\"') {
                                        b = getchar();
                                        while (b != '\"') {
                                            if (b == '\\') {
                                                b = getchar();
                                                if (b != '\"') {
                                                    addchar(thatword, '\\', endofword);
                                                    addchar(thatword, b, endofword);
                                                } else {
                                                    addchar(thatword, b, endofword);
                                                }
                                            } else {
                                                addchar(thatword, b, endofword);
                                            }
                                            b = getchar();
                                        }
                                        b = getchar();
                                    } else {
                                        addchar(thatword, b, endofword);
                                        b = getchar();
                                    }
                                }
                            }
                        }
                        if (b == '\n') {
                            *endofword = 1;
                        } else {
                            if (b == '|') {
                                *endofword = -1;
                            } else {
                                if (b == '&') {
                                    *endofword = 2;
                                } else {
                                    if (b == '<') {
                                        *endofword = 3;
                                    } else {
                                        if (b == '>') {
                                            *endofword = 4;

                                        }
                                    }
                                }
                            }
                        }
                        if (thatword != 0) {
                            (*thatword).thatchar[(*thatword).len] = 0;
                        }
                    }
                }
            }
        }
    }
    return thatword;
}
struct word* inwordwithfirstsymbol(int* endofword,int b) {
    struct word *thatword = (struct word *) malloc(sizeof(struct word));
    (*thatword).buff = 8;
    (*thatword).thatchar = (char *) malloc((*thatword).buff * sizeof(char));
    (*thatword).len = 0;
    while (b == ' ') {
        b = getchar();
    }
    if (b == '\n') {
        *endofword = 1;
        free(thatword->thatchar);
        free(thatword);
        thatword = 0;
    } else {
        if (b == '|') {
            *endofword = -1;
            free(thatword->thatchar);
            free(thatword);
            thatword = 0;
        } else {
            if (b=='<'){
                *endofword = 3;
                free(thatword->thatchar);
                free(thatword);
                thatword = 0;
            } else {
                if (b == '>') {
                    *endofword = 4;
                    free(thatword->thatchar);
                    free(thatword);
                    thatword = 0;

                }else{
                    if (b == '&'){
                        *endofword = 2;
                        free(thatword->thatchar);
                        free(thatword);
                        thatword = 0;
                    }else {
                        while (b != ' ' && b != '\n' && b != '|' && b != '&' && b != '<' && b != '>') {
                            if (b == '\\') {
                                b = getchar();
                                if (b != '\n') {
                                    addchar(thatword, '\\', endofword);
                                    addchar(thatword, b, endofword);
                                }
                                b = getchar();
                            } else {
                                if (b == '\'') {
                                    b = getchar();
                                    while (b != '\'') {
                                        addchar(thatword, b, endofword);
                                        b = getchar();
                                    }
                                    b = getchar();
                                } else {
                                    if (b == '\"') {
                                        b = getchar();
                                        while (b != '\"') {
                                            if (b == '\\') {
                                                b = getchar();
                                                if (b != '\"') {
                                                    addchar(thatword, '\\', endofword);
                                                    addchar(thatword, b, endofword);
                                                } else {
                                                    addchar(thatword, b, endofword);
                                                }
                                            } else {
                                                addchar(thatword, b, endofword);
                                            }
                                            b = getchar();
                                        }
                                        b = getchar();
                                    } else {
                                        addchar(thatword, b, endofword);
                                        b = getchar();
                                    }
                                }
                            }
                        }
                        if (b == '\n') {
                            *endofword = 1;
                        } else {
                            if (b == '|') {
                                *endofword = -1;
                            } else {
                                if (b == '&') {
                                    *endofword = 2;
                                } else {
                                    if (b == '<') {
                                        *endofword = 3;
                                    } else {
                                        if (b == '>') {
                                            *endofword = 4;

                                        }
                                    }
                                }
                            }
                        }
                        if (thatword != 0) {
                            (*thatword).thatchar[(*thatword).len] = 0;
                        }
                    }
                }
            }
        }
    }
    return thatword;
}
struct words* inwords(int* endofwords,struct word** inputfile,struct word** outputfile,int* whathaveido){
    struct words* thatwords = (struct words*)malloc(sizeof(struct word));
    thatwords->len = 0;
    thatwords->buff = 8;
    (*thatwords).word=(struct word**) malloc((*thatwords).buff * sizeof(struct word*));
    if (*endofwords != 2) {
        *endofwords = 0;
    }
    while(*endofwords == 0 || *endofwords == 4 || *endofwords == 3) {
        if (*endofwords == 3){
            *inputfile = inword(endofwords);
            if (*endofwords == 3){
                *endofwords = 0;
            }
        }else{
            if (*endofwords == 4){
                int q = getchar();
                if (q == '>'){
                    *outputfile = inword(endofwords);
                    *whathaveido = 1;
                }else{
                    *outputfile = inwordwithfirstsymbol(endofwords,q);
                    *whathaveido = -1;
                }
                if (*endofwords == 4){
                    *endofwords = 0;
                }
            }else {
                if ((*thatwords).len < (*thatwords).buff) {
                    (*thatwords).word[(*thatwords).len] = inword(endofwords);
                    (*thatwords).len++;
                } else {
                    struct word **helpingwords = (struct word **) malloc((*thatwords).buff * sizeof(struct word *));
                    for (int i = 0; i < (*thatwords).buff; i++) {
                        helpingwords[i] = (*thatwords).word[i];
                    }
                    free((*thatwords).word);
                    (*thatwords).buff = (*thatwords).buff * 2;
                    (*thatwords).word = (struct word **) malloc((*thatwords).buff * sizeof(struct word *));
                    for (int i = 0; i < ((*thatwords).buff) / 2; i++) {
                        (*thatwords).word[i] = helpingwords[i];
                    }
                    free(helpingwords);
                }
            }
        }
    }
    while (thatwords->word[thatwords->len-1] == 0){
        thatwords->len--;
    }
    return thatwords;
}
struct list* inlist(int* endoflist,struct word** inputfile,struct word** outputfile,int* whathaveido){
    struct list* qq = (struct list*)malloc(sizeof(struct list));
    qq->words = inwords(endoflist,inputfile,outputfile,whathaveido);
    struct list* qq1 = qq;
    qq1->next = 0;
    while (*endoflist == -1){
        qq1->next = (struct list*)malloc(sizeof(struct list));
        qq1->next->words = inwords(endoflist,inputfile,outputfile,whathaveido);
        qq1->next->next = 0;
        qq1=qq1->next;
    }
    return qq;
}

char** translate(struct words* thatwords){
    char** command;
    command = (char **) malloc((thatwords->len +1)* sizeof(char*));
    for (int i = 0; i < thatwords->len; i++) {
        command[i] = (thatwords->word)[i]->thatchar;
    }
    command[thatwords->len] = 0;
    return command;
}

void outcommand(char** command,struct word** inputfile,struct word** outputfile,int* whathaveido, int number , int nnn, int** pipes){
    if (fork() == 0) {
        int inf;
        int outf;
        for (int i=0;i < nnn-1;i++) {
            if (i != number - 2 && i != number - 1) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            if (i == number - 2) {
                close(pipes[i][1]);
                dup2(pipes[i][0], STDIN_FILENO);
            }
            if (i == number - 1) {
                close(pipes[i][0]);
                dup2(pipes[i][1], STDOUT_FILENO);
            }
        }
        if (number==nnn){
            if (*outputfile != 0) {
                if (*whathaveido==-1){
                    outf = open((*outputfile)->thatchar,O_WRONLY | O_TRUNC |  O_CREAT, 0666);
                    dup2(outf,STDOUT_FILENO);
                }else{
                    outf = open((*outputfile)->thatchar,O_WRONLY | O_APPEND | O_CREAT, 0666);
                    dup2(outf,STDOUT_FILENO);
                }
            }

        }

        if (number == 1){
            if (*inputfile != 0){
                inf = open((*inputfile)->thatchar,O_RDONLY,0666);
                dup2(inf,STDIN_FILENO);
            }
        }
        execvp(command[0], command);
        close(pipes[number-1][0]);
        close(pipes[number][1]);
        exit(0);
    }
}
void outcommandwithfon(char** command,struct word** inputfile,struct word** outputfile,int* whathaveido, int number , int nnn, int** pipes){
    int qqq = fork();
    int status;
    if (qqq == 0) {
        int inf;
        int outf;
        for (int i=0;i < nnn-1;i++){
            if (i != number-2 && i!=number-1){
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            if (i == number-2){
                close(pipes[i][1]);
                dup2(pipes[i][0],STDIN_FILENO);
            }
            if (i == number-1){
                close(pipes[i][0]);
                dup2(pipes[i][1],STDOUT_FILENO);

            }
        }
        if (number==nnn){
            if (*outputfile != 0) {
                if (*whathaveido==-1){
                    outf = open((*outputfile)->thatchar,O_WRONLY | O_TRUNC |  O_CREAT, 0666);
                    dup2(outf,STDOUT_FILENO);
                }else{
                    outf = open((*outputfile)->thatchar,O_WRONLY | O_APPEND | O_CREAT, 0666);
                    dup2(outf,STDOUT_FILENO);
                }
            }

        }
        if (number == 1){
            if (*inputfile != 0){
                inf = open((*inputfile)->thatchar,O_RDONLY,0666);
                dup2(inf,STDIN_FILENO);
            }
        }
        execvp(command[0], command);
        close(pipes[number-1][0]);
        close(pipes[number][1]);
        exit(0);
    }else{
        waitpid(qqq,&status,WNOHANG);
    }
}

void outlist(struct list* commands,struct word** inputfile,struct word** outputfile,int* whathaveido, int nnn,int** pipes){

    if (commands != 0){
        outcommand(commands->command,inputfile,outputfile,whathaveido,commands->number,nnn,pipes);
        outlist(commands->next,inputfile,outputfile,whathaveido,nnn,pipes);
        for(int i = 0; i< nnn-1;i++){
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        while(wait(0)!=-1){};
    }

}
void outlist1(struct list* commands,struct word** inputfile,struct word** outputfile,int* whathaveido, int nnn,int** pipes){
    if (fork()){
        wait(0);
    }else{
        outlist(commands,inputfile,outputfile,whathaveido,nnn,pipes);
    }
}
void outlistwithfon(struct list* commands,struct word** inputfile,struct word** outputfile,int* whathaveido, int nnn,int** pipes){
    if (commands != 0){
        outcommandwithfon(commands->command,inputfile,outputfile,whathaveido,commands->number,nnn,pipes);
        outlistwithfon(commands->next,inputfile,outputfile,whathaveido,nnn,pipes);
        for(int i = 0; i< nnn-1;i++) {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
    }
}
void dellist(struct list* commands){
    if (commands!=0){
        dellist(commands->next);
        for(int i = 0; i < commands->words->len ; i++){
            free(commands->words->word[i]->thatchar);
            free(commands->words->word[i]);
        }
        free(commands->words->word);
        free(commands->words);
        free(commands->command);
        free(commands);
    }
}

int numeratelist(struct list* commands){
    int i = 0;
    while (commands!=0){
        i++;
        commands->number=i;
        commands->command=translate(commands->words);
        commands=commands->next;
    }
    return i;
}

int main() {
    char way[100];
    struct word *outputfile = 0;
    int whathaveido = 0;
    struct word *inputfile = 0;
    int endoflist = -1;
    struct word *xmxm;
    struct words *thatwords;
    struct list *commands;
    int nnn;
    while(1) {
        getcwd(way,100);
        printf("%s>>тут пиши команду>>",way);
        commands = inlist(&endoflist, &inputfile, &outputfile, &whathaveido);
        if (commands->words->len==0){
            continue;
        }
        nnn = numeratelist(commands);
        if (commands->command[0][0]=='e' && commands->command[0][1]=='x' && commands->command[0][2]=='i' && commands->command[0][3]=='t' && commands->command[0][4]==0){
            break;
        }
        if (commands->words->word == 0){
            continue;
        }
        if (commands->command[0][0]=='c' && commands->command[0][1]=='d'){
            chdir(commands->command[1]);
        }else{
            int **pipes = (int **) malloc((nnn - 1) * sizeof(int *));
            for (int i = 0; i < nnn - 1; i++) {
                pipes[i] = (int *) malloc(2 * sizeof(int));
                pipe(pipes[i]);
            }
            if (endoflist == 2) {
                xmxm = inword(&endoflist);
                if (xmxm != 0) {
                    printf("Косяк, знак & не в конце файла, исправь\n");
                    dellist(commands);
                } else {
                    outlistwithfon(commands, &inputfile, &outputfile, &whathaveido, nnn, pipes);
                    if (inputfile != 0) {
                        free(inputfile->thatchar);
                        free(inputfile);
                        inputfile=0;
                    }
                    if (outputfile != 0) {
                        free(outputfile->thatchar);
                        free(outputfile);
                        outputfile=0;
                    }
                }
                if (xmxm != 0) {
                    free(xmxm->thatchar);
                    free(xmxm);
                }
            } else {
                outlist1(commands, &inputfile, &outputfile, &whathaveido, nnn, pipes);
                if (inputfile != 0) {
                    free(inputfile->thatchar);
                    free(inputfile);
                    inputfile=0;
                }
                if (outputfile != 0) {
                    free(outputfile->thatchar);
                    free(outputfile);
                    outputfile=0;
                }
            }
            for (int i = 0; i < nnn - 1; i++) {
                free(pipes[i]);
                pipes[i] = 0;
            }
            if (nnn!=1){
                free(pipes);
                pipes = 0;
            }
        }
        dellist(commands);
    }
    dellist(commands);
 return 0;
}