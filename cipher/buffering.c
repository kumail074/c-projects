#include <stdio.h>

int main(){
    char buffer[BUFSIZ];
    int a, b;

    setbuf(stdout, buffer);

    printf("type a letter: ");
    a = getchar();
    printf("type a letter: ");
    b = getchar();

    printf("%c %c\n", a, b);
    return 0;
  }
