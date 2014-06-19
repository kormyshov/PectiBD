#include "header.h"

using namespace std;

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

	bool f = false;
	for(int i=0; i<(int)school_names.size(); ++i){
		if(is_similary_school(name, school_names[i].c_str())){
			if(!f){
				cout << "\nВозможно Вы имели ввиду одну из этих школ:\n";
				f = true;
			}
			cout << school_names[i] << endl;
		}
	}
	char gen_name[101];
	if(f){
		cout << "Прервать добавление новой школы? (y/n): ";
		char c;
		cin >> c;
		if(c == 'y') return ;
		cin.getline(gen_name, 100);
	}

	cout << "Введите название школы в родительном падеже (например Гимназии №11 г. Красноярска или Шуваевской СОШ): ";
	cin.getline(gen_name, 100);

	char query[1001];
	sprintf(query, "INSERT INTO Schools VALUES (\'%s\', \'%s\')", name, gen_name);

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
	sprintf(query, "DELETE FROM Schools WHERE Name LIKE \'%s\'", similary_sch[c-1].c_str());
	ret = sqlite3_exec(db, query, 0, 0, &err);
	if(ret != SQLITE_OK){
		cout << "Ошибка при удалении из таблицы Schools: " << err << endl;
		sqlite3_free(err);
		return ;
	}
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

bool is_similary_school(const char *s1, const char *s2){

	//cout << s1 << "(" << strlen(s1) << ")" << " ~ " << s2 << "(" << strlen(s2) << ")" << " = " << DMdistance(s1, s2) << endl;
	return (DMdistance(s1, s2) < 10);
}

