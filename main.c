#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

// Function to view all products
void viewAll(struct Product *p, int n) {
    if (n == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\n========= PRODUCT LIST =========\n");
    for (int i = 0; i < n; i++) {
        printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               p[i].id, p[i].name, p[i].price, p[i].quantity);
    }
}

// Function to add a new product
void addProduct(struct Product **p, int *n) {
    *p = realloc(*p, (*n + 1) * sizeof(struct Product));
    if (*p == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter new product details:\n");
    printf("Product ID: ");
    scanf("%d", &(*p)[*n].id);
    getchar();
    printf("Product Name: ");
    fgets((*p)[*n].name, 50, stdin);
    (*p)[*n].name[strcspn((*p)[*n].name, "\n")] = '\0';
    printf("Product Price: ");
    scanf("%f", &(*p)[*n].price);
    printf("Product Quantity: ");
    scanf("%d", &(*p)[*n].quantity);

    (*n)++;
    printf("Product added successfully!\n");
}

void updateQuantity(struct Product *p, int n) {
    int id, newQty, found = 0;
    printf("Enter Product ID to update quantity: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (p[i].id == id) {
            printf("Enter new Quantity: ");
            scanf("%d", &newQty);
            p[i].quantity = newQty;
            printf("Quantity updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product ID not found.\n");
    }
}

void searchByID(struct Product *p, int n) {
    int id, found = 0;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (p[i].id == id) {
            printf("Product Found:\n");
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   p[i].id, p[i].name, p[i].price, p[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

void searchByName(struct Product *p, int n) {
    char searchName[50];
    int found = 0;
    printf("Enter name to search (partial allowed): ");
    getchar();
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    printf("Products Found:\n");
    for (int i = 0; i < n; i++) {
        if (strstr(p[i].name, searchName) != NULL) {
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   p[i].id, p[i].name, p[i].price, p[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching products found.\n");
    }
}

void searchByPrice(struct Product *p, int n) {
    float min, max;
    int found = 0;

    printf("Enter minimum price: ");
    scanf("%f", &min);
    printf("Enter maximum price: ");
    scanf("%f", &max);

    printf("Products in price range:\n");
    for (int i = 0; i < n; i++) {
        if (p[i].price >= min && p[i].price <= max) {
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   p[i].id, p[i].name, p[i].price, p[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found in this price range.\n");
    }
}

void deleteProduct(struct Product **p, int *n) {
    int id, found = 0;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if ((*p)[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                (*p)[j] = (*p)[j + 1];
            }
            *p = realloc(*p, (*n - 1) * sizeof(struct Product));
            (*n)--;
            printf("Product deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

int main() {
    struct Product *inventory;
    int n, choice;

    printf("Enter initial number of products: ");
    scanf("%d", &n);

    inventory = calloc(n, sizeof(struct Product));
    if (inventory == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for product %d:\n", i + 1);
        printf("Product ID: ");
        scanf("%d", &inventory[i].id);
        getchar();
        printf("Product Name: ");
        fgets(inventory[i].name, 50, stdin);
        inventory[i].name[strcspn(inventory[i].name, "\n")] = '\0';
        printf("Product Price: ");
        scanf("%f", &inventory[i].price);
        printf("Product Quantity: ");
        scanf("%d", &inventory[i].quantity);
    }

    do {
        printf("\n========= INVENTORY MENU =========\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(&inventory, &n);
                break;
            case 2:
                viewAll(inventory, n);
                break;
            case 3:
                updateQuantity(inventory, n);
                break;
            case 4:
                searchByID(inventory, n);
                break;
            case 5:
                searchByName(inventory, n);
                break;
            case 6:
                searchByPrice(inventory, n);
                break;
            case 7:
                deleteProduct(&inventory, &n);
                break;
            case 8:
                free(inventory);
                printf("Memory released successfully. Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}
