#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

void print_menu();

void menu_exit();
void menu_create_bd();
void menu_add_school();
void menu_del_school();
void menu_print_schools();
void menu_add_course();
void menu_del_course();
void menu_print_courses();
void menu_add_name();
void menu_del_name();
void menu_print_names();

bool is_similary_school(const char *, const char *);

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
									{103, menu_del_school},
									{104, menu_print_schools},
									{105, menu_add_course},
									{106, menu_del_course},
									{107, menu_print_courses},
									{111, menu_add_name},
									{112, menu_del_name},
									{113, menu_print_names},
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
	cout << "103. Удалить школу\n";
	cout << "104. Вывести школы\n";
	cout << "105. Добавить направление\n";
	cout << "106. Удалить направление\n";
	cout << "107. Вывести направления\n";
	cout << "111. Добавить имя\n";
	cout << "112. Удалить имя\n";
	cout << "113. Вывести имена\n";
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

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Courses(Name, Dat_name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Courses: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Names(Name, Dat_name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

vector<string> school_names;
int add_school_name(void *not_used, int cnt, char **arg, char **sz){

	string s(arg[0]);
	school_names.push_back(s);

	return 0;
}

void menu_add_school(){

	cout << "Введите название школы (например Гимназия №11 г. Красноярска или Шуваевская СОШ): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	school_names.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM Schools ORDER BY Name", add_school_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	cout << "\nВозможно Вы имели ввиду одну из этих школ:\n";
	for(int i=0; i<(int)school_names.size(); ++i){
		if(is_similary_school(name, school_names[i].c_str())) cout << school_names[i] << endl;
	}
	cout << "Прервать добавление новой школы? (y/n): ";
	char c;
	cin >> c;
	if(c == 'y') return ;

	cout << "Введите название школы в родительном падеже (например Гимназии №11 г. Красноярска или Шуваевской СОШ): ";
	char gen_name[101];
	cin.getline(gen_name, 100);
	cin.getline(gen_name, 100);

	char query[1001];
	sprintf(query, "INSERT INTO Schools VALUES (\"%s\", \"%s\")", name, gen_name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_school(){

	cout << "Введите название школы (например Гимназия №11 г. Красноярска или Шуваевская СОШ): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	school_names.clear();
	ret = sqlite3_exec(db, "SELECT Name FROM Schools ORDER BY Name", add_school_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	cout << "\nВозможно Вы имели ввиду одну из этих школ:\n";
	int cnt = 1;
	vector<string> similary_sch;
	for(int i=0; i<(int)school_names.size(); ++i){
		if(is_similary_school(name, school_names[i].c_str())){
			cout << cnt++ << ". " << school_names[i] << endl;
			similary_sch.push_back(school_names[i]);
		}
	}
	cout << "Введите номер пункта или 0, чтобы отменить: ";
	int c;
	cin >> c;
	if(!c || c >= cnt) return ;

	char query[1001];
	sprintf(query, "DELETE FROM Schools WHERE Name LIKE \"%s\"", similary_sch[c-1].c_str());
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}
}

void print_string(const char *s, int cnt){

	int i;
	for(i=0; s[i] && i<cnt; ++i){
		printf("%c", s[i]);
		if(s[i] == -48 || s[i] == -47) if(s[i+1] != -47 && s[i+1] != -48)++cnt;
		if(s[i] == -30) cnt += 2;
	}
	for(; i<cnt; ++i) printf(" ");
}

int print_schools(void *not_used, int cnt, char **arg, char **sz){

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

int DMcost(char c1, char c2){

	if(c1 == c2) return 0;
	if((c1 >= '0' && c1 <= '9') || (c2 >= '0' && c2 <= '9')) return 5;
	return 1;
}

int DMdistance(const char *s1, const char *s2){

	int n = strlen(s1);
	int m = strlen(s2);

	int **mm = new int*[n+1];
	for(int i=0; i<=n; ++i){
		mm[i] = new int[m+1];
		for(int j=0; j<=m; ++j){
			if(!i || !j){
				mm[i][j] = i+j;
				continue ;
			}
			mm[i][j] = mm[i-1][j] + 2;
			mm[i][j] = min(mm[i][j], mm[i][j-1] + 2);
			mm[i][j] = min(mm[i][j], mm[i-1][j-1] + DMcost(s1[i-1], s2[j-1]));
		}
	}
	return mm[n][m];
}

bool is_similary_school(const char *s1, const char *s2){

	//cout << s1 << "(" << strlen(s1) << ")" << " ~ " << s2 << "(" << strlen(s2) << ")" << " = " << DMdistance(s1, s2) << endl;
	return (DMdistance(s1, s2) < 10);
}

void menu_add_course(){

	cout << "Введите название направления (например Информатика): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	cout << "Введите название направления в дательном падеже и с маленькой буквы (например информатике): ";
	char dat_name[101];
	cin.getline(dat_name, 100);

	char query[1001];
	sprintf(query, "INSERT INTO Courses VALUES (\"%s\", \"%s\")", name, dat_name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Courses: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_course(){

	cout << "Введите название направления (например Информатика): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "DELETE FROM Courses WHERE Name LIKE \"%s\"", name);
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Courses: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

int print_courses(void *not_used, int cnt, char **arg, char **sz){

	printf("|| ");
	print_string(arg[0], 30);
	printf(" || ");
	print_string(arg[1], 30);
	printf(" ||\n");

	return 0;
}

void menu_print_courses(){

	printf("|| ");
	print_string("Направление", 30);
	printf(" || ");
	print_string("Дательный падеж", 30);
	printf(" ||\n");
	printf("===");
	printf("==============================");
	printf("====");
	printf("==============================");
	printf("===\n");

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM Courses ORDER BY Name", print_courses, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы Courses: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

bool is_similary_name(const char *s1, const char *s2){

	//cout << s1 << "(" << strlen(s1) << ")" << " ~ " << s2 << "(" << strlen(s2) << ")" << " = " << DMdistance(s1, s2) << endl;
	return (DMdistance(s1, s2) < 5);
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

	cout << "\nВозможно Вы имели ввиду одно из этих имён:\n";
	for(int i=0; i<(int)list_names.size(); ++i){
		if(is_similary_name(name, list_names[i].c_str())) cout << list_names[i] << endl;
	}
	cout << "Прервать добавление нового имени? (y/n): ";
	char c;
	cin >> c;
	if(c == 'y') return ;

	cout << "Введите имя в дательном падеже (например Ивану): ";
	char dat_name[101];
	cin.getline(dat_name, 100);
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
