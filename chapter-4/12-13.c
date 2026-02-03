#include <stdio.h>
#define MAXSIZE 100

int itoa(char [], int);

void reverse(char arr[], int begin, int end);

void reverse(char s[], int begin, int end) {
    if (begin < end) {
        char temp = s[begin];
        s[begin] = s[end];
        s[end] = temp;
        
        reverse(s, begin+1, end-1);
    }
}

int itoa(char arr[], int n) {
    static int i=0;
    static int size = 0;
    if (n/10) { 
        size++;
        itoa(arr, n/10);
    }
    arr[i++] = n%10 + '0';

    if (size == i) 
        arr[i] = '\0';
    return i;
}

int main(void) {
    char arr[MAXSIZE];

    int size = itoa(arr, 151);
    reverse(arr, 0, size-1); 
    printf("array is %s", arr);
}
