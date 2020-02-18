#include <iostream>
#include <numeric>
#include <time.h>
#include <cstdlib>

using namespace std;

// A - 65

int Sum(int* array, int n)
{
	return accumulate(array, array + n, 0);
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
	int elemek[6] = { 0 };
	int elemek_count = 6;
};
struct Player
{
	char fal[5][5];
	int fal_count = 5;
	char padlovonal[7] = { 0 };
	int padlovonal_count = 7;
	char mintasorok[5][5];
	int mintasorok_count = 5;
	int pontszam = 0;

	int id;
	float vegeredmeny;
};

// 11. feladat
int Teli_sorok(Player* player)
{
	int n = 0;
	bool teli = true;

	for (int i = 0; i < player->fal_count; i++)
	{
		teli = true;
		for (int j = 0; j < player->fal_count; j++)
		{
			if (player->fal[i][j] == '-')
			{
				teli = false;
				break;
			}
		}
		if (teli) n++;
	}
	return n;
}
int Teli_oszlopok(Player* player)
{
	int n = 0;
	bool teli = true;

	for (int i = 0; i < player->fal_count; i++)
	{
		teli = true;
		for (int j = 0; j < player->fal_count; j++)
		{
			if (player->fal[j][i] == '-')
			{
				teli = false;
				break;
			}
		}
		if (teli) n++;
	}
	return n;
}

// Segedfuggvenyek
void Player_csere(Player* player_a, Player* player_b)
{
	Player p = *player_a;
	*player_a = *player_b;
	*player_b = p;
}
void Buborek(Player* players, int jatekosszam)
{
	for (int i = 0; i < jatekosszam - 1; i++)
	{
		for (int j = 0; j < jatekosszam - i - 1; j++)
		{
			if (players[j].vegeredmeny > players[j + 1].vegeredmeny)
			{
				Player_csere(&players[j], &players[j + 1]);
			}
		}
	}
}
bool Empty_korong(Korong* korong)
{
	for (int i = 0; i < korong->elemek_count; i++)
	{
		if (korong->elemek[i] != '-') return false;
	}
	return true;
}
bool Empty_kozos(Kozos* kozos)
{
	for (int i = 0; i < kozos->elemek_count - 1; i++) //ha nincs -1, akkor nem lesz jo a szinvalasztas
	{
		if (kozos->elemek[i] != 0) return false;
	}
	return true;
}
bool Korong_contains(Korong* korong, char c)
{
	for (int i = 0; i < korong->elemek_count; i++)
	{
		if (korong->elemek[i] == c) return true;
	}
	return false;
}
bool Kozos_contains(Kozos* kozos, char c)
{
	if (kozos->elemek[c - 65] > 0) return true;
	return false;
}
bool Helyes_csempe(Player* player, char c, int sor)
{
	for (int i = 0; i <= sor; i++)
	{
		if (player->mintasorok[sor][i] != '-' && player->mintasorok[sor][i] != c) return false;
	}
	for (int i = 0; i < player->fal_count; i++)
	{
		if (player->fal[sor][i] == c) return false;
	}
	return true;
}
bool Mintasor_tele(Player* player, int sor)
{
	if (player->mintasorok[sor][sor] != '-') return true;
	return false;
}
int Csempe_szamol(Korong* korong, char c)
{
	int n = 0;
	for (int i = 0; i < korong->elemek_count; i++)
	{
		if (korong->elemek[i] == c) n++;
	}
	return n;
}
int Csempe_szamol(Kozos* kozos, char c)
{
	return kozos->elemek[c - 65];
}
int Pontozas(Player* player, int sor, int oszlop)
{
	int pont = 1;
	bool vizszintes = false, fuggologes = false;

	for (int i = oszlop + 1; i < player->fal_count; i++) { //jobb
		if (player->fal[sor][i] != '-') {
			pont++;
			vizszintes = true;
		}
		else break;
	}
	for (int i = oszlop - 1; i >= 0; i--) { //bal
		if (player->fal[sor][i] != '-') {
			pont++;
			vizszintes = true;
		}
		else break;
	}
	for (int i = sor + 1; i < player->fal_count; i++) { //le
		if (player->fal[i][oszlop] != '-') {
			pont++;
			fuggologes = true;
		}
		else break;
	}
	for (int i = sor - 1; i >= 0; i--) { //fel
		if (player->fal[i][oszlop] != '-') {
			pont++; 
			fuggologes = true;
		}
		else break;
	}

	if (vizszintes && fuggologes) pont++;
	return pont;
}
int Buntetopontok(Player* player)
{
	int bunteto = 0;

	for (int i = 0; i < player->padlovonal_count; i++)
	{
		if (player->padlovonal[i] != '-')
		{
			if (i == 0 || i == 1) bunteto += 1;
			else if (i > 1 && i < 5) bunteto += 2;
			else bunteto += 3;
			player->padlovonal[i] = '-';
		}
		else break;
	}
	return bunteto;
}
void Scoreboard(Player* players, int jatekosszam)
{
	cout << "\n\n";

	for (int i = 0; i < jatekosszam; i++)
	{
		players[i].vegeredmeny = players[i].pontszam + Teli_sorok(&players[i]) / 10.0f;
	}
	Buborek(players, jatekosszam);

	int jel_hely = 1;

	cout << "\n" << jel_hely << ". hely: " << players[jatekosszam - 1].id + 1 << ". jatekos - " << players[jatekosszam - 1].pontszam << " pont";
	for (int i = jatekosszam - 2; i >= 0; i--)
	{
		if (players[i].vegeredmeny != players[i + 1].vegeredmeny) jel_hely = jatekosszam - i;
		cout << "\n" << jel_hely << ". hely: " << players[i].id + 1 << ". jatekos - " << players[i].pontszam << " pont";
	}

	cout << "\n==============================\n";
}
void cinclear()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 2. feladat
Korong* Create_korongok(int jatekosszam)
{
	int korongszam = 5;

	switch (jatekosszam)
	{
	case 3:
		korongszam = 7;
		break;
	case 4:
		korongszam = 9;
		break;
	}

	Korong* temp = new Korong[korongszam];
	if (temp == nullptr) exit(EXIT_FAILURE);
	return temp;
}

// 3. feladat
struct Game
{
	Korong* korongok;
	int korongok_count;
	Kozos kozos;
	int zsak[5] = { 20, 20, 20, 20, 20 };
	int zsak_count = 5;
	int doboz[5] = { 0 };
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

// 4. feladat
void Draw_korongok(Game* game)
{
	cout << "\n";

	for (int i = 0; i < game->korongok_count; i++)
	{
		cout << i + 1 << ".\t\t";
		for (int j = 0; j < game->korongok[i].elemek_count; j++)
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
			if (i == 5) cout << "X";
			else cout << char(i + 65);
		}
	}
}

// 1|5. feladat
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
	return 'A';
}

// 6. feladat
void Elokeszit(Game* game)
{
	for (int i = 0; i < game->korongok_count; i++)
	{
		for (int j = 0; j < game->korongok[i].elemek_count; j++)
		{
			game->korongok[i].elemek[j] = Huzas(game);
		}
	}
	game->kozos.elemek[5] = 1;
}

// 7. feladat
Player* Create_jatekosok(int jatekosszam)
{
	Player* players = new Player[jatekosszam];
	if (players == nullptr) exit(EXIT_FAILURE);

	for (int i = 0; i < jatekosszam; i++)
	{
		players[i].id = i;

		//Fal feltöltése
		for (int j = 0; j < players->fal_count; j++)
		{
			for (int k = 0; k < players->fal_count; k++)
			{
				// DEBUG
				// if (j == 2) players[i].fal[j][k] = k + 65;
				// else players[i].fal[j][k] = '-';

				// LIVE
				players[i].fal[j][k] = '-';
			}
		}

		//Padlovonal feltoltese
		for (int j = 0; j < players->padlovonal_count; j++)
		{
			players[i].padlovonal[j] = '-';
		}

		//Mintasorok feltoltese
		for (int j = 0; j < players->mintasorok_count; j++)
		{
			for (int k = 0; k < players->mintasorok_count; k++) players[i].mintasorok[j][k] = '-';
		}

		//Kezdopontszam
		players[i].pontszam = 0;
	}

	return players;
}

// 8. feladat
void Draw_player(Player player)
{
	cout << "\n\n";

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
	cout << "-1 -1 -2 -2 -2 -3 -3\n\n";
}

// 9. feladat
void Csempevalaszto(Player* player, Game* game)
{
	int valasz_korong;
	char valasz_szin;
	int valasz_mintasor;
	bool ok;
	int csempe_c;

	do
	{
		ok = true;
		cout << "Valassz korongot: ";
		cin >> valasz_korong;
		if (cin.fail()) ok = false;
		cinclear();

		if (valasz_korong < 0 || valasz_korong > game->korongok_count) { ok = false; }
		else if (valasz_korong != 0 && Empty_korong(&game->korongok[valasz_korong - 1])) { ok = false; }
		else if (valasz_korong == 0 && Empty_kozos(&game->kozos)) { ok = false; }
	} while (!ok); // Helyes-e a korong, es van-e tartalma

	do
	{
		ok = true;
		cout << "Valassz szint: ";
		cin >> valasz_szin;
		cinclear();

		valasz_szin = toupper(valasz_szin);
		if (valasz_szin < 'A' || valasz_szin > 'E') { ok = false; }
		else if (valasz_korong != 0 && !Korong_contains(&game->korongok[valasz_korong - 1], valasz_szin)) { ok = false; }
		else if (valasz_korong == 0 && !Kozos_contains(&game->kozos, valasz_szin)) { ok = false; }
	} while (!ok); //Helyes-e a csempe szine, es tartalmazza-e a korong

	// Csempeket megszamolni
	if (valasz_korong == 0) csempe_c = Csempe_szamol(&game->kozos, valasz_szin);
	else csempe_c = Csempe_szamol(&game->korongok[valasz_korong - 1], valasz_szin);

	do
	{
		ok = true;
		cout << "Valassz mintasort(" << csempe_c << "): ";
		cin >> valasz_mintasor;
		if (cin.fail()) ok = false;
		cinclear();

		if (valasz_mintasor < 0 || valasz_mintasor > player->mintasorok_count) ok = false;
		else if (valasz_mintasor != 0 && !Helyes_csempe(player, valasz_szin, valasz_mintasor - 1)) ok = false;
		else if (valasz_mintasor != 0 && Mintasor_tele(player, valasz_mintasor - 1)) ok = false;
	} while (!ok); // Helyes-e a mintasor szama (es lehet-e oda rakni a valasztott csempebol)



	// Korongrol/kozosbol elvenni a csempeket
	if (valasz_korong == 0) game->kozos.elemek[valasz_szin - 65] = 0;
	else {
		for (int i = 0; i < game->korongok[valasz_korong - 1].elemek_count; i++) {
			if (game->korongok[valasz_korong - 1].elemek[i] != valasz_szin) game->kozos.elemek[game->korongok[valasz_korong - 1].elemek[i] - 65]++;
			game->korongok[valasz_korong - 1].elemek[i] = '-';
		}
	}

	// Kezdojatekos jelzo elvetele, padlovonalra kuldese (ha nincs teli)
	if (valasz_korong == 0 && game->kozos.elemek[5] >= 1) {
		game->kozos.elemek[5] = 0;
		for (int i = 0; i < player->padlovonal_count; i++) {
			if (player->padlovonal[i] == '-')
			{
				player->padlovonal[i] = 'X';
				break;
			}
		}
	}

	// Csempek a jatekos mintasorara
	if (valasz_mintasor != 0)
	{
		for (int i = 0; i < valasz_mintasor; i++) { //valasz_mintasor -> egyben az is, hogy hány csempe mehet a mintasorra összesen
			if (player->mintasorok[valasz_mintasor - 1][i] == '-' && csempe_c > 0) {
				player->mintasorok[valasz_mintasor - 1][i] = valasz_szin;
				csempe_c--;
			}
		}
	}
	else //Csempek a jatekos padlovonalara (ha szandekosan oda kuldi)
	{
		for (int i = 0; i < player->padlovonal_count; i++)
		{
			if (csempe_c == 0) break;
			if (player->padlovonal[i] == '-')
			{
				player->padlovonal[i] = valasz_szin;
				csempe_c--;
			}
		}
	}


	// Felesleges csempek a padlovonalra
	if (csempe_c > 0) {
		for (int i = 0; i < player->padlovonal_count; i++) {
			if (player->padlovonal[i] == '-')
			{
				player->padlovonal[i] = valasz_szin;
				csempe_c--;
			}
			if (csempe_c == 0) break;
		}
	}

	// Maradek csempeket a dobozba eldobni
	if (csempe_c > 0) {
		game->doboz[valasz_szin - 65] += csempe_c;
	}
}

// 10. feladat
void Csempe_kezeles(Player* player, Game* game)
{
	bool ok;
	int oszlop;

	for (int i = 0; i < player->mintasorok_count; i++)
	{
		if (player->mintasorok[i][i] != '-') //ha az utolso [i][i] csempe nem ures, teli van a sor
		{
			do
			{
				ok = true;

				Draw_player(*player);
				cout << "\n" << i + 1 << ". sor, valassz oszlopot: ";
				cin >> oszlop;
				cinclear();

				if (oszlop < 1 || oszlop > 5) ok = false; //ha hibas input
				else
				{
					for (int j = 0; j < player->fal_count; j++)
					{
						if (player->fal[j][oszlop - 1] == player->mintasorok[i][0]) ok = false; //az oszlopban van-e az adott csempebol
					}
					if (player->fal[i][oszlop - 1] != '-') ok = false; //van-e mar valami az adott helyen
				}
			} while (!ok);

			game->doboz[player->mintasorok[i][0] - 65] += i - 1;
			player->fal[i][oszlop - 1] = player->mintasorok[i][0];
			player->pontszam += Pontozas(player, i, oszlop - 1);
			for (int j = 0; j <= i; j++) player->mintasorok[i][j] = '-';
		}
		else //ha nem lett meg a mintasor, szimpla uritese a dobozba
		{
			for (int j = 0; j < i; j++)
			{
				if (player->mintasorok[i][j] != '-')
				{
					game->doboz[player->mintasorok[i][j] - 65]++;
					player->mintasorok[i][j] = '-';
				}
			}
		}
	}

	player->pontszam -= Buntetopontok(player);
	if (player->pontszam < 0) player->pontszam = 0;

	cout << "-----------------------------\n";

	Draw_player(*player);
}

// 12. feladat
int Bonusz(Player* player, Game* game)
{
	int bonuszpontok = 0;
	int csempek_szama[5] = { 0 };

	bonuszpontok += Teli_sorok(player) * 2;
	bonuszpontok += Teli_oszlopok(player) * 7;

	for (int i = 0; i < player->fal_count; i++)
	{
		for (int j = 0; j < player->fal_count; j++)
		{
			if (player->fal[i][j] != '-')
			{
				csempek_szama[player->fal[i][j] - 65]++;
				if (csempek_szama[player->fal[i][j] - 65] == 5) bonuszpontok += 10;
			}
		}
	}

	return bonuszpontok;
}

bool Check_jatekvege(Player* players, int jatekosszam)
{
	for (int i = 0; i < jatekosszam; i++)
	{
		if (Teli_sorok(&players[i]) > 0) return true;
	}
	return false;
}
bool Check_korvege(Game* game)
{
	for (int i = 0; i < game->kozos.elemek_count; i++)
	{
		if (game->kozos.elemek[i] > 0) return false;
	}
	for (int i = 0; i < game->korongok_count; i++)
	{
		for (int j = 0; j < game->korongok[i].elemek_count; j++)
		{
			if (game->korongok[i].elemek[j] != '-') return false;
		}
	}
	return true;
}

int main()
{
	srand((unsigned int)time(NULL));
	int jatekosszam;
	int jelenlegi_jatekos = 0;

	do
	{
		cout << "Jatekosok szama (2-4): ";
		cin >> jatekosszam;
		cout << "\n";
		cinclear();
	} while (jatekosszam < 2 || jatekosszam > 4);

	Game game(jatekosszam);
	Player* players = Create_jatekosok(jatekosszam);

	do
	{
		Elokeszit(&game);

		//Csempek a mintavonalra helyezése
		do
		{
			if (jelenlegi_jatekos >= jatekosszam) jelenlegi_jatekos = 0;
			cout << "---- " << jelenlegi_jatekos + 1 << ". JATEKOS -------------------------";
			Draw_korongok(&game);
			Draw_player(players[jelenlegi_jatekos]);
			Csempevalaszto(&players[jelenlegi_jatekos], &game);
			Draw_player(players[jelenlegi_jatekos]);
			jelenlegi_jatekos++;
		} while (!Check_korvege(&game));

		//Csempek mintavonalrol a falra helyezese
		for (int i = 0; i < jatekosszam; i++)
		{
			cout << "---- " << i + 1 << ". JATEKOS -------------------------";
			Csempe_kezeles(&players[i], &game);
		}

	} while (!Check_jatekvege(players, jatekosszam));

	//Bonuszpontok kiirasa
	cout << "==============================";
	for (int i = 0; i < jatekosszam; i++)
	{
		cout << "\n" << i + 1 << ". jatekos: " << Bonusz(&players[i], &game) << " bonuszpont";
		players[i].pontszam += Bonusz(&players[i], &game);
	}

	//Vegso pontok kiirása
	Scoreboard(players, jatekosszam);

	delete[] players;
}

