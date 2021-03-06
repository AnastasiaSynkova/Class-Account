// Task2_CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Сынкова Анастасия 91гр. задача 11
/*
Условие :
	Реализовать класс Account, который представляет банковский счет. В классе должны быть 4 поля: фамилия, номер счета, процент начисления, сумма в рублях.
	Операции : 
		1) сменить владельца
		2) снять сумму со счета
		3) положить деньги на счет
		4) начислить проценты
		5) перевести сумму в доллары/евро
*/
#include "pch.h"
#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Account
{
private:
	string FIO;
	int id;
	double percent;
	double sum;
public:
	Account()
	{
		FIO = "";
		id = 0;
		percent = 0;
		sum = 0;
	}

	//инициализация (открытие счета)
	void Init(string Fam, int AccId, double Percent, double Sum)
	{
		FIO = Fam;
		id = AccId;
		id = AccId;
		percent = Percent;
		sum = Sum;
	}

	//сменить владельца счета
	void ReplaceName(string Fam)
	{
		FIO = Fam;
	}

	//снять деньги со счета
	void GetMoney(double theSum)
	{
		if (theSum <= sum)
			sum -= theSum;
		else
			cout << "Попытка снять со счета сумму, превышающую размер счета" << endl;
	}

	//положить деньги на счет
	void Put(double theSum)
	{
		sum += theSum;
	}

	//начислить проценты
	void Credit()
	{
		sum += percent / 100.0 * sum;
	}

	//перевести сумму в доллары\евро по курсу
	double MoveIn(double curs)
	{
		return sum / curs;
	}

	//вывести на экран данные счета
	void Display()
	{
		cout << endl << "Фамилия владельца: " << FIO << endl << "Номер счета: " << id << endl << "Процентная ставка: " << percent << "%" << endl << "Сумма на счете: " << fixed << setprecision(5) << sum << endl;
	}

	//ввод числа с заданными границами
	double InputMin(const char *txt, double min)
	{
		double num;
		cout << txt << endl;
		cin >> num;
		while (num < min)
		{
			cout << "Недопустимое значение, введите еще раз:" << endl;
			cin >> num;
		}
		return num;
	}

	int InputNumber(string str, int min)
	{
		int num;
		cout << str << endl;
		cin >> num;
		while (num < min)
		{
			cout << "Недопустимое значение, введите еще раз:" << endl;
			cin >> num;
		}
		return num;
	}

	//считать данные счета с клавиатуры
	void ReadKey(char str[], int &Accid, double &Accpercent, double &Accsum)
	{
		cout << "Введите фамилию владельца" << endl;
		cin >> str;
		Accid = InputNumber("Введите номер счета", 1);
		Accpercent = InputMin("Введите процентную ставку", 0.0);
		Accsum = InputMin("Введите сумму счета", 0.0);
	}

	friend bool operator == (const Account &s1, const Account &s2)
	{
		const double eps = 0.1e-10;
		if ((s1.FIO == s2.FIO) && (s1.id == s2.id) && (abs(s1.percent - s2.percent)<eps) && (abs(s1.sum - s2.sum)<eps))
			return true;
		return false;
	}

	friend bool operator < (const Account &s1, const Account &s2)
	{
		if (s1.sum > s2.sum)
			return true;
		return false;
	}

	friend bool operator > (const Account &s1, const Account &s2)
	{
		if (s1.sum < s2.sum)
			return true;
		return false;
	}
};

//ввод числа с заданными границами
int InputNum(const char *txt, int min, int max)
{
	int num;
	cout << txt << endl; //вывод вопроса на экран
	cin >> num;
	while ((num < min) || (num > max)) //пока число num не попадает в диапозон [min..max] 
	{
		cout << "Недопустимое значение, введите еще раз:" << endl;
		cin >> num;
	}
	return num;
}

//выбор пункта меню
int SelectInputMenuItem(void)
{
	cout << "1 - Открыть счет" << endl;
	cout << "2 - Вывести данные счета" << endl;
	cout << "3 - Изменить владельца" << endl;
	cout << "4 - Снять сумму со счета" << endl;
	cout << "5 - Положить деньги на счет" << endl;
	cout << "6 - Перевести сумму в доллары/евро" << endl;
	cout << "7 - Начислить проценты" << endl;
	cout << "8 - Сравнить два счета" << endl;
	return InputNum("0 - выход", 0, 8);
}

int main()
{
	setlocale(LC_ALL, "Russian"); //русский язык	
	Account acc;
	const double dol = 65.67;
	const double evr = 74.94;
	char str[20];
	int Accid;
	double Accpercent;
	double Accsum;
	int n;
	
	int MenuItem = -1;
	while (MenuItem != 0)
	{
		MenuItem = SelectInputMenuItem();
		
			switch (MenuItem)
			{
			case 1:
				acc.ReadKey(str, Accid, Accpercent, Accsum);
				acc.Init(str, Accid, Accpercent, Accsum);
				break;
			case 2:
				acc.Display();
				break;
			case 3:
				cout << "Введите имя нового владельца" << endl;
				cin >> str;
				acc.ReplaceName(str);
				break;
			case 4:
				Accsum = acc.InputMin("Введите сумму, которую вы хотите снять", 0);
				acc.GetMoney(Accsum);
				break;
			case 5:
				Accsum = acc.InputMin("Введите сумму, которую вы хотите положить", 0);
				acc.Put(Accsum);
				break;
			case 6:
				n = InputNum("Если вы хотите перевести в доллары - нажмите 1, если в евро - нажмите 2", 1, 2);
				switch (n)
				{
				case 1:
					cout << "Сумма счета в долларах = " << acc.MoveIn(dol) << endl;
					break;
				case 2:
					cout << "Сумма счета в рублях = " << acc.MoveIn(evr) << endl;
					break;
				}
				break;
			case 7:
				acc.Credit();
				acc.Display();
				break;
			case 8:
			{
				Account acc2;
				acc2.ReadKey(str, Accid, Accpercent, Accsum);
				acc2.Init(str, Accid, Accpercent, Accsum);
				if (acc == acc2)
					cout << "Счета совпадают" << endl;
				else
					cout << "Счета не совпадают" << endl;
				break;
			}
			default:
				return 0;
			}
	}
	return 0;
}