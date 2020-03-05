/*Gerard Lab 8 Pet Store inventory program*/

#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>
#include<string>
#include <vector>
using namespace std;

//sets up the values of the inventory object
struct Inventory
{
	string itemNum;
	string merch;
	string quantity;
	string price;
};

long bytePos(int);
void showItem(Inventory);

//sets up the starter data in a 2d array 
const int maxCol = 4;
const int maxRow = 10;
string starterData[maxRow][maxCol] = { 
	{"24","Leashes","25","9.55"}, 
	{"39","Collars","30","8.99"}, 
	{"15","Scoopers","10","19.99"},
	{"45","Cages","15","24.99"},
	{"77","Toys","80","5.99"},
	{"56","Food","120","89.89"},
	{"68","Treats","50","24.95"},
	{"48","Booties","12","18.99"},
	{"25","Medicine","5","56.69"},
	{"42","Bowls","10","6.20"},
	};


int main()
{	//stores info for petStore inventory.
	vector<Inventory> petStore;
	char response = 'p';
	string input;
	int numRec;

	fstream itemListFile("petStore.dat", ios::in | ios::out);

	//Puts the data into the new inventory 
	for (int i = 0; i < 10; i++)
	{
		Inventory newInv;
		
		newInv.itemNum = starterData[i][0];
		newInv.merch = starterData[i][1];
		newInv.quantity = starterData[i][2];
		newInv.price = starterData[i][3];

		petStore.push_back(newInv);
	}
	numRec = 10;

	//Checks the first item in the invetory 
		cout << "First item in inventory:\n";
		itemListFile.seekg(bytePos(0), ios::beg);
		itemListFile.read(reinterpret_cast<char*>(&petStore), sizeof(petStore));
		showItem(petStore[0]);

		//Askes the user to make a selection 
		while (toupper(response) != 'E') {
			cout << "Enter 'A' to add a record.\nEnter 'D' to delete a record.\nEnter 'E' to exit.\nEnter 'V' to view current inventory";
			cin >> response;
			cin.ignore();

			//collects the new input data from the user.
			if (toupper(response) == 'A') {
				Inventory newInv;
				cout << "Enter the information" << endl;
				cout << "Enter the Item number\n";
				getline(cin, input);
				char temp[50];
				strcpy_s(temp, input.c_str());
				newInv.itemNum = temp;

				cout << "Enter the Merchandise name\n";
				getline(cin, input);
				strcpy_s(temp, input.c_str());
				newInv.merch = temp;

				cout << "Enter the quantity\n";
				getline(cin, input);
				strcpy_s(temp, input.c_str());
				newInv.quantity = temp;

				cout << "Enter the Price per item\n";
				getline(cin, input);
				strcpy_s(temp, input.c_str());
				newInv.price = temp;

				petStore.push_back(newInv);

				itemListFile.write((char*)(&petStore), sizeof(petStore));
				//prints the new input
				cout << "New item in inventory:\n";
				itemListFile.seekg(bytePos(numRec), ios::beg);
				itemListFile.read((char*)(&petStore), sizeof(petStore));
				showItem(petStore[numRec]);
				numRec++;

			}//Sees if the user would like to delete an input. 
			else if (toupper(response) == 'D') {
				cout << "DELETED" << endl;
				petStore.erase(petStore.begin());
				numRec--;

				itemListFile.write((char*)(&petStore), sizeof(petStore));
				//Prints the new first item in the invetory 
				cout << "First item in inventory:\n";
				itemListFile.seekg(bytePos(0), ios::beg);
				itemListFile.read((char*)(&petStore), sizeof(petStore));
				showItem(petStore[0]);
			}
			else if (toupper(response) == 'V') {
				cout << "Item Number\tItem Name\tQuantity\tPrice"<< endl;
				for (int r = 0; r < petStore.size(); r++)
				{
					cout << petStore[r].itemNum << "\t" << petStore[r].merch << "\t" << petStore[r].quantity << "\t" << petStore[r].price << endl;
				}
			}
		}

		return 0;
}
//keeps track of current position. 
long bytePos(int pos)
{
	return sizeof(Inventory) * pos;
}
//pulls the data out of the array to display the item. 
void showItem(Inventory item)
{
	cout << "Record number: ";
	cout << item.itemNum << endl;
	cout << "Merchandise name: ";
	cout << item.merch << endl;
	cout << "Quantity of item: ";
	cout << item.quantity << endl;
	cout << "Cost per item: ";
	cout << item.price << endl;
}