#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Order {
    int orderId;
    int quantity;
    char customerName[50];
    char productName[50];
    struct Order *next;
};

struct Queue {
    struct Order *front;
    struct Order *rear;
};

void initQueue(struct Queue *queue) {
    queue->front = queue->rear = NULL;
}

bool isEmpty(struct Queue *queue) {
    return (queue->front == NULL);
}

void enqueue(struct Queue *queue, int orderId, int quantity, const char *customerName, const char *productName) {
    struct Order *newOrder = (struct Order *)malloc(sizeof(struct Order));
    if (newOrder == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newOrder->orderId = orderId;
    newOrder->quantity = quantity;
    int i;
    for (i = 0; i < 50 && customerName[i] != '\0'; i++) {
        newOrder->customerName[i] = customerName[i];
    }
    newOrder->customerName[i] = '\0';
    for (i = 0; i < 50 && productName[i] != '\0'; i++) {
        newOrder->productName[i] = productName[i];
    }
    newOrder->productName[i] = '\0';
    newOrder->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newOrder;
    } else {
        queue->rear->next = newOrder;
        queue->rear = newOrder;
    }
}

void dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    struct Order *temp = queue->front;
    queue->front = queue->front->next;
    printf("Dequeued Order:\n");
    printf("Order ID: %d\n", temp->orderId);
    printf("Quantity: %d\n", temp->quantity);
    printf("Customer Name: %s\n", temp->customerName);
    printf("Product Name: %s\n", temp->productName);
    free(temp);
}

void displayNextOrder(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Next Order to process:\n");
    printf("Order ID: %d\n", queue->front->orderId);
    printf("Quantity: %d\n", queue->front->quantity);
    printf("Customer Name: %s\n", queue->front->customerName);
    printf("Product Name: %s\n", queue->front->productName);
}

void displayOrders(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Orders in the Queue:\n");
    struct Order *current = queue->front;
    while (current != NULL) {
        printf("Order ID: %d\n", current->orderId);
        printf("Quantity: %d\n", current->quantity);
        printf("Customer Name: %s\n", current->customerName);
        printf("Product Name: %s\n", current->productName);
        current = current->next;
    }
}

void updateOrder(struct Queue *queue, int orderId, int quantity, const char *customerName, const char *productName) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    struct Order *current = queue->front;
    while (current != NULL) {
        if (current->orderId == orderId) {
            current->quantity = quantity;
            int i;
            for (i = 0; i < 50 && customerName[i] != '\0'; i++) {
                current->customerName[i] = customerName[i];
            }
            current->customerName[i] = '\0';
            for (i = 0; i < 50 && productName[i] != '\0'; i++) {
                current->productName[i] = productName[i];
            }
            current->productName[i] = '\0';
            printf("Order updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Order not found!\n");
}

void deleteOrder(struct Queue *queue, int orderId) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    struct Order *current = queue->front;
    struct Order *prev = NULL;
    while (current != NULL) {
        if (current->orderId == orderId) {
            if (current == queue->front) {
                queue->front = queue->front->next;
                free(current);
                printf("Order deleted successfully!\n");
                return;
            }
            prev->next = current->next;
            free(current);
            printf("Order deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Order not found!\n");
}

void displayMenu() {
    printf("\nOrder Management System\n");
    printf("1. New Order\n");
    printf("2. Update Order\n");
    printf("3. Delete Order\n");
    printf("4. Process Next Order with Confirmation\n");
    printf("5. Display All Orders\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Queue orderQueue;
    initQueue(&orderQueue);
    int choice, orderId, quantity;
    char customerName[50], productName[50];

    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Order ID: ");
                scanf("%d", &orderId);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                printf("Enter Customer Name: ");
                scanf("%s", customerName);
                printf("Enter Product Name: ");
                scanf("%s", productName);
                enqueue(&orderQueue, orderId, quantity, customerName, productName);
                printf("Order added successfully!\n");
                break;
            case 2:
                printf("Enter Order ID to update: ");
                scanf("%d", &orderId);
                printf("Enter new Quantity: ");
                scanf("%d", &quantity);
                printf("Enter new Customer Name: ");
                scanf("%s", customerName);
                printf("Enter new Product Name: ");
                scanf("%s", productName);
                updateOrder(&orderQueue, orderId, quantity, customerName, productName);
                break;
            case 3:
                printf("Enter Order ID to delete: ");
                scanf("%d", &orderId);
                deleteOrder(&orderQueue, orderId);
                break;
            case 4:
                displayNextOrder(&orderQueue);
                dequeue(&orderQueue);
                break;
            case 5:
                displayOrders(&orderQueue);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
