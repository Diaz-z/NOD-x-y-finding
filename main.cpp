#include <iostream>
#include <math.h>
#include <cstdio>
#include <algorithm>
#include <random>
#include <time.h>

using namespace std;
int NOD(int x, int y)
{
	using namespace std;
	int tmp_res = 0;
	vector<int> vector_a;

	if (x < y)
	{
		swap(x, y);
	}

	vector_a.push_back(x);
	vector_a.push_back(y);

	while (vector_a[1] != 0)
	{
		tmp_res = vector_a[0] % vector_a[1];
		if (tmp_res < vector_a[1])
		{
			swap(vector_a[0], vector_a[1]);
			vector_a[1] = tmp_res;
		}
		else
		{
			vector_a[0] = tmp_res;
		}
		/*cout << "TMP pare: " << vector_a[0] << ' ' << vector_a[1] << endl;*/
	}
	return vector_a[0];
}
vector<int> XYNODfind(int a, int b)
{
	using namespace std;
	int q;
	vector<int> U, V, T;
	U = {a, 1, 0};
	V = {b, 0, 1};
	cout << "log: " << endl;
	while (V[0] != 0)
	{
		if (U[0] < V[0])
		{
			swap(V, U);
		}
		q = U[0] / V[0];
		T = {U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2]};
		for (size_t i = 0; i <= 2; i++)
		{
			cout << U[i] << " ";
		}
		U = V;
		V = T;
		cout << endl;
	}
	for (size_t i = 0; i <= 2; i++)
	{
		cout << U[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i <= 2; i++)
	{
		cout << V[i] << " ";
	}
	return U;
}
// void swapArray(int* a, int* b, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		int tmp = a[i];
//		a[i] = b[i];
//		b[i] = tmp;
//	}
// }
// void evklid2(int a, int b, int(&arr)[3]) {
//	if (b > a) {
//		cout << "swap values!" << endl; swap(a, b);
//	}
//	int c = 1;
//	int u[3] = { a,1,0 };
//	int v[3] = { b,0,1 };
//	while (v[0] != 0) {
//		int q = a / b;
//		int T[3] = { (u[0] % v[0]),(u[1] - q * v[1]),(u[2] - q * v[2]) };
//		swapArray(u, v, 3);
//		swapArray(v, T, 3);
//		//��������
//		//cout << endl;
//		//for (int i = 0; i < 3; i++)
//		// cout << u[i] << '\t';
//		//cout << endl;
//		//for (int i = 0; i < 3; i++)
//		// cout << v[i] << '\t';
//		// ��������
//	}
//	swapArray(arr, u, 3);
// }
int modexp(int x, int y, int p)
{
	int Y = 1;
	int k = int(log2(y))+1;
	for (int i = 0; i <= k; i++)
	{
		if (y % 2 != 0)
		{
			long long c = pow(2, i);
			int X = 1;
			while (c--)
			{
				X = (X % p * x % p) % p;
			}
			Y = (Y % p * X %p ) % p;
		}
		y /= 2;
	}
	return Y;
}
int stepen(int a, int x, int p)
{
	int i = 0;

	int x2[30];
	int vi = x;

	while (x >= 1)
	{
		x2[i] = x % 2;
		x /= 2;
		i++;
	}
	int n = i;
	long long *arr = new long long[n];
	arr[0] = a;
	for (int i = 1; i < n; i++)
	{
		arr[i] = (arr[i - 1] % p * arr[i - 1] % p) % p;
	}
	long long v = 1;
	for (int j = 0; j < n; j++)
	{
		if (x2[j] > 0)
		{
			v = (v % p * x2[j]% p * arr[j] % p) % p;
		}
	}
	delete [] arr;
	return v;
}
bool isprime(int p)
{
	if (p <= 1)
		return false;
	int b = (int)pow(p, 0.5);
	for (int i = 2; i <= b; i++)
	{
		if ((p % i) == 0)
			return false;
	}
	return true;
}
int GetRandomNumber(int min, int max)
{
	// ���������� ��������� ��������� �����
	srand(time(NULL));

	// �������� ��������� ����� - �������
	int num = min + rand() % (max - min + 1);

	return num;
}
vector<int> Helman(int Xa, int Xb)
{
	long range = 1e5;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dist(1, range);
	long long q, p, g;
	do
	{
		/* q = gen() % range; */
		//q = GetRandomNumber(1, range);
		q = dist(gen);
		p = 2 * q + 1;
	} while (!isprime(q) || !isprime(p));
	cout << "q,p: " << q << "\t" << p;
	do
	{
		/* g = 1 + gen() % (p - 1); */
		g = GetRandomNumber(1, p - 1);
	} while (stepen(g, q, (p)) == 1);
	/*cout << endl << g << endl;*/
	// cout << modexp(g,q,p);
	long long Ya = stepen(g, Xa, p);
	long long Yb = stepen(g, Xb, p);
	// cout << Xa << "\t" << Xa << endl;
	/*cout << Ya << "\t" << Yb;*/
	long long Zab = stepen(Yb, Xa, p);
	long long Zba = stepen(Ya, Xb, p);
	/*cout << endl << Zab << "\t" << Zba << endl;*/
	vector<int> Z;
	Z.push_back(Zab);
	Z.push_back(Zba);
	return Z;
}
int main()
{
	int a, b, x, p;
	/* 	cout <<endl<<"finding x,y NOD| Please, enter a: ";
		cin >> a;
		cout <<"Please, enter b: ";
		cin >> b; */
	a = 63;
	b = 72;
	cout << "The equation is: " << a << "*x + y*" << b << "=" << NOD(a, b) << endl;
	vector<int> U = XYNODfind(a, b);
	cout << endl
		 << "result: NOD=" << U[0] << " x=" << U[1] << " y=" << U[2] << endl;
	/*cout <<endl<<"(a^x)mod(p)| Please, enter a: ";
	cin >> a;
	cout << "Please, enter x: ";
	cin >> x;
	cout << "Please, enter p: ";
	cin >> p; */
	a = 3;
	x = 29;
	p = 11;
	cout << "(a^x)mod(p)=" << stepen(a, x, p) << endl;
	int Xa, Xb;
	cout << endl
		 << "Helman key finding| Please, enter Xa: ";
	/* cin >> Xa;
	cout <<"Please, enter Xb: ";
	cin >> Xb; */
	Xa = 11;
	Xb = 121;
	vector<int> Key = Helman(Xa, Xb);
	cout << endl
		 << "Helman key| Za,Zb: " << Key[0] << "," << Key[1] << endl;
}