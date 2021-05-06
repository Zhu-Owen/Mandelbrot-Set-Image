#include <iostream>
#include <fstream>
using namespace std;

int findMandel(double cr, double ci, int max_it) {
	int i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < max_it && zr * zr + zi * zi < 4.0) {
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}

double toReal(int x, int w, double mir, double mxr) {
	return x * ((mxr - mir) / w) + mir;
}

double toImag(int y, int h, double mii, double mxi) {
	return y * ((mxi - mii) / h) + mii;
}

int main() {
	ifstream fin("input.txt");
	int w, h, maxn;
	double mxr, mir, mxi, mii;
	//
	if (!fin) {
		cout << "Error!\n";
		cin.ignore();
		return 0;
	}
	fin >> w >> h >> maxn >> mir >> mxr >> mii >> mxi;
	//     2736 1824 2048   -2.4    1.0    -1.3   1.3 background
	ofstream fout("outimage.ppm");
	fout << "P3" << endl;
	fout << w << " " << h << endl;
	fout << "256" << endl;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			double cr = toReal(x, w, mir, mxr);
			double ci = toImag(y, h, mii, mxi);
			int n = findMandel(cr, ci, maxn);
			int r = (n * n % 256), g = (n * 2 % 256), b = (n * 2 % 256); // Change Colors Here!
			fout << r << " " << g << " " << b << " ";
		}
		cout << endl;
	}
	fout.close();
	cout << "Finished!";
	return 0;
}