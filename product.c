#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_SUB_PRODUCTS 10

typedef struct {
    char name[30];
    char unit[10];
} SubProduct;

typedef struct {
    int productId;
    char productName[30];
    char productType[30];
    char unit[10];
    SubProduct subProducts[MAX_SUB_PRODUCTS];
    int subProductCount;
} Product;

// Function prototypes
void addProduct(Product *products, int *productCount);
void displayProducts(Product *products, int productCount);
void updateProduct(Product *products, int productCount);
void deleteProduct(Product *products, int *productCount);
void searchProduct(Product *products, int productCount);
void initializeProducts(Product *products, int *productCount);

int main() {
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    int option;

    // Initialize products with built-in data
    initializeProducts(products, &productCount);

    do {
        printf("\n--- Product Management System ---\n");
        printf("1. Display Products\n");
        printf("2. Add Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product\n");
        printf("6. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                displayProducts(products, productCount);
                break;
            case 2:
                addProduct(products, &productCount);
                break;
            case 3:
                updateProduct(products, productCount);
                break;
            case 4:
                deleteProduct(products, &productCount);
                break;
            case 5:
                searchProduct(products, productCount);
                break;
            case 6:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (option != 6);

    return 0;
}

// Initialize the products with built-in data
void initializeProducts(Product *products, int *productCount) {
    // Built-in Sugar product
    products[0].productId = 1;
    strcpy(products[0].productName, "Sugar");
    strcpy(products[0].productType, "Solid");
    strcpy(products[0].unit, "1Kg");
    products[0].subProductCount = 2;
    strcpy(products[0].subProducts[0].name, "Sugar 1Kg");
    strcpy(products[0].subProducts[0].unit, "1Kg");
    strcpy(products[0].subProducts[1].name, "Sugar 10Kg");
    strcpy(products[0].subProducts[1].unit, "10Kg");

    // Built-in Tea product
    products[1].productId = 2;
    strcpy(products[1].productName, "Tea");
    strcpy(products[1].productType, "Solid");
    strcpy(products[1].unit, "200gm");
    products[1].subProductCount = 3;
    strcpy(products[1].subProducts[0].name, "Tea 200gm");
    strcpy(products[1].subProducts[0].unit, "200gm");
    strcpy(products[1].subProducts[1].name, "Tea 500gm");
    strcpy(products[1].subProducts[1].unit, "500gm");
    strcpy(products[1].subProducts[2].name, "Tea 1Kg");
    strcpy(products[1].subProducts[2].unit, "1Kg");

    // Built-in Milk product
    products[2].productId = 3;
    strcpy(products[2].productName, "Milk");
    strcpy(products[2].productType, "Liquid");
    strcpy(products[2].unit, "1ltr");
    products[2].subProductCount = 2;
    strcpy(products[2].subProducts[0].name, "Milk 1ltr");
    strcpy(products[2].subProducts[0].unit, "1ltr");
    strcpy(products[2].subProducts[1].name, "Milk 500ml");
    strcpy(products[2].subProducts[1].unit, "500ml");

    *productCount = 3;  // 3 built-in products
}

// Function to add a new product and initialize its sub-products
void addProduct(Product *products, int *productCount) {
    if (*productCount >= MAX_PRODUCTS) {
        printf("Product limit reached! Cannot add more products.\n");
        return;
    }

    Product newProduct;
    newProduct.productId = *productCount + 1;  // Auto-increment ID
    printf("Enter Product Name: ");
    scanf("%s", newProduct.productName);
    printf("Enter Product Type: ");
    scanf("%s", newProduct.productType);
    printf("Enter Unit: ");
    scanf("%s", newProduct.unit);

    // No sub-products initially for user-added products
    newProduct.subProductCount = 0;

    products[*productCount] = newProduct;
    (*productCount)++;
    printf("Product added successfully!\n");
}

// Function to display products in a formatted table
void displayProducts(Product *products, int productCount) {
    // Header of the table
    printf("\n+------------+--------------------+--------------------+----------+\n");
    printf("| Product ID | Product Name        | Product Type       | Unit     |\n");
    printf("+------------+--------------------+--------------------+----------+\n");

    // Loop through each product and display in the formatted table
    for (int i = 0; i < productCount; i++) {
        printf("| %-10d | %-18s | %-18s | %-8s |\n", 
               products[i].productId, products[i].productName, products[i].productType, products[i].unit);
        
        // Display sub-products if available
        if (products[i].subProductCount > 0) {
            printf("+------------+--------------------+--------------------+----------+\n");
            printf("|            | Sub-Products:       |                    |          |\n");
            for (int j = 0; j < products[i].subProductCount; j++) {
                printf("|            | %-18s |                    | %-8s |\n", 
                       products[i].subProducts[j].name, products[i].subProducts[j].unit);
            }
        }

        // Bottom divider after each product
        printf("+------------+--------------------+--------------------+----------+\n");
    }
}

void updateProduct(Product *products, int productCount) {
    int productId;
    printf("Enter Product ID to update: ");
    scanf("%d", &productId);

    if (productId < 1 || productId > productCount) {
        printf("Invalid Product ID!\n");
        return;
    }

    Product *product = &products[productId - 1]; // Adjusting for 0-based index
    printf("Updating Product: %s\n", product->productName);
    printf("Enter new Product Name (current: %s): ", product->productName);
    scanf("%s", product->productName);
    printf("Enter new Product Type (current: %s): ", product->productType);
    scanf("%s", product->productType);
    printf("Enter new Unit (current: %s): ", product->unit);
    scanf("%s", product->unit);

    printf("Product updated successfully!\n");
}

void deleteProduct(Product *products, int *productCount) {
    int productId;
    printf("Enter Product ID to delete: ");
    scanf("%d", &productId);

    if (productId < 1 || productId > *productCount) {
        printf("Invalid Product ID!\n");
        return;
    }

    for (int i = productId - 1; i < *productCount - 1; i++) {
        products[i] = products[i + 1]; // Shift products to the left
    }
    (*productCount)--; // Decrement product count
    printf("Product deleted successfully!\n");
}

void searchProduct(Product *products, int productCount) {
    int productId;
    printf("Enter Product ID to search: ");
    scanf("%d", &productId);

    if (productId < 1 || productId > productCount) {
        printf("Invalid Product ID!\n");
        return;
    }

    Product *product = &products[productId - 1]; // Adjusting for 0-based index
    printf("Product found: ID: %d, Name: %s, Type: %s, Unit: %s\n", 
           product->productId, product->productName, product->productType, product->unit);

    // Displaying sub-products
    printf("  Sub-Products for %s:\n", product->productName);
    for (int j = 0; j < product->subProductCount; j++) {
        printf("    %s (%s)\n", product->subProducts[j].name, product->subProducts[j].unit);
    }
}
