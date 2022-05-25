#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "w");
    for (int i = 0; i < 1500; ++i){
        fprintf(fp, "%d->", i);
    }
    return 0;
}
