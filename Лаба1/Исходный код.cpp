#include <iostream>
#include <fstream>
using namespace std;
const int maxn = 100;

bool converge(double *xNew, double *xOld, int count, double eps)
{
	double norm = 0;
	for (int i = 0; i < count; i++)
	{
		norm += (xNew[i] - xOld[i])*(xNew[i] - xOld[i]);
	}
	if (sqrt(norm) >= eps)
		return false;
	return true;
}

void findAnswer(double *xNew,const int n,double indexNearX[maxn][maxn],double *freeTerms,double eps)
{
	double xOld[maxn];
	do
	{
		for (int i = 0; i < n; i++)
			xOld[i] = xNew[i];
		for (int i = 0; i < n; i++)
		{
			double var = 0;
			for (int j = 0; j < i; j++)
				var += (indexNearX[i][j] * xNew[j]);
			for (int j = i + 1; j < n; j++)
				var += (indexNearX[i][j] * xOld[j]);
			xNew[i] = (freeTerms[i] - var) / indexNearX[i][i];
		}
	} while (!converge(xNew, xOld,n,eps));
}

int readFromFile(double indexNearX[maxn][maxn], double *freeTerms, double &eps)
{
	ifstream input;
	input.open("input.txt");
	int count;
	input >> count>>eps;
	for (int i = 0; i < count; i++)
	for (int j = 0; j < count; j++)
	{
		input >> indexNearX[i][j];
		if (j == count - 1) input >> freeTerms[i];
	}
	input.close();
	return count;
}

void answer(double *xAns, int count)
{
	ofstream out("output.txt");
	for (int i = 0; i < count; i++)
		out << xAns[i]<<" ";
	out << endl;
	out.close();
}

int main()
{
	double xAns[maxn] = { 0 };
	double indexNearX[maxn][maxn] = { 0 };
	double freeTerm[maxn] = { 0 }, eps = 0;
	int count = readFromFile(indexNearX, freeTerm,eps);
	for (int i = 0; i < count; i++) xAns[i] = 0;
	double flag = 0;
	for (int i = 0; i < count;i++)
	for (int j = 0; j < count; j++)
		if (i != j)flag += indexNearX[i][j] * indexNearX[i][j];
	if (flag < 1)
	{
		findAnswer(xAns, count, indexNearX, freeTerm, eps);
		answer(xAns, count);
	}
	else
	{
		cout << "No answer\n";
		ofstream out("output.txt");
		out << "No answer" << endl;
		out.close();
	}
	return 0;
}