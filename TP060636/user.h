#ifndef  USER_H
#define USER_H

using namespace std;

class User {
public:
	string username, password;
};

class Admin: public User {
public:
	Admin() {};
	~Admin() {};
	void getInfo();
	int checkInfo();

	int adminMenu();

	void addManager();
	void deleteManager();
	void editManager();
	void viewManager();
	void searchManager();

	void addCustomer();
	void deleteCustomer();
	void editCustomer();
	void viewCustomer();
	void searchCustomer();
};

class Manager : public User {
public:
	string name, department, contact;

	Manager() {};
	~Manager() {};
	void getInfo();
	int checkInfo();

	int managerMenu();
	
	void addProduct(string, string);
	void deleteProduct(string);
	void editProduct(string);
	void viewProduct(string);
	void searchProduct();

	void addOrder();
	void deleteOrder();
	void editOrder();
	void viewOrder();
	void searchOrder();
};

class Customer : public User {
public:
	string name, contact, address, billingAddress, cardType;

	Customer() {};
	~Customer() {};
	void getInfo();
	int checkInfo();

	int customerMenu();

	void searchProduct();
	void viewCatalogue();
	class Product* addProductToCart(class Product*, class Order*, Customer);
	class Product* displayBill(class Product*, class Order*);
};

// Function declarations
void search();
string randomizedOrderID();

// Obtaining username and password for respective account
void obtainInfo(string &username, string &password) {
	cout << "\n\n\tEnter username [-1 to return] : ";
	getline(cin, username);
	if (username == "-1") {
		return;
	}
	cout << "\tEnter password: ";
	getline(cin, password);
}

void Admin::getInfo() {
	obtainInfo(username, password);
}

void Manager::getInfo() {
	obtainInfo(username, password);
}

void Customer::getInfo() {
	obtainInfo(username, password);
}

// Hard coded username and password as main admin is behind coding
int Admin::checkInfo() {
	if (username == "-1") {
		return 0;
	}
	else if (username == "admin" && password == "admin") {
		return 1;
	}
	else {
		cout << "\n\tInvalid user credential.\n\t[Press enter to continue]" << endl;
		while (getchar() != '\n');
		return 0;
	}
}

int Manager::checkInfo() {
	if (username == "-1") {
		return 0;
	}
	string line, id, pass;
	ifstream File;

	File.open("Administration information.txt");

	while (getline(File, line)) {

		stringstream lineObj(line);
		getline(lineObj, id, '|');
		getline(lineObj, pass, '|');
		if (username == id && password == pass) {
			getline(lineObj, name, '|');
			getline(lineObj, department, '|');
			getline(lineObj, contact, '|');
			File.close();
			return 1;
		}
	}
	File.close();
	cout << "\n\tInvalid user credential.\n\t[Press enter to continue]" << endl;
	while (getchar() != '\n');
	return 0;
}

int Customer::checkInfo() {
	if (username == "-1") {
		return 0;
	}
	string line, id, pass;
	ifstream File;

	File.open("Customer information.txt");
	
	while (getline(File, line)) {

		stringstream lineObj(line);
		getline(lineObj, id, '|');
		getline(lineObj, pass, '|');

		if (username == id && password == pass) {
			getline(lineObj, name, '|');
			getline(lineObj, contact, '|');
			getline(lineObj, address, '|');
			getline(lineObj, billingAddress, '|');
			getline(lineObj, cardType, '|');
			File.close();
			return 1;
		}
	}
	File.close();
	cout << "\n\tInvalid user credential.\n\t[Press enter to continue]" << endl;
	while (getchar() != '\n');
	return 0;
}

// Same function for both manager and customer
void search() {
	string inputID, line, id, name, price, category, fragility, rating, quantity, date;
	bool flg = false;

	system("cls");
	cout << "\n\n\tSEARCH PRODUCT:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}

	ifstream File;
	File.open("Inventory.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, id, '|');
		getline(lineObj, name, '|');
		getline(lineObj, price, '|');
		getline(lineObj, category, '|');
		getline(lineObj, fragility, '|');
		getline(lineObj, rating, '|');
		getline(lineObj, quantity, '|');
		getline(lineObj, date, '|');
		if (inputID == id) {
			flg = true;
			cout << "\n\n\tID              : " << id <<
				"\n\tName            : " << name <<
				"\n\tPrice           : " << price <<
				"\n\tCategory        : " << category <<
				"\n\tFragility       : " << fragility <<
				"\n\tRating          : " << rating <<
				"\n\tQuantity        : " << quantity <<
				"\n\tExpiration date : " << date << "\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
			break;
		}
	}
	File.close();

	if (flg == false) {
		cout << "\n\n\tProduct is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

// Same function to generate order ID for manager and customer
string randomizedOrderID() {
	string id, line;
	stringstream randomVal;
	bool flg;
	srand(time(NULL));
	do {
		flg = false;
		// To generate five random alphabet and six random number
		char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
							  'h', 'i', 'j', 'k', 'l', 'm', 'n',
							  'o', 'p', 'q', 'r', 's', 't', 'u',
							  'v', 'w', 'x', 'y', 'z' };
		for (int i = 0; i < 5; i++) {
			id = id + alphabet[rand() % 26];
		}
		randomVal << setfill('0') << setw(6) << 1 + (rand() % 999999);
		id = id + randomVal.str();
		ifstream File;
		File.open("Order.txt");

		while (getline(File, line)) {
			if (line.substr(0, 10) == id) {
				flg = true;
			}
		}
	} while (flg);
	return id;
}


#endif