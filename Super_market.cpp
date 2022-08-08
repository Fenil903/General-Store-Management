#include <bits/stdc++.h>
using namespace std;
struct item
{
    long long int id;
    string name;
    float rate;
    int quantity;
    item *next;
};

struct customer
{
    long long int cid;
    string name;
    float points;
    customer *next;
};

class Linklist_item
{
private:
    item *tail;
    item *head;

public:
    Linklist_item()
    {
        head = NULL;
        tail = NULL;
    }
    item *gethead()
    {
        return head;
    }
    item *gettail()
    {
        return tail;
    }

    void front(item *newNode)
    {
        if (head == NULL)
        {
            newNode->next = head;
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
    }

    void last(item *newNode)
    {
        if (head == NULL)
        {
            newNode->next = NULL;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            newNode->next = NULL;
        }
    }

    void after(item *a, item *newNode)
    {
        newNode->next = a->next;
        a->next = newNode;
    }
};

class Hash_item : public Linklist_item
{
private:
    Linklist_item *chain = new Linklist_item[10];

public:
    void insert(long long int key, string name, float rate, int quantity)
    {
        int index = key % 10;
        item *newNode = new item;
        newNode ->id = key;
        newNode ->name = name;
        newNode ->rate = rate;
        newNode ->quantity = quantity;
        if (chain[index].gethead() == NULL)
        {
            chain[index].front(newNode);
        }
        else
        {
            item *temp = chain[index].gethead();
            item *prev = new item;
            while (temp != NULL && newNode ->id >= temp ->id)
            {
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL)
            {
                chain[index].last(newNode);
            }
            else if (chain[index].gethead() == temp)
            {
                chain[index].front(newNode);
            }
            else
            {
                chain[index].after(prev, newNode);
            }
        }
    }

    void displayHash_item()
    {
        for (int i = 0; i < 10; i++)
        {
            item *temp = chain[i].gethead();
            cout << "chain[" << i << "]-->";

            while (temp != NULL)
            {
                cout << temp ->name << "-->";
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }

    item *search(long long int id)
    {
        int index = id % 10;
        int flag = 0;
        item *temp = chain[index].gethead();
        item *pre = new item;
        pre ->id = 0;
        pre ->name = '\0';
        pre ->quantity = 0;
        pre ->rate = 0.0;

        while (temp != NULL)
        {
            if (temp ->id == id)
            {
                return temp;
                flag = 1;
                break;
            }
            else
            {
                temp = temp ->next;
            }
        }
        if (flag == 0)
        {
            return pre;
        }
        return NULL;
    }

    void del(long long int value)
    {
        int key = value % 10;
        item *temp = chain[key].gethead(), *dealloc;
        if (temp != NULL)
        {
            if (temp ->id == value)
            {
                dealloc = temp;
                temp = temp ->next;
                free(dealloc);
            }
            else
            {
                while (temp ->next)
                {
                    if (temp ->next ->id == value)
                    {
                        dealloc = temp ->next;
                        temp ->next = temp ->next ->next;
                        free(dealloc);
                    }
                    temp = temp ->next;
                }
            }
        }
    }
};

class inventory : public Hash_item
{
private:
    Hash_item h;

    void add_item(long long int id, string proname, float rate, int quantity)
    {
        h.insert(id, proname, rate, quantity);
    }

    void remove_item(long long int id)
    {
        h.del(id);
    }

    void update_item(long long int id, float rate, int quantity)
    {
        item *temp = h.search(id);
        temp ->rate = rate;
        temp ->quantity += quantity;
    }

public:
    void update_stock(long long int id, int quantity)
    {
        item *temp = h.search(id);
        temp ->quantity -= quantity;
    }

    item *get_product_info(long long int id)
    {
        return h.search(id);
    }
    friend class manager; // class manager can access all the private or protected members of the inventory class but
                          // billing class can not access all members
};

class manager
{
private:
    long long int id;
    string name;

public:
    void add_item_manager(long long int id, string proname, float rate, int quantity, inventory i)
    {
        i.add_item(id, proname, rate, quantity);
    }
    void remove_item_manager(long long int id, inventory i)
    {
        i.remove_item(id);
    }
    void update_item_manager(long long int id, float rate, int quantity, inventory i)
    {
        i.update_item(id, rate, quantity);
    }
    void update_stock_manager(long long int id, int quantity, inventory i)
    {
        i.update_stock(id, quantity);
    }
    void get_product_info_manager(long long int id, inventory i)
    {
        i.get_product_info(id);
    }
    void print_product_info(long long int id, inventory i)
    {
        item *temp = i.get_product_info(id);
        cout << "ID: " << temp->id << setw(10) << "Name: " << temp->name << setw(10) << "Rate: " << temp->rate << "   Quantity: " << temp->quantity << endl;
    }
};
class Linklist_customer
{
private:
    customer *tail;
    customer *head;

public:
    Linklist_customer()
    {
        head = NULL;
        tail = NULL;
    }
    customer *gethead()
    {
        return head;
    }
    customer *gettail()
    {
        return tail;
    }
    void front(customer *newNode)
    {
        if (head == NULL)
        {
            newNode ->next = head;
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode ->next = head;
            head = newNode;
        }
    }
    void last(customer *newNode)
    {
        if (head == NULL)
        {
            newNode ->next = NULL;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail ->next = newNode;
            tail = newNode;
            newNode ->next = NULL;
        }
    }
    void after(customer *a, customer *newNode)
    {
        newNode ->next = a->next;
        a ->next = newNode;
    }
};
class Hash_customer : public Linklist_customer
{
private:
    Linklist_customer *chain = new Linklist_customer[10];

public:
    void insert(long long int key, string name, float points)
    {
        int index = key % 10;
        customer *newNode = new customer;
        newNode ->cid = key;
        newNode ->name = name;
        newNode ->points = points;
        if (chain[index].gethead() == NULL)
        {
            chain[index].front(newNode);
        }
        else
        {
            customer *temp = chain[index].gethead();
            customer *prev = new customer;
            while (temp != NULL && newNode ->cid >= temp ->cid)
            {
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL)
            {
                chain[index].last(newNode);
            }
            else if (chain[index].gethead() == temp)
            {
                chain[index].front(newNode);
            }
            else
            {
                chain[index].after(prev, newNode);
            }
        }
    }
    void displayHash_customer()
    {
        for (int i = 0; i < 10; i++)
        {
            customer *temp = chain[i].gethead();
            cout << "chain[" << i << "]-->";
            while (temp != NULL)
            {
                cout << temp ->name << "-->";
                temp = temp ->next;
            }
            printf("NULL\n");
        }
    }
    customer *search(long long int id)
    {
        int index = id % 10;
        int flag = 0;
        customer *temp = chain[index].gethead();
        customer *pre = new customer;
        pre ->cid = 0;
        pre ->name = '\0';
        pre ->points = 0.0;
        while (temp != NULL)
        {
            if (temp ->cid == id)
            {
                return temp;
                flag = 1;
                break;
            }
            else
            {
                temp = temp ->next;
            }
        }
        if (flag == 0)
        {
            return pre;
        }
        return NULL;
    }
    void del(long long int value)
    {
        int key = value % 10;
        customer *temp = chain[key].gethead(), *dealloc;
        if (temp != NULL)
        {
            if (temp ->cid == value)
            {
                dealloc = temp;
                temp = temp ->next;
                free(dealloc);
            }
            else
            {
                while (temp ->next)
                {
                    if (temp ->next ->cid == value)
                    {
                        dealloc = temp->next;
                        temp ->next = temp ->next ->next;
                        free(dealloc);
                    }
                    temp = temp ->next;
                }
            }
        }
    }
};

class billing : public inventory, public Hash_customer
{
private:
    Hash_item h;
    long int transaction_id = 2020100;

public:
    item *buy_item(long long int id, int quantity, inventory i)
    {
        item *temp = i.get_product_info(id);
        return temp;
    }
    item *cancel_item(long long int id, int quantity, inventory i)
    {
        item *temp = i.get_product_info(id);
        return temp;
    }
    void assign_customerid(long long int pnumber, string name, Hash_customer h1)
    {
        h1.insert(pnumber, name, 0.0);
    }
    long int return_tran_id()
    {
        transaction_id = transaction_id + 1;
        return transaction_id;
    }
    void update_stock_billing(long long int id, int quantity, inventory i)
    {
        i.update_stock(id, quantity);
    }
    void assign_points(long long int id, float sum, Hash_customer h1)
    {
        customer *temp = h1.search(id);
        temp->points = sum;
    }
};
int main()
{
    inventory i;
    manager m;
    long long int INVENTORY_DATASET[100] = {
        111100000001, 111100000002, 111100000003, 111100000004, 111100000005, 111100000006, 111100000007, 111100000008, 111100000009, 111100000010, 111100000011, 111100000012, 111100000013, 111100000014, 111100000015, 111100000016, 111100000017, 111100000018, 111100000019, 111100000020, 111100000021, 111100000022, 111100000023, 111100000024, 111100000025, 111100000026, 111100000027, 111100000028, 111100000029, 111100000030, 111100000031, 111100000032, 111100000033, 111100000034, 111100000035, 111100000036, 111100000037, 111100000038, 111100000039, 111100000040, 111100000041, 111100000042, 111100000043, 111100000044, 111100000045, 111100000046, 111100000047, 111100000048, 111100000049, 222200001111, 222200001114, 222200001117, 222200001120, 222200001123, 222200001126, 222200001129, 222200001132, 222200001135, 222200001138, 222200001141, 222200001144, 222200001147, 222200001150, 222200001153, 222200001156, 222200001159, 222200001162, 222200001165, 222200001168, 222200001171, 222200001174, 222200001177, 222200001180, 222200001183, 222200001186, 222200001189, 222200001192, 222200001195, 222200001198, 222200001201, 222200001204, 222200001207, 222200001210, 222200001213, 222200001216, 222200001219, 222200001222, 222200001225, 222200001228, 222200001231, 222200001234, 222200001237, 222200001240, 222200001243, 222200001246, 222200001249, 222200001252, 222200001255, 222200001258, 222200001261};
    string INVENTORY_DATASET_NAME[100] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100"};
    float INVENTORY_DATASET_RATE[100] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000, 1010, 1020, 1030, 1040, 1050, 1060, 1070, 1080, 1090};
    int INVENTORY_DATASET_QUAN[100];
    for (int k = 0; k < 100; k++)
    {
        INVENTORY_DATASET_QUAN[k] = 20;
    }
    for (int j = 0; j < 100; j++)
    {
        m.add_item_manager(INVENTORY_DATASET[j], INVENTORY_DATASET_NAME[j], INVENTORY_DATASET_RATE[j], INVENTORY_DATASET_QUAN[j], i);
    }
    long long int CUSTOMER_DATASET[100] = {
        9400000001, 9400000002, 9400000003, 9400000004, 9400000005, 9400000006, 9400000007, 9400000008, 9400000009, 9400000010, 9400000011, 9400000012, 9400000013, 9400000014, 9400000015, 9400000016, 9400000017, 9400000018, 9400000019, 9400000020, 9400000021, 9400000022, 9400000023, 9400000024, 9400000025, 9400000026, 9400000027, 9400000028, 9400000029, 9400000030, 9400000031, 9400000032, 9400000033, 9400000034, 9400000035, 9400000036, 9400000037, 9400000038, 9400000039, 9400000040,
        9400000041, 9400000042, 9400000043, 9400000044, 9400000045, 9400000046, 9400000047, 9400000048, 9400000049, 9400000050, 9400000051, 9400000052, 9400000053, 9400000054, 9400000055, 9400000056, 9400000057, 9400000058, 9400000059, 9400000060, 9400000061, 9400000062, 9400000063, 9400000064, 9400000065, 9400000066, 9400000067, 9400000068, 9400000069, 9400000070, 9400000071, 9400000072, 9400000073, 9400000074, 9400000075, 9400000076, 9400000077, 9400000078, 9400000079, 9400000080,
        9400000081, 9400000082, 9400000083, 9400000084, 9400000085, 9400000086, 9400000087, 9400000088, 9400000089, 9400000090, 9400000091, 9400000092, 9400000093, 9400000094, 9400000095, 9400000096, 9400000097, 9400000098, 9400000099, 9400000100};
    string CUSTOMER_DATASET_NAME[100] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100"};
    float CUSTOMER_DATASET_POINTS[100] = {0};
    Hash_customer h1;
    for (int j = 0; j < 100; j++)
    {
        h1.insert(CUSTOMER_DATASET[j], CUSTOMER_DATASET_NAME[j], CUSTOMER_DATASET_POINTS[j]);
    }
    int n;
    billing b;
    long long int phone_number;
    cout << "Enter your phone number: ";
    cin >> phone_number; // Input customer id
    cout << endl;
    string name;
    cout << "Enter your name: ";
    cin >> name; // Input name of the customer
    cout << endl;
    b.assign_customerid(phone_number, name, h1);
    cout << setw(70) << "SuperStore" << endl;
    cout << setw(40) << "Customer ID: " << phone_number << setw(50);
    cout << "Transaction ID: " << b.return_tran_id() << endl;
    cout << endl;
    cout << "Enter the number of items you want to buy: " << endl;
    cin >> n; // Input the number of items you want to buy
    int t = 2 * n;
    int sum = 0;
    cout << setw(40) << "Product ID" << setw(20) << "Product Name" << setw(20) << "Quantity" << setw(20) << "Rate" << endl;
    long long int ids[n]; // For manager
    int k = 0;
    while (t--)
    {
        cout << "1 for buying item" << endl;
        cout << "0 for cancelling item" << endl;
        cout << "2 for leaving the shopping in between" << endl;
        int choice;
        cin >> choice; // Choosing the option of buying, cancelling or exitting the billing process
        if (choice == 2)
            break;
        long long int id;
        int quantity;
        cout << "Enter id of the product you want to buy/cancel:\n";
        cin >> id;
        cout << "Enter quantity of the product you want to buy/cancel:\n";
        cin >> quantity; // Input id and quantity of product you want to buy
        if (choice == 1)
        {
            item *ni = b.buy_item(id, quantity, i);
            b.update_stock_billing(id, quantity, i);
            sum += (ni->rate * quantity);
            cout << setw(40) << ni->id << setw(20) << ni->name << setw(20) << quantity << setw(20) << ni->rate * quantity << endl;
            ids[k] = id;
            k = k + 1;
        }
        else if (choice == 0)
        {
            item *ni = b.cancel_item(id, quantity, i);
            b.update_stock_billing(id, -quantity, i);
            sum -= (ni->rate * quantity);
            cout << "Cancelled Item: " << setw(24) << ni->id << setw(20) << ni->name << setw(20) << quantity << setw(17) << "-" << ni->rate * quantity << endl;
        }
        else if (choice == 2)
        {
            break;
        }
        else
        {
            cout << "[WARNING] No such option present" << endl;
        }
    }
    cout << setw(97) << "Total Cost: " << sum << endl;
    cout << endl;
    b.assign_points(phone_number, sum, h1);
    cout << setw(97) << "Points: " << sum << endl; // Assignning the total amount of the bill as points earned
    cout << setw(70) << "THANK YOU" << endl;
    cout << endl;
    // If manager wants to access the inventory class
    for (int k = 0; k < n; k++)
    {
        m.print_product_info(ids[k], i);
    }
}

/*
    // Some of the example inputs are given below.
*/

// For entering a custom input
// Input mobile number
// Input name
// Input number of items you want to buy
//  Step 1: Enter 1 for buying item 0 for cancelling item and 2 for leaving the process of billing in between
//  Step 2: Enter id of the product you want to buy
//  Step 3: Enter the quantity of the product you want to buy
// Repeat steps 1,2 and 3 n(number of items you wanted to buy) number of times

// Example of input
//  Mobile number: 9400025251
//  Name: abc
//  Number of items: 2
//  Choice : 1
//  ID: 111100000001
//  Quantity: 2
//  Choice : 1
//  ID: 111100000002
//  Quantity: 2
//  Choice : 2 For the customer to quit the billing process

// Example of dataset given by Prof. Bakul Gohel
//  Mobile number: 9400000011
//  Name : 11
//  Number of items: 3
//  Choice : 1
//  ID: 111100000001
//  Quantity: 3
//  Choice : 1
//  ID: 222200001114
//  Quantity: 1
//  Choice: 1
//  ID: 222200001234
//  Quantity: 2
//  Choice : 2 For the customer to quit the billing
