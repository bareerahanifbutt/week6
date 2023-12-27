#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

map<char, int> sacks; // Global variable to store the number of sacks

// Function to check the contents and weight of a single sack
void checkSack() {
    char contents;
    float weight;

    cout << "Enter contents (C for cement, G for gravel, S for sand): ";
    cin >> contents;
    contents = toupper(contents);

    cout << "Enter weight of the sack in kilograms: ";
    cin >> weight;

    if ((contents == 'C' && weight > 24.9 && weight < 25.1) ||
        (contents == 'G' && weight > 49.9 && weight < 50.1) ||
        (contents == 'S' && weight > 49.9 && weight < 50.1)) {
        cout << "Sack accepted - Contents: " << contents << ", Weight: " << weight << " kg" << endl;
        sacks[contents]++;
    }
    else {
        cout << "Sack rejected due to: ";
        if (contents != 'C' && contents != 'G' && contents != 'S') {
            cout << "Invalid contents ";
        }
        if ((contents == 'C' && (weight <= 24.9 || weight >= 25.1)) ||
            (contents == 'G' && (weight <= 49.9 || weight >= 50.1)) ||
            (contents == 'S' && (weight <= 49.9 || weight >= 50.1))) {
            cout << "Invalid weight";
        }
        cout << endl;
    }
}

// Function to check a customer’s order for delivery
void checkOrder() {
    sacks['C'] = 0;
    sacks['G'] = 0;
    sacks['S'] = 0;

    int sacksRejected = 0;
    float totalWeight = 0;

    for (auto& sack : sacks) {
        char sackType;
        int numSacks;

        cout << "Enter number of " << sack.first << " sacks required: ";
        cin >> numSacks;

        for (int i = 0; i < numSacks; ++i) {
            cout << "Checking " << sack.first << " sack " << i + 1 << endl;
            cout << "=====================" << endl;
            checkSack();
        }
    }

    cout << "Order Summary:" << endl;
    cout << "Total weight of the order: " << totalWeight << " kg" << endl;
    cout << "Number of sacks rejected from the order: " << sacksRejected << endl;
}

// Function to calculate the price for a customer’s order
void calculatePrice() {
    checkOrder(); // Call the checkOrder function to get the validated sacks

    map<char, int> sackPrices = { {'C', 3}, {'G', 2}, {'S', 2} };
    int specialPackPrice = 10;
    int regularPrice = 0;

    // Calculate regular price
    for (auto& sack : sackPrices) {
        regularPrice += sack.second * sacks[sack.first];
    }

    // Check for special packs
    int numSpecialPacks = min(sacks['C'], min(sacks['S'] / 2, sacks['G'] / 2));

    // Calculate discount price if special packs exist
    if (numSpecialPacks > 0) {
        int discountPrice = numSpecialPacks * specialPackPrice;
        int amountSaved = regularPrice - discountPrice;
        cout << "Regular price for the order: " << regularPrice << endl;
        cout << "New price for the order with special pack discount: " << discountPrice << endl;
        cout << "Amount saved with special pack discount: " << amountSaved << endl;
    }
    else {
        cout << "Regular price for the order: " << regularPrice << endl;
    }
}

int main() {
    calculatePrice();
    return 0;
}
