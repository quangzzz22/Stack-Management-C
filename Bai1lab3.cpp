#include <stdio.h>
#include <stdlib.h>

// a. Khai báo c?u trúc stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

// b. Vi?t th? t?c kh?i t?o stack r?ng
void khoi_tao_stack(Stack* s) {
    s->top = NULL;
}

// c. Vi?t th? t?c xét stack r?ng
int stack_rong(Stack* s) {
    return s->top == NULL ? 1 : 0;
}

// d. Vi?t th? t?c thêm m?t ph?n t? vào stack (PUSH)
void push(Stack* s, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Loi: Khong du bo nho!\n");
        return;
    }
    node->data = value;
    node->next = s->top;
    s->top = node;
}

// e. Vi?t th? t?c xoá m?t ph?n t? trong stack (POP)
int pop(Stack* s) {
    if (stack_rong(s)) {
        printf("Loi: Stack rong, khong the pop!\n");
        return -1;
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

// Hàm d? xem ph?n t? d?u stack (không xoá)
int top(Stack* s) {
    if (stack_rong(s)) {
        printf("Loi: Stack rong!\n");
        return -1;
    }
    return s->top->data;
}

// f. Áp d?ng stack d? d?i s? h? th?p phân sang h? nh? phân
void doi_sang_nhi_phan(int n) {
    if (n == 0) {
        printf("So nhi phan: 0\n");
        return;
    }
    
    Stack s;
    khoi_tao_stack(&s);
    
    // Chia n cho 2 liên ti?p và luu ph?n du vào stack
    int temp = n;
    while (temp > 0) {
        int du = temp % 2;
        push(&s, du);
        temp = temp / 2;
    }
    
    // L?y các ph?n t? t? stack d? in ra (t? bit cao d?n bit th?p)
    printf("So nhi phan: ");
    while (!stack_rong(&s)) {
        printf("%d", pop(&s));
    }
    printf("\n");
}

// Hàm in ra các ph?n t? trong stack (không xoá)
void in_stack(Stack* s) {
    if (stack_rong(s)) {
        printf("Stack rong!\n");
        return;
    }
    printf("Cac phan tu trong stack (tu tren xuong duoi): ");
    Node* current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Hàm xoá toàn b? stack
void xoa_stack(Stack* s) {
    while (!stack_rong(s)) {
        pop(s);
    }
}

int main() {
    Stack stack;
    
    printf("===== QUAN LY STACK =====\n\n");
    
    // b. Kh?i t?o stack r?ng
    khoi_tao_stack(&stack);
    printf("1. Khoi tao stack rong\n");
    printf("   Stack rong: %s\n\n", stack_rong(&stack) ? "Co" : "Khong");
    
    // d. Thêm các ph?n t? vào stack
    printf("2. Them cac phan tu vao stack: 5, 10, 15, 20\n");
    push(&stack, 5);
    push(&stack, 10);
    push(&stack, 15);
    push(&stack, 20);
    in_stack(&stack);
    printf("\n");
    
    // c. Xét stack r?ng
    printf("3. Kiem tra stack rong: %s\n\n", stack_rong(&stack) ? "Co" : "Khong");
    
    // Xem ph?n t? d?u
    printf("4. Phan tu o dau stack: %d\n\n", top(&stack));
    
    // e. Xoá các ph?n t? t? stack
    printf("5. Lay va xoa phan tu khoi stack:\n");
    printf("   Pop: %d\n", pop(&stack));
    printf("   Pop: %d\n", pop(&stack));
    in_stack(&stack);
    printf("\n");
    
    // Xoá toàn b? stack
    xoa_stack(&stack);
    
    // f. Chuy?n d?i s? t? h? 10 sang h? 2
    printf("6. Chuyen doi tu he 10 sang he 2:\n");
    printf("   ");
    doi_sang_nhi_phan(10);
    printf("   ");
    doi_sang_nhi_phan(25);
    printf("   ");
    doi_sang_nhi_phan(100);
    printf("   ");
    doi_sang_nhi_phan(0);
    
    return 0;
}
