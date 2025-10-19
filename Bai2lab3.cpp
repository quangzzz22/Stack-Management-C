#include <stdio.h>
#include <stdlib.h>

// a. Khai b�o c?u tr�c queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;  // Con tr? d?u queue (ph?n t? d?u ti�n)
    Node* rear;   // Con tr? cu?i queue (ph?n t? cu?i c�ng)
} Queue;

// b. Vi?t th? t?c kh?i t?o queue r?ng
void khoi_tao_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// c. Vi?t th? t?c x�t queue r?ng
int queue_rong(Queue* q) {
    return q->front == NULL ? 1 : 0;
}

// d. Vi?t th? t?c th�m m?t ph?n t? v�o queue (ENQUEUE)
void enqueue(Queue* q, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Loi: Khong du bo nho!\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    
    if (queue_rong(q)) {
        q->front = node;
    } else {
        q->rear->next = node;
    }
    q->rear = node;
}

// e. Vi?t th? t?c xo� m?t ph?n t? trong queue (DEQUEUE)
int dequeue(Queue* q) {
    if (queue_rong(q)) {
        printf("Loi: Queue rong, khong the dequeue!\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

// H�m d? xem ph?n t? d?u queue (kh�ng xo�)
int front_queue(Queue* q) {
    if (queue_rong(q)) {
        printf("Loi: Queue rong!\n");
        return -1;
    }
    return q->front->data;
}

// H�m d? xem ph?n t? cu?i queue (kh�ng xo�)
int rear_queue(Queue* q) {
    if (queue_rong(q)) {
        printf("Loi: Queue rong!\n");
        return -1;
    }
    return q->rear->data;
}

// H�m in ra c�c ph?n t? trong queue (kh�ng xo�)
void in_queue(Queue* q) {
    if (queue_rong(q)) {
        printf("Queue rong!\n");
        return;
    }
    printf("Cac phan tu trong queue (FIFO - tu trc xuong sau): ");
    Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// H�m xo� to�n b? queue
void xoa_queue(Queue* q) {
    while (!queue_rong(q)) {
        dequeue(q);
    }
}

int main() {
    Queue queue;
    
    printf("===== QUAN LY QUEUE (HANG DOI) =====\n\n");
    
    // b. Kh?i t?o queue r?ng
    khoi_tao_queue(&queue);
    printf("1. Khoi tao queue rong\n");
    printf("   Queue rong: %s\n\n", queue_rong(&queue) ? "Co" : "Khong");
    
    // d. Th�m c�c ph?n t? v�o queue
    printf("2. Them cac phan tu vao queue: 10, 20, 30, 40, 50\n");
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50);
    in_queue(&queue);
    printf("\n");
    
    // c. X�t queue r?ng
    printf("3. Kiem tra queue rong: %s\n\n", queue_rong(&queue) ? "Co" : "Khong");
    
    // Xem ph?n t? d?u v� cu?i
    printf("4. Phan tu o dau queue (front): %d\n", front_queue(&queue));
    printf("   Phan tu o cuoi queue (rear): %d\n\n", rear_queue(&queue));
    
    // e. Xo� c�c ph?n t? t? queue
    printf("5. Lay va xoa phan tu khoi queue (FIFO):\n");
    printf("   Dequeue: %d\n", dequeue(&queue));
    printf("   Dequeue: %d\n", dequeue(&queue));
    in_queue(&queue);
    printf("\n");
    
    // Th�m l?i ph?n t?
    printf("6. Them phan tu: 60, 70\n");
    enqueue(&queue, 60);
    enqueue(&queue, 70);
    in_queue(&queue);
    printf("\n");
    
    // Xo� to�n b? queue
    printf("7. Xoa het queue:\n");
    xoa_queue(&queue);
    printf("   Queue rong: %s\n", queue_rong(&queue) ? "Co" : "Khong");
    
    return 0;
}
