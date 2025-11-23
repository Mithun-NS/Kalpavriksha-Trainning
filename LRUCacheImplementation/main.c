#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000   

typedef struct Node {
    int key;
    char value[100];
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int capacity;
    int size;

    Node* head;     
    Node* tail;    

    Node* map[MAX];  
} LRUCache;

Node* createNode(int key, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

LRUCache* createCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    for(int i = 0; i < MAX; i++)
        cache->map[i] = NULL;
    return cache;
}

void removeNode(LRUCache* cache, Node* node) {
    if (!node) return;
    if (node->prev)
        node->prev->next = node->next;
    else
        cache->head = node->next;   
    if (node->next)
        node->next->prev = node->prev;
    else
        cache->tail = node->prev;   
}

void insertAtHead(LRUCache* cache, Node* node) {
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head)
        cache->head->prev = node;
    cache->head = node;
    if (cache->tail == NULL)
        cache->tail = node;
}

char* get(LRUCache* cache, int key) {
    if (key < 0 || key >= MAX || cache->map[key] == NULL)
        return NULL;
    Node* node = cache->map[key];
    removeNode(cache, node);
    insertAtHead(cache, node);

    return node->value;
}

void put(LRUCache* cache, int key, char* value) {
    if (cache->map[key] != NULL) {
        Node* node = cache->map[key];
        strcpy(node->value, value);
        removeNode(cache, node);
        insertAtHead(cache, node);
        return;
    }
    Node* newNode = createNode(key, value);
    insertAtHead(cache, newNode);
    cache->map[key] = newNode;
    cache->size++;
    if (cache->size > cache->capacity) {
        Node* lru = cache->tail;

        cache->map[lru->key] = NULL;
        removeNode(cache, lru);
        free(lru);

        cache->size--;
    }
}

int main() {
    char command[20];
    int key, capacity;
    char data[100];
    LRUCache* cache = NULL;
    while (1) {
        scanf("%s", command);
        if (strcmp(command, "createCache") == 0) {
            scanf("%d", &capacity);
            cache = createCache(capacity);
        }
        else if (strcmp(command, "put") == 0) {
            scanf("%d %s", &key, data);
            put(cache, key, data);
        }
        else if (strcmp(command, "get") == 0) {
            scanf("%d", &key);
            char* value = get(cache, key);

            if (value == NULL)
                printf("NULL\n");
            else
                printf("%s\n", value);
        }

        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }
    return 0;
}
