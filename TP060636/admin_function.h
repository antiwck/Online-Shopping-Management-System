#ifndef ADMIN_FUNCTION_H
#define ADMIN_FUNCTION_H

// Function declaration
string randomizedCustomerID();

int Admin::adminMenu() {
	string opt;
	int optInt;
	system("cls");
	cout << "\n\n\tAdmin menu:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tPlease select one of the following operations:-\n\t1. Add manager\n\t2. Delete manager\n\t3. Edit manager\n\t4. View manager\n\t5. Search manager\n\t6. Add customer\n\t7. Delete customer\n\t8. Edit customer\n\t9. View customer\n\t10. Search customer" << endl;
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

void Admin::addManager() {
	Manager m;
	string opt;
	do {
		system("cls");
		cout << "\n\n\tADD MANAGER:-" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter the following information:- " << endl;
		cout << "\tID [-1 to return] : ";
		getline(cin, m.username);
		if (m.username == "-1") {
			return;
		}
		cout << "\tPassword          : ";
		getline(cin, m.password);
		cout << "\tName              : ";
		getline(cin, m.name);
		cout << "\tDepartment        : ";
		getline(cin, m.department);
		cout << "\tContact           : ";
		getline(cin, m.contact);
		cout << "\n\n\tInformation:-\n\n\tID         : " << m.username << "\n\tPassword   : " << m.password << "\n\tName       : " << m.name << "\n\tDepartment : " << m.department << "\n\tContact    : " << m.contact;
		cout << "\n\n\tPress [y] to continue, [x] to retry, [e] to abort and return to menu.\n\t";
		getline(cin, opt);

		if (opt == "y" || opt == "Y") {
			string data = m.username + '|' + m.password + '|' + m.name + '|' + m.department + '|' + m.contact + "\n";
			ofstream File;
			File.open("Administration information.txt", ios::app);
			File << data;
			File.close();
			cout << "\n\tNew manager has been added successfully.\n\t[Press enter to continue]" << endl;
			while (getchar() != '\n');
			break;
		}
		else if (opt != "y" && opt != "Y" && opt != "x" && opt != "X" && opt != "e" && opt != "E") {
			cout << "\n\tInvalid input. Please retry.\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	} while (opt != "e" && opt != "E");
}

void Admin::deleteManager() {
	Manager m1, m2;
	string inputID, inputPassword, line;
	bool flg = false;

	system("cls");
	cout << "\n\n\tDELETE MANAGER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}
	cout << "\tPassword   : ";
	getline(cin, inputPassword);

	ifstream File;
	ofstream File2;
	File.open("Administration information.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, m1.username, '|');
		getline(lineObj, m1.password, '|');
		getline(lineObj, m1.name, '|');
		getline(lineObj, m1.department, '|');
		getline(lineObj, m1.contact, '|');
		if (inputID == m1.username && inputPassword == m1.password) {
			flg = true;
			m2 = m1;
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Administration information.txt");
	rename("temporary.txt", "Administration information.txt");

	if (flg == true) {
		cout << "\n\n\tManager deleted:-\n\n\tID         : " << m2.username << "\n\tPassword   : " << m2.password << "\n\tName       : " << m2.name << "\n\tDepartment : " << m2.department << "\n\tContact    : " << m2.contact << "\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else {
		cout << "\n\n\tManager is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::editManager() {
	Manager m;
	string inputID, inputPassword, line;
	bool flg = false;
	int opt;

	system("cls");
	cout << "\n\n\tEDIT MANAGER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}
	cout << "\tPassword   : ";
	getline(cin, inputPassword);

	ifstream File;
	ofstream File2;
	File.open("Administration information.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, m.username, '|');
		getline(lineObj, m.password, '|');
		getline(lineObj, m.name, '|');
		getline(lineObj, m.department, '|');
		getline(lineObj, m.contact, '|');
		if (inputID == m.username && inputPassword == m.password) {
			flg = true;
			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. ID\n\t2. Password\n\t3. Name\n\t4. Department\n\t5. Contact\n\tOption: ";
			cin >> opt;
			cin.ignore();
			switch (opt) {
			case 1:
				cout << "\n\tNew ID: ";
				getline(cin, m.username);
				break;
			case 2:
				cout << "\n\tNew password: ";
				getline(cin, m.password);
				break;
			case 3:
				cout << "\n\tNew name: ";
				getline(cin, m.name);
				break;
			case 4:
				cout << "\n\tNew department: ";
				getline(cin, m.department);
				break;
			case 5:
				cout << "\n\tNew contact: ";
				getline(cin, m.contact);
				break;
			default:
				cout << "\n\tInvalid input.";
				break;
			}
			string data = m.username + '|' + m.password + '|' + m.name + '|' + m.department + '|' + m.contact + "\n";
			File2 << data;
			cout << "\n\n\tManager new information:-\n\n\tID         : " << m.username << "\n\tPassword   : " << m.password << "\n\tName       : " << m.name << "\n\tDepartment : " << m.department << "\n\tContact    : " << m.contact << "\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Administration information.txt");
	rename("temporary.txt", "Administration information.txt");

	if (flg == false) {
		cout << "\n\n\tManager is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::viewManager() {
	Manager m;
	string line;
	int ctr;

	system("cls");
	cout << "\n\n\tVIEW MANAGER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tManager list:-" << endl;

	ifstream File;
	File.open("Administration information.txt");

	ctr = 1;
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, m.username, '|');
		getline(lineObj, m.password, '|');
		getline(lineObj, m.name, '|');
		getline(lineObj, m.department, '|');
		getline(lineObj, m.contact, '|');
		cout << "\n\tManager #" << ctr << "\n\tID         : " << m.username << "\n\tPassword   : " << m.password << "\n\tName       : " << m.name << "\n\tDepartment : " << m.department << "\n\tContact    : " << m.contact << endl;
		ctr++;
	}
	cout << "\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

void Admin::searchManager() {
	Manager m;
	string inputID, line;
	bool flg = false;

	system("cls");
	cout << "\n\n\tSEARCH MANAGER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}

	ifstream File;
	File.open("Administration information.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, m.username, '|');
		getline(lineObj, m.password, '|');
		getline(lineObj, m.name, '|');
		getline(lineObj, m.department, '|');
		getline(lineObj, m.contact, '|');
		if (inputID == m.username) {
			flg = true;
			cout << "\n\tID         : " << m.username << "\n\tPassword   : " << m.password << "\n\tName       : " << m.name << "\n\tDepartment : " << m.department << "\n\tContact    : " << m.contact << "\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
			break;
		}
	}
	File.close();

	if (flg == false) {
		cout << "\n\n\tManager is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

string randomizedCustomerID() {
	bool flg = false;
	string id, line;
	stringstream randomVal;
	srand(time(NULL));

	do {
		randomVal << setfill('0') << setw(6) << 1 + (rand() % 999999);
		id = "wck" + randomVal.str();

		ifstream File;
		File.open("Customer information.txt");

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

void Admin::addCustomer() {
	Customer c;
	string opt;
	bool flg = false;

	do {
		system("cls");
		cout << "\n\n\tADD CUSTOMER:-" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter the following information:- " << endl;
		cout << "\tPassword       [-1 to return] : ";
		getline(cin, c.password);
		if (c.password == "-1") {
			return;
		}
		cout << "\tName                          : ";
		getline(cin, c.name);
		cout << "\tContact                       : ";
		getline(cin, c.contact);
		cout << "\tAddress                       : ";
		getline(cin, c.address);
		cout << "\tBilling address [16 digits]   : ";
		getline(cin, c.billingAddress);
		cout << "\tCard type [Credit/Debit card] : ";
		getline(cin, c.cardType);
		c.username = randomizedCustomerID();
		cout << "\n\n\tInformation:-" <<
			"\n\n\tID              : " << c.username <<
			"\n\tPassword        : " << c.password <<
			"\n\tName            : " << c.name <<
			"\n\tcontact         : " << c.contact <<
			"\n\tAddress         : " << c.address <<
			"\n\tBilling address : " << c.billingAddress <<
			"\n\tCard type       : " << c.cardType;
		cout << "\n\n\tPress [y] to continue, [x] to retry, [e] to abort and return to menu.\n\t";
		cin >> opt;
		cin.ignore();
		
		if (opt == "y" || opt == "Y") {
			string data = c.username + '|' + c.password + '|' + c.name + '|' + c.contact + '|' + c.address + '|' + c.billingAddress + '|' + c.cardType;
		
			string line;
			ifstream verifyUser;
			ofstream File;
		
			verifyUser.open("Customer information.txt");
			while (getline(verifyUser, line)) {
				if (line.substr(9) == data.substr(9)) {
					flg = true;
					break;
				}
			}
			if (!flg) {
				File.open("Customer information.txt", ios::app);
				File << data << endl;
				File.close();
				cout << "\n\tNew customer has been added successfully." << endl;
				Sleep(2000);
				break;
			}
			else {
				cout << "\n\tCustomer already existed in the system. Information will be discarded" << endl;
				Sleep(2000);
			}
		}
		else if (opt != "y" && opt != "Y" && opt != "x" && opt != "X" && opt != "e" && opt != "E") {
			cout << "\n\tInvalid input. Please retry.\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
	} while (opt != "e" && opt != "E");
}

void Admin::deleteCustomer() {
	Customer c1, c2;
	string inputID, inputPassword, line;
	bool flg = false;

	system("cls");
	cout << "\n\n\tDELETE CUSTOMER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}
	cout << "\tPassword          : ";
	getline(cin, inputPassword);

	ifstream File;
	ofstream File2;
	File.open("Customer information.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, c1.username, '|');
		getline(lineObj, c1.password, '|');
		getline(lineObj, c1.name, '|');
		getline(lineObj, c1.contact, '|');
		getline(lineObj, c1.address, '|');
		getline(lineObj, c1.billingAddress, '|');
		getline(lineObj, c1.cardType, '|');
		if (inputID == c1.username && inputPassword == c1.password) {
			flg = true;
			c2 = c1;
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Customer information.txt");
	rename("temporary.txt", "Customer information.txt");

	if (flg == true) {
		cout << "\n\n\tCustomer deleted:-\n\n\tID              : " << c2.username <<
			"\n\tPassword        : " << c2.password <<
			"\n\tName            : " << c2.name <<
			"\n\tcontact         : " << c2.contact <<
			"\n\tAddress         : " << c2.address <<
			"\n\tBilling address : " << c2.billingAddress <<
			"\n\tCard type       : " << c2.cardType << "\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
	else {
		cout << "\n\n\tCustomer is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::editCustomer() {
	Customer c;
	string inputID, inputPassword, line;
	bool flg = false;
	int opt;

	system("cls");
	cout << "\n\n\tEDIT CUSTOMER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}
	cout << "\tPassword   : ";
	getline(cin, inputPassword);

	ifstream File;
	ofstream File2;
	File.open("Customer information.txt");
	File2.open("temporary.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, c.username, '|');
		getline(lineObj, c.password, '|');
		getline(lineObj, c.name, '|');
		getline(lineObj, c.contact, '|');
		getline(lineObj, c.address, '|');
		getline(lineObj, c.billingAddress, '|');
		getline(lineObj, c.cardType, '|');
		if (inputID == c.username && inputPassword == c.password) {
			flg = true;
			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. ID\n\t2. Password\n\t3. Name\n\t4. Contact\n\t5. Address\n\t6. Billing addess\n\t7. Card type\n\tOption: ";
			cin >> opt;
			cin.ignore();
			switch (opt) {
			case 1:
				cout << "\n\tNew ID: ";
				getline(cin, c.username);
				break;
			case 2:
				cout << "\n\tNew password: ";
				getline(cin, c.password);
				break;
			case 3:
				cout << "\n\tNew name: ";
				getline(cin, c.name);
				break;
			case 4:
				cout << "\n\tNew contact: ";
				getline(cin, c.contact);
				break;
			case 5:
				cout << "\n\tNew address: ";
				getline(cin, c.address);
				break;
			case 6:
				cout << "\n\tNew billing address: ";
				getline(cin, c.billingAddress);
				break;
			case 7:
				cout << "\n\tNew card type: ";
				getline(cin, c.cardType);
				break;
			default:
				cout << "\n\tInvalid input.";
				break;
			}
			string data = c.username + '|' + c.password + '|' + c.name + '|' + c.contact + '|' + c.address + '|' + c.billingAddress + '|' + c.cardType + "\n";
			File2 << data;
			cout << "\n\n\tCustomer new information:-" <<
				"\n\n\tID              : " << c.username <<
				"\n\tPassword        : " << c.password <<
				"\n\tName            : " << c.name <<
				"\n\tcontact         : " << c.contact <<
				"\n\tAddress         : " << c.address <<
				"\n\tBilling address : " << c.billingAddress <<
				"\n\tCard type       : " << c.cardType <<
				"\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			File2 << line << endl;
		}
	}
	File.close();
	File2.close();
	remove("Customer information.txt");
	rename("temporary.txt", "Customer information.txt");

	if (flg == false) {
		cout << "\n\n\tCustomer is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::viewCustomer() {
	Customer c;
	string line;
	int ctr;

	system("cls");
	cout << "\n\n\tVIEW CUSTOMER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tCustomer list:-" << endl;

	ifstream File;
	File.open("Customer information.txt");

	ctr = 1;
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, c.username, '|');
		getline(lineObj, c.password, '|');
		getline(lineObj, c.name, '|');
		getline(lineObj, c.contact, '|');
		getline(lineObj, c.address, '|');
		getline(lineObj, c.billingAddress, '|');
		getline(lineObj, c.cardType, '|');
		cout << "\n\n\tcustomer #" << ctr <<
			"\n\tID              : " << c.username <<
			"\n\tPassword        : " << c.password <<
			"\n\tName            : " << c.name <<
			"\n\tcontact         : " << c.contact <<
			"\n\tAddress         : " << c.address <<
			"\n\tBilling address : " << c.billingAddress <<
			"\n\tCard type       : " << c.cardType << endl;
		ctr++;
	}
	cout << "\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

void Admin::searchCustomer() {
	Customer c;
	string inputID, line;
	bool flg = false;

	system("cls");
	cout << "\n\n\tSEARCH MANAGER:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tID [-1 to return] : ";
	getline(cin, inputID);
	if (inputID == "-1") {
		return;
	}

	ifstream File;
	File.open("Customer information.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, c.username, '|');
		getline(lineObj, c.password, '|');
		getline(lineObj, c.name, '|');
		getline(lineObj, c.contact, '|');
		getline(lineObj, c.address, '|');
		getline(lineObj, c.billingAddress, '|');
		getline(lineObj, c.cardType, '|');
		if (inputID == c.username) {
			flg = true;
			cout <<
				"\n\tID              : " << c.username <<
				"\n\tPassword        : " << c.password <<
				"\n\tName            : " << c.name <<
				"\n\tcontact         : " << c.contact <<
				"\n\tAddress         : " << c.address <<
				"\n\tBilling address : " << c.billingAddress <<
				"\n\tCard type       : " << c.cardType <<
				"\n\n\t[Press enter to continue]" << endl;
			while (getchar() != '\n');
			break;
		}
	}
	File.close();

	if (flg == false) {
		cout << "\n\n\tCustomer is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

#endif