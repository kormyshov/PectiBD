#include "header.h"

using namespace std;

void menu_add_instructor(){

	cout << "Введите ФИО инструктора: ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "INSERT INTO Instructors VALUES (\"%s\")", name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Instructors: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_instructor(){

	cout << "Введите ФИО инструктора: ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "DELETE FROM Instructors WHERE Name LIKE \"%s\"", name);
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Instructors: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

int print_instructors(void *not_used, int cnt, char **arg, char **sz){

	printf("|| ");
	print_string(arg[0], 50);
	printf(" ||\n");

	return 0;
}

void menu_print_instructors(){

	printf("|| ");
	print_string("Фамилия, имя и отчество", 50);
	printf(" ||\n");
	printf("===");
	printf("==================================================");
	printf("===\n");

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM Instructors ORDER BY Name", print_instructors, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы Instructors: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

vector<pair<string,string> > instructors;
int add_instructor(void *not_used, int cnt, char **arg, char **nu){
	string id(arg[0]);
	string nm(arg[1]);
	instructors.push_back(make_pair(id, nm));

	return 0;
}

vector<pair<string,string> > get_instructors(){

	char *err = 0;
	int ret = 0;

	instructors.clear();

	ret = sqlite3_exec(db, "SELECT rowid, Name FROM Instructors ORDER BY Name", add_instructor, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Seasons: " << err << endl;
		sqlite3_free(err);
	}

	return instructors;
}
