#include <iostream>

using namespace std;

static string csempek = "ABCDE";

struct Korong
{
	char elemek[4];
};


// 2. feladat
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

// 3. feladat
struct Game
{
	Korong* korongok = Korongok(2);
	int korongok_count = 5; //ez
	int kozos[6] = { 0, 0, 0, 0, 0, 0 };
	int zsak[5] = { 20, 20, 20, 20, 20 };
	int doboz[5] = { 0, 0, 0, 0, 0 };

	public:
		Game()
		{

		}

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

// 1. feladat | 5. feladat
char Huzas(Game _game)
{
	if (Sum(_game.zsak) == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			_game.zsak[i] = _game.doboz[i];
			_game.doboz[i] = 0;
		}
	}

	char csempe = 'A';
	int szam = rand() % Sum(_game.zsak);
	int min = 20;

	for (int i = 0; i < sizeof(_game.zsak); i++)
	{
		if (szam < min)
		{
			_game.zsak[i]--;
			csempe = csempek[i];
			break;
		}
		else min += _game.zsak[i];
	}
	return csempe;
}

// 4. feladat
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

	cout << "Kozos:\t";
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
					cout << "1";
					break;
			}
		}
	}
}

// 6. feladat
Game Elokeszit(Game _game)
{
	for (int i = 0; i < _game.korongok_count; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_game.korongok[i].elemek[j] = Huzas(_game);
		}
		_game.kozos[5] = 1;
	}

	return _game;
}

// 7/1. feladat
struct Player
{
	char fal[5][5] = { '.' };
	char padlovonal[7] = { '_' };
	char mintasorok[5][5] = { '-' };
	int pontszam = 0;
};

// 7/2. feladat
Player* Jatekosok(int _jatekosszam)
{
	return new Player[_jatekosszam];
}

void Draw_player(Player _player)
{
	cout << "\n";

	cout << "1 2 3 4 5     Pontok: " << _player.pontszam << "\n";

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_player.fal[i][j] == '.') cout << ". ";
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
		if (_player.padlovonal[i] == '_') cout << " _ ";
		else cout << " " << _player.padlovonal[i] << " ";
	}
	cout << "\n";
	cout << "-1 -1 -2 -2 -2 -3 -3";
}

int main()
{
	Player jatekos;

	Game game;
	game = Elokeszit(game);
	Draw_korongok(game);
	Draw_player(jatekos);
}