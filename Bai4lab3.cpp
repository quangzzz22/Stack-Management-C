#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// ===== STACK FOR CHARACTERS =====
typedef struct {
    char arr[MAX];
    int top;
} CharStack;

void init_char_stack(CharStack* s) {
    s->top = -1;
}

int char_stack_empty(CharStack* s) {
    return s->top == -1;
}

void push_char(CharStack* s, char c) {
    if (s->top < MAX - 1) {
        s->arr[++s->top] = c;
    }
}

char pop_char(CharStack* s) {
    if (char_stack_empty(s)) {
        return '\0';
    }
    return s->arr[s->top--];
}

char top_char(CharStack* s) {
    if (char_stack_empty(s)) {
        return '\0';
    }
    return s->arr[s->top];
}

// ===== STACK FOR STRINGS =====
typedef struct {
    char arr[MAX][MAX];
    int top;
} StringStack;

void init_string_stack(StringStack* s) {
    s->top = -1;
}

int string_stack_empty(StringStack* s) {
    return s->top == -1;
}

void push_string(StringStack* s, char* str) {
    if (s->top < MAX - 1) {
        strcpy(s->arr[++s->top], str);
    }
}

char* pop_string(StringStack* s) {
    if (string_stack_empty(s)) {
        return NULL;
    }
    return s->arr[s->top--];
}

char* top_string(StringStack* s) {
    if (string_stack_empty(s)) {
        return NULL;
    }
    return s->arr[s->top];
}

// ===== PHAN A: KIEM TRA CAP NGOAC =====
int is_opening(char c) {
    return c == '(' || c == '[' || c == '{';
}

int is_closing(char c) {
    return c == ')' || c == ']' || c == '}';
}

int is_matching(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    return 0;
}

int check_brackets(char* str) {
    CharStack stack;
    init_char_stack(&stack);
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        
        if (is_opening(c)) {
            push_char(&stack, c);
        }
        else if (is_closing(c)) {
            if (char_stack_empty(&stack)) {
                return 0;
            }
            char open = pop_char(&stack);
            if (!is_matching(open, c)) {
                return 0;
            }
        }
    }
    
    return char_stack_empty(&stack);
}

// ===== PHAN B: KIEM TRA CAP TAG HTML =====
int extract_tag_name(char* str, int* pos, char* tag_name) {
    if (str[*pos] != '<') {
        return 0;
    }
    
    (*pos)++;
    int is_closing = 0;
    
    // Ki?m tra xem có ph?i </tag> không
    if (str[*pos] == '/') {
        is_closing = 1;
        (*pos)++;
    }
    
    // L?y tên tag (ch? ch? cái thu?ng)
    int len = 0;
    while (str[*pos] != '\0' && str[*pos] != '>' && islower(str[*pos])) {
        tag_name[len++] = str[*pos];
        (*pos)++;
    }
    tag_name[len] = '\0';
    
    // Ki?m tra xem có '>' không
    if (str[*pos] != '>') {
        return 0;
    }
    
    (*pos)++;
    
    // N?u tag_name r?ng thì không h?p l?
    if (len == 0) {
        return 0;
    }
    
    // Tr? v? 1 n?u là opening tag, -1 n?u là closing tag
    return is_closing ? -1 : 1;
}

int check_html_tags(char* str) {
    StringStack stack;
    init_string_stack(&stack);
    
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '<') {
            char tag_name[MAX];
            int tag_type = extract_tag_name(str, &i, tag_name);
            
            if (tag_type == 0) {
                return 0; // Tag không h?p l?
            }
            else if (tag_type == 1) {
                // Opening tag: d?y vào stack
                push_string(&stack, tag_name);
            }
            else {
                // Closing tag: so kh?p v?i stack
                if (string_stack_empty(&stack)) {
                    return 0;
                }
                char* top_tag = pop_string(&stack);
                if (strcmp(top_tag, tag_name) != 0) {
                    return 0;
                }
            }
        }
        else {
            i++;
        }
    }
    
    return string_stack_empty(&stack);
}

int main() {
    printf("===== KIEM TRA DAU NGOAC VA HTML-LIKE TAGS =====\n\n");
    
    // ===== TEST PHAN A =====
    printf("PHAN A: KIEM TRA CAP NGOAC\n");
    printf("================================\n");
    
    char test_brackets[][50] = {
        "([{}])",
        "([)]",
        "{[()]}",
        "((()))",
        "([)]",
        "",
        "(",
        ")"
    };
    
    int num_tests_a = sizeof(test_brackets) / sizeof(test_brackets[0]);
    
    for (int i = 0; i < num_tests_a; i++) {
        printf("Input: \"%s\"  ?  ", test_brackets[i]);
        if (check_brackets(test_brackets[i])) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    printf("\n");
    
    // ===== TEST PHAN B =====
    printf("PHAN B: KIEM TRA CAP TAG HTML\n");
    printf("================================\n");
    
    char test_tags[][100] = {
        "<b><i>ok</i></b>",
        "<b><i></b></i>",
        "<div><p>text</p></div>",
        "<a><b></a></b>",
        "<html></html>",
        "",
        "<b></c>",
        "<b>",
        "</b>"
    };
    
    int num_tests_b = sizeof(test_tags) / sizeof(test_tags[0]);
    
    for (int i = 0; i < num_tests_b; i++) {
        printf("Input: \"%s\"  ?  ", test_tags[i]);
        if (check_html_tags(test_tags[i])) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    printf("\n");
    
    // ===== NHAP TU NGUOI DUNG =====
    printf("NHAP DU LIEU CUA BAN\n");
    printf("================================\n");
    
    char user_input[MAX];
    int choice;
    
    while (1) {
        printf("\nChon:\n");
        printf("1. Kiem tra cap ngoac\n");
        printf("2. Kiem tra cap tag HTML\n");
        printf("3. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar(); // Lo?i b? ký t? newline
        
        if (choice == 1) {
            printf("Nhap chuoi ngoac: ");
            fgets(user_input, MAX, stdin);
            user_input[strcspn(user_input, "\n")] = '\0'; // Xoá newline
            
            if (check_brackets(user_input)) {
                printf("KET QUA: YES\n");
            } else {
                printf("KET QUA: NO\n");
            }
        }
        else if (choice == 2) {
            printf("Nhap chuoi tag HTML: ");
            fgets(user_input, MAX, stdin);
            user_input[strcspn(user_input, "\n")] = '\0'; // Xoá newline
            
            if (check_html_tags(user_input)) {
                printf("KET QUA: YES\n");
            } else {
                printf("KET QUA: NO\n");
            }
        }
        else if (choice == 3) {
            printf("Thoat chuong trinh!\n");
            break;
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    }
    
    return 0;
}
