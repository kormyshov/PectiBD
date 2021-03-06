#include "header.h"

using namespace std;

void print_menu();

void menu_exit();
void menu_create_bd();

std::string fname = "db.sqlite3";
sqlite3 *db = 0;

int main(){

	if(sqlite3_open(fname.c_str(), &db)){
		cerr << "Ошибка открытия/создания БД: " << sqlite3_errmsg(db) << endl;
		exit(0);
	}

	int a;
	map<int, void (*)()> func = {
									{11, menu_add_comstruct},
									{12, menu_del_comstruct},
									{13, menu_print_comstruct},
									{14, menu_load_comstruct},
									{21, menu_add_pupil},
									{22, menu_load_pupil},
									{101, menu_create_bd},
									{102, menu_add_school},
									{103, menu_del_school},
									{104, menu_print_schools},
									{105, menu_add_course},
									{106, menu_del_course},
									{107, menu_print_courses},
									{108, menu_add_instructor},
									{109, menu_del_instructor},
									{110, menu_print_instructors},
									{111, menu_add_season},
									{112, menu_del_season},
									{113, menu_print_seasons},
									{201, menu_add_name},
									{202, menu_del_name},
									{203, menu_print_names},
									{204, menu_add_midname},
									{205, menu_del_midname},
									{206, menu_print_midnames},
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
	cout << "\n 11. Добавить комсостав\n";
	cout << " 12. Удалить комсостав\n";
	cout << " 13. Вывести комсостав\n";
	cout << " 14. Загрузить комсостав из файла\n";
	cout << "\n 21. Добавить курсанта\n";
	cout << " 22. Загрузить курсантов из файла\n";
	cout << "\n101. Создание базы данных\n";
	cout << "102. Добавить школу\n";
	cout << "103. Удалить школу\n";
	cout << "104. Вывести школы\n";
	cout << "105. Добавить направление\n";
	cout << "106. Удалить направление\n";
	cout << "107. Вывести направления\n";
	cout << "108. Добавить инструктора\n";
	cout << "109. Удалить инструктора\n";
	cout << "110. Вывести инструкторов\n";
	cout << "111. Добавить смену\n";
	cout << "112. Удалить смену\n";
	cout << "113. Вывести смены\n";
	cout << "201. Добавить имя\n";
	cout << "202. Удалить имя\n";
	cout << "203. Вывести имена\n";
	cout << "204. Добавить отчество\n";
	cout << "205. Удалить отчество\n";
	cout << "206. Вывести отчества\n";
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

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Instructors(Name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Instructors: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Seasons(Name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Seasons: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Names(Name, Dat_name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы Names: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS MiddleNames(Name, Dat_name)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS CommandStructure(Season, Number, Instructor)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Crews(Season, Number, Pupil)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	ret = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Pupils(Surname, NameID, SecondNameID, SchoolID, Class, Sex, Date, DatSurmane)", 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при создании таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

