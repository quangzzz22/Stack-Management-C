#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 1000

// ===== STACK FOR OPERATORS =====
typedef struct {
    char arr[MAX];
    int top;
} OpStack;

void init_op_stack(OpStack* s) {
    s->top = -1;
}

int op_stack_empty(OpStack* s) {
    return s->top == -1;
}

void push_op(OpStack* s, char c) {
    if (s->top < MAX - 1) {
        s->arr[++s->top] = c;
    }
}

char pop_op(OpStack* s) {
    if (op_stack_empty(s)) {
        return '\0';
    }
    return s->arr[s->top--];
}

char top_op(OpStack* s) {
    if (op_stack_empty(s)) {
        return '\0';
    }
    return s->arr[s->top];
}

// ===== STACK FOR NUMBERS (DOUBLE) =====
typedef struct {
    double arr[MAX];
    int top;
} NumStack;

void init_num_stack(NumStack* s) {
    s->top = -1;
}

int num_stack_empty(NumStack* s) {
    return s->top == -1;
}

void push_num(NumStack* s, double val) {
    if (s->top < MAX - 1) {
        s->arr[++s->top] = val;
    }
}

double pop_num(NumStack* s) {
    if (num_stack_empty(s)) {
        return 0;
    }
    return s->arr[s->top--];
}

// ===== OPERATOR FUNCTIONS =====
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int is_right_associative(char op) {
    return op == '^';
}

double apply_operator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Loi: Chia cho 0!\n");
                return 0;
            }
            return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// ===== INFIX TO POSTFIX (SHUNTING-YARD ALGORITHM) =====
void infix_to_postfix(char* infix, char* postfix) {
    OpStack op_stack;
    init_op_stack(&op_stack);
    
    int postfix_idx = 0;
    int infix_idx = 0;
    
    while (infix[infix_idx] != '\0') {
        char c = infix[infix_idx];
        
        // Bo qua khoang trang
        if (c == ' ') {
            infix_idx++;
            continue;
        }
        
        // Neu la chu so
        if (isdigit(c)) {
            while (isdigit(infix[infix_idx])) {
                postfix[postfix_idx++] = infix[infix_idx++];
            }
            postfix[postfix_idx++] = ' ';
            continue;
        }
        
        // Neu la toan tu
        if (is_operator(c)) {
            int prec = get_precedence(c);
            int right_assoc = is_right_associative(c);
            
            while (!op_stack_empty(&op_stack)) {
                char top = top_op(&op_stack);
                if (top == '(') break;
                
                int top_prec = get_precedence(top);
                
                if (right_assoc) {
                    if (top_prec > prec) {
                        postfix[postfix_idx++] = pop_op(&op_stack);
                        postfix[postfix_idx++] = ' ';
                    } else {
                        break;
                    }
                } else {
                    if (top_prec >= prec) {
                        postfix[postfix_idx++] = pop_op(&op_stack);
                        postfix[postfix_idx++] = ' ';
                    } else {
                        break;
                    }
                }
            }
            
            push_op(&op_stack, c);
            infix_idx++;
            continue;
        }
        
        // Neu la ngoac mo
        if (c == '(') {
            push_op(&op_stack, c);
            infix_idx++;
            continue;
        }
        
        // Neu la ngoac dong
        if (c == ')') {
            while (!op_stack_empty(&op_stack) && top_op(&op_stack) != '(') {
                postfix[postfix_idx++] = pop_op(&op_stack);
                postfix[postfix_idx++] = ' ';
            }
            
            if (!op_stack_empty(&op_stack)) {
                pop_op(&op_stack); // Xoa ngoac mo
            }
            
            infix_idx++;
            continue;
        }
        
        infix_idx++;
    }
    
    // Xoa tat ca toan tu con lai
    while (!op_stack_empty(&op_stack)) {
        postfix[postfix_idx++] = pop_op(&op_stack);
        postfix[postfix_idx++] = ' ';
    }
    
    postfix[postfix_idx] = '\0';
}

// ===== EVALUATE POSTFIX EXPRESSION =====
double evaluate_postfix(char* postfix) {
    NumStack num_stack;
    init_num_stack(&num_stack);
    
    int i = 0;
    while (postfix[i] != '\0') {
        char c = postfix[i];
        
        // Bo qua khoang trang
        if (c == ' ') {
            i++;
            continue;
        }
        
        // Neu la chu so
        if (isdigit(c)) {
            double num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push_num(&num_stack, num);
            continue;
        }
        
        // Neu la toan tu
        if (is_operator(c)) {
            if (num_stack.top < 1) {
                printf("Loi: Bieu thuc khong hop le!\n");
                return 0;
            }
            
            double b = pop_num(&num_stack);
            double a = pop_num(&num_stack);
            double result = apply_operator(a, b, c);
            push_num(&num_stack, result);
            i++;
            continue;
        }
        
        i++;
    }
    
    if (num_stack.top == 0) {
        return num_stack.arr[0];
    } else {
        printf("Loi: Bieu thuc khong hop le!\n");
        return 0;
    }
}

int main() {
    printf("===== CHUYEN TRUNG TO -> HAU TO VA TINH GIA TRI =====\n");
    printf("(Shunting-Yard Algorithm)\n\n");
    
    // ===== TEST CASES =====
    char test_cases[][100] = {
        "3 + 4 * ( 2 - 1 )",
        "( 1 + 2 ) * 3",
        "10 + 2 * 6",
        "( 10 + 2 ) * 6",
        "2 ^ 3 + 1",
        "10 / 2 + 3",
        "100 - 50 * 2",
        "( 3 + 4 ) * ( 5 - 2 )"
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("CAC TEST CASES:\n");
    printf("=================================\n\n");
    
    for (int i = 0; i < num_tests; i++) {
        char postfix[MAX];
        infix_to_postfix(test_cases[i], postfix);
        double result = evaluate_postfix(postfix);
        
        printf("Trung to:  %s\n", test_cases[i]);
        printf("Hau to:    %s\n", postfix);
        printf("Gia tri:   %.0f\n", result);
        printf("---------------------------------\n");
    }
    
    // ===== NHAP TU NGUOI DUNG =====
    printf("\nNHAP BIEU THUC CUA BAN\n");
    printf("=================================\n");
    
    char infix[MAX];
    char postfix[MAX];
    
    while (1) {
        printf("\nNhap bieu thuc (hoac 'EXIT' de thoat): ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = '\0';
        
        if (strcmp(infix, "EXIT") == 0) {
            printf("Thoat chuong trinh!\n");
            break;
        }
        
        if (strlen(infix) == 0) {
            continue;
        }
        
        infix_to_postfix(infix, postfix);
        double result = evaluate_postfix(postfix);
        
        printf("Trung to:  %s\n", infix);
        printf("Hau to:    %s\n", postfix);
        printf("Gia tri:   %.0f\n", result);
    }
    
    return 0;
}
