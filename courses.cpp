#include "header.h"

using namespace std;

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
