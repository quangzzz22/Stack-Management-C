#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Kh?i t?o stack
void khoi_tao(Stack* s) {
    s->top = -1;
}

// Ki?m tra stack r?ng
int stack_rong(Stack* s) {
    return s->top == -1;
}

// Ki?m tra stack d?y
int stack_day(Stack* s) {
    return s->top == MAX - 1;
}

// L?y kích thu?c stack
int kich_thuoc(Stack* s) {
    return s->top + 1;
}

// Thêm ph?n t? vào stack (PUSH)
void push(Stack* s, int value) {
    if (stack_day(s)) {
        printf("FULL\n");
        return;
    }
    s->arr[++s->top] = value;
}

// Xoá ph?n t? kh?i stack (POP)
int pop(Stack* s) {
    if (stack_rong(s)) {
        printf("EMPTY\n");
        return -1;
    }
    return s->arr[s->top--];
}

// Xem ph?n t? d?u stack (TOP)
int top_stack(Stack* s) {
    if (stack_rong(s)) {
        printf("EMPTY\n");
        return -1;
    }
    return s->arr[s->top];
}

// In ra các ph?n t? trong stack
void in_stack(Stack* s) {
    if (stack_rong(s)) {
        printf("Stack rong!\n");
        return;
    }
    printf("Stack (tu tren xuong duoi): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    khoi_tao(&stack);
    
    char command[20];
    int value;
    
    printf("===== STACK BANG MANG (MAX = %d) =====\n", MAX);
    printf("Cac lenh: PUSH <value>, POP, TOP, SIZE, PRINT, END\n\n");
    
    while (1) {
        printf("Lenh: ");
        scanf("%s", command);
        
        if (strcmp(command, "PUSH") == 0) {
            scanf("%d", &value);
            if (stack_day(&stack)) {
                printf("FULL\n");
            } else {
                push(&stack, value);
                printf("Them %d vao stack\n", value);
            }
        }
        else if (strcmp(command, "POP") == 0) {
            if (stack_rong(&stack)) {
                printf("EMPTY\n");
            } else {
                int val = pop(&stack);
                printf("%d\n", val);
            }
        }
        else if (strcmp(command, "TOP") == 0) {
            if (stack_rong(&stack)) {
                printf("EMPTY\n");
            } else {
                printf("%d\n", top_stack(&stack));
            }
        }
        else if (strcmp(command, "SIZE") == 0) {
            printf("%d\n", kich_thuoc(&stack));
        }
        else if (strcmp(command, "PRINT") == 0) {
            in_stack(&stack);
        }
        else if (strcmp(command, "END") == 0) {
            printf("Ket thuc chuong trinh!\n");
            break;
        }
        else {
            printf("Lenh khong hop le!\n");
        }
    }
    
    return 0;
}
