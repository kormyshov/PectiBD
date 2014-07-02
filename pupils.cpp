#include "header.h"

using namespace std;

int psp;
int print_similary_pupil(void *not_used, int cnt, char **arg, char **nu){

	printf("%d. %s %s %s\n", psp, arg[0], arg[1], arg[2]);

	return 0;
}

int name_id;
int search_enter_name(void *not_used, int cnt, char **arg, char **nu){

	sscanf(arg[0], "%d", &name_id);

	return 0;
}
int enter_name(){

	cout << "Введите имя (например Иван): ";
	char name[101];
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;
	char query[1001];

	name_id = -1;
	sprintf(query, "SELECT rowid FROM Names WHERE Name LIKE \'%s\'", name);
	ret = sqlite3_exec(db, query, search_enter_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Names: " << err << endl;
		sqlite3_free(err);
	}
	if(name_id != -1) return name_id;

	cout << "Такого имени не найдено, его необходимо добавить...\n\n";
	menu_add_name();

	return enter_name();
}

int get_name_id(char name[]){

	//cout << "Имя: " << name << endl;

	char *err = 0;
	int ret = 0;
	char query[1001];

	name_id = -1;
	sprintf(query, "SELECT rowid FROM Names WHERE Name LIKE \'%s\'", name);
	ret = sqlite3_exec(db, query, search_enter_name, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Names: " << err << endl;
		sqlite3_free(err);
	}
	if(name_id != -1) return name_id;

	cout << "Имени " << name << " не найдено, его необходимо добавить...\n\n";
	menu_add_name();

	return get_name_id(name);
}

int midname_id;
int search_enter_midname(void *not_used, int cnt, char **arg, char **nu){

	sscanf(arg[0], "%d", &midname_id);

	return 0;
}
int enter_middle_name(){

	cout << "Введите отчество (например Иванович): ";
	char midname[101];
	cin.getline(midname, 100);

	char *err = 0;
	int ret = 0;
	char query[1001];

	midname_id = -1;
	sprintf(query, "SELECT rowid FROM MiddleNames WHERE Name LIKE \'%s\'", midname);
	ret = sqlite3_exec(db, query, search_enter_midname, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
	}
	if(midname_id != -1) return midname_id;

	cout << "Такого отчества не найдено, его необходимо добавить...\n\n";
	menu_add_midname();

	return enter_middle_name();
}

int get_middle_name_id(char midname[]){

	char *err = 0;
	int ret = 0;
	char query[1001];

	midname_id = -1;
	sprintf(query, "SELECT rowid FROM MiddleNames WHERE Name LIKE \'%s\'", midname);
	ret = sqlite3_exec(db, query, search_enter_midname, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы MiddleNames: " << err << endl;
		sqlite3_free(err);
	}
	if(midname_id != -1) return midname_id;

	cout << "Отчества " << midname << " не найдено, его необходимо добавить...\n\n";
	menu_add_midname();

	return get_middle_name_id(midname);
}

int school_id;
int search_enter_school(void *not_used, int cnt, char **arg, char **nu){

	sscanf(arg[0], "%d", &school_id);

	return 0;
}
int enter_school(){

	cout << "Введите название школы (например Гимназия № 11 г. Красноярска или Шуваевская СОШ): ";
	char name[101];
	cin.getline(name, 100);
	cin.getline(name, 100);

	char *err = 0;
	int ret = 0;
	char query[1001];

	school_id = -1;
	sprintf(query, "SELECT rowid FROM Schools WHERE Name LIKE \'%s\'", name);
	ret = sqlite3_exec(db, query, search_enter_school, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Schools: " << err << endl;
		sqlite3_free(err);
	}
	if(school_id != -1) return school_id;

	cout << "Такой школы не найдено, её необходимо добавить...\n\n";
	menu_add_school();

	return enter_school();
}

int get_school_id(char name[]){

	char *err = 0;
	int ret = 0;
	char query[1001];

	school_id = -1;
	sprintf(query, "SELECT rowid FROM Schools WHERE Name LIKE \'%s\'", name);
	ret = sqlite3_exec(db, query, search_enter_school, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Schools: " << err << endl;
		sqlite3_free(err);
	}
	if(school_id != -1) return school_id;

	cout << "Школы " << name << " не найдено, её необходимо добавить...\n\n";
	menu_add_school();

	return get_school_id(name);
}

void menu_add_pupil(){

	cout << "Введите фамилию (например Иванов): ";
	char surname[101];
	cin.getline(surname, 100);
	cin.getline(surname, 100);

	char *err = 0;
	int ret = 0;
	char query[1001];

	vector<pair<string, string> > snm = get_surnames();

	bool f = false;
	psp = 0;
	for(int i=0; i<(int)snm.size(); ++i){
		if(is_similary_surname(surname, snm[i].second.c_str())){
			if(!f){
				cout << "\nВозможно Вы имели ввиду одного из этих курсантов:\n";
				f = true;
			}
			psp++;
			sprintf(query, "SELECT Pupils.Surname, Names.Name, MiddleNames.Name FROM Pupils, Names, MiddleNames WHERE Pupils.NameID LIKE Names.rowid AND Pupils.SecondNameID LIKE MiddleNames.rowid AND Pupils.rowid LIKE \'%s\'", snm[i].first.c_str());
			ret = sqlite3_exec(db, query, print_similary_pupil, 0, &err);
			if(ret != SQLITE_OK){
				cout << "Ошибка при считывании из таблиц Pupils, Names, MiddleNames: " << err << endl;
				sqlite3_free(err);
			}
		}
	}
	char dat_surname[101];
	if(f){
		cout << "Прервать добавление нового курсанта? (y/n): ";
		char c;
		cin >> c;
		if(c == 'y') return ;
		cin.getline(dat_surname, 100);
	}

	cout << "Введите фамилию в дательном падеже (например Иванову): ";
	cin.getline(dat_surname, 100);

	int nm = enter_name();
	int mnm = enter_middle_name();

	char bdate[21];
	cout << "Введите дату рождения (например 28.02.1993): ";
	cin.getline(bdate, 20);

	char sex[9];
	cout << "Введите пол (м/ж): ";
	cin >> sex;

	int sch = enter_school();

	int cl;
	cout << "Введите класс (например 10): ";
	cin >> cl;

	sprintf(query, "INSERT INTO Pupils VALUES (\'%s\', %d, %d, %d, %d, \'%s\', \'%s\', \'%s\')", surname, nm, mnm, sch, cl, sex, bdate, dat_surname);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Pupils: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

void menu_load_pupil(){

	cout << "Введите имя файла: ";
	char str[101];
	cin >> str;

	ifstream in(str);

	while(in){
		char surname[101], dat_surname[101], name[101], midname[101], bdate[21], sex[9], school[101], cl[9];
		in.getline(surname, 100);
		if(!in) break;
		in.getline(dat_surname, 100);
		if(!in) break;
		in.getline(name, 100);
		if(!in) break;
		in.getline(midname, 100);
		if(!in) break;
		in.getline(bdate, 20);
		if(!in) break;
		in.getline(sex, 8);
		if(!in) break;
		in.getline(school, 100);
		if(!in) break;
		in.getline(cl, 8);
		//cout << surname << " " << name << " " << midname << " " << school << " " << cl << " " << bdate << " " << sex << " " << dat_surname << endl;
		int icl;
		sscanf(cl, "%d", &icl);

		add_pupil(surname, dat_surname, name, midname, bdate, sex, school, icl);
	}
}

int flag_exist_pupil;
int flag_add_pupil(void *not_used, int cnt, char **arg, char **nu){

	flag_exist_pupil = true;

	return 0;
}

void add_pupil(char surname[], char dat_surname[], char name[], char midname[], char bdate[], char sex[], char school[], int cl){

	//cout << surname << " " << name << " " << midname << " " << school << " " << cl << " " << bdate << " " << sex << " " << dat_surname << endl;

	int nm  = get_name_id(name);
	int mnm = get_middle_name_id(midname);
	int sch = get_school_id(school);

	char *err = 0;
	int ret = 0;
	char query[1001];

	flag_exist_pupil = false;
	sprintf(query, "SELECT rowid FROM Pupils WHERE Surname LIKE \'%s\' AND NameID LIKE \'%d\' AND SecondNameID LIKE \'%d\'", surname, nm, mnm);
	ret = sqlite3_exec(db, query, flag_add_pupil, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Pupils: " << err << endl;
		sqlite3_free(err);
	}

	if(flag_exist_pupil) return ;

	sprintf(query, "INSERT INTO Pupils VALUES (\'%s\', %d, %d, %d, %d, \'%s\', \'%s\', \'%s\')", surname, nm, mnm, sch, cl, sex, bdate, dat_surname);

	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при добавлении в таблицу Pupils: " << err << endl;
		sqlite3_free(err);
		return ;
	}

}

bool is_similary_surname(const char *s1, const char *s2){

	return (DMdistance(s1, s2) < 5);
}

vector<pair<string,string> > surnames;
int add_surname(void *not_used, int cnt, char **arg, char **nu){
	string id(arg[0]);
	string nm(arg[1]);
	surnames.push_back(make_pair(id, nm));

	return 0;
}

vector<pair<string,string> > get_surnames(){

	char *err = 0;
	int ret = 0;

	surnames.clear();

	ret = sqlite3_exec(db, "SELECT rowid, Surname FROM Pupils", add_surname, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при считывании из таблицы Pupils: " << err << endl;
		sqlite3_free(err);
	}

	return surnames;
}
