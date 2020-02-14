#include <iostream>
#include <numeric>
#include <time.h>

using namespace std;

int Sum(int array[], int n)
{
	int sum = 0;
	return accumulate(array, array + n, sum);
}

struct Csempek
{
	char elemek[5] = { 'A', 'B', 'C', 'D', 'E' };
	int elemek_count = 5;
};
struct Korong
{
	char elemek[4] = { '-', '-', '-', '-' };
	int elemek_count = 4;
};
struct Kozos
{
	int elemek[6] = { 0, 0, 0, 0, 0, 0 };
	int elemek_count = 6;
	bool jelzo = false; //ez lehet kell még
};

struct Player
{
	char fal[5][5];
	int fal_count = 5;
	char padlovonal[7];
	int padlovonal_count = 7;
	char mintasorok[5][5];
	int mintasorok_count = 5;
	int pontszam = 0;
};

bool Empty_korong(Korong korong)
{
	for (int i = 0; i < korong.elemek_count; i++)
	{
		if (korong.elemek[i] != '-') return false;
	}
	return true;
}
bool Empty_kozos(Kozos kozos)
{
	for (int i = 0; i < kozos.elemek_count; i++)
	{
		if (kozos.elemek[i] != '-') return false;
	}
	return true;
}
bool Korong_contains(Korong korong, char c)
{
	for (int i = 0; i < korong.elemek_count; i++)
	{
		if (korong.elemek[i] == c) return true;
	}
	return false;
}
bool Kozos_contains(Kozos kozos, char c)
{
	for (int i = 0; i < kozos.elemek_count; i++)
	{
		if (kozos.elemek[i] == c) return true;
	}
	return false;
}
bool Helyes_csempe(Player player, char c, int sor)
{
	for (int i = 0; i < sor; i++)
	{
		if (player.mintasorok[sor][i] != '-' && player.mintasorok[sor][i] != c) return false;
	}
	for (int i = 0; i < player.fal_count; i++)
	{
		if (player.fal[sor][i] != '-' && player.fal[sor][i] != c) return false;
	}
	return true;
}
int Csempe_szamol(Korong korong, char c)
{
	int n = 0;
	for (int i = 0; i < korong.elemek_count; i++)
	{
		if (korong.elemek[i] == c) n++;
	}
	return n;
}
int Csempe_szamol(Kozos kozos, char c)
{
	int index = c - 16;
	return kozos.elemek[index];
}

Korong* Create_korongok(int jatekosszam)
{
	int korongszam = 5;

	switch (jatekosszam)
	{ //case 2 és default folosleges?
	case 2:
		korongszam = 5;
		break;
	case 3:
		korongszam = 7;
		break;
	case 4:
		korongszam = 9;
		break;
	default:
		korongszam = 5;
	}

	return new Korong[korongszam];
}

struct Game
{
	Korong* korongok;
	int korongok_count;
	Kozos kozos;
	int zsak[5] = { 20, 20, 20, 20, 20 };
	int zsak_count = 5;
	int doboz[5] = { 0, 0, 0, 0, 0 };
	int doboz_count = 5;

	Csempek csempek;

	Game(int jatekosszam)
	{
		korongok = Create_korongok(jatekosszam);

		switch (jatekosszam)
		{
		case 2:
			korongok_count = 5;
			break;
		case 3:
			korongok_count = 7;
			break;
		case 4:
			korongok_count = 9;
			break;
		default:
			korongok_count = 5;
			break;
		}
	}

	~Game() { delete[] korongok; }
};

void Draw_korongok(Game* game) //mutató, vagy Game?
{
	for (int i = 0; i < game->korongok_count; i++)
	{
		cout << i + 1 << ".\t\t";
		for (int j = 0; j < game->korongok->elemek_count; j++) //?
		{
			cout << game->korongok[i].elemek[j];
		}
		cout << "\n";
	}

	cout << "0. Kozos:\t";
	for (int i = 0; i < game->kozos.elemek_count; i++)
	{
		for (int j = 0; j < game->kozos.elemek[i]; j++)
		{
			switch (i)
			{
			case 0:
				cout << "A";
				break;
			case 1:
				cout << "B";
				break;
			case 2:
				cout << "C";
				break;
			case 3:
				cout << "D";
				break;
			case 4:
				cout << "E";
				break;
			case 5:
				cout << "X";
				break;
			}
		}
		//if (game->kozos.jelzo) cout << "X";
	}

}

char Huzas(Game* game)
{
	if (Sum(game->zsak, game->zsak_count) == 0)
	{
		for (int i = 0; i < game->zsak_count; i++)
		{
			game->zsak[i] = game->doboz[i];
			game->doboz[i] = 0;
		}
	}

	int num = rand() % Sum(game->zsak, game->zsak_count);
	int min = game->zsak[0];

	for (int i = 0; i < game->zsak_count; i++)
	{
		if (num < min)
		{
			game->zsak[i]--;
			return game->csempek.elemek[i];
		}
		else min += game->zsak[i];
	}
	return 'A'; //return path
}

void Elokeszit(Game* game)
{
	for (int i = 0; i < game->korongok_count; i++)
	{
		for (int j = 0; j < game->korongok->elemek_count; j++)
		{
			game->korongok[i].elemek[j] = Huzas(game);
		}
	}
	game->kozos.elemek[5] = 1;
	game->kozos.jelzo = true;
}

Player* Create_jatekosok(int jatekosszam)
{
	Player* players = new Player[jatekosszam];

	for (int i = 0; i < jatekosszam; i++)
	{
		//Fal feltöltése
		for (int j = 0; j < players->fal_count; j++)
		{
			for (int k = 0; k < players->fal_count; k++) players[i].fal[j][k] = '-';
		}

		//Padlóvonal feltöltése
		for (int j = 0; j < players->padlovonal_count; j++)
		{
			players[i].padlovonal[j] = '-';
		}

		//Mintasorok feltöltése
		for (int j = 0; j < players->mintasorok_count; j++)
		{
			for (int k = 0; k < players->mintasorok_count; k++) players[i].mintasorok[j][k] = '-';
		}

		//Kezdõpontszám
		players[i].pontszam = 0;
	}

	return players;
}

void Draw_player(Player player)
{
	cout << "\n";

	cout << "1 2 3 4 5     Pontok: " << player.pontszam << "\n";

	for (int i = 0; i < player.fal_count; i++)
	{
		for (int j = 0; j < player.fal_count; j++)
		{
			if (player.fal[i][j] == '-') cout << ". ";
			else cout << player.fal[i][j] << " ";
		}
		cout << " " << i + 1 << "  ";
		for (int j = 0; j < i + 1; j++)
		{
			if (player.mintasorok[i][j] == '-') cout << "-";
			else cout << player.mintasorok[i][j];
		}
		cout << "\n";
	}
	for (int i = 0; i < player.padlovonal_count; i++)
	{
		if (player.padlovonal[i] == '-') cout << " _ ";
		else cout << " " << player.padlovonal[i] << " ";
	}
	cout << "\n";
	cout << "-1 -1 -2 -2 -2 -3 -3";
}

void Csempevalaszto(Player* player, Game* game)
{
	int valasz_korong;
	char valasz_szin;
	int valasz_mintasor;
	bool ok;

	do
	{
		ok = true;
		cout << "Valassz korongot: ";
		cin >> valasz_korong;

		if (valasz_korong < 0 || valasz_korong > game->korongok_count) ok = false;
		else if (valasz_korong != 0 && Empty_korong(game->korongok[valasz_korong])) ok = false;
		else if (Empty_kozos(game->kozos)) ok = false;
	} while (!ok); //Helyes szám: vagy korong, vagy közös

	do
	{
		ok = true;
		cout << "Valassz szint: ";
		cin >> valasz_szin;

		valasz_szin = toupper(valasz_szin);
		if (valasz_szin < 'A' || valasz_szin > 'E') ok = false;
		else if (valasz_korong != 0 && !Korong_contains(game->korongok[valasz_korong], valasz_szin)) ok = false;
		else if (!Kozos_contains(game->kozos, valasz_szin)) ok = false;
	} while (!ok); //Helyes szám: A-B-C-D-E

	do
	{
		ok = true;
		cout << "Valassz mintasort: ";
		cin >> valasz_mintasor;

		if (valasz_mintasor < 0 || valasz_mintasor > player->mintasorok_count) ok = false;
		else if (valasz_mintasor != 0 && !Helyes_csempe(*player, valasz_szin, valasz_mintasor)) ok = false;
	} while (!ok); //Helyes szám: egy mintasor sorszáma



	// Csempeket megszamolni
	int csempe_c;
	bool kezdocsempe = false;
	if (valasz_korong == 0) csempe_c = Csempe_szamol(game->kozos, valasz_szin);
	else csempe_c = Csempe_szamol(game->korongok[valasz_korong], valasz_szin);

	// Korongrol/kozosbol elvenni a csempeket
	if (valasz_korong == 0) game->kozos.elemek[valasz_szin - 17] = 0;
	else {
		for (int i = 0; i < game->korongok[valasz_korong].elemek_count; i++) {
			if (game->korongok->elemek[i] == valasz_szin) game->csempek.elemek[i] = '-';
		}
	}

	// Kezdojatekos jelzo elvetele, padlovonalra kuldese (ha nincs teli)
	if (valasz_korong == 0 && game->kozos.elemek[5] >= 1) {
		game->kozos.elemek[5] = 0;
		kezdocsempe = true; //ez még jó lehet valamire
		for (int i = 0; i < player->padlovonal_count; i++) {
			if (player->padlovonal[i] == '-') player->padlovonal[i] = 'X';
		}
	}

	// Csempek a jatekos mintasorara
	for (int i = 0; i < valasz_mintasor; i++) {
		if (player->mintasorok[valasz_mintasor][i] == '-') {
			player->mintasorok[valasz_mintasor][i] = valasz_szin;
			csempe_c--;
		}
	}

	// Felesleges csempek a padlovonalra
	if (csempe_c > 0) {
		for (int i = 0; i < player->padlovonal_count; i++) {
			if (player->padlovonal[i] == '-') player->padlovonal[i] = valasz_szin;
			csempe_c--;
		}
	}

	// Maradek csempeket a dobozba eldobni
	if (csempe_c > 0) {
		game->doboz[valasz_szin - 17] += csempe_c;
	}
}

int main()
{
	srand(time(NULL));
	int jatekosszam;

	do
	{
		cout << "Jatekosok szama (2-4): ";
		cin >> jatekosszam;
	} while (jatekosszam < 2 || jatekosszam > 4);

	Game game(jatekosszam);
	Player player;

	Create_korongok(jatekosszam);
	Elokeszit(&game);
	Draw_korongok(&game);
	Player* players = Create_jatekosok(jatekosszam);
	Draw_player(players[0]);

	Csempevalaszto(&players[0], &game);
}