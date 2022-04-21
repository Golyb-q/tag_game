#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;
int main()
{
	srand(time(0));
	system("chcp 1251");

	int X1, Y1,					//корды второго числа
		X0, Y0,					//корды нуля
		matrix[100][100],		//основная матрица игры
		WINMmatrix[100][100],	//матрица для проверки проходимости. после успешной проверки содержит правельную конфигурацию
		i, j,					//размер игры
		n1;						//перемещение чисел

	do
	{
		cout << "Размер игры (>1, <=100):\n";
		cin >> i >> j;
	} while (i <= 1 || j <= 1 || i > 100 || j > 100);
	cout << endl;

	//создание игры
	for (int x = 0; x < j; x++)
		for (int y = 0; y < i; y++)
			matrix[x][y] = x * i + y;

	//перемешивание игры
	int step, parity;
	do
	{
		step = 0;
		//перемешать случайно
		for (int x = 0; x < j; x++)
			for (int y = 0; y < i; y++)
				swap(matrix[x][y], matrix[rand() % j][rand() % i]);

		//проверить проходимость https://youtu.be/YUNhFR2vglQ?t=920
			//узнаем четность конфигурации
		for (int x = 0; x < j; x++)
			for (int y = 0; y < i; y++) {
				WINMmatrix[x][y] = matrix[x][y];
				if (WINMmatrix[x][y] == 0) {
					parity = ((i - 1 - x) + (j - 1 - y)) % 2;
					X0 = x; Y0 = y;
				}
			}
			//узнаем параметр беспорядка
		for (int N1 = 0; N1 < i * j - 1; N1++)
			for (int N2 = N1; WINMmatrix[N1 / i][N1 % i] != N1 + 1; N2++)
				if (WINMmatrix[N2 / i][N2 % i] == N1 + 1) {
					swap(WINMmatrix[N2 / i][N2 % i], WINMmatrix[N1 / i][N1 % i]);
					step++;
				}
	} while (step % 2 != parity);
	cout << endl;

	//показать результат
	for (int x = 0; x < j; x++) {
		for (int y = 0; y < i; y++)
			cout << matrix[x][y] << "\t";
		cout << endl;
	}

	//перемещение чисел игроком
	int score = 0;
	for (bool WIN = false; !WIN;) {
		//cout << "Введите индексы чисел, которые нужно поменять местами\n";
		//поверка деопазона, близости, наличия нуля
		int p;
		do
		{
			cout << "Управляфйте пустым местом (нулем) на нумападе: 8426\n8 - вверх\n4 - влево\n2 - вниз\n6 - вправо" << "\n";
			cin >> n1;

			X1 = X0;
			Y1 = Y0;
			switch (n1){
				case 8: X1 -= 1; break;
				case 4: Y1 -= 1; break;
				case 2: X1 += 1; break;
				case 6: Y1 += 1; break;
			}
		} while (
			n1 > 9 ||
			n1 < 0 ||
			n1 % 2 == 1 ||
			X1 >= j || Y1 >= i ||
			X1 <= -1 || Y1 <= -1);

		score++;
		swap(matrix[X0][Y0], matrix[X1][Y1]);
		X0 = X1;
		Y0 = Y1;

		//показать результат и проверить победу
		cout << "\n\nИгра:\n";
		WIN = true;
		for (int x = 0; x < j; x++) {
			//игра
			for (int y = 0; y < i; y++) {
				cout << matrix[x][y] << "\t";
				//сравнение с правельной конфигурацией
				if (matrix[x][y] != WINMmatrix[x][y])
					WIN = false;
			}
			cout << endl;
		}
	}
	cout << "\nПоздравляю с победой!\nХодов потрачено: " << score;
}