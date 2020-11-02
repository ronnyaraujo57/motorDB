#include <string>
#include <vector>
using namespace std;

//funciones de apoyo
vector<string> Split(string cadena, char separador);
int ToInt(string p_num);
bool ValidarFecha(string p_fecha);

//clases
class Colums{
	private:
		int ID;
		string Nombre;
		int EntityID;
		string Type;
	public:
		Colums(int,int,string,string);
		//getters
		int getID();
		string getNombre();
		int getEntityID();
		string getType();		
};

class Entity{
	private:
		int ID;
		string Nombre;
		vector<Colums> AllColums;
		vector<string> Data;
		bool LeerCSV();
		void loadColums();
		void AsignarEstados(string p_campos);
	public:
		Entity(string nombre);
		void Alta(vector<string> columnas);
		void Baja(string PK);
		bool Busg(string Criterio);
		bool Acceso_A_DB(vector<string> p_datos);
		//getters
		int getID();
		string getNombre();
		vector<Colums> getAllColums(){ return AllColums; };
		vector<string> getData(){ return Data; };
		
};

class PK{
	private:
		int ID;
		int EntityID;
		int ColumsID;
	public:
		PK(int,int);
		//getters
		int getID();
		int getEntityID();
		int getColumsID();
};

class FK{
	private:
		int ID;
		int EntityPadreID;
		int EntityHijoID;
		int ColumsPadreID;
		int ColumsHijoID;
	public:
		FK(int,int,int,int);
		//getters
		int getID();
		int getEntityPadreID();
		int getEntityHijoID();
		int getColumsPadreID();
		int getColumsHijoID();
};
