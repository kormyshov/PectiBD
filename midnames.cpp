#include "header.h"

using namespace std;

bool is_similary_midname(const char *s1, const char *s2){

	//cout << s1 << "(" << strlen(s1) << ")" << " ~ " << s2 << "(" << strlen(s2) << ")" << " = " << DMdistance(s1, s2) << endl;
	return (DMdistance(s1, s2) < 6);
}

vector<string> list_midnames;
int add_list_midname(void *not_used, int cnt, char **arg, char **sz){

	string s(arg[0]);
	list_midnames.push_back(s);

	return 0;
}

void menu_add_midname(){

	cout << "Введите отчество (например Иванович): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	list_midnames.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM MiddleNames ORDER BY Name", add_list_midname, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	bool f = false;
	for(int i=0; i<(int)list_midnames.size(); ++i){
		if(is_similary_midname(name, list_midnames[i].c_str())){
			if(!f){
				cout << "\nВозможно Вы имели ввиду одно из этих отчеств:\n";
				f = true;
			}
			cout << list_midnames[i] << endl;
		}
	}
	char dat_name[101];
	if(f){
		cout << "Прервать добавление нового отчества? (y/n): ";
		char c;
		cin >> c;
		if(c == 'y') return ;
		cin.getline(dat_name, 100);
	}

	cout << "Введите отчество в дательном падеже (например Ивановичу): ";
	cin.getline(dat_name, 100);

	char query[1001];
	sprintf(query, "INSERT INTO MiddleNames VALUES (\"%s\", \"%s\")", name, dat_name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_midname(){

	cout << "Введите отчество (например Иванович): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	list_midnames.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM MiddleNames ORDER BY Name", add_list_midname, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	cout << "\nВозможно Вы имели ввиду одно из этих отчеств:\n";
	int cnt = 1;
	vector<string> similary_nm;
	for(int i=0; i<(int)list_midnames.size(); ++i){
		if(is_similary_midname(name, list_midnames[i].c_str())){
			cout << cnt++ << ". " << list_midnames[i] << endl;
			similary_nm.push_back(list_midnames[i]);
		}
	}
	cout << "Введите номер пункта или 0, чтобы отменить: ";
	int c;
	cin >> c;
	if(!c || c >= cnt) return ;

	char query[1001];
	sprintf(query, "DELETE FROM MiddleNames WHERE Name LIKE \"%s\"", similary_nm[c-1].c_str());
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}
}

int print_midnames(void *not_used, int cnt, char **arg, char **sz){

	printf("|| ");
	print_string(arg[0], 30);
	printf(" || ");
	print_string(arg[1], 30);
	printf(" ||\n");

	return 0;
}

void menu_print_midnames(){

	printf("|| ");
	print_string("Отчество", 30);
	printf(" || ");
	print_string("Дательный падеж", 30);
	printf(" ||\n");
	printf("===");
	printf("==============================");
	printf("====");
	printf("==============================");
	printf("===\n");

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM MiddleNames ORDER BY Name", print_midnames, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

