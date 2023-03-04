#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <Windows.h> // For sleep function
#include <fstream> // For file stream
#include <sstream> // For stringstream (Objectifying string for manipulation)
#include <iomanip> // For customer id formatting
#include <cstdlib> // For srand
#include <vector>  // For variable size array
#include <ctime>

#include "user.h"
#include "admin_function.h"
#include "manager_function.h"
#include "customer_function.h"

using namespace std;

int main() {
	string opt;
	do {
		system("cls");
		cout << "\n\n\tWelcome to HORIZON [Online Shopping System]" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter your authorisation:" << endl;
		cout << "\t1. Administrator\n\t2. Manager\n\t3. Customer\n\tOption [-1 to exit]: ";
		getline(cin, opt);

		if (opt == "1") {
			Admin admin;
			admin.getInfo();
			if (admin.checkInfo()) {
				int opt;
				do {
					opt = admin.adminMenu();
					switch (opt) {
					case 1:
						admin.addManager();
						break;
					case 2:
						admin.deleteManager();
						break;
					case 3:
						admin.editManager();
						break;
					case 4:
						admin.viewManager();
						break;
					case 5:
						admin.searchManager();
						break;
					case 6:
						admin.addCustomer();
						break;
					case 7:
						admin.deleteCustomer();
						break;
					case 8:
						admin.editCustomer();
						break;
					case 9:
						admin.viewCustomer();
						break;
					case 10:
						admin.searchCustomer();
						break;
					case -1:
						break;
					default:
						cout << "\n\tInvalid input.\n\t[Press enter to continue]" << endl;
						while (getchar() != '\n');
						break;
					}
				} while (opt != -1);
			};
		}
		else if (opt == "2") {
			Manager manager;
			manager.getInfo();
			if (manager.checkInfo()) {
				int opt = 0;
				do {
					opt = manager.managerMenu();
					switch (opt) {
					case 1:
						manager.addProduct(manager.username, manager.department);
						break;
					case 2:
						manager.deleteProduct(manager.username);
						break;
					case 3:
						manager.editProduct(manager.username);
						break;
					case 4:
						manager.viewProduct(manager.username);
						break;
					case 5:
						manager.searchProduct();
						break;
					case 6:
						manager.addOrder();
						break;
					case 7:
						manager.deleteOrder();
						break;
					case 8:
						manager.editOrder();
						break;
					case 9:
						manager.viewOrder();
						break;
					case 10:
						manager.searchOrder();
						break;
					case -1:
						break;
					default:
						cout << "\n\tInvalid input.\n\t[Press enter to continue]" << endl;
						while (getchar() != '\n');
						break;
					}
				} while (opt != -1);
			};
		}
		else if (opt == "3") {
			Product* head = NULL;
			Order order;
			Customer customer;;
			customer.getInfo();
			if (customer.checkInfo()) {
				int opt = 0;
				do {
					opt = customer.customerMenu();
					switch (opt) {
					case 1:
						customer.searchProduct();
						break;
					case 2:
						customer.viewCatalogue();
						break;
					case 3:
						head = customer.addProductToCart(head, &order, customer);
						break;
					case 4:
						head = customer.displayBill(head, &order);
						break;
					case -1:
						break;
					default:
						cout << "\n\tInvalid input.\n\t[Press enter to continue]" << endl;
						while (getchar() != '\n');
						break;
					}
				} while (opt != -1);
			}
		}
		else if (opt == "-1") {
			cout << "\n\tSystem has been shut down.";
		}
		else {
			cout << "\n\tInvalid input.\n\t[Press enter to continue]" << endl;
			while (getchar() != '\n');
		}
	} while (opt != "-1");
	
	return 0;
}

