#include <iostream>
#include <map>

using namespace std;

void print_menu();

void menu_exit();

int main(){

	int a;
	map<int, void (*)()> func = {{0, menu_exit}};
	do{
		print_menu();
		cin >> a;
		if(func.count(a)) func[a]();
		else cout << "Wrong number.\n";
	}while(true);

	return 0;
}

void print_menu(){

	cout << "\n\n\nWelcome to PectiBD.\n\nMain menu:\n";
	cout << "0. Exit\n\n";
	cout << "Enter number: ";
}

void menu_exit(){

	cout << "Are you sure? (y/n): ";
	char c;
	cin >> c;
	if(c == 'y') exit(0);
}
