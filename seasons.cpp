#include "header.h"

using namespace std;

void menu_add_season(){

	cout << "Введите смену: ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "INSERT INTO Seasons VALUES (\"%s\")", name);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Seasons: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_del_season(){

	cout << "Введите смену: ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;

	char query[1001];
	sprintf(query, "DELETE FROM Seasons WHERE Name LIKE \"%s\"", name);
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Seasons: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

int cnt_seasons;
int print_seasons(void *not_used, int cnt, char **arg, char **sz){

	printf("|| %2d. || ", ++cnt_seasons);
	print_string(arg[0], 30);
	printf(" ||\n");

	return 0;
}

void menu_print_seasons(){

	printf("||  №  || ");
	print_string("Смена", 30);
	printf(" ||\n");
	printf("==========");
	printf("==============================");
	printf("===\n");

	cnt_seasons = 0;

	char *err = 0;
	int ret = sqlite3_exec(db, "SELECT * FROM Seasons ORDER BY Name", print_seasons, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы Seasons: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

vector<pair<string,string> > seasons;
int add_season(void *not_used, int cnt, char **arg, char **nu){
	string id(arg[0]);
	string nm(arg[1]);
	seasons.push_back(make_pair(id, nm));

	return 0;
}

vector<pair<string,string> > get_seasons(){

	char *err = 0;
	int ret = 0;

	seasons.clear();

	ret = sqlite3_exec(db, "SELECT rowid, Name FROM Seasons ORDER BY Name DESC", add_season, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Seasons: " << err << endl;
		sqlite3_free(err);
	}

	return seasons;
}

