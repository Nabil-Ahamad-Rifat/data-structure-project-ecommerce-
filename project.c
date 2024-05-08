#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for users, products, and orders
typedef struct User
{
    char username[50];
    char password[50];
    int userType; // 1 for buyer, 2 for seller
    struct User *next;
} User;

typedef struct Product
{
    int productId;
    char productName[50];
    float price;
    int category; // Added category field
    struct Product *next;
} Product;

typedef struct Order
{
    int orderId;
    char productName[50];
    float totalPrice;
    struct Order *next;
} Order;

// Function prototypes
void buyerMenu(User *currentUser);
void sellerMenu(User *currentUser);
User *login();
void buyerRegistration();
void sellerRegistration();
User *createUser(char username[], char password[], int userType);
User *findUser(char username[], char password[]);
void addProduct(int productId, const char *productName, float price, const int category);
void updateProduct();
void viewProducts();
void viewOrders();
void createOrder(int productId);
void viewProducts(Product *head);
void displayOrders(Order *head);
const char *getCategoryName(int category); // Declare getCategoryName
void nabil();
void searchByCategory(Product *head, int category);
Product *deleteProduct(Product *head, int productId);
Product *updateProductpro(Product *head, int productId, const char *newName, float newPrice, int newCategory);
// Global variables
User *userList = NULL;
User *loggedInUser = NULL;
Product *productList = NULL;
Order *orderList = NULL;

// Function to add sample products for each category
void addSampleProducts()
{
    addProduct(1, "Refrigerator", 500.0, 1);
    addProduct(2, "Oxygen Concentrator", 300.0, 2);
    addProduct(3, "Plumbing Service", 50.0, 3);
    addProduct(4, "Washing Machine", 450.0, 1);
    addProduct(5, "First Aid Kit", 20.0, 2);
    addProduct(6, "Electrical Repair", 40.0, 3);
}

int main()
{
    int choice;

    do
    {
        printf("\n----- Home Service Project -----\n");
        printf("1. Login\n");
        printf("2. Buyer Registration\n");
        printf("3. Seller Registration\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            loggedInUser = login();
            if (loggedInUser != NULL)
            {
                if (loggedInUser->userType == 1)
                    buyerMenu(loggedInUser);
                else if (loggedInUser->userType == 2)
                    sellerMenu(loggedInUser);
            }
            break;
        case 2:
            buyerRegistration();
            break;
        case 3:
            sellerRegistration();
            break;
        case 4:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

User *login()
{
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    return findUser(username, password);
}

User *findUser(char username[], char password[])
{
    User *current = userList;

    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
        {
            printf("Login successful! Welcome, %s!\n", username);
            return current;
        }

        current = current->next;
    }

    printf("Login failed. Invalid username or password.\n");
    return NULL;
}

void buyerRegistration()
{
    char username[50];
    char password[50];

    printf("Enter desired username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    User *newUser = createUser(username, password, 1); // 1 represents buyer
    newUser->next = userList;
    userList = newUser;

    printf("Buyer registration successful!\n");
}

void sellerRegistration()
{
    char username[50];
    char password[50];

    printf("Enter desired username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    User *newUser = createUser(username, password, 2); // 2 represents seller
    newUser->next = userList;
    userList = newUser;

    printf("Seller registration successful!\n");
}

User *createUser(char username[], char password[], int userType)
{
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->userType = userType;
    newUser->next = NULL;

    return newUser;
}

void buyerMenu(User *currentUser)
{
    int choice;
    int id;
    // Add sample products for each category
    if (productList == NULL)
    {
        addSampleProducts();
    }

    do
    {
        printf("\n----- Buyer Menu -----\n");
        printf("1. Home Appliances\n");
        printf("2. Medical Kit\n");
        printf("3. Home Service\n");
        printf("4. view product \n");
        printf("5. View Orders\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            searchByCategory(productList, 1);

            printf("Enter product id to order :");
            scanf("%d", &id);
            createOrder(id);
            break;
        case 2:
            searchByCategory(productList, 2);

            printf("Enter product id to order :");
            scanf("%d", &id);
            createOrder(id);
            break;
        case 3:
            searchByCategory(productList, 3);

            printf("Enter product id to order :");
            scanf("%d", &id);
            createOrder(id);
            break;
        case 4:
            viewProducts(productList);
            break;
        case 5:
            viewOrders();
            break;
        case 6:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);
}

void sellerMenu(User *currentUser)
{
    int choice;
    int id;
    addSampleProducts();
    do
    {
        printf("\n----- Seller Menu -----\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete product \n");
        printf("4. View Products\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            nabil();
            break;
        case 2:
            updateProduct();
            break;

        case 3:

            printf("Enter the product id whitch you want to delete :");
            scanf("%d", &id);
            productList = deleteProduct(productList, id);
            break;
        case 4:

            viewProducts(productList); // 0 indicates view all products for the seller
            break;
        case 5:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
}

void addProduct(int productId, const char *productName, float price, int category)
{
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->productId = productId;
    strcpy(newProduct->productName, productName);
    newProduct->price = price;
    newProduct->category = category; // Add category to the product
    newProduct->next = productList;
    productList = newProduct;
}

void updateProduct()
{
    int productId;
    char newName[50];
    float newPrice;
    int newCategory;
    printf("Enter the product ID to update: ");
    scanf("%d", &productId);
    printf("Enter new product name: ");
    scanf("%s", newName);
    printf("Enter new product price: ");
    scanf("%f", &newPrice);
    printf("Enter new product Category: ");
    scanf("%s", newCategory);
    productList = updateProductpro(productList, productId, newName, newPrice, newCategory);
}

Product *updateProductpro(Product *head, int productId, const char *newName, float newPrice, int newCategory)
{
    Product *current = head;

    while (current != NULL)
    {
        if (current->productId == productId)
        {
            strcpy(current->productName, newName);
            current->price = newPrice;
            current->category = newCategory;
            printf("Product with ID %d updated successfully.\n", productId);
            return head;
        }

        current = current->next;
    }

    printf("Product with ID %d not found.\n", productId);
    return head;
}

void viewProducts(Product *head)
{
    printf("\n----- All Products -----\n");
    Product *current = head;

    while (current != NULL)
    {
        printf("ID: %d, Name: %s, Price: %.2f, Category: %d\n", current->productId, current->productName, current->price, current->category);
        current = current->next;
    }
}

void viewOrders()
{
    printf("\n----- Order List -----\n");
    displayOrders(orderList);
}

void createOrder(int productId)
{
    Product *currentProduct = productList;

    while (currentProduct != NULL)
    {
        if (currentProduct->productId == productId)
        {
            Order *newOrder = (Order *)malloc(sizeof(Order));
            newOrder->next = NULL;

            newOrder->orderId = rand(); // Generate a random order ID (for simplicity)
            strcpy(newOrder->productName, currentProduct->productName);
            newOrder->totalPrice = currentProduct->price;

            newOrder->next = orderList;
            orderList = newOrder;

            printf("Order placed successfully!\n");
            return;
        }

        currentProduct = currentProduct->next;
    }

    printf("Product not found with ID %d. Order placement failed.\n", productId);
}

void displayProducts(Product *head)
{
    Product *current = head;

    while (current != NULL)
    {
        printf("ID: %d, Name: %s, Price: %.2f, Category: %s\n", current->productId, current->productName, current->price, current->category);
        current = current->next;
    }
}

void displayOrders(Order *head)
{
    Order *current = head;

    while (current != NULL)
    {
        printf("Order ID: %d, Product: %s, Total Price: %.2f\n", current->orderId, current->productName, current->totalPrice);
        current = current->next;
    }
}

const char *getCategoryName(int category)
{
    switch (category)
    {
    case 1:
        return "Home Appliances";
    case 2:
        return "Medical Kit";
    case 3:
        return "Home Service";
    default:
        return "Unknown Category";
    }
}
void nabil()
{
    int id;
    char name[50];
    float price;
    int category;

    printf("Enter product ID: ");
    scanf("%d", &id);
    printf("Enter product name: ");
    scanf("%s", name);
    printf("Enter product price: ");
    scanf("%f", &price);
    printf("Enter product category: ");
    scanf("%d", &category);

    addProduct(id, name, price, category);

    printf("Product added successfully!\n");
}

void searchByCategory(Product *head, int category)
{
    printf("\n----- Products in Category %d -----\n", category);
    Product *current = head;
    int found = 0;

    while (current != NULL)
    {
        if (current->category == category)
        {
            printf("ID: %d, Name: %s, Price: %.2f, Category: %d\n", current->productId, current->productName, current->price, current->category);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
    {
        printf("No products found in Category %d.\n", category);
    }
}
Product *deleteProduct(Product *head, int productId)
{
    Product *current = head;
    Product *prev = NULL;

    while (current != NULL)
    {
        if (current->productId == productId)
        {
            if (prev == NULL)
            {
                // Deleting the first node
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Product with ID %d deleted successfully.\n", productId);
            return head;
        }

        prev = current;
        current = current->next;
    }

    printf("Product with ID %d not found.\n", productId);
    return head;
}