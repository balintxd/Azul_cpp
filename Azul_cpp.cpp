#include <iostream>

using namespace std;

static string csempek = "ABCDE";

struct Korong
{
	char elemek[4];
};


// 2. feladat (Korongok t�mbj�nek lefoglal�sa)
Korong* Korongok(int _jatekosszam)
{
	int korongszam = 0;

	switch (_jatekosszam)
	{
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
		break;
	}

	return new Korong[korongszam];

	//Korong* array = new Korong[korongszam];
	//return array;

}

// 3. feladat (Game strukt)
struct Game
{
	Korong* korongok;
	int korongok_count;
	int kozos[6] = { 0, 0, 0, 0, 0, 0 };
	int zsak[5] = { 20, 20, 20, 20, 20 };
	int doboz[5] = { 0, 0, 0, 0, 0 };

	Game(int _jatekosszam)
	{
		korongok = Korongok(_jatekosszam);

		switch (_jatekosszam)
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

int Sum(int _array[])
{
	int sum = 0;
	for (int i = 0; i < sizeof(_array); i++)
	{
		sum += _array[i];
	}
	return sum;
}
bool Korong_empty(Korong _korong)
{
	for (int i = 0; i < sizeof(_korong.elemek); i++)
	{
		if (_korong.elemek[i] != '-') return false;
	}
	return true;
}
bool Korong_contains(Korong _korong, char _szin)
{
	for (int i = 0; i < sizeof(_korong.elemek); i++)
	{
		if (_szin == _korong.elemek[i]) return true;
	}
	return false;
}
bool Kozos_contains(int _kozos[], char _szin)
{
	for (int i = 0; i < sizeof(_kozos) - 1; i++)
	{
		if (i = _szin - 65)
		{
			if (_kozos[i] > 0) return true;
			else return false;
		}
	}
	return false;
}


// 1. feladat | 5. feladat (Zs�kb�l h�z�s)
char Huzas(Game* _game)
{
	if (Sum(_game->zsak) == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			_game->zsak[i] = _game->doboz[i];
			_game->doboz[i] = 0;
		}
	}

	char csempe = 'A';
	int szam = rand() % Sum(_game->zsak);
	int min = 20;

	for (int i = 0; i < sizeof(_game->zsak); i++)
	{
		if (szam < min)
		{
			_game->zsak[i]--;
			csempe = csempek[i];
			break;
		}
		else min += _game->zsak[i];
	}
	return csempe;
}

// 4. feladat (Korongok �s k�z�s megjelen�t�se)
void Draw_korongok(Game _game)
{
	for (int i = 0; i < _game.korongok_count; i++)
	{
		cout << i + 1 << ".\t";

		for (int j = 0; j < sizeof(_game.korongok[i].elemek); j++)
		{
			cout << _game.korongok[i].elemek[j];
		}
		cout << "\n";
	}

	cout << "0. Kozos:\t";
	for (int i = 0; i < sizeof(_game.kozos); i++)
	{
		for (int j = 0; j < _game.kozos[i]; j++)
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
	}
}

// 6. feladat (Fordul� el�k�sz�t�se)
void Elokeszit(Game* _game)
{
	for (int i = 0; i < _game->korongok_count; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_game->korongok[i].elemek[j] = Huzas(_game);
		}
		_game->kozos[5] = 1;
	}
}

// 7-1. feladat (Player strukt)
struct Player
{
	char fal[5][5];
	char padlovonal[7];
	char mintasorok[5][5];
	int pontszam;
};

// 7-2. feladat (Player t�mb lefoglal�sa)
Player* Jatekosok(int _jatekosszam)
{
	Player* array = new Player[_jatekosszam];

	for (int i = 0; i < _jatekosszam; i++)
	{
		//Fal felt�lt�se
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++) array[i].fal[j][k] = '-';
		}

		//Padl�vonal felt�lt�se
		for (int j = 0; j < 7; j++)
		{
			array[i].padlovonal[j] = '-';
		}

		//Mintasorok felt�lt�se
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++) array[i].mintasorok[j][k] = '-';
		}

		//Kez�pontsz�m
		array[i].pontszam = 0;
	}

	return array;
}

// 8. feladat (Player megjelen�t�se)
void Draw_player(Player _player)
{
	cout << "\n";

	cout << "1 2 3 4 5     Pontok: " << _player.pontszam << "\n";

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_player.fal[i][j] == '-') cout << ". ";
			else cout << _player.fal[i][j] << " ";
		}
		cout << " " << i + 1 << "  ";
		for (int j = 0; j < i; j++)
		{
			if (_player.mintasorok[i][j] == '-') cout << "-";
			else cout << _player.mintasorok[i][j];
		}
		cout << "\n";
	}
	for (int i = 0; i < sizeof(_player.padlovonal); i++)
	{
		if (_player.padlovonal[i] == '-') cout << " _ ";
		else cout << " " << _player.padlovonal[i] << " ";
	}
	cout << "\n";
	cout << "-1 -1 -2 -2 -2 -3 -3";
}

// 9. feladat (Csemp�k v�laszt�sa)
void Valasztas(Player* _player, Game* _game)
{
	int valasz_korong = -1;
	char valasz_szin;
	int valasz_mintasor = -1;
	bool helyes = true;

	Draw_korongok(*_game);

	do
	{
		helyes = true;
		cout << "\nValassz egy korongot: ";
		cin >> valasz_korong;

		if (valasz_korong <= -1 || valasz_korong > _game->korongok_count) helyes = false;
		else if (valasz_korong == 0 && Sum(_game->kozos) == 0) helyes = false;
		else if (Korong_empty(_game->korongok[valasz_korong])) helyes = false;
	} while (!helyes);

	do
	{
		helyes = true;
		cout << "\nValassz egy szint: ";
		cin >> valasz_szin;

		if (valasz_szin >= 'a' && valasz_szin <= 'e') valasz_szin = toupper(valasz_szin);

		if (valasz_korong != 0)
		{
			if (valasz_szin < 'A' && valasz_szin > 'E') helyes = false;
			else if (!Korong_contains(_game->korongok[valasz_korong], valasz_szin)) helyes = false;
		}
		else
		{
			if (!Kozos_contains(_game->kozos, valasz_szin)) helyes = false;
		}
	} while (!helyes);

	do
	{
		helyes = true;
		cout << "\nValassz mintasort (0-padlovonal): ";
		cin >> valasz_mintasor;

		if (valasz_mintasor < 0 || valasz_mintasor > 5) helyes = false;
		if (valasz_mintasor == 0)
		{

		}

	} while (!helyes);

}

int main()
{
	int jatekosszam;

	cout << "Jatekosok szama (2-4): ";
	cin >> jatekosszam;

}