#ifndef CUSTOMER_FUNCTION_H
#define CUSTOMER_FUNCTION_H

int Customer::customerMenu() {
	string opt;
	int optInt;
	system("cls");
	cout << "\n\n\tCustomer menu:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tPlease select one of the following operations:-\n\t1. Search product\n\t2. View catalogue\n\t3. Add item to cart\n\t4. Display bill" << endl;
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

void Customer::searchProduct() {
	search();
}

void Customer::viewCatalogue() {
	// Allow selection of category for product vieving
	vector<string> category;
	string line, dataIgnore, cat, opt, categorySelected;

	system("cls");
	cout << "\n\n\tView catalouge:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tDepartments:-" << endl;

	ifstream File;
	File.open("Administration information.txt");
	while (getline(File, line)) {
		stringstream lineObj(line);
		for (int i = 0; i < 3; i++) {
			getline(lineObj, dataIgnore, '|');
		}
		getline(lineObj, cat, '|');
		category.push_back(cat);
	}
	File.close();
	
	for (int i = 0; i < category.size(); i++) {
		cout << "\n\t" << i+1 << ". " << category[i];
	}
	cout << "\n\tOption [-1 to return] : ";
	getline(cin, opt);
	if (opt == "-1") {
		return;
	}

	try {
		if (category.size() < stoi(opt)) {
			throw 404;
		}
		else {
			categorySelected = category[stoi(opt)-1];
			cout << "\n\t----------------------------------------" << endl;
			cout << "\t" << categorySelected << ":-";
		}
	}
	catch (...) {
		cout << "\n\tDepartment is not found\n\t[Press enter to continue]";
		while (getchar() != '\n');
		return;
	}


	Product p;
	string price, fragility, rating, quantity;
	int ctr = 1;

	File.open("Inventory.txt");
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, p.id, '|');
		getline(lineObj, p.name, '|');
		getline(lineObj, price, '|');
		getline(lineObj, p.category, '|');
		getline(lineObj, fragility, '|');
		getline(lineObj, rating, '|');
		getline(lineObj, quantity, '|');
		getline(lineObj, p.expirationDate, '|');
		if (p.category == categorySelected) {
			cout << "\n\n\tProduct #" << ctr;
			cout << "\n\tID              : " << p.id;
			cout << "\n\tName            : " << p.name;
			cout << "\n\tPrice           : RM " << price;
			cout << "\n\tFragility [1-5] : " << fragility;
			cout << "\n\tRating    [1-5] : " << rating;
			cout << "\n\tExpiration date : " << p.expirationDate;
			ctr++;
		}
	}
	cout << "\n\n\t[Press enter to continue]";
	while (getchar() != '\n');
}

Product* Customer::addProductToCart(Product* head, Order *order, Customer customer) {
	string line, inputID, quit = "n";

	system("cls");
	cout << "\n\n\tADD ITEM TO CART:-" << endl;
	cout << "\t------------------------------------------------" << endl;

	do {
		head = append(head, *(&order));
		cout << "\n\tContinue to add item? [y to continue, x to stop]: ";
		getline(cin, quit);
	} while (quit == "y" || quit == "Y");

	order->orderID = randomizedOrderID();
	order->customerID = customer.username;
	order->billingAddress = customer.billingAddress;
	order->paymentType = customer.cardType;

	if (head != NULL) {
		cout << "\n\tItem/items has/have been placed in order.\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	return head;
}

Product* Customer::displayBill(Product *head, Order *order) {
	string quit = "n";

	system("cls");
	cout << "\n\n\tBILL:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	if (head != NULL) {
		cout << "\n\n\tOrder id: " << order->orderID << endl;
		display(head, *order);
		printf("\n\n\tTotal price : RM %.2f", order->totalPrice);
		cout << "\n\n\t[Press 'e' to complete order or 'x' to discard order or 'c' to continue shopping]: ";
		getline(cin, quit);
		if (quit == "e" || quit == "E") {
			modifyFileAfterCompleteOrder(head, *order);
		}
		else if (quit == "x" || quit == "X") {
			head = NULL;
			order->totalPrice = 0.0F;
			cout << "\n\tOrder has been discarded\n\t[Press enter to continue].";
			while (getchar() != '\n');
			return head;
		}
		else if (quit == "c" || quit == "C") {
			return head;
		}
		else {
			cout << "\n\tInvalid input. System will return to customer menu.\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	}
	else {
		cout << "\n\tThere is no bill available to view.\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	return head;
}

#endif