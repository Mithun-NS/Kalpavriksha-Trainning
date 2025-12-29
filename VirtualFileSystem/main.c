#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 1024

typedef struct FreeBlock {
    int index;
    struct FreeBlock *prev;
    struct FreeBlock *next;
} FreeBlock;

typedef struct FileNode {
    char name[64];
    int isDirectory;
    int blockPointers[NUM_BLOCKS];
    int blockCount;
    struct FileNode *next;
    struct FileNode *parent;
    struct FileNode *child;
} FileNode;

unsigned char virtualDisk[NUM_BLOCKS][BLOCK_SIZE];
FreeBlock *freeListHead = NULL;
FileNode *root = NULL;
FileNode *currentDir = NULL;

void initializeFreeBlocks() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        FreeBlock *node = malloc(sizeof(FreeBlock));
        node->index = i;
        node->next = node->prev = NULL;
        if (!freeListHead) freeListHead = node;
        else {
            FreeBlock *t = freeListHead;
            while (t->next) t = t->next;
            t->next = node;
            node->prev = t;
        }
    }
}

FreeBlock* getFreeBlock() {
    if (!freeListHead) return NULL;
    FreeBlock *temp = freeListHead;
    freeListHead = freeListHead->next;
    if (freeListHead) freeListHead->prev = NULL;
    temp->next = temp->prev = NULL;
    return temp;
}

void returnFreeBlock(int index) {
    FreeBlock *node = malloc(sizeof(FreeBlock));
    node->index = index;
    node->next = node->prev = NULL;
    if (!freeListHead) freeListHead = node;
    else {
        FreeBlock *t = freeListHead;
        while (t->next) t = t->next;
        t->next = node;
        node->prev = t;
    }
}

FileNode* createNode(const char *name, int isDir, FileNode *parent) {
    FileNode *node = malloc(sizeof(FileNode));
    strcpy(node->name, name);
    node->isDirectory = isDir;
    node->child = NULL;
    node->next = NULL;
    node->parent = parent;
    node->blockCount = 0;
    for (int i = 0; i < NUM_BLOCKS; i++) node->blockPointers[i] = -1;
    return node;
}

void insertChild(FileNode *parent, FileNode *child) {
    if (!parent->child) {
        parent->child = child;
        child->next = child;
    } else {
        FileNode *t = parent->child;
        while (t->next != parent->child) t = t->next;
        t->next = child;
        child->next = parent->child;
    }
}

FileNode* findChild(FileNode *dir, const char *name) {
    if (!dir->child) return NULL;
    FileNode *t = dir->child;
    do {
        if (strcmp(t->name, name) == 0) return t;
        t = t->next;
    } while (t != dir->child);
    return NULL;
}

void writeFile(FileNode *file, const char *content) {
    int len = strlen(content);
    int blocksNeeded = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = 0; i < file->blockCount; i++)
        if (file->blockPointers[i] >= 0) returnFreeBlock(file->blockPointers[i]);
    file->blockCount = 0;

    for (int b = 0; b < blocksNeeded; b++) {
        FreeBlock *blk = getFreeBlock();
        if (!blk) {
            printf("Disk full\n");
            return;
        }
        int idx = blk->index;
        free(blk);
        file->blockPointers[file->blockCount++] = idx;

        for (int j = 0; j < BLOCK_SIZE; j++) {
            int pos = b * BLOCK_SIZE + j;
            virtualDisk[idx][j] = (pos < len) ? content[pos] : 0;
        }
    }
}

void readFile(FileNode *file) {
    if (file->blockCount == 0) {
        printf("File empty\n");
        return;
    }
    for (int i = 0; i < file->blockCount; i++) {
        int idx = file->blockPointers[i];
        for (int j = 0; j < BLOCK_SIZE && virtualDisk[idx][j]; j++)
            putchar(virtualDisk[idx][j]);
    }
    printf("\n");
}

void deleteFile(FileNode *parent, FileNode *file) {
    for (int i = 0; i < file->blockCount; i++)
        if (file->blockPointers[i] >= 0) returnFreeBlock(file->blockPointers[i]);

    FileNode *cur = parent->child, *prev = NULL;
    do {
        if (cur == file) break;
        prev = cur;
        cur = cur->next;
    } while (cur != parent->child);

    if (cur == parent->child && cur->next == cur) parent->child = NULL;
    else {
        if (parent->child == cur) parent->child = cur->next;
        prev->next = cur->next;
    }
    free(file);
}

void listDirectory(FileNode *dir) {
    if (!dir->child) {
        printf("(empty)\n");
        return;
    }
    FileNode *t = dir->child;
    do {
        printf("%s%s\n", t->name, t->isDirectory ? "/" : "");
        t = t->next;
    } while (t != dir->child);
}

void showDiskStatus() {
    int freeCount = 0;
    FreeBlock *t = freeListHead;
    while (t) {
        freeCount++;
        t = t->next;
    }
    printf("Total Blocks: %d\nUsed Blocks: %d\nFree Blocks: %d\n",
           NUM_BLOCKS, NUM_BLOCKS - freeCount, freeCount);
}

int main() {
    initializeFreeBlocks();

    root = createNode("/", 1, NULL);
    currentDir = root;

    FileNode *docs = createNode("docs", 1, currentDir);
    insertChild(currentDir, docs);

    FileNode *notes = createNode("notes.txt", 0, docs);
    insertChild(docs, notes);

    writeFile(notes, "This is my first note in the virtual file system.");

    printf("\nContents of /docs:\n");
    listDirectory(docs);

    printf("\nReading file:\n");
    readFile(notes);

    printf("\nDeleting file notes.txt...\n");
    deleteFile(docs, notes);

    printf("\nAfter deletion:\n");
    listDirectory(docs);

    printf("\nDisk status:\n");
    showDiskStatus();

    return 0;
}