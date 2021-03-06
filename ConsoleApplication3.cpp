// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#define MENU "1 - catalog\n2 - exit"
using namespace std;

class car {
public:
	string model = "Solaris";        //1
	int year = 2018;	        	 //2
	string color = "red";	 //3
	float engine_v = 1.6f;			 //4
	bool AKPP = false;				 //5
	float power = 120.5f;			 //6
	float fuel = 60;				 //7
	float fuel_to_km = 6.7f;		 //8
	bool gabarites = true;			 //9
	bool SW_heating;				 //10
	bool ABS = true;				 //11
	bool EDS;						 //12
	bool navigation;				 //13
	bool computer;					 //14
	bool seat_heating;				 //15
	bool roof_container;			 //16
	int airbag_count = 2;			 //17

	car() {}

	void PrintToScreen()
	{
		cout << model << endl
			<< "year " << year << endl
			<< "color " << color << endl
			<< "engine size " << engine_v << endl
			<< "AKPP " << AKPP << endl
			<< "power " << power << endl
			<< "fuel value " << fuel << endl
			<< "fuel to km " << fuel_to_km << endl
			<< "gabarites " << gabarites << endl
			<< "steering wheel heating " << SW_heating << endl
			<< "ABS " << ABS << endl
			<< "EDS " << EDS << endl
			<< "navigation " << navigation << endl
			<< "computer " << computer << endl
			<< "seat heating " << seat_heating << endl
			<< "roof container " << roof_container << endl
			<< "airbag count " << airbag_count << endl << endl;
	}

	void PrintShort()
	{
		cout << model << " " << engine_v << " " << power << " " << color << " " << year << endl;
	}

	bool Compare(car car2)
	{
		return model == car2.model
			&& year == car2.year
			&& color == car2.color
			&& engine_v == car2.engine_v
			&& AKPP == car2.AKPP
			&& power == car2.power
			&& fuel == car2.fuel
			&& fuel_to_km == car2.fuel_to_km
			&& SW_heating == car2.SW_heating
			&& gabarites == car2.gabarites
			&& SW_heating == car2.SW_heating
			&& ABS == car2.ABS
			&& EDS == car2.EDS
			&& navigation == car2.navigation
			&& computer == car2.computer
			&& seat_heating == car2.seat_heating
			&& roof_container == car2.roof_container
			&& airbag_count == car2.airbag_count;
	}

	~car() {}
};

class CarHandler {
protected:
	CarHandler * successor;

public:
	CarHandler() {}
	CarHandler(CarHandler *successor) : successor(successor) { }

	virtual void carRequest(const car& request) {
		successor->carRequest(request);
	}
protected:
	vector<car> loadFromFile(const string filename)
	{
		vector<car> cars = vector<car>();
		ifstream f;
		f.open(filename);
		int carCount;
		f >> carCount;
		for (int i = 0; i < carCount; i++)
		{
			int paramCount;
			f >> paramCount;
			car c = car();

			for (int j = 0; j < paramCount; j++)
			{
				int paramInd;
				f >> paramInd;
				switch (paramInd)
				{
				case 1:
					f >> c.model;
					break;

				case 2:
					f >> c.year;
					break;

				case 3:
					f >> c.color;
					break;

				case 4:
					f >> c.engine_v;
					break;

				case 5:
					f >> c.AKPP;
					break;

				case 6:
					f >> c.power;
					break;

				case 7:
					f >> c.fuel;
					break;

				case 8:
					f >> c.fuel_to_km;
					break;

				case 9:
					f >> c.gabarites;
					break;

				case 10:
					f >> c.SW_heating;
					break;

				case 11:
					f >> c.ABS;
					break;

				case 12:
					f >> c.EDS;
					break;

				case 13:
					f >> c.navigation;
					break;

				case 14:
					f >> c.computer;
					break;

				case 15:
					f >> c.seat_heating;
					break;

				case 16:
					f >> c.roof_container;
					break;

				case 17:
					f >> c.airbag_count;
					break;

				default:
					break;
				}
			}
			cars.push_back(c);
		}
		return cars;
	}
};

class Salon : public CarHandler
{
protected:
	CarHandler * nHandler;
	vector<car> cars = vector<car>();

public:
	Salon(CarHandler* nHandler) : nHandler(nHandler) {
		this->nHandler = nHandler;
		cars = loadFromFile("salon.txt");
	};

	virtual void carRequest(const car& request)
	{
		for (car c : cars)
			if (c.Compare(request))
			{
				cout << "Car found in salon" << endl;
				cout << "\n";
				c.PrintToScreen();
				return;
			}

		cout << "car not found in salon, asking dealer" << endl;
		nHandler->carRequest(request);
	}

	vector<car> getCars()
	{
		return cars;
	}

	~Salon() {};
};

class Dealer : public CarHandler
{
protected:
	CarHandler * nHandler;
	vector<car> cars = vector<car>();

public:
	Dealer(CarHandler* nHandler) : nHandler(nHandler) {
		this->nHandler = nHandler;
		cars = loadFromFile("dealer.txt");
	};

	virtual void carRequest(const car& request)
	{
		for (car c : cars)
			if (c.Compare(request))
			{
				cout << "Car found in dealer" << endl;
				cout << "\n";
				c.PrintToScreen();
				return;
			}

		cout << "car not found in dealer, asking factory" << endl;
		nHandler->carRequest(request);
	}

	vector<car> getCars()
	{
		return cars;
	}

	~Dealer() {};
};

class Factory : public CarHandler
{
protected:
	CarHandler * nHandler;
	vector<car> cars = vector<car>();

public:
	Factory() {
		cars = loadFromFile("manufacture.txt");
	};

	Factory(CarHandler* nHandler) : nHandler(nHandler) {
		this->nHandler = nHandler;
	};

	virtual void carRequest(const car& request)
	{
		for (car c : cars)
			if (c.Compare(request))
			{
				cout << "Car found in factory" << endl;
				cout << "\n";
				c.PrintToScreen();
				return;
			}

		cout << "car not found at factory. Requesting make it" << endl;
		cout << "\n";
	}

	vector<car> getCars()
	{
		return cars;
	}

	~Factory() {};
};

int main()
{
	Factory *factory = new Factory();
	Dealer *dealer = new Dealer(factory);
	Salon *salon = new Salon(dealer);
	char ch;
	int chosen_car,a;
	vector<car> cars = vector<car>();
	for (car c : factory->getCars())
		cars.push_back(c);
	for (car c : dealer->getCars())
		cars.push_back(c);
	for (car c : salon->getCars())
		cars.push_back(c);
	do {
		cout << MENU << endl;
		cin >> ch;
		switch (ch) {
		case '1':	cout << "Catalog" << endl;
			for (int i = 0; i < cars.size(); i++)
			{
				cout << i << " ";
				cars.at(i).PrintShort();
			}
			do {
				cout << "Choose a car" << endl;
				a = cars.size();
				cin >> chosen_car;
			} while (chosen_car >= a);
			system("cls");
			salon->carRequest(cars.at(chosen_car));
			system("pause");
			system("cls");
			break;
		}
	} while (ch != '2');
	return 0;
}