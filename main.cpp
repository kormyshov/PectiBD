#include <iostream>
#include <sqlite3.h>
#include <map>
#include <string>

using namespace std;

void print_menu();

void menu_exit();
void menu_create_bd();
void menu_add_school();
void menu_print_schools();

string fname = "db.sqlite3";
sqlite3 *db = 0;

int main(){

	if(sqlite3_open(fname.c_str(), &db)){
		cerr << "Ошибка открытия/создания БД: " << sqlite3_errmsg(db) << endl;
		exit(0);
	}

	int a;
	map<int, void (*)()> func = {
									{101, menu_create_bd},
									{102, menu_add_school},
									{104, menu_print_schools},
									{0,   menu_exit}
	};

	do{
		print_menu();
		cin >> a;
		if(func.count(a)) func[a]();
		else cout << "Неверное число. Попробуйте ещё раз.\n";
	}while(true);

	sqlite3_close(db);

	return 0;
}

void print_menu(){

	cout << "\n\n\nДобро пожаловать в PectiBD.\n\nГлавное меню:\n";
	cout << "\n101. Создание базы данных\n";
	cout << "102. Добавить школу\n";
	cout << "104. Вывести школы\n";
	cout << "0. Выход\n\n";
	cout << "Введите номер пункта меню: ";
}

void menu_exit(){

	cout << "Вы уверены, что хотите выйти? (y/n): ";
	char c;
	cin >> c;
	if(c == 'y') exit(0);
}

void menu_create_bd(){

	char *err = 0;
	int ret = 0;

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Schools(Name, Gen_name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}


}

void menu_add_school(){

	cout << "Введите название школы (например Гимназия №11 г. Красноярска или Шуваевская СОШ): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	cout << "Введите название школы в родительном падеже (например Гимназии №11 г. Красноярска или Шуваевской СОШ): ";
	char gen_name[101];
	cin.getline(gen_name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "INSERT INTO Schools VALUES (\"%s\", \"%s\")", name, gen_name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void print_string(char *s, int cnt){

	int i;
	for(i=0; s[i] && i<cnt; ++i){
		printf("%c", s[i]);
		if(s[i] == -48 || s[i] == -47) if(s[i+1] != -47 && s[i+1] != -48)++cnt;
		if(s[i] == -30) cnt += 2;
	}
	for(; i<cnt; ++i) printf(" ");
}

int print_schools(void *not_used, int cnt, char **arg, char **sz){

	//arg[0][62] = '\0';
	//arg[1][62] = '\0';
	printf("|| ");
	print_string(arg[0], 30);
	printf(" || ");
	print_string(arg[1], 30);
	printf(" ||\n");

	return 0;
}

void menu_print_schools(){

	printf("|| ");
	print_string("Название школы", 30);
	printf(" || ");
	print_string("Родительный падеж", 30);
	printf(" ||\n");
	printf("===");
	printf("==============================");
	printf("====");
	printf("==============================");
	printf("===\n");

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM Schools ORDER BY Name", print_schools, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}
