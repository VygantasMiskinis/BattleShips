#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <string>
#include <windows.h>
#define bruksnys cout << "-----------------------" << endl
using namespace std;
class zaidejas

{
private:
	int orientacija;
	char y1, y2, x1, x2; // laivo statymui ir saudymui skirtos koordinates (saudant naudoju tik 1 koordinates)
	string vardas;
	char lentele[10][10];
	vector <pair<int, int>> jauNebeturi; // useless delete
	int laivynas[4];
	int HP;
	bool ignoreErrors;
	vector <pair<pair<int,int>, pair<int, int>>> laivuKoord;
public:
	zaidejas() :y1(0), y2(0), x1(0), x2(0), ignoreErrors(0), HP(0),orientacija(-1)

	{

		srand(time(0));
		laivuKoord.empty();

	}
	zaidejas(bool ig, string name) :y1(0), y2(0), x1(0), x2(0), HP(0), ignoreErrors(ig), vardas(name), orientacija(-1)

	{
		srand(time(0));
		laivuKoord.empty();

	}

	~zaidejas() {

		if (HP != 0) {
			cout << "Champion: " << vardas << endl;
			system("pause");
		}
	}

	bool arJauApsaudytas(int iks,int yg) // useless delete this
	{
		bool nenaudotas;
		nenaudotas = true;
		for (auto it : jauNebeturi)
			if (it.first == iks&&it.second == yg)
				nenaudotas = false;
		return nenaudotas;
	}
	void saudymoFaze()
	{
		if (ignoreErrors)
			ignoreErrors = false;
		else
			ignoreErrors = true;
	}
	void pradineLent() //kintamuju inicilizacija
	{ 
		laivynas[0] = 0;
		laivynas[1] = 0;
		laivynas[2] = 0;
		laivynas[3] = 0;
		for (int i = 0; i<4; i++)
			laivynas[i] = 0;
		for (int i = 0; i<10; i++)
			for (int j = 0; j < 10; j++)
			{
				lentele[i][j] = '.';
			}	
	
	}
	void irasymas() //laivu statymo ir saudymo koordinaciu irasymas
	{
		cout << "Enter ships coordinates [A-J] [0-9] [A-J] [0-9]" << endl;

		cin >> y1 >> x1 >> y2 >> x2;
	}
	void irasymasSaud()
	{
		cout << "Enter shot coordinates " << endl;
		cin >> y1 >> x1;
	}
	bool nepilnas()// ar visi laivai jau suevesti
	{
		if (laivynas[0] == 4 && laivynas[1] == 3 && laivynas[2] == 2 && laivynas[3] == 1) {
			return false;
		}
		return true;
	}
	bool netuscias()
	{
		if (HP == 0) return false;
		return true;
	}
	void Err(int code) // klaidingai suvesti duomenys
	{
		if (!ignoreErrors)
		{
			if (code == 1)
			{
				cout << "!!! All ships of this length have already been placed !!!" << endl;
				bruksnys;
			}
			if (code == 2)
			{
				cout << "!!! Ship is too long !!!" << endl;
				bruksnys;
			}
			if (code == 3)
			{
				cout << "!!! Coordinates entered incorectly !!!" << endl;
				bruksnys;
			}
			if (code == 4)
			{
				cout << "!!! Ships are too close to each other !!!" << endl;
				bruksnys;
			}
			if (code == 5)
			{
				cout << "!!! You already shot at this square !!!" << endl;

			}
			if (code == 6)
			{
				cout << " Shot at empty square " << endl;

			}
			if (code == 7)
			{
				cout << " You hit a ship " << endl;

			}
			if (code == 8)
			{
				cout << " You sunk a ship " << endl;

			}

		}
	}

	bool arLieciasi(int xt1, int yt1, int xt2, int yt2)
	{

		for (int i = xt1; i <= xt2; i++)
			for (int j = yt1; j <= yt2; j++)
			{
				if (i + 1<10)
				{
					if (lentele[i + 1][j] == 'o') { return true; }

					if (j + 1<10)
					{
						if (lentele[i + 1][j + 1] == 'o') { return true; }
						if (lentele[i][j + 1] == 'o')
						{
							return true;
						}

					}
					if (j - 1 >= 0)
					{
						if (lentele[i + 1][j - 1] == 'o') { return true; }
						if (lentele[i][j - 1] == 'o') { return true; }

					}
				}

				if (i - 1 >= 0)
				{
					if (lentele[i - 1][j] == 'o') { return true; }
					if (j + 1 < 10)
					{
						if (lentele[i - 1][j + 1] == 'o') { return true; }
						if (lentele[i][j + 1] == 'o') { return true; }
						
							
						
					}
					if (j - 1 >= 0)
					{
						if (lentele[i - 1][j - 1] == 'o') { return true; }
						if (lentele[i][j - 1] == 'o') { return true; }
					}



				}


			}
		return false;
	}
	void Laivai()//laivo ivedimas
	{

		double ilgis;



		y2 = tolower(y2);
		int Y2 = y2 - 97;
		y1 = tolower(y1);
		int Y1 = y1 - 97;
		int X1 = x1 - 48;
		int X2 = x2 - 48;
		if (X2<X1 || Y2<Y1) { swap(X1, X2); swap(Y1, Y2); }
		ilgis = sqrt(pow(X1 - X2, 2) + pow(Y1 - Y2, 2));
		if (X1 != X2&&Y1 != Y2) Err(3);

		else if (X1<0 || X2<0 || X1>9 || X2>9 || y1<97 || y2<97 || y1>106 || y2>106)
			Err(3);
		else if (ilgis>3) Err(2);

		else if (laivynas[int(ilgis)] >= 4 - ilgis)
			Err(1);
		else if (arLieciasi(X1, Y1, X2, Y2)) Err(4);

		else
		{

			for (int i = X1; i <= X2; i++)
				for (int j = Y1; j <= Y2; j++)
				{
					lentele[i][j] = 'o';
					HP++;


				}
			laivynas[int(ilgis)]++;
			laivuKoord.push_back(make_pair(make_pair (Y1,X1) , make_pair( Y2,X2) ));
		}
	}
	bool arNusove(int xt, int yt)

	{
		bool pasove = false;
		// surandame i kuri laiva ieina tada tikrinama ar tas laivas nusautas
		for (auto it : laivuKoord)
		{
			pasove = false;
			for (int i = it.first.second; i <= it.second.second; i++)
				for (int j = it.first.first; j <= it.second.first; j++)
				{
					if (i == xt&&j == yt)
					{
						pasove = true;
						break;
					}
				}
			if (pasove)
				for (int i = it.first.second; i <= it.second.second; i++)
					for (int j = it.first.first; j <= it.second.first; j++)
					{
						if (lentele[i][j] == 'o') return false;
						if (i == it.second.second&&j == it.second.first) return true;
					}
		}


		return false;
	}
	void susprogdinti(int xt, int yt)
	{
		bool susprogdintas = false;
		for (auto it : laivuKoord)
		{
			susprogdintas = false;
			
			for (int i = it.first.second; i <= it.second.second; i++)
				for (int j = it.first.first; j <= it.second.first; j++)
				{
					if (i == xt&&j == yt)
					{
						susprogdintas = true;
						break;
					}
				}
			    if(susprogdintas)
				for (int i = it.first.second; i <= it.second.second; i++)
					for (int j = it.first.first; j <= it.second.first; j++)
					{
					
					
						orientacija = -1;
						lentele[i][j] = 'X';
						
						
					if (i - 1 >= 0) lentele[i - 1][j] = 'X';
						if (i + 1 < 10) lentele[i + 1][j] = 'X';
						if (j - 1 >= 0) lentele[i][j-1] = 'X';
						if (j + 1 < 10) lentele[i][j+1] = 'X';
						if (i - 1 >= 0 && j - 1 >= 0) lentele[i - 1][j - 1] = 'X';
						if (i - 1 >= 0 && j + 1 < 10) lentele[i - 1][j + 1] = 'X';
						if (i + 1 < 10 && j + 1 < 10) lentele[i + 1][j + 1] = 'X';
						if (i + 1 < 10 && j - 1 >= 0) lentele[i + 1][j - 1] = 'X';
					

					
					}
			
		}
		jauNebeturi.clear();
		
	}
	bool Suvis()   // X-pasautas laivas o- tuscias/nepasautas laukelis #-pasautas tuscias laukas
	{
		y1 = tolower(y1);
		int Y1 = y1 - 97;
		int X1 = x1 - 48;


		if (X1 < 0 || X1>9 || y1 < 97 || y1>106) { Err(3); return true; }
		else
		{
			if (lentele[X1][Y1] == 'X' || lentele[X1][Y1] == '#' || lentele[X1][Y1]=='0')
			{
				Err(5);
				return true;
			}

			if (lentele[X1][Y1] == '.')
			{
				lentele[X1][Y1] = '#';
				Err(6);

			}
			else  if (lentele[X1][Y1] == 'o')
			{
				lentele[X1][Y1] = '0';
				HP--;
				

					if (arNusove(X1, Y1))
					{
						susprogdinti(X1,Y1);
						Err(8);
					}
					
					 	
					
				
				else Err(7);
				return true;
			}

		}
		return false;

	}
	void isvedimas()
	{
		bruksnys;
		cout << "  V " << vardas << " V  " <<"HP "<<HP<<endl;
		bruksnys;
		cout << "    ";
		for (char raid = 'A'; raid <= 'J'; raid++)
			cout << raid << " ";
		cout << endl;
		for (int i = 0; i<10; i++)
			for (int j = 0; j<10; j++)
			{
				if (j == 0)
				{
					cout << i;

					cout << " | ";

				}

				cout << lentele[i][j];
				cout << " ";
				if (j == 9) cout << endl;

			}
	}
	void nepilnasIsvedimas()
	{
		bruksnys;
		cout << "  V " << vardas << " V  " << "HP " << HP << endl;
		bruksnys;
		cout << "    ";
		for (char raid = 'A'; raid <= 'J'; raid++)
			cout << raid << " ";
		cout << endl;
		for (int i = 0; i<10; i++)
			for (int j = 0; j<10; j++)
			{
				if (j == 0)
				{
					cout << i;

					cout << " | ";

				}

				if(lentele[i][j]=='X'|| lentele[i][j]=='0'|| lentele[i][j]=='#')
					cout<< lentele[i][j];
				else cout << '.';
				cout << " ";
				if (j == 9) cout << endl;

			}
	}
	void generatorius()
	{
		int ilg(0);
		for (int i = 3; i>=0; i--)
		{
			if (laivynas[i]<4 - i) { ilg = i; i = -1; }
		}

		int temp;
		temp = rand() % 10;
		y1 = temp + 97;
		temp = rand() % 10;
		x1 = temp + '0';
		temp = rand() % 4;

		switch (temp)
		{
		case (0):
			x2 = x1;
			y2 = y1 + ilg;

			break;
		case (1):
			x2 = x1 + ilg;
			y2 = y1;
			break;
		case (2):
			x2 = x1;
			y2 = y1 - ilg;
			break;
		case (3):

			x2 = x1 - ilg;
			y2 = y1;

			break;
		}
		cout << "";

	}
	void generatoriusSaud()
	{
		int iks, yg;
        int tempy,tempx;
		bool protingas = false;
		/* lenteleje iesko 0 jei randa daro protinga saudima (jei ne tiesiog saudo)
		protingas saudymas:
		tikrina aplink rasta 0 jei randa bet koki laukeli(nepasauta) sauna, kitu atveju pereina prie kito 0
		*/
		for(int i=0;i<10;i++)
			for (int j = 0; j < 10; j++)
			{
				
				
				if (lentele[i][j] == '0')
				{
					iks = i;
					yg = j;
					protingas = true;
					i = 10;
					break;
				}

				
			}

		if (protingas)
		{
			bool rado = false;




			if (lentele[iks][yg] == '0')
			{
				while (!rado)
				{
					int salis = -1;
					if (orientacija == -1) //0 virsun 1 iks desine 2 iks apacia 3 iks kaire
					{
						salis = rand() % 4;

						if (iks - 1 >= 0)
							if ((lentele[iks - 1][yg] == '.' || lentele[iks - 1][yg] == 'o') && salis == 0)
							{
								if (lentele[iks - 1][yg] == 'o') orientacija = 0;
								tempx = iks - 1;
								tempy = yg;
								rado = true;
							}
						if (yg + 1 < 10)
							if ((lentele[iks][yg + 1] == '.' || lentele[iks][yg + 1] == 'o') && salis == 1)
							{
								if (lentele[iks][yg + 1] == 'o') {
									orientacija = 1;
								}

								tempx = iks;
								tempy = yg + 1;
								rado = true;

							}
						if (iks + 1 < 10)
							if ((lentele[iks + 1][yg] == '.' || lentele[iks + 1][yg] == 'o') && salis == 2)
							{
								if (lentele[iks + 1][yg] == 'o') orientacija = 2;
								tempx = iks + 1;
								tempy = yg;
								rado = true;

							}
						if (yg - 1 >= 0)
							if ((lentele[iks][yg - 1] == '.' || lentele[iks][yg - 1] == 'o') && salis == 3)
							{
								if (lentele[iks][yg - 1] == 'o') {
									orientacija = 3;
								}

								tempx = iks;
								tempy = yg - 1;
								rado = true;

							}

					}
					
					if (!rado)
					{

						if (iks - 1 >= 0)
							if (lentele[iks - 1][yg] != '#' && orientacija == 0)
							{
								while (lentele[iks - 1][yg] == '0'&&lentele[iks - 1][yg] != '#'&&iks - 1 >= 0)
								{
									iks--;
								}

								if (lentele[iks - 1][yg] != '0'&&lentele[iks - 1][yg] != '#'&&iks - 1 >= 0)
								{
									tempx = iks - 1;
									tempy = yg;
									rado = true;
								}
							}
						if (yg + 1 < 10)
							if (lentele[iks][yg + 1] != '#' && orientacija == 1)
							{
								while (lentele[iks][yg + 1] == '0'&&lentele[iks][yg + 1] != '#' && yg + 1 < 10)yg++;
								if (lentele[iks][yg + 1] != '0'&&lentele[iks][yg + 1] != '#' && yg + 1 < 10)
								{
									tempx = iks;
									tempy = yg + 1;
									rado = true;
								}

							}
						if (iks + 1 < 10)
							if (lentele[iks + 1][yg] != '#' && orientacija == 2)
							{
								while (lentele[iks + 1][yg] == '0'&&lentele[iks + 1][yg] != '#' &&iks + 1 < 10)
								{
									iks++;
								}
								if (lentele[iks + 1][yg] != '0'&&lentele[iks + 1][yg] != '#' &&iks + 1 < 10)
								{
									tempx = iks + 1;
									tempy = yg;
									rado = true;
								}

							}
						if (yg - 1 >= 0)
							if (lentele[iks][yg - 1] != '#' && orientacija == 3)
							{
								while (lentele[iks][yg - 1] == '0'&&lentele[iks][yg - 1] != '#' && yg - 1 >= 0)yg--;
								if (lentele[iks][yg - 1] != '0'&&lentele[iks][yg - 1] != '#' && yg - 1 >= 0)
								{
									tempx = iks;
									tempy = yg - 1;
									rado = true;
								}


							}

						if (!rado&&orientacija!=-1)
						{
							if (orientacija >= 2) orientacija -= 2;
							else orientacija += 2;
						}

					}
				}

			}


		}
		else
		{
			tempy = rand() % 10;

			tempx = rand() % 10;
		}
		
          
			y1 = tempy + 97;
			
			x1 = tempx + '0';
		
	}
	


};


int main()
{
	
	
	zaidejas mano(false, "Player");
	zaidejas priesas(true, "AI");

	mano.pradineLent();
	priesas.pradineLent();
	
		while (mano.nepilnas()) //ivedimo faze
		{
			mano.isvedimas();
			bruksnys;
			mano.irasymas();
			system("cls");
			mano.Laivai();


		}

		


	while (priesas.nepilnas()) //ivedimo faze kompiuterio
	{

		priesas.generatorius();
		priesas.Laivai();

	}


	priesas.saudymoFaze();
	mano.saudymoFaze();
	while (mano.netuscias() && priesas.netuscias())
	{


		mano.isvedimas();
		priesas.nepilnasIsvedimas();
	
		
			priesas.irasymasSaud();

			system("cls");
			while (priesas.Suvis()&&priesas.netuscias()) // saudant i priesa kreipemes i prieso objekta
			{

				mano.isvedimas();
				priesas.nepilnasIsvedimas();

				priesas.irasymasSaud();
				system("cls");
				if (!priesas.netuscias()) break;


			}
	
		mano.generatoriusSaud();
		system("cls");

		while (mano.Suvis() && mano.netuscias()) // saudant i priesa kreipemes i prieso objekta 
		{

			mano.isvedimas();
			priesas.nepilnasIsvedimas();

			mano.generatoriusSaud();
			Sleep(1000);
			system("cls");
			if (!mano.netuscias()) break;


		}



		// struktura :
		// 1. isvedami laivynai
		// 2. sauna zaidejas 2.5 patikrinama ar laimejo
		// 3. sauna priesas 3.5 patikrinama ar priesas laimejo
		// clear screen

	}

	mano.isvedimas();
	priesas.isvedimas();
	


}

/*
vienas 4
du 3
trys 2
keturi 1
*/

/*
laivu koordinaciu talpinimas protingam kompiuteriui:
reikia talpinti kiekvieno laivo pradine ir galine kordinates
vector <--- pair <int, int> koord laivai

irasant irasome pradzios ir pabaigos koordinate kaip laiva
saudant:
pasovus zymime zenklu '0'
{
  po suvio tikrinama ar kazkurio laivo koordinates pilnai uzsipildytos '0' jei taip '0' pakeiciami X bei pasalinamas laivas is laivu saraso 


}

pilnai nusovus laiva zymime 'X'

*/