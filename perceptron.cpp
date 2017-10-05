#include "matrix.h"
#include <iostream>
#define error 0.00000000001
#define Matrix Matrix<double>

using namespace std;

Matrix degrau(Matrix Y) {
	Matrix result = Matrix(Y.get_rows(), 1, 0.0);

	for (int i = 0; i < Y.get_rows(); i++) {
		if (Y(i, 0) >= -error) {
			result(i, 0) = 1;
		} else {
			result(i, 0) = 0;
		}
	}

	return result;
}

Matrix perceptron(int max_it, double rate, Matrix X, Matrix D) {
	Matrix W = Matrix(D.get_rows(), X.get_rows(), 0.0);
	int t = 0, E = 1;
	
	while (t < max_it && E > 0) {
		E = 0;
		for (int i = 0; i < X.get_cols(); i++) {
			Matrix Yi = degrau(W*X.getColumn(i));
			Matrix Ei = D.getColumn(i) - Yi;
			W = W + (Ei*X.getColumn(i).transpose())*rate;
			E = E + Ei.sum();
		}
		t++;
	}

	cout << "Numero de iteracoes: " << t << endl;
	return W;
}

int main () {

	// Read input
	int numero_amostras, qtd_carac, qtd_saidas; cin >> numero_amostras >> qtd_carac >> qtd_saidas;

	vector< vector<double> > amostras;
	vector< vector<double> > saidas;

	for (int i = 0; i < numero_amostras; i++) {
		vector<double> amostrai;
		vector<double> saidai;
		amostrai.push_back(1);							   // coloca o bias
		for (int j = 0; j < qtd_carac; j++) {
			double a; cin >> a;
			amostrai.push_back(a);
		}
		for (int j = 0; j < qtd_saidas; j++) {
			double s; cin >> s;
			saidai.push_back(s);
		}
		amostras.push_back(amostrai);
		saidas.push_back(saidai);
	}

	vector<double> in;
	for (int i = 0; i < amostras.size(); i++) {
		for (int j = 0; j < amostras[i].size(); j++) {
			in.push_back(amostras[i][j]);			
		}
	}

	vector<double> out;
	for (int i = 0; i < saidas.size(); i++) {
		for (int j = 0; j < saidas[i].size(); j++) {
			out.push_back(saidas[i][j]);
		}
	}
	
	Matrix X = Matrix(numero_amostras, qtd_carac+1, 0.0);
	X.init(in);
	X = X.transpose();
	
	Matrix D = Matrix(qtd_saidas, numero_amostras, 0.0);
	D.init(out);
	
	double rate = 0.05, max_it = 100;

	Matrix ans = perceptron(max_it, rate, X, D);

	ans.print();
	
	return 0;
}
