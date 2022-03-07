#include<stdio.h>
#include <string.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;
Node* input_LinkedList() {
    char str[1024];
    char* delim = " ";
    scanf("%[^\n]", str);
    Node* head = (Node*)malloc(sizeof(Node));
    Node* end = head;
    Node* node;
    int count = 0;
    char* p = strtok(str, delim);
    head->data = atoi(p);
    count++;
    while ((p = strtok(NULL, delim))) {
        node = (Node*)malloc(sizeof(Node));
        node->data = atoi(p);
        head->next = node;
        head = head->next;
        count++;
    }
    return end;
}
int main() {
    Node* head = input_LinkedList();
    int positive[1024];
    int pos_count = 0;
    int negative[1024];
    int neg_count = 0;
    while (head != NULL) {
        if (head->data > 0) {
            positive[pos_count++] = head->data;
        }
        else {
            negative[neg_count++] = head->data;
        }
        head = head->next;
    }
    for (int i = pos_count - 1; i >= 0; i--) {
        printf("%5d", positive[i]);
    }
    printf("\n");
    for (int i = 0; i < neg_count; i++) {
        printf("%5d", negative[i]);
    }
    printf("\n");
}