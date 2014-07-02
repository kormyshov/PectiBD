#include "header.h"

using namespace std;

bool is_similary_name(const char *s1, const char *s2){

	//cout << s1 << "(" << strlen(s1) << ")" << " ~ " << s2 << "(" << strlen(s2) << ")" << " = " << DMdistance(s1, s2) << endl;
	return (DMdistance(s1, s2) < 4);
}

vector<string> list_names;
int add_list_name(void *not_used, int cnt, char **arg, char **sz){

	string s(arg[0]);
	list_names.push_back(s);

	return 0;
}

void menu_add_name(){

	cout << "Введите имя (например Иван): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	list_names.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM Names ORDER BY Name", add_list_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	bool f = false;
	for(int i=0; i<(int)list_names.size(); ++i){
		if(is_similary_name(name, list_names[i].c_str())){
			if(!f){
				cout << "\nВозможно Вы имели ввиду одно из этих имён:\n";
				f = true;
			}
			cout << list_names[i] << endl;
		}
	}
	char dat_name[101];
	if(f){
		cout << "Прервать добавление нового имени? (y/n): ";
		char c;
		cin >> c;
		if(c == 'y') return ;
		cin.getline(dat_name, 100);
	}

	cout << "Введите имя в дательном падеже (например Ивану): ";
	cin.getline(dat_name, 100);

	char query[1001];
	sprintf(query, "INSERT INTO Names VALUES (\"%s\", \"%s\")", name, dat_name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_name(){

	cout << "Введите имя (например Иван): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	list_names.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM Names ORDER BY Name", add_list_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	cout << "\nВозможно Вы имели ввиду одно из этих имён:\n";
	int cnt = 1;
	vector<string> similary_nm;
	for(int i=0; i<(int)list_names.size(); ++i){
		if(is_similary_name(name, list_names[i].c_str())){
			cout << cnt++ << ". " << list_names[i] << endl;
			similary_nm.push_back(list_names[i]);
		}
	}
	cout << "Введите номер пункта или 0, чтобы отменить: ";
	int c;
	cin >> c;
	if(!c || c >= cnt) return ;

	char query[1001];
	sprintf(query, "DELETE FROM Names WHERE Name LIKE \"%s\"", similary_nm[c-1].c_str());
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}
}

int print_names(void *not_used, int cnt, char **arg, char **sz){

	printf("|| ");
	print_string(arg[0], 30);
	printf(" || ");
	print_string(arg[1], 30);
	printf(" ||\n");

	return 0;
}

void menu_print_names(){

	printf("|| ");
	print_string("Имя", 30);
	printf(" || ");
	print_string("Дательный падеж", 30);
	printf(" ||\n");
	printf("===");
	printf("==============================");
	printf("====");
	printf("==============================");
	printf("===\n");

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM Names ORDER BY Name", print_names, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

vector<pair<string,string> > names;
int add_name(void *not_used, int cnt, char **arg, char **nu){
	string id(arg[0]);
	string nm(arg[1]);
	names.push_back(make_pair(id, nm));

	return 0;
}

vector<pair<string,string> > get_names(){

	char *err = 0;
	int ret = 0;

	names.clear();

	ret = sqlite3_exec(db, "SELECT rowid, Name FROM Names", add_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Names: " << err << endl;
		sqlite3_free(err);
	}

	return names;
}
