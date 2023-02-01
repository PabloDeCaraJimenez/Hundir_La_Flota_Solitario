# include <iostream>
# include <vector>
# include <time.h>
# include <windows.h>
# include <string>
using namespace std;


/*
Portaaviones, Buque, Submarino, Cruzero, Lancha.
*/

vector<pair<int,int>> ocupadas;

void delay(int segundos) {
	for(int i = (time(NULL) + segundos); time(NULL) != i; time(NULL));
}

class Barco {
public:
	int orientacion;
	int numero;
	int letra;
	vector<pair<int,int>> coordenadas;
	vector<bool> estado;

	nuevoBarco(int tama, int plus){
		bool coloca = false;
		this->coordenadas.resize(tama);
		this->estado.resize(tama);
		srand(time(NULL)+plus);
		this->orientacion = rand()%2;
		if (this->orientacion == 0){
			this->numero = rand()%10;
			this->letra = rand()%(tama+1)+(tama-1);
			this->coordenadas[0] = {this->numero, this->letra};
			for (int i = 0; i < this->coordenadas.size()-1; i++){
				this->coordenadas[i+1] = {this->coordenadas[i].first, (this->coordenadas[i].second)-1};
			}
		}
		else if (this->orientacion == 1){
			this->numero = rand()%(tama+1)+(tama-1);
			this->letra = rand()%10;
			this->coordenadas[0] = {this->numero, this->letra};
			for (int i = 0; i < this->coordenadas.size()-1; i++){
				this->coordenadas[i+1] = {(this->coordenadas[i].first)-1, this->coordenadas[i].second};
			}
		}
	}
	bool check(vector<pair<int,int>> misCoordenadas){
		bool miColoca = true;
		for (int i = 0; i < misCoordenadas.size(); i++){
			for (int j = 0; j < ocupadas.size(); j++){
				if ((misCoordenadas[i].first == ocupadas[j].first) and(misCoordenadas[i].second == ocupadas[j].second)){
					miColoca = false;
				}
			}
		}
		return miColoca;
	}
	ocupa(vector<pair<int,int>> misCoordenadas){
		for (int i = 0; i <= misCoordenadas.size()-1; i++){
			ocupadas.push_back(misCoordenadas[i]);
		}
	}
};

class Portaaviones : public Barco{
private:
	int tama = 5;
	int plus = 154897;

public:
	Portaaviones(){
		bool coloca = false;
		while (!coloca){
			nuevoBarco(this->tama, this->plus);
			coloca = check(this->coordenadas);
		}
		ocupa(this->coordenadas);
	}

};

class Buque : public Barco{
private:
	int tama = 4;
	int plus = 374826;

public:
	Buque(){
		bool coloca = false;
		while (!coloca){
			nuevoBarco(this->tama, this->plus);
			coloca = check(this->coordenadas);
		}
		ocupa(this->coordenadas);
	}

};

class Submarino : public Barco{
private:
	int tama = 4;
	int plus = 746281;

public:
	Submarino(){
		bool coloca = false;
		while (!coloca){
			nuevoBarco(this->tama, this->plus);
			coloca = check(this->coordenadas);
		}
		ocupa(this->coordenadas);
	}

};

class Crucero : public Barco{
private:
	int tama = 3;
	int plus = 937548;

public:
	Crucero(){
		bool coloca = false;
		while (!coloca){
			nuevoBarco(this->tama, this->plus);
			coloca = check(this->coordenadas);
		}
		ocupa(this->coordenadas);
	}

};

class Lancha : public Barco{
private:
	int tama = 2;
	int plus = 483702;

public:
	Lancha(){
		bool coloca = false;
		while (!coloca){
			nuevoBarco(this->tama, this->plus);
			coloca = check(this->coordenadas);
		}
		ocupa(this->coordenadas);
	}

};

class Tablero {
private:
	int numFilas;
	int numColum;
	string separador;
	vector<string*> reticula;
	bool haInsertado = false;
	bool confirmar = false;
	Portaaviones portaaviones;
	Buque buque;
	Submarino submarino;
	Crucero crucero;
	Lancha lancha;

	vector<string*> creaReticula(int nFil, int nCol){
		if (this->reticula.size()>0){
			this->reticula.resize(this->reticula.size() - numFilas);
		}
		int i;
		for (i = 0; i < nFil; i++){
			string* miFila = new string[nCol];
			for (int j = 0; j < nCol; j++){
				miFila[j] = " ";
			}
			this->reticula.push_back(miFila);
		}
	}
	void setNumFilas(int numFilas){
		creaReticula(numFilas, this->numColum);
		this->numFilas = numFilas;
	}
	void setNumColum(int numColum){
		creaReticula(this->numFilas, numColum);
		this->numColum = numColum;
	}
	void SetColor(int value){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
	}
	void separaFilas(){
		cout << "			";
		for (int i = 0; i < this->numFilas; i++){
			cout << char(197) << char(196) << char(196) << char(196);
		}
		cout << char(197) << endl;
	}
	void numeros(){
		int miNumero = 48;
		cout << "			";
		for (int i = 0; i < this->numFilas; i++, miNumero++){
			cout << "  " << char(miNumero) << " ";
		}
		cout << " " << endl;
	}

public:
	Tablero(int numFilas = 10, int numColum = 10, string separador = "|"){
		this->numFilas = numFilas;
		this->numColum = numColum;
		this->separador = separador;
		creaReticula(numFilas, numColum);
	}
	~Tablero(){
		for (int i = 0; i < numFilas; i++){
			delete this->reticula[i];
		}
	}
	void imprimir(){
		int miLetra = 65;
		string agua;
		string tocado;
		string hundido;
		agua = char(126);
		tocado = char(207);
		hundido = char(254);
		cout << endl;
		numeros();
		separaFilas();
		for (int i = 0; i < this->numFilas; i++, miLetra++){
			cout <<"                       " << char(miLetra) << separador << " ";
			for (int j = 0; j < this->numColum; j++){
				if (this->reticula[i][j] == agua){
					SetColor(11);
				}
				else if (this->reticula[i][j] == tocado or this->reticula[i][j] == hundido){
					SetColor(12);
				}
				cout << this->reticula[i][j];
				SetColor(7);
				cout << " " << this->separador << " ";
			}
			cout << endl;
			separaFilas();
		}
		cout << endl;
	}
	void consultarDato(int F, int C){
		if(this->numFilas>=F && this->numColum>=C){
			if (this->reticula[F-1][C-1] == "") cout << "CASILLA " << F << "," << C << ": " << "-SIN DATOS-" << endl;
			else cout << "CASILLA " << F << "," << C << ": " << this->reticula[F-1][C-1] << endl;
		}
		else cout << "CASILLA " << F << "," << C << ": -NO EXISTE-" << endl;
	}
	void insertarDato(char dato, int fila, int colum){
		this->haInsertado = false;
		if (this->numFilas >= fila && this->numColum >= colum)
			if (this->reticula[fila][colum] == " "){
				this->reticula[fila][colum] = dato;
				this->haInsertado = true;
			}
			else {
				if (confirmar){
					bool sobreescribir = false;
					string siONo;
					cout << "la casilla " << fila << "," << colum << " ya tiene un dato (" << this->reticula[fila-1][colum-1] << ")" << endl;
					cout << "Si desea sobreescribirlo inserte S, en caso contrario inserte N ==> ";
					cin >> siONo;
					if (siONo == "S" or siONo == "s") sobreescribir = true;
					if (sobreescribir){
						this->reticula[fila][colum] = dato;
						this->haInsertado = true;
					}
				}
				else {
					this->reticula[fila][colum] = dato;
					this->haInsertado = true;
				}
			}
		else cout << "La casilla " << fila << "," << colum << " no existe." << endl;
	}
	bool contains(vector<pair<int,int>> vector, pair<int,int> dato){
		bool contiene = false;
			for (int i = 0; i < vector.size(); i++){
				if (vector[i].first == dato.first and vector[i].second == dato.second) contiene = true;
			}
		return contiene;
	}
	int marcar(Barco miBarco, pair<int,int> dato){
		int marca = 0;
		for (int i = 0; i < miBarco.coordenadas.size(); i++){
			if (miBarco.coordenadas[i].first == dato.first and miBarco.coordenadas[i].second == dato.second){
				marca = 1;
				if (contains(this->portaaviones.coordenadas, dato)){
					this->portaaviones.estado[i] = true;
					bool hunde = true;
					for (int j = 0; j < this->portaaviones.estado.size(); j++){
						if (this->portaaviones.estado[j] == false) hunde = false;
					}
					if(hunde) marca = 2;
				}
				if (contains(this->buque.coordenadas, dato)){
					this->buque.estado[i] = true;
					bool hunde = true;
					for (int j = 0; j < this->buque.estado.size(); j++){
						if (this->buque.estado[j] == false) hunde = false;
					}
					if(hunde) marca = 2;
				}
				if (contains(this->submarino.coordenadas, dato)){
					this->submarino.estado[i] = true;
					bool hunde = true;
					for (int j = 0; j < this->submarino.estado.size(); j++){
						if (this->submarino.estado[j] == false) hunde = false;
					}
					if(hunde) marca = 2;
				}
				if (contains(this->crucero.coordenadas, dato)){
					this->crucero.estado[i] = true;
					bool hunde = true;
					for (int j = 0; j < this->crucero.estado.size(); j++){
						if (this->crucero.estado[j] == false) hunde = false;
					}
					if(hunde) marca = 2;
				}
				if (contains(this->lancha.coordenadas, dato)){
					this->lancha.estado[i] = true;
					bool hunde = true;
					for (int j = 0; j < this->lancha.estado.size(); j++){
						if (this->lancha.estado[j] == false) hunde = false;
					}
					if(hunde) marca = 2;
				}
			}
		}
		return marca;
	}
	pair<int,int> disparo(pair<int,int> dato){
		pair<int,int> toca;
		toca.first = 0;
		toca.second = 0;
		if (contains(this->portaaviones.coordenadas, dato)){
			toca.first = marcar(this->portaaviones, dato);
			toca.second = 1;
		}
		else if (contains(this->buque.coordenadas, dato)){
			toca.first = marcar(this->buque, dato);
			toca.second = 2;
		}
		else if (contains(this->submarino.coordenadas, dato)){
			toca.first = marcar(this->submarino, dato);
			toca.second = 3;
		}
		else if (contains(this->crucero.coordenadas, dato)){
			toca.first = marcar(this->crucero, dato);
			toca.second = 4;
		}
		else if (contains(this->lancha.coordenadas, dato)){
			toca.first = marcar(this->lancha, dato);
			toca.second = 5;
		}
		return toca;
	}
	bool contiene(string digitos, char dato){
		bool contiene = false;
		for (int i = 0; i < digitos.size(); i++){
			if (digitos[i] == dato) contiene = true;
		}
		
		return contiene;
	}
	void hundir(int miBarco){
		if (miBarco == 1){
			for (int i = 0; i < 5; i++){
				insertarDato(char(254), this->portaaviones.coordenadas[i].first, this->portaaviones.coordenadas[i].second);
			}
		}
		else if (miBarco == 2){
			for (int i = 0; i < 4; i++){
				insertarDato(char(254), this->buque.coordenadas[i].first, this->buque.coordenadas[i].second);
			}
		}
		else if (miBarco == 3){
			for (int i = 0; i < 4; i++){
				insertarDato(char(254), this->submarino.coordenadas[i].first, this->submarino.coordenadas[i].second);
			}
		}
		else if (miBarco == 4){
			for (int i = 0; i < 3; i++){
				insertarDato(char(254), this->crucero.coordenadas[i].first, this->crucero.coordenadas[i].second);
			}
		}
		else if (miBarco == 5){
			for (int i = 0; i < 2; i++){
				insertarDato(char(254), this->lancha.coordenadas[i].first, this->lancha.coordenadas[i].second);
			}
		}
	}
	void jugar(){
		string calificacion;
		int turno = 0;
		int gana = 5;
		vector<pair<int,int>> probadas;
		string posibles = "0123456789";
		pair<int,int> misCoordenadas;
		imprimir();
		while (gana > 0){
			pair<int,int> misDisparos;
			string apunto;
			string letraYNumero;
			bool prueba = false;
			while (!prueba){
				cout << "INTRODUCE COORDENADAS:	";
				cin >> letraYNumero;
				letraYNumero[0] = toupper(letraYNumero[0]);
				apunto = letraYNumero;
				apunto[0] = int((letraYNumero[0])-17);
				cout << endl;
				if (apunto.size() == 2 and contiene(posibles, apunto[0]) and contiene(posibles, apunto[1])){
					int coor1 = int(apunto[0])-48;
					int coor2 = int(apunto[1])-48;
					misCoordenadas = {coor1, coor2};
					if (contains(probadas, misCoordenadas)){
						cout << "YA HAS PROBADO ESTAS COORDENADAS." << endl;
					}
					else {
						probadas.push_back(misCoordenadas);
						prueba = true;
					}
				}
				else cout << "COORDENADAS INCORRECTAS." << endl;
			}
			misDisparos = disparo(misCoordenadas);
			if (misDisparos.first == 1){
				insertarDato(char(207), misCoordenadas.first, misCoordenadas.second);
				cout << "			" << letraYNumero << ": ";
				SetColor(12);
				cout << "TOCADO!" << endl;
			}
			else if (misDisparos.first == 2){
				string barco;
				hundir(misDisparos.second);
				if (misDisparos.second == 1) barco = "PORTAAVIONES";
				if (misDisparos.second == 2) barco = "BUQUE";
				if (misDisparos.second == 3) barco = "SUBMARINO";
				if (misDisparos.second == 4) barco = "CRUCERO";
				if (misDisparos.second == 5) barco = "LANCHA";
				cout << "			" << letraYNumero << ": ";
				SetColor(12);
				cout << barco << " TOCADO Y HUNDIDO!!!" << endl;
				gana--;
			}
			else {
				insertarDato(char(126), misCoordenadas.first, misCoordenadas.second);
				cout << "			" << letraYNumero << ": ";
				SetColor(11);
				cout << "AGUA" << endl;
				turno++;
			}
			SetColor(7);
			imprimir();
		}
		if (turno < 15){
			calificacion = "INCREIBLE!!!";
			SetColor(13);
		}
		else if (turno < 30){
			calificacion = "MUY BIEN!!";
			SetColor(10);
		}
		else if (turno < 45){
			calificacion = "BIEN!";
			SetColor(11);
		}
		else if (turno < 60){
			calificacion = "NO ESTA MAL";
			SetColor(14);
		}
		else{
			calificacion = "YA ERA HORA!!";
			SetColor(12);
		}
		cout << "			VICTORIA!!!" << endl;
		cout << "			" << calificacion << endl;
		cout << "			HAS NECESITADO " << turno << " TURNOS: " << endl;
		SetColor(7);
	}
};

int main() {
	cout << endl << "BIENVENIDO A \"HUNDIR LA FLOTA\"" << endl;
	bool jugamos = true;
	string otra = "";

	while(jugamos){
		Tablero miTablero(10, 10);
		otra = "";
		miTablero.jugar();
		while (otra != "s" and otra != "S" and otra != "n" and otra != "N"){
			cout << endl << "OTRA PARTIDA? (S/N) ";
			cin >> otra;
			cout << endl;
			if (otra == "n" or otra == "N") jugamos = false;
			else if (otra == "s" or otra == "S") jugamos = true;
			else cout << "Perdone, no le he entendido." << endl;
		}
	}
	cout << "HASTA OTRA!!" << endl;
	delay(2);

	return 0;
}