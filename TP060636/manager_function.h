#ifndef MANAGER_FUNCTION_H
#define MANAGER_FUNCTION_H

#include "order.h"

string randomizedProductID(string);

int Manager::managerMenu() {
	string opt;
	int optInt;
	system("cls");
	cout << "\n\n\tManager menu:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tPlease select one of the following operations:-\n\t1. Add product\n\t2. Delete product\n\t3. Edit product\n\t4. View product\n\t5. Search product\n\t6. Add order\n\t7. Delete order\n\t8. Edit order\n\t9. View order\n\t10. Search order" << endl;
	cout << "\tOption [-1 to exit]: ";
	getline(cin, opt);
	try {
		optInt = stoi(opt);
	}
	catch (...) {
		return 0;
	}
	return optInt;
}

string randomizedProductID(string managerID) {
	bool flg = false;
	string id, line;
	stringstream randomVal;
	srand(time(NULL));

	do {
		randomVal << setfill('0') << setw(6) << 1 + (rand() % 999999);

		id = managerID.substr(0, 2) + randomVal.str();

		ifstream File;
		File.open("Inventory.txt");

		while (getline(File, line)) {
			if (line.substr(0, 9) == id) {
				flg = true;
				break;
			}
			else {
				flg = false;
			}
		}
	} while (flg);

	return id;
}

void Manager::addProduct(string managerID, string managerDepartment) {
	Product p;
	string line, opt;
	char price2D[PRICE_BUFFER];
	bool flg = false;
	do {
		system("cls");
		cout << "\n\n\tADD PRODUCT:-" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter the following information:- " << endl;
		p.id = randomizedProductID(managerID);
		cout << "\tName [-1 to return] : ";
		getline(cin, p.name);
		if (p.name == "-1") {
			return;
		}
		cout << "\tPrice               : ";
		cin >> p.price;
		cin.ignore();
		sprintf(price2D, "%.2f", p.price);
		p.category = managerDepartment;
		cout << "\tFragility           : ";
		cin >> p.fragility;
		cin.ignore();
		cout << "\tRating              : ";
		cin >> p.rating;
		cin.ignore();
		cout << "\tQuantity            : ";
		cin >> p.quantity;
		cin.ignore();
		cout << "\tExpiration date [DD/MM/YYYY]/[- for none]: ";
		getline(cin, p.expirationDate);

		cout << "\n\n\tProduct:-"
			"\n\n\tID              : " << p.id <<
			"\n\tName            : " << p.name <<
			"\n\tPrice           : RM " << price2D <<
			"\n\tCategory        : " << p.category <<
			"\n\tFragility       : " << p.fragility <<
			"\n\tRating          : " << p.rating <<
			"\n\tQuantity        : " << p.quantity <<
			"\n\tExpiration date : " << p.expirationDate;
		cout << "\n\n\tPress [y] to continue, [x] to retry, [e] to abort and return to menu.\n\t";
		getline(cin, opt);

		if (opt == "y" || opt == "Y") {
			string data = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + to_string(p.fragility) + '|' + to_string(p.rating) + '|' + to_string(p.quantity) + '|' + p.expirationDate;
			ofstream File;
			ifstream verifyProduct;

			verifyProduct.open("Inventory.txt");
			while (getline(verifyProduct, line)) {
				if (line.substr(8) == data.substr(8)) {
					flg = true;
					break;
				}
			}

			if (!flg) {
				File.open("Inventory.txt", ios::app);
				File << data << endl;
				File.close();
				cout << "\n\tNew product has been added successfully\n\t[Press enter to continue]";
				while (getchar() != '\n');
				break;
			}
			else {
				cout << "\n\tProduct already existed in the system. Information will be discarded\n\t[Press enter to continue]";
				while (getchar() != '\n');
			}

		}
		else if (opt != "y" && opt != "Y" && opt != "x" && opt != "X" && opt != "e" && opt != "E") {
			cout << "\n\tInvalid input. Please retry.\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	} while (opt != "e" && opt != "E");
}

void Manager::deleteProduct(string managerID) {
	Product p1, p2;
	string inputID, line, price, fragility, rating, quantity;
	char price2D[PRICE_BUFFER];
	bool flg = false;

	system("cls");
	cout << "\n\n\tDELETE PRODUCT:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}

	if (managerID.substr(0, 2) == inputID.substr(0, 2)) {
		ifstream File;
		ofstream File2;
		File.open("Inventory.txt");
		File2.open("temporary.txt");

		while (getline(File, line)) {
			stringstream lineObj(line);
			getline(lineObj, p1.id, '|');
			getline(lineObj, p1.name, '|');
			getline(lineObj, price, '|');
			getline(lineObj, p1.category, '|');
			getline(lineObj, fragility, '|');
			getline(lineObj, rating, '|');
			getline(lineObj, quantity, '|');
			getline(lineObj, p1.expirationDate, '|');
			if (inputID == p1.id) {
				flg = true; 
				p2 = p1;
				sprintf(price2D, "%.2f", stof(price));
				p2.fragility = stoi(fragility);
				p2.rating = stoi(rating);
				p2.quantity = stoi(quantity);
			}
			else {
				File2 << line << endl;
			}
		}
		File.close();
		File2.close();
		remove("Inventory.txt");
		rename("temporary.txt", "Inventory.txt");

		if (flg == true) {
			cout << "\n\n\tProduct deleted:-"
				"\n\n\tID              : " << p2.id <<
				"\n\tName            : " << p2.name <<
				"\n\tPrice           : RM " << price2D <<
				"\n\tCategory        : " << p2.category <<
				"\n\tFragility       : " << p2.fragility <<
				"\n\tRating          : " << p2.rating <<
				"\n\tQuantity        : " << p2.quantity <<
				"\n\tExpiration date : " << p2.expirationDate <<
				"\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			cout << "\n\n\tProduct is not found!\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	}
	else {
		cout << "\n\n\tProduct is not under manager supervision!\n\tPlease retry\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Manager::editProduct(string managerID) {
	Product p;
	string inputID, line, price, fragility, rating, quantity, quanOpt;
	char *price2D;
	bool flg = false;
	int opt, quantityAdd, quantityDeduct;
	float newPrice;

	system("cls");
	cout << "\n\n\tEDIT PRODUCT:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}

	if (managerID.substr(0, 2) == inputID.substr(0, 2)) {
		ifstream File;
		ofstream File2;
		File.open("Inventory.txt");
		File2.open("temporary.txt");

		while (getline(File, line)) {
			stringstream lineObj(line);
			getline(lineObj, p.id, '|');
			getline(lineObj, p.name, '|');
			getline(lineObj, price, '|');
			price2D = &price[0];
			getline(lineObj, p.category, '|');
			getline(lineObj, fragility, '|');
			getline(lineObj, rating, '|');
			getline(lineObj, quantity, '|');
			getline(lineObj, p.expirationDate, '|');
			if (inputID == p.id) {
				flg = true;
				cout << "\n\n\tWhich aspect would you like to edit?\n\t1. Name\n\t2. Price\n\t3. Fragility\n\t4. Rating\n\t5. Quantity\n\t6. Expiration date\n\tOption: ";
				cin >> opt;
				cin.ignore();
				switch (opt) {
				case 1:
					cout << "\n\tNew name: ";
					getline(cin, p.name);
					break;
				case 2:
					cout << "\n\tNew price: ";
					cin >> newPrice;
					cin.ignore();
					sprintf(price2D, "%.2f", newPrice);
					break;
				case 3:
					cout << "\n\tNew fragility: ";
					getline(cin, fragility);
					break;
				case 4:
					cout << "\n\tNew rating: ";
					getline(cin, rating);
					break;
				case 5:
					do {
						cout << "\n\t1. Increase quantity\n\t2. Decrease quantity\n\tOption: ";
						getline(cin, quanOpt);
						if (quanOpt == "1") {
							cout << "\n\tEnter quantity to be added: ";
							cin >> quantityAdd;
							cin.ignore();
							quantity = to_string(stoi(quantity) + quantityAdd);
						}
						else if (quanOpt == "2") {
							cout << "\n\tEnter quantity to be deducted: ";
							cin >> quantityDeduct;
							cin.ignore();
							if (quantityDeduct > stoi(quantity)) {
								cout << "\n\tInventory quantity is less than input amount!";
							}
							else {
								quantity = to_string(stoi(quantity) - quantityDeduct);
							}
						}
						else {
							cout << "\n\tInvalid input. Please select 1 or 2." << endl;
						}
					} while (quanOpt != "1" && quanOpt != "2");
					break;
				case 6:
					cout << "\n\tNew expiration date [DD/MM/YYYY]/[- for none]: ";
					getline(cin, p.expirationDate);
					break;
				default:
					cout << "\n\tInvalid input.";
					break;
				}
				string data = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + fragility + '|' + rating + '|' + quantity + '|' + p.expirationDate + '\n';
				File2 << data;
				cout << "\n\n\tProduct new information:-"
					"\n\n\tID              : " << p.id <<
					"\n\tName            : " << p.name <<
					"\n\tPrice           : RM " << price2D <<
					"\n\tCategory        : " << p.category <<
					"\n\tFragility       : " << fragility <<
					"\n\tRating          : " << rating <<
					"\n\tQuantity        : " << quantity <<
					"\n\tExpiration date : " << p.expirationDate <<
					"\n\n\t[Press enter to continue]";
				while (getchar() != '\n');
			}
			else {
				File2 << line << endl;
			}
		}
		File.close();
		File2.close();
		remove("Inventory.txt");
		rename("temporary.txt", "Inventory.txt");

		if (flg == false) {
			cout << "\n\n\tProduct is not found!\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	}
	 else {
		cout << "\n\n\tProduct is not under manager supervision!\n\tPlease retry\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Manager::viewProduct(string managerID) {
	string line, id, name, price, category, fragility, rating, quantity, date;
	int ctr, opt;

	system("cls");
	cout << "\n\n\tVIEW PRODUCT:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tProduct list:-" << endl;

	cout << "\n\t1. View all products\n\t2. View products under manager\n\tOption: ";
	cin >> opt;
	cin.ignore();

	if (opt == 1) {
		ifstream File;
		File.open("Inventory.txt");

		ctr = 1;
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
			cout << "\n\tProduct #" << ctr <<
				"\n\n\tID              : " << id <<
				"\n\tName            : " << name <<
				"\n\tPrice           : RM " << price <<
				"\n\tCategory        : " << category <<
				"\n\tFragility       : " << fragility <<
				"\n\tRating          : " << rating <<
				"\n\tQuantity        : " << quantity <<
				"\n\tExpiration date : " << date << endl;
			ctr++;
		}
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
		File.close();
	}
	else if (opt == 2) {
		ifstream File;
		File.open("Inventory.txt");

		ctr = 1;
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
			if (managerID.substr(0, 2) == id.substr(0, 2)) {
				cout << "\n\tProduct #" << ctr <<
					"\n\n\tID              : " << id <<
					"\n\tName            : " << name <<
					"\n\tPrice           : RM " << price <<
					"\n\tCategory        : " << category <<
					"\n\tFragility       : " << fragility <<
					"\n\tRating          : " << rating <<
					"\n\tQuantity        : " << quantity <<
					"\n\tExpiration date : " << date << endl;
				ctr++;
			}
		}
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
		File.close();
	}
	else {
		cout << "\n\tInvalid input. Please retry\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Manager::searchProduct() {
	search();
}

void Manager::addOrder() {
	string opt = "e";
	string line;
	bool flg = false;
	Order order;

	do {
		order.totalPrice = 0.0f;
		system("cls");
		cout << "\n\n\tAdd order:-" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter the following information:- " << endl;
		cout << "\n\tCustomer id [-1 to return] : ";
		getline(cin, order.customerID);
		if (order.customerID == "-1") {
			return;
		}
		cout << "\n\t--------------------------------------------";

		// to verify new order must have a corresponding customer
		ifstream customercheck;
		customercheck.open("customer information.txt");
		while (getline(customercheck, line)) {
			if (line.substr(0, 9) == order.customerID) {
				string ignoreData;
				flg = true;
				stringstream lineObj(line);
				for (int i = 0; i < 5; i++) {
					getline(lineObj, ignoreData, '|');
				}
				getline(lineObj, order.billingAddress, '|');
				getline(lineObj, order.paymentType, '|');
			}
		}

		if (flg) {
			string cont;
			Product* head = NULL;
			order.orderID = randomizedOrderID();

			do {
				head = append(head, &order);
				cout << "\n\tContinue to add item? [y to continue, x to stop]: ";
				getline(cin, cont);
			} while (cont == "y" || cont == "Y");

			cout << "\n\t--------------------------------------------";
			cout << "\n\n\tOrder ID: " << order.orderID << endl;
			display(head, order);
			printf("\n\n\tTotal price : RM%.2f", order.totalPrice);
			cout << "\n\t--------------------------------------------";
			cout << "\n\n\t[Press 'e' to complete order or 'x' to discard order]: ";
			getline(cin, opt);
			if (opt == "e" || opt == "E") {
				modifyFileAfterCompleteOrder(head, order);
			}
			else {
				cout << "\n\tOrder has been discarded\n\t[press enter to continue].";
				while (getchar() != '\n');
			}
		}
		else {
			cout << "\n\n\tcustomer is not found!\n\t[press enter to continue]";
			while (getchar() != '\n');
		}
	} while (opt != "e" && opt != "E");
}

void Manager::deleteOrder() {
	string inputOrderID, orderID, line;
	bool flg = false;

	system("cls");
	cout << "\n\n\tDELETE ORDER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tOrder ID  [-1 to return] : ";
	getline(cin, inputOrderID);
	if (inputOrderID == "-1") {
		return;
	}

	ifstream File;
	ofstream File2;
	File.open("Order.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, orderID, '|');
		if (inputOrderID == orderID) {
			flg = true;
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Order.txt");
	rename("temporary.txt", "Order.txt");

	if (flg == true) {
		cout << "\n\n\tOrder " << inputOrderID << " has been deleted.\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else {
		cout << "\n\n\tOrder " << inputOrderID << " is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Manager::editOrder() {
	// Allows editing of customer id, item (product id, quantity) and add new entry
	string inputOrderID, line, customerID, itemList, totalPrice;
	bool flg = false;
	int opt;
	Product* head = NULL, *ptr = NULL;
	Order order;

	system("cls");
	cout << "\n\n\tEDIT ORDER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tOrder ID  [-1 to return] : ";
	getline(cin, inputOrderID);
	if (inputOrderID == "-1") {
		return;
	}

	ifstream File;
	ofstream File2;
	File.open("Order.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, order.orderID, '|');
		if (inputOrderID == order.orderID) {
			getline(lineObj, order.customerID, '|');
			getline(lineObj, itemList, '|');
			getline(lineObj, totalPrice, '|');
			order.totalPrice = stof(totalPrice);
			getline(lineObj, order.billingAddress, '|');
			getline(lineObj, order.paymentType, '|');
			getline(lineObj, order.date, '|');
			flg = true;

			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. Customer ID\n\t2. Item list\n\t3. Add new entry\n\tOption: ";
			cin >> opt;
			cin.ignore();

			switch (opt) {
			case 1:
				// Update new customer id
				head = getItem(order.orderID, head, 0);
				itemList = "";
				cout << "\n\tNew ID: ";
				getline(cin, order.customerID);
				break;
			case 2: {
				int num, opt;
				head = getItem(order.orderID, head, 1);
				cout << "\n\n\tSelect the product number to edit: ";
				cin >> num;
				cin.ignore();
				cout << "\n\tEdit option:-\n\t1. Product\n\t2. Quantity\n\tOption: ";
				cin >> opt;
				cin.ignore();
				if (opt == 1) {
					// Edit product entirely
					head = editOrderProduct(num, head, &order);
				}
				else if (opt == 2) {
					// Edit product quantity which can be increased or decreased
					string quanOpt, quanAdd, quanDed;
					do {
						cout << "\n\t1. Increase quantity\n\t2. Decrease quantity\n\tOption: ";
						getline(cin, quanOpt);
						if (quanOpt == "1") {
							cout << "\n\tEnter quantity to be added: ";
							getline(cin, quanAdd);
							head = editProductQuantity(quanAdd, quanOpt, head, num, &order);
						}
						else if (quanOpt == "2") {
							cout << "\n\tEnter quantity to be deducted: ";
							getline(cin, quanDed);
							head = editProductQuantity(quanDed, quanOpt, head, num, &order);
						}
						else {
							cout << "\n\tInvalid input. Please select 1 or 2.\n\t[Press enter to continue]";
							while (getchar() != '\n');
						}
					} while (quanOpt != "1" && quanOpt != "2");
				}
				else {
					cout << "\n\n\tInvalid input.\n\t[Press enter to continue]";
					while (getchar() != '\n');
				}
				itemList = "";
			}
				break;
			case 3: {
				// Adding new entry
				head = getItem(order.orderID, head, 0);
				head = append(head, &order);
				
				string price, fragility, rating, data, quantity, prodID;
				char* price2D;
				ifstream F1;
				ofstream F2;
				Product p;
				Product* ptr;

				// To go to last node of item list (Linked list)
				ptr = head;
				while (ptr->link != NULL) {
					ptr = ptr->link;
				}
				prodID = ptr->id;
				
				if (prodID != order.appendProdID) {
					// Update inventory file but new entry already existed in order list
					F1.open("Inventory.txt");
					F2.open("temporary3.txt");
					while (getline(F1, line)) {
						stringstream lineObj(line);
						getline(lineObj, p.id, '|');
						getline(lineObj, p.name, '|');
						getline(lineObj, price, '|');
						price2D = &price[0];
						getline(lineObj, p.category, '|');
						getline(lineObj, fragility, '|');
						getline(lineObj, rating, '|');
						getline(lineObj, quantity, '|');
						p.quantity = stoi(quantity);
						getline(lineObj, p.expirationDate, '|');
						if (p.id == order.appendProdID) {
							p.quantity = p.quantity - order.appendProdQuant;
						}
						data = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + fragility + '|' + rating + '|' + to_string(p.quantity) + '|' + p.expirationDate;
						F2 << data << endl;
					}
					F1.close();
					F2.close();
					remove("Inventory.txt");
					rename("temporary3.txt", "Inventory.txt");
				}
				else {
					// Update inventory file and new entry does not exist in order list
					F1.open("Inventory.txt");
					F2.open("temporary3.txt");
					while (getline(F1, line)) {
						stringstream lineObj(line);
						getline(lineObj, p.id, '|');
						getline(lineObj, p.name, '|');
						getline(lineObj, price, '|');
						price2D = &price[0];
						getline(lineObj, p.category, '|');
						getline(lineObj, fragility, '|');
						getline(lineObj, rating, '|');
						getline(lineObj, quantity, '|');
						p.quantity = stoi(quantity);
						getline(lineObj, p.expirationDate, '|');
						if (p.id == prodID) {
							p.quantity = p.quantity - order.appendProdQuant;
						}
						data = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + fragility + '|' + rating + '|' + to_string(p.quantity) + '|' + p.expirationDate;
						F2 << data << endl;
					}
					F1.close();
					F2.close();
					remove("Inventory.txt");
					rename("temporary3.txt", "Inventory.txt");
				}
				itemList = "";
			}
				break;
			default:
				cout << "\n\n\tInvalid input.\n\t[Press enter to continue]";
				while (getchar() != '\n');
				break;
			}
			ptr = head;
			if (!ptr) {
				continue;
			}
			else {
				// Update order file
				while (ptr) {
					char price2D[10];
					sprintf(price2D, "%.2f", ptr->price);
					itemList = itemList + ptr->id + "," + ptr->name + "," + price2D + "," + to_string(ptr->quantity) + "," + ptr->expirationDate + ",";
					ptr = ptr->link;
				}
				char totalPrice2D[PRICE_BUFFER];
				sprintf(totalPrice2D, "%.2f", order.totalPrice);
				line = order.orderID + '|' + order.customerID + '|' + itemList + '|' + totalPrice2D + '|' + order.billingAddress + '|' + order.paymentType + '|' + order.date;
				File2 << line << endl;
			}
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Order.txt");
	rename("temporary.txt", "Order.txt");

	if (flg == true) {
		cout << "\n\tUpdated order:-" << endl;
		display(head, order);
		cout << "\n\n\tOrder " << inputOrderID << " has been updated.\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else {
		cout << "\n\n\tOrder " << inputOrderID << " is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Manager::viewOrder() {
	string line, price, ignoreData;
	Order order;
	int ctr = 1;
	Product* head = NULL;

	system("cls");
	cout << "\n\n\tVIEW ORDER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tORDER list:-" << endl;

	ifstream File;
	File.open("Order.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, order.orderID, '|');
		getline(lineObj, order.customerID, '|');
		getline(lineObj, ignoreData, '|');
		getline(lineObj, price, '|');
		getline(lineObj, order.billingAddress, '|');
		getline(lineObj, order.paymentType, '|');
		getline(lineObj, order.date, '|');
		cout << "\t__________________________________";
		cout << "\n\tOrder #" << ctr << "\n\tOrder id        : " << order.orderID << "\n\tCustomer id     : " << order.customerID;
		getItem(order.orderID, head, 1);
		cout << "\n\t__________________________________";
		cout << "\n\tTotal cost      : RM " << price << "\n\tBilling address : " << order.billingAddress << "\n\tPayment type    : " << order.paymentType << "\n\tDate            : " << order.date << endl;
		cout << "\t__________________________________";
		cout << "\n\n\t------------------------------------------------" << endl;
		ctr++;
	}
	cout << "\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

void Manager::searchOrder() {
	string inputOrderID, line, ignoreData, price;
	Order order;
	Product* head = NULL;

	system("cls");
	cout << "\n\n\tSEARCH ORDER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tOrder ID  [-1 to return] : ";
	getline(cin, inputOrderID);
	if (inputOrderID == "-1") {
		return;
	}

	ifstream File;
	File.open("Order.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, order.orderID, '|');
		if (order.orderID == inputOrderID) {
			getline(lineObj, order.customerID, '|');
			getline(lineObj, ignoreData, '|');
			getline(lineObj, price, '|');
			getline(lineObj, order.billingAddress, '|');
			getline(lineObj, order.paymentType, '|');
			getline(lineObj, order.date, '|');
			cout << "\n\tOrder id : " << order.orderID << "\n\tCustomer id : " << order.customerID;
			getItem(order.orderID, head, 1);
			cout << "\n\t__________________________________";
			cout << "\n\tTotal cost      : RM " << price << "\n\tBilling address : " << order.billingAddress << "\n\tPayment type    : " << order.paymentType << "\n\tDate            : " << order.date << endl;
			cout << "\t__________________________________";
			break;
		}
	}
	cout << "\n\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

#endif