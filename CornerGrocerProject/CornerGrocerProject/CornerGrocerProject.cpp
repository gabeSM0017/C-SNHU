//CornerGrocerProject.cpp
//Gabriel San Miguel
//12/6/2023
//7-3 Project 3

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Product {
private:
	string productName;
	int purchasesCount;

public:
	//Default constructor
	Product() : productName(""), purchasesCount(0) {}
	//Accessor for product name
	string getName() const {
		return productName;
	}
	//Mutator for setting product name
	void setProductName(string& name) {
		productName = name;
	}
	//Mutator for setting product name
	void setNumPurchased(int num) {
		purchasesCount = num;
	}
	//Accessor for the number of purchases
	int getNumPurchased() const {
		return purchasesCount;
	}
	//Function to print product details
	void printProduct() const {
		cout << "Product: " << productName << ", Purchases: " << purchasesCount << endl;
	}
};



class PurchasesProducts {
private:
	map<string, int> productsList;

public:
	//Function to record products from the file and update the productsList
	void recordProducts(ifstream& inFS) {
		ofstream outFS("frequesncy.dat");
		string productName;

		while (inFS >> productName) {
			
			productName[0] = toupper(productName[0]);
			for (int i = 1; i < productName.length(); ++i) {
				productName[i] = tolower(productName[i]);
			}
			if (productName.back() != 's') {
				productName += "s";
			}

			productsList[productName]++;
		}
		//Write data to output
		for (const auto& product : productsList) {
			outFS << product.first << " " << product.second << endl;
		}
	}
	//Function to print a list of products and the purchase counts
	void printProducts() const {
		cout << "\tProducts List:" << endl;
		cout << "-----------------------------------" << endl;

		for (const auto& product : productsList) {
			int numSpaces = 15 - (product.first.length() + to_string(product.second).length() + 1) / 2;
			cout << string(numSpaces, ' ') << product.first << " " << product.second << endl;
		}
		cout << "-----------------------------------" << endl;
		cout << endl;
	}

	//Function to print a histogram to display the purchase counts
	void displayHistogram() const {
		cout << "\n\n\tProducts Histogram:" << endl;
		cout << "-----------------------------------" << endl;

		for (const auto& product : productsList) {
			int numSpaces = 15 - (product.first.length() + to_string(product.second).length() + 1) / 2;
			cout << string(numSpaces, ' ') << product.first << " ";
			for (int i = 0; i < product.second; ++i) {
				cout << "*";
			}
			cout << endl;
		}
		cout << "-----------------------------------" << endl;
		cout << endl;
	}
	//Function to get all the products in the productsList
	map<string, int> getAllProducts() const {
		return productsList;
	}
};


int main() {
	//Open the file
	ifstream inFile("CS210_Project_Three_Input_File.txt");
	//Checks if the file opens correctly and if not give a error message
	if (!inFile) {
		cerr << "Error opening file." << endl;
		return 1;
	}
	//Records products, prints product lists and displays the histogram
	PurchasesProducts products;
	products.recordProducts(inFile);
	products.printProducts();
	products.displayHistogram();

	return 0;
}