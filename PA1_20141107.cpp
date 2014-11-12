#include <iostream>
#include <string>
#include <cmath>

using namespace std;


/////////////////////////Helper Function Pointers
int nint(float);
void printMenu(int);


/////////////////////////Start main code
int main()
{
    //set cout precision to 2 for 2 decimal places
    cout.precision(2);

    //declare variables
    int productId, productQuantity, startOverOrAdd, counter, totalNonZeroProductIds;
    char anotherItemFlag, satisfiedWithOrderFlag;
    
    //initialize Total Amount and CartQuantity to 0
    float TotalAmount = 0;
    float CartQuantity [14];

    for(int i = 0; i < 14; i++)
    {
        CartQuantity[i] = 0;
    }

    //set CONSTANTS
    string MenuItems[14] = {"narf", "Regular", "Decaf", "Americano", "Latte", "Espresso", "Cappuccino", "Macchiato", "Plain Muffin", "Blueberry Muffin", "Raspberry Muffin", "Scone", "Blueberry Scone", "Croissant"};
    float PriceLists[14] = {0, 1.50, 1.25, 2.25, 2.50, 2.25, 2.75, 2.5, 1.00, 1.25, 1.25, 0.75, 1.00, 0.75};

    //print first menu
    printMenu(1);

    //get productId
    cout << "\n";
    cout << "What would you like?(1-13): ";
    cin >> productId;

    //get productQuantity
    cout << "\n";
    cout << "How many would you like?: ";
    cin >> productQuantity;

    //add first productId to CartQuantity
    CartQuantity[productId] += productQuantity;

    //anything else?
    cout << "\n";
    cout << "Would you like anything else?(Y/N): ";
    cin >> anotherItemFlag;

    //initialize this because you need to enter outer while loop
    satisfiedWithOrderFlag = 'N';

    while (satisfiedWithOrderFlag == 'N')
    {
        while (anotherItemFlag == 'Y')
        {
            //print second menu
            printMenu(2);

            //get productId
            cout << "\n";
            cout << "What would you like?(1-13): ";
            cin >> productId;

            //get productQuantity
            cout << "\n";
            cout << "How many would you like?: ";
            cin >> productQuantity;

            //add subsequent productId to CartQuantity
            CartQuantity[productId] += productQuantity;

            //anything else?
            cout << "\n";
            cout << "Would you like anything else?(Y/N): ";
            cin >> anotherItemFlag;
        }

        //print recipt
        if (anotherItemFlag == 'N')
        {
            //to avoid errors, always recalculate TotalAmount by resetting to 0
            TotalAmount = 0;
            totalNonZeroProductIds = 0;
            counter = 1;
            cout << "\n";
            cout << "You have ordered: ";
            for (int i = 1; i < 14; i++) 
            {
                if (CartQuantity[i] != 0) 
                {
                    totalNonZeroProductIds ++;
                }
            }

            for (int i = 1; i < 14; i++) 
            {
                if (CartQuantity[i] != 0 and counter < totalNonZeroProductIds) 
                {
                    TotalAmount += CartQuantity[i] * PriceLists[i];
                    cout << nint(CartQuantity[i]) << " " << MenuItems[i] << " ($" << fixed << PriceLists[i] << "), ";
                    counter ++;
                }
                else if (CartQuantity[i] != 0) 
                {
                    TotalAmount += CartQuantity[i] * PriceLists[i];
                    cout << nint(CartQuantity[i]) << " " << MenuItems[i] << " ($" << fixed << PriceLists[i] << ")";
                }
            }
            cout << "\n";
            cout << "Your total is: $" << fixed << TotalAmount;
            cout << "\n";
        }

        //after seeing receipt, what does the fickle customer do?
        cout << "\n";
        cout << "Are you satisfied with your order?(Y/N): ";
        cin >> satisfiedWithOrderFlag;

        if (satisfiedWithOrderFlag == 'Y') 
        {
            cout << "\n";
            cout << "Thank you for shopping at Hunter Cafe CMS! Have a nice day!";
            cout << "\n";
            break;
        }
        else if (satisfiedWithOrderFlag == 'N')
        {
            cout << "\n";
            cout << "Would you like to add items to your order (1) or start over (2): ";
            cin >> startOverOrAdd;
            if (startOverOrAdd == 2)
            {
                //re-assign CartQuantity to 0
                for(int i = 0; i < 14; i++)
                {
                    CartQuantity[i] = 0;
                }
            }
            anotherItemFlag = 'Y';
        } 
        else 
        {
            cout << "\n";
            cout << "Please enter a valid response";
        }
    }

    return 0;
}

/////////////////////Helper Function Definitions

//use nint to cast floats to ints
int nint(float d)
{
   return std::floor(d+0.5);
}

//use printMenu to print two types of
void printMenu(int menuType)
{
    //menuType 1 = Welcome menu
    if (menuType == 1)
    {
        cout << "******Hunter Cafe CMS*******\n";
        cout << "Welcome! Here is the Cafe Menu:\n";
        cout << "\n";
        cout << " **Coffee**        **Cost($)**          **Snacks**            **Cost($)**\n";
        cout << "1) Regular            1.50              8)Plain Muffin          1.00\n";
        cout << "2) Decaf              1.25              9)Blueberry Muffin      1.25\n";
        cout << "3) Americano          2.25              10)Raspberry Muffin     1.25\n";
        cout << "4) Latte              2.50              11)Scone                0.75\n";
        cout << "5) Espresso           2.25              12)Blueberry Scone      1.00\n";
        cout << "6) Cappuccino         2.75              13)Croissant            0.75\n";
        cout << "7) Macchiato          2.50\n";
    }
    //menuType 2 = Returning menu
    else if (menuType == 2)
    {
        cout << "\n";
        cout << "Here is the Cafe Menu:\n";
        cout << "\n";
        cout << " **Coffee**        **Cost($)**          **Snacks**            **Cost($)**\n";
        cout << "1) Regular            1.50              8)Plain Muffin          1.00\n";
        cout << "2) Decaf              1.25              9)Blueberry Muffin      1.25\n";
        cout << "3) Americano          2.25              10)Raspberry Muffin     1.25\n";
        cout << "4) Latte              2.50              11)Scone                0.75\n";
        cout << "5) Espresso           2.25              12)Blueberry Scone      1.00\n";
        cout << "6) Cappuccino         2.75              13)Croissant            0.75\n";
        cout << "7) Macchiato          2.50\n";
    }
}