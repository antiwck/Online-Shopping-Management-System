#ifndef ORDER_H
#define ORDER_H

#define PRICE_BUFFER 10

// Linked list data structure
class Product {
public:
	string id, name, category, expirationDate;
	int fragility = 0, rating = 0, quantity = 0;
	float price = 0.00;
	Product* link;
};

class Order {
public:
	string orderID, customerID, billingAddress, paymentType, date, appendProdID;
	int appendProdQuant;
	float totalPrice = 0.0;
};

// Additonal functions
// Function declarations
Product* append(Product*, Order*);
void display(Product*, Order);
Product* getItem(string, Product*, int);
Product* editOrderProduct(int, Product*, Order*);
void modifyFileAfterCompleteOrder(Product*, Order);
string date();


Product* append(Product* head, Order *order) {
	string line, id, name, price, quantity, date, fragility, dataIgnore;
	bool flg = false, flg2 = false;
	
	Product* ptr = NULL, * temp = new Product();

	cout << "\n\tProduct id [-1 to return] : ";
	getline(cin, temp->id);
	if (temp->id == "-1") {
		return head;
	}
	cout << "\tQuantity: ";
	cin >> temp->quantity;
	cin.ignore();
	
	// To obtain item name, price, available quantity and expiration date
	ifstream File;
	File.open("Inventory.txt");
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, id, '|');
		getline(lineObj, name, '|');
		getline(lineObj, price, '|');
		getline(lineObj, dataIgnore, '|');
		getline(lineObj, fragility, '|');
		getline(lineObj, dataIgnore, '|');
		getline(lineObj, quantity, '|');
		getline(lineObj, date, '|');
		if (temp->id == id) {
			flg = true;
			break;
		}
	}
	File.close();
	temp->name = name;
	temp->price = stof(price);
	temp->fragility = stoi(fragility);
	temp->expirationDate = date;

	// To check if item already in list
	ptr = head;
	while (ptr) {
		if (ptr->id == id) {
			flg2 = true;
			break;
		}
		else {
			ptr = ptr->link;
		}
	}

	order->appendProdID = temp->id;
	order->appendProdQuant = temp->quantity;
	
	if (flg) {
		// check if quantity is sufficient, if not break
		if (stoi(quantity) < temp->quantity) {
			cout << "\n\tQuantity of " << name << " is insufficient.\n\tItem is discarded from list.";
			while (getchar() != '\n');
		}
		else {
			if (flg2) {
				ptr = head;
				while (ptr) {
					if (ptr->id == id) {
						ptr->quantity = ptr->quantity + temp->quantity;
						break;
					}
					else {
						ptr = ptr->link;
					}
				}
			}
			else {
				temp->link = NULL;
				ptr = head;
				if (head == NULL) {
					head = temp;
				}
				else {
					while (ptr->link) {
						ptr = ptr->link;
					}
					ptr->link = temp;
				}
			}
			
			// Totalling the price with inclusion of fragility packaging
			switch (temp->fragility) {
			case 1:
				order->totalPrice = order->totalPrice + (temp->price * temp->quantity) + (1.50 * temp->quantity);
				break;
			case 2:
				order->totalPrice = order->totalPrice + (temp->price * temp->quantity) + (2.00 * temp->quantity);
				break;
			case 3:
				order->totalPrice = order->totalPrice + (temp->price * temp->quantity) + (2.50 * temp->quantity);
				break;
			case 4:
				order->totalPrice = order->totalPrice + (temp->price * temp->quantity) + (3.00 * temp->quantity);
				break;
			case 5:
				order->totalPrice = order->totalPrice + (temp->price * temp->quantity) + (3.50 * temp->quantity);
				break;
			}
		}
	}
	else {
		cout << "\n\tProduct is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	return head;
}

void display(Product* head, Order order) {
	int ctr = 1;
	Product* ptr;
	ptr = head;
	cout << "\n\tItem list:\n";
	if (ptr == NULL) {
		cout << "\n\tThere is no item list.\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else {
		cout << "\n\tCustomer id : " << order.customerID;
		while (ptr) {
			cout << "\n\n\tProduct #" << ctr;
			cout << "\n\tID              : " << ptr->id;
			cout << "\n\tName            : " << ptr->name;
			printf("\n\tPrice           : RM% .2f", ptr->price);
			cout << "\n\tQuantity        : " << ptr->quantity;
			cout << "\n\tExpiration date : " << ptr->expirationDate;
			ptr = ptr->link;
			ctr++;
		}
	}
}

Product* getItem(string orderID, Product* head, int show) {
	string line, orderList, ignoreData, productID, productName, productPrice, productQuantity, productExpirationDate;
	int ctr = 1;
	Product* ptr = NULL, * temp;

	ifstream File;
	File.open("Order.txt");
	while (getline(File, line)) {
		if (line.substr(0, 11) == orderID) {
			stringstream lineObj(line);
			getline(lineObj, ignoreData, '|');
			getline(lineObj, ignoreData, '|');
			getline(lineObj, orderList, '|');
			break;
		}
	}
	stringstream orderObj(orderList);
	while (true) {
		temp = new Product();
		getline(orderObj, productID, ',');
		getline(orderObj, productName, ',');
		getline(orderObj, productPrice, ',');
		getline(orderObj, productQuantity, ',');
		getline(orderObj, productExpirationDate, ',');
		
		// To prevent going one extra loop
		if (!orderObj) {
			break;
		}

		temp->id = productID;
		temp->name = productName;
		temp->price = stof(productPrice);
		temp->quantity = stoi(productQuantity);
		temp->expirationDate = productExpirationDate;
		temp->link = NULL;
		ptr = head;
		if (head == NULL) {
			head = temp;
		}
		else {
			while (ptr->link) {
				ptr = ptr->link;
			}
			ptr->link = temp;
		}
	}
	if (show == 1) {
		ptr = head;
		while (ptr) {
			cout << "\n\n\tProduct #" << ctr;
			cout << "\n\tID              : " << ptr->id;
			cout << "\n\tName            : " << ptr->name;
			printf("\n\tPrice           : RM% .2f", ptr->price);
			cout << "\n\tQuantity        : " << ptr->quantity;
			cout << "\n\tExpiration date : " << ptr->expirationDate;
			ptr = ptr->link;
			ctr++;
		}
	}
	return head;
}

Product* editOrderProduct(int num, Product* head, Order *order) {
	string newProductID, line, ignoreData, productPrice, availableQuantity, prodCategory, prodFrag, prodRat;
	bool found = false, flg = false, flg2 = false;;
	float newProductPrice;
	int ctr = 1, newProductQuantity;

	Product* ptr = head;
	while (ptr) {
		if (ctr == num) {
			found = true;
			cout << "\n\tNew product ID : ";
			getline(cin, newProductID);
			cout << "\tQuantity       : ";
			cin >> newProductQuantity;
			cin.ignore();

			// To verify product, available quantity and rewrite inventory accordingly
			ifstream File1;
			ofstream File2;
			File1.open("Inventory.txt");
			File2.open("temporary1.txt");

			while (getline(File1, line)) {
				if (line.substr(0, 8) == newProductID) {
					stringstream lineObj(line);
					getline(lineObj, ptr->id, '|');
					getline(lineObj, ptr->name, '|');
					getline(lineObj, productPrice, '|');
					getline(lineObj, prodCategory, '|');
					getline(lineObj, prodFrag, '|');
					getline(lineObj, prodRat, '|');
					getline(lineObj, availableQuantity, '|');
					getline(lineObj, ptr->expirationDate, '|');

					// If available quantity is not sufficient
					if (stoi(availableQuantity) < newProductQuantity) {
						cout << "\n\tQuantity of " << ptr->name << " is insufficient.\n\tItem is discarded from list.";
						break;
					}
					// If available quantity is sufficient
					else {
						// For order total price, reduce the total by quantity of removed product price and add the new product quantity pricing
						order->totalPrice = order->totalPrice - (ptr->price * ptr->quantity) + (newProductQuantity * stof(productPrice));

						ptr->quantity = newProductQuantity;
						ptr->price = stof(productPrice);

						line = ptr->id + '|' + ptr->name + '|' + productPrice + '|' + prodCategory + '|' + prodFrag + '|' + prodRat + '|' + to_string(stoi(availableQuantity) - ptr->quantity) + '|' + ptr->expirationDate;
						File2 << line << endl;
						flg = true;
					}
				}
				else {
					File2 << line << endl;
				}
			}

			File1.close();
			File2.close();
			remove("Inventory.txt");
			rename("temporary1.txt", "Inventory.txt");
		}

		Product* temp = ptr->link;
		if (temp) {
			ptr = ptr->link;
		}
		else {
			break;
		}
		ctr++;
	}
	if (!found) {
		cout << "\n\tInput is out of list.\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else if(!flg){
		cout << "\n\tProduct is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	return head;
}

Product* editProductQuantity(string quantityMod, string opt, Product* head, int num, Order *order) {
	string line, productID, price, fragility, rating, quantityInventory;
	char price2D[PRICE_BUFFER];
	Product p;

	// To get the new product ID
	Product* ptr = head;
	int ctr = 1;
	while (ctr != num) {
		ptr = ptr->link;
		ctr++;
	}
	productID = ptr->id;

	// To check with inventory if available quantity is sufficient
	ifstream File;
	ofstream File2;
	File.open("Inventory.txt");
	File2.open("temporary2.txt");

	while (getline(File, line)) {
		if (line.substr(0, 8) == productID) {
			stringstream lineObj(line);
			getline(lineObj, p.id, '|');
			getline(lineObj, p.name, '|');
			getline(lineObj, price, '|');
			sprintf(price2D, "%.2f", stof(price));
			getline(lineObj, p.category, '|');
			getline(lineObj, fragility, '|');
			getline(lineObj, rating, '|');
			getline(lineObj, quantityInventory, '|');
			getline(lineObj, p.expirationDate, '|');
			if (opt == "1") {
				if (stoi(quantityInventory) < stoi(quantityMod)) {
					cout << "\n\tProduct quantity is insufficient. There is/are only " << quantityInventory << " available.\n\t[Press enter to continue]";
					while (getchar() != '\n');
				}
				else {
					quantityInventory = to_string(stoi(quantityInventory) - stoi(quantityMod));
					ptr->quantity = ptr->quantity + stoi(quantityMod);
					order->totalPrice = order->totalPrice + (stoi(quantityMod) * stof(price2D));
				}
			}
			else {
				if (ptr->quantity <= stoi(quantityMod)) {
					quantityInventory = to_string(stoi(quantityInventory) + ptr->quantity);
					order->totalPrice = order->totalPrice - (ptr->price * ptr->quantity);
					cout << "\n\t" << productID << " has been deducted to less than 0, product will be remove from order.\n\t[Press enter to continue]";
					while (getchar() != '\n');

					// Removing the item from item linked list
					ptr = head;
					if (ptr->id == productID) {
						head = ptr->link;
					}
					else {
						while (ptr->link) {
							if (ptr->link->id == productID) {
								Product* temp = ptr->link;
								if (temp->link) {
									ptr->link = temp->link;
								}
								else {
									ptr->link = NULL;
									break;
								}
								free(temp);
							}
							ptr = ptr->link;
						}
					}
				}
				else {
					quantityInventory = to_string(stoi(quantityInventory) + stoi(quantityMod));
					ptr->quantity = ptr->quantity - stoi(quantityMod);
					order->totalPrice = order->totalPrice - (stoi(quantityMod) * stof(price2D));
				}
			}
			line = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + fragility + '|' + rating + '|' + quantityInventory + '|' + p.expirationDate;
			File2 << line << endl;
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Inventory.txt");
	rename("temporary2.txt", "Inventory.txt");
	return head;
}

void modifyFileAfterCompleteOrder(Product* head, Order order) {
	string line, data, itemList, price, fragility, rating, quantity;
	char* price2D;

	// edit inventory by going through each line and check with linked list, if match, deduct quantity and write to new file else write to new file
	ifstream File1;
	ofstream File2;
	Product p;
	Product* ptr;
	File1.open("Inventory.txt");
	File2.open("temporary.txt");
	while (getline(File1, line)) {
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
		ptr = head;
		while (ptr) {
			if (ptr->id == p.id) {
				p.quantity = p.quantity - ptr->quantity;
				break;
			}
			else {
				ptr = ptr->link;
			}
		}
		data = p.id + '|' + p.name + '|' + price2D + '|' + p.category + '|' + fragility + '|' + rating + '|' + to_string(p.quantity) + '|' + p.expirationDate;
		File2 << data << endl;
	}
	File1.close();
	File2.close();
	remove("Inventory.txt");
	rename("temporary.txt", "Inventory.txt");

	// Writing the order into file
	order.date = date();
	ofstream File;
	File.open("Order.txt", ios::app);
	ptr = head;
	while (ptr) {
		char price2D[10];
		sprintf(price2D, "%.2f", ptr->price);
		itemList = itemList + ptr->id + "," + ptr->name + "," + price2D + "," + to_string(ptr->quantity) + "," + ptr->expirationDate + ",";
		ptr = ptr->link;
	}
	char totalPrice2D[PRICE_BUFFER];
	sprintf(totalPrice2D, "%.2f", order.totalPrice);
	data = order.orderID + '|' + order.customerID + '|' + itemList + '|' + totalPrice2D + '|' + order.billingAddress + '|' + order.paymentType + '|' + order.date;
	File << data << endl;
	File.close();

	cout << "\n\tOrder has been completed\n\t[press enter to continue]";
	while (getchar() != '\n');
}

string date() {
	// Date and time of system
	time_t currTime = time(0);
	tm* ltm = localtime(&currTime);
	string d, m, y, date;
	d = to_string(ltm->tm_mday);
	m = to_string(1 + ltm->tm_mon);
	y = to_string(1900 + ltm->tm_year);
	date = d + '/' + m + '/' + y;
	return date;
}

#endif