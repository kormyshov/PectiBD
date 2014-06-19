#include "header.h"

using namespace std;

void menu_add_comstruct(){

	char *err = 0;
	int ret = 0;

	vector<pair<string,string> > seasons = get_seasons();

	cout << "Список смен:\n";
	for(int i=0; i<(int)seasons.size(); ++i)
		cout << i+1 << ". " << seasons[i].second << endl;

	cout << "Выберите смену (или 0, чтобы прервать добавление): ";
	int n;
	cin >> n;
	n--;
	if(n<0 || n>= seasons.size()) return ;

	cout << "Введите номер экипажа: ";
	int m;
	cin >> m;
	if(!m) return ;

	vector<pair<string,string> > instructors = get_instructors();

	cout << "Список инструкторов:\n";
	for(int i=0; i<(int)instructors.size(); ++i)
		cout << i+1 << ". " << instructors[i].second << endl;

	cout << "Выберите инструктора (или 0, чтобы прервать добавление): ";
	int k;
	cin >> k;
	k--;
	if(k<0 || k>= instructors.size()) return ;

	char query[1001];
	sprintf(query, "INSERT INTO CommandStructure VALUES (\'%s\', %d, \'%s\')", seasons[n].first.c_str(), m, instructors[k].first.c_str());

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу CommandStructure: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

int number_command;
vector<pair<int,string> > load_res;

int add_res(void *not_used, int n, char **arg, char **nu){

	string s(arg[0]);
	load_res.push_back(make_pair(number_command, s));

	return 0;
}

void menu_load_comstruct(){

	char *err = 0;
	int ret = 0;

	vector<pair<string,string> > seasons = get_seasons();

	cout << "Список смен:\n";
	for(int i=0; i<(int)seasons.size(); ++i)
		cout << i+1 << ". " << seasons[i].second << endl;

	cout << "Выберите смену (или 0, чтобы прервать добавление): ";
	int n;
	cin >> n;
	n--;
	if(n<0 || n>= seasons.size()) return ;

	cout << "Введите имя файла: ";
	char str[101];
	cin >> str;

	ifstream in(str);
	number_command = 0;
	load_res.clear();
	int len = 0;
	for(; in; ){
		in.getline(str, 100);
		if(!in) break;
		if(str[0] >= '0' && str[0] <= '9'){
			sscanf(str, "%d", &number_command);
			continue ;
		}
		len++;

		char query[1001];
		sprintf(query, "SELECT rowid FROM Instructors WHERE Name LIKE \'%s\'", str);
		ret = sqlite3_exec(db, query, add_res, 0, &err);

		if(len != load_res.size()){
			cout << "Не найден инструктор " << str << endl;
			return ;
		}
	}

	for(int i=0; i<(int)load_res.size(); ++i){

		char query[1001];
		sprintf(query, "INSERT INTO CommandStructure VALUES (\'%s\', %d, \'%s\')", seasons[n].first.c_str(), load_res[i].first, load_res[i].second.c_str());

		ret = sqlite3_exec(db, query, 0, 0, &err);
		if(ret != SQLITE_OK){
			cout << "Ошибка при добавлении в таблицу CommandStructure: " << err << endl;
			sqlite3_free(err);
			return ;
		}
	}

}

vector<pair<string,pair<string,string> > > vect_comstruct;
int del_comstruct(void *not_used, int n, char **arg, char **nu){

	string id(arg[0]);
	string nc(arg[1]);
	string nm(arg[2]);

	vect_comstruct.push_back(make_pair(id, make_pair(nc, nm)));

	return 0;
}

void menu_del_comstruct(){

	char *err = 0;
	int ret = 0;

	vector<pair<string,string> > seasons = get_seasons();

	cout << "Список смен:\n";
	for(int i=0; i<(int)seasons.size(); ++i)
		cout << i+1 << ". " << seasons[i].second << endl;

	cout << "Выберите смену (или 0, чтобы прервать удаление): ";
	int n;
	cin >> n;
	n--;
	if(n<0 || n>= seasons.size()) return ;

	vect_comstruct.clear();
	char query[1001];
	sprintf(query, "SELECT CommandStructure.rowid, CommandStructure.Number, Instructors.Name FROM CommandStructure, Instructors WHERE Season LIKE \'%s\' AND CommandStructure.Instructor LIKE Instructors.rowid", seasons[n].first.c_str());
	ret = sqlite3_exec(db, query, del_comstruct, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы CommandStructure: " << err << endl;
		sqlite3_free(err);
		return ;
	}

	cout << "Список экипажей и их инструкторов: \n";
	for(int i=0; i<(int)vect_comstruct.size(); ++i)
		cout << i+1 << ". " << vect_comstruct[i].second.second << " (" << vect_comstruct[i].second.first << " экипаж)\n";

	cout << "Выберите лишнюю запись (или 0, чтобы прервать удаление): ";
	cin >> n;
	n--;
	if(n<0 || n >= vect_comstruct.size()) return ;

	sprintf(query, "DELETE FROM CommandStructure WHERE rowid LIKE \"%s\"", vect_comstruct[n].first.c_str());
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы CommandStructure: " << err << endl;
		sqlite3_free(err);
		return ;
	}
}

int cnt;
int print_comstruct(void *not_used, int n, char **arg, char **nu){
	int num;
	sscanf(arg[0], "%d", &num);
	if(num != cnt){
		printf("========");
		printf("==============================");
		printf("===\n");
	}
	printf("|| ");
	if(num != cnt) printf("%d", num); else printf(" ");
	printf(" || ");
	print_string(arg[1], 30);
	printf(" ||\n");

	cnt = num;

	return 0;
}

void menu_print_comstruct(){

	char *err = 0;
	int ret = 0;

	vector<pair<string,string> > seasons = get_seasons();

	cout << "Список смен:\n";
	for(int i=0; i<(int)seasons.size(); ++i)
		cout << i+1 << ". " << seasons[i].second << endl;

	cout << "Выберите смену (или 0, чтобы прервать операцию): ";
	int n;
	cin >> n;
	n--;
	if(n<0 || n>= seasons.size()) return ;

	cnt = 0;

	printf("|| Э || ");
	print_string("Инструктор", 30);
	printf(" ||\n");

	char query[1001];
	sprintf(query, "SELECT CommandStructure.Number, Instructors.Name FROM CommandStructure, Instructors WHERE CommandStructure.Season LIKE \'%s\' AND Instructors.rowid LIKE CommandStructure.Instructor ORDER BY Number", seasons[n].first.c_str());
	ret = sqlite3_exec(db, query, print_comstruct, 0, &err);

	printf("========");
	printf("==============================");
	printf("===\n");

	if(ret != SQLITE_OK){
		cout << "Ошибка при выводе таблицы CommandStructure: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

