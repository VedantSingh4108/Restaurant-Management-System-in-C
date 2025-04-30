#include <stdio.h>
#include <stdlib.h>
#define MAX 20

struct Queue {
    int front, rear;
    int items[MAX];
};

void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct Queue *q) {
    return ((q->rear + 1) % MAX == q->front);
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

void addCustomerToWaitlist(struct Queue *q, int value) {
    if (isFull(q)) {
        printf("Sorry, the waitlist is full! Cannot add customer %d.\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    printf("Customer %d added to the waitlist.\n", value);
}

int serveCustomer(struct Queue *q) {
    if (isEmpty(q)) {
        printf("The waitlist is empty! No customer to serve.\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return item;
}

int peekNextCustomer(struct Queue *q) {
    if (isEmpty(q)) {
        printf("The waitlist is empty! No customer to serve.\n");
        return -1;
    }
    return q->items[q->front];
}

void removeCustomerFromWaitlist(struct Queue *q, int value) {
    if (isEmpty(q)) {
        printf("The waitlist is empty! Cannot remove customer %d.\n", value);
        return;
    }
    int found = 0;
    int count = (q->rear - q->front + MAX) % MAX + 1;
    for (int i = 0; i < count; i++) {
        int index = (q->front + i) % MAX;
        if (q->items[index] == value) {
            found = 1;
            for (int j = index; j != q->rear; j = (j + 1) % MAX) {
                q->items[j] = q->items[(j + 1) % MAX];
            }
            q->rear = (q->rear - 1 + MAX) % MAX;
            if (q->rear == -1) {
                q->front = -1;
            }
            printf("Customer %d removed from the waitlist.\n", value);
            break;
        }
    }
    if (!found) {
        printf("Customer %d not found in the waitlist.\n", value);
    }
}

void displayWaitlist(struct Queue *q) {
    if (isEmpty(q)) {
        printf("The waitlist is empty!\n");
        return;
    }
    printf("Current customers on the waitlist: ");
    int count = (q->rear - q->front + MAX) % MAX + 1;
    for (int i = 0; i < count; i++) {
        printf("%d ", q->items[(q->front + i) % MAX]);
    }
    printf("\n");
}

void showMenu() {
    printf("\nRestaurant Operations:\n");
    printf("1. Add Customer to the Waitlist\n");
    printf("2. Serve Next Customer\n");
    printf("3. Remove Customer from the Waitlist\n");
    printf("4. Peek Next Customer to Serve\n");
    printf("5. Display Waitlist\n");
    printf("6. Close the Restaurant\n");
    printf("Enter your choice: ");
}

void showAvailableSeats(struct Queue *q) {
    int availableSeats = MAX - ((q->rear - q->front + MAX) % MAX) - 1;
    printf("Seats available: %d\n", availableSeats);
}

void handleInvalidChoice() {
    printf("Invalid choice! Please try again.\n");
}

void showRestaurantStatus(int isOpen) {
    if (isOpen) {
        printf("Restaurant is Open!\n");
    } else {
        printf("Restaurant is Closed!\n");
    }
}

int main() {
    struct Queue q;
    int isOpen = 1;
    initQueue(&q);

    addCustomerToWaitlist(&q, 101);
    addCustomerToWaitlist(&q, 102);
    addCustomerToWaitlist(&q, 103);

    int choice, customerId;

    while (isOpen) {
        showRestaurantStatus(isOpen);
        showMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            handleInvalidChoice();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter customer ID to add to the waitlist: ");
                if (scanf("%d", &customerId) != 1) {
                    while (getchar() != '\n');
                    handleInvalidChoice();
                    continue;
                }
                addCustomerToWaitlist(&q, customerId);
                showAvailableSeats(&q);
                break;

            case 2:
                customerId = serveCustomer(&q);
                if (customerId != -1) {
                    printf("Serving customer %d\n", customerId);
                }
                showAvailableSeats(&q);
                break;
                
            case 3:
                printf("Enter customer ID to remove from the waitlist: ");
                if (scanf("%d", &customerId) != 1) {
                    while (getchar() != '\n');
                    handleInvalidChoice();
                    continue;
                }
                removeCustomerFromWaitlist(&q, customerId);
                showAvailableSeats(&q);
                break;

            case 4:
                customerId = peekNextCustomer(&q);
                if (customerId != -1) {
                    printf("Next customer to be served: %d\n", customerId);
                }
                break;

            case 5:
                displayWaitlist(&q);
                showAvailableSeats(&q);
                break;

            case 6:
                printf("Closing the restaurant...\n");
                isOpen = 0;
                break;

            default:
                handleInvalidChoice();
        }
    }
    printf("Restaurant is now closed. Exiting program...\n");
    return 0;
}
