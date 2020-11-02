#include <string>
#include <vector>
#include "SystemCatalog_lib.h"
using namespace std;

class VinculoDB{
	private:
		string Nombre;
	public:
		VinculoDB(string p_nombre){ Nombre =  p_nombre; };
		bool Escribir(string p_registro);
		vector<string> getData();
		vector<string> getData(string p_criterio, int p_campo);
		//metodos de apoyo
		vector<string> Split(string cadena, char separador);
		int ToInt(string p_num);
		string ToString(int p_num);
		int getMaxID();
};

class Provincia: public VinculoDB{
	private:
		int ProvID;
		string Nombre;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Provincia(string p_nombre);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return ProvID; };	
		string getNombre(){ return Nombre; };
		vector<string> getAllData(){ return Data; };
};

class Municipio: public VinculoDB{
	private:
		int MunicID;
		string Nombre;
		Provincia* ProvID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Municipio(string p_nombre, int p_prov_id);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return MunicID; };	
		string getNombre(){ return Nombre; };
		Provincia getProvicia(){ return *ProvID; };
		vector<string> getAllData(){ return Data; };
};

class Sector: public VinculoDB{
	private:
		int SectID;
		string Nombre;
		Municipio* MunicID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Sector(string p_nombre, int p_munic_id);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return SectID; };	
		string getNombre(){ return Nombre; };
		Municipio getMunicipio(){ return *MunicID; };
		vector<string> getAllData(){ return Data; };
};

class Direccion: public VinculoDB{
	private:
		int DirecID;
		string Descripcion;
		Sector* SecID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Direccion(string p_descrip, int _secID);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return DirecID; };	
		string getDescripcion(){ return Descripcion; };
		Sector getSector(){ return *SecID; };
		vector<string> getAllData(){ return Data; };
};

class Marca: public VinculoDB{
	private:
		int MarcaID;
		string Marc_Nombre;
		string Marc_Year;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Marca(string p_nombre, string p_year);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return MarcaID; };	
		string getNombre(){ return Marc_Nombre; };
		string getYear(){ return Marc_Year; };
		vector<string> getAllData(){ return Data; };
};

class Modelo: public VinculoDB{
	private:
		int ModeloID;
		string Mod_Nombre;
		string Mod_Year;
		Marca* MarcaID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Modelo(string p_nombre, string p_year, int p_marca_id);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return ModeloID; };
		string getNombre(){ return Mod_Nombre; };
		Marca getMarca(){ return *MarcaID; };
		vector<string> getAllData(){ return Data; };
};

class Vehiculo: public VinculoDB{
	private:
		int VehID;
		Modelo* ModeloID;
		string Veh_Year;
		string PlacaNum;
		string Color;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Vehiculo(int p_modelo, string p_year, string p_placa, string p_color);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return VehID; };
		Modelo getModelo(){ return *ModeloID; };		
		string getYear();
		string getPlaca();
		string getColor();
		vector<string> getAllData(){ return Data; };
};

class Licencia: public VinculoDB{
	private:
		int LicID;
		int Categoria;
		string FechaVencimiento;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Licencia(int p_categoria, string p_fechaV);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return LicID; };
		int getCategoria(){ return Categoria; };	
		string getFechaVen(){ return FechaVencimiento; };
		vector<string> getAllData(){ return Data; };
};

class Persona: public VinculoDB{
	private:
		int PersID;
		string Oficio;
		string Pers_Nombre;
		string Pers_Apellido;
		string Pers_Cedula;
		Licencia* LicID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Persona(string p_oficio, string p_nombre, string p_apellido, string p_cedula, int p_licId);
		Persona(string p_oficio, string p_nombre, string p_apellido, string p_cedula);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return PersID; };	
		string getOficio(){ return Oficio; };
		string getNombre(){ return Pers_Nombre; };
		string getApelligo(){ return Pers_Apellido; };
		string getCedula(){ return Pers_Cedula; };
		Licencia getLicencia(){ return *LicID; };
		vector<string> getAllData(){ return Data; };
};

class Unidad: public VinculoDB{
	private:
		int UnidID;
		Vehiculo* VehID;
		Persona* PersID;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Unidad(int p_veh, int p_pers);
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return UnidID; };
		Vehiculo getVehiculo(){ return *VehID; };
		Persona getConductor(){ return *PersID; };
		vector<string> getAllData(){ return Data; };
};

class Ruta: public VinculoDB{
	private:
		int RutaID;
		Direccion* PuntoInicio;
		Direccion* PuntoFinal;
		Unidad* UnidID;
		Persona* PersID;
		string Fecha;
		vector<string> Data;
		void AsignarEstado(vector<string> p_campos);
	public:
		Ruta(int p_direc_id1, int p_direc_id2, int p_unid_id, int p_pers_id, string p_fecha);		
		bool Busg(int p_criterio);
		bool Busg(string p_criterio);
		bool Grabar();
		bool Leer();
		//getters
		int getID(){ return RutaID; };
		Direccion getP_Inicio(){ return *PuntoInicio; };
		Direccion getP_Final(){ return *PuntoFinal; };
		Unidad getUnidad(){ return *UnidID; };
		Persona getCliente(){ return *PersID; };
		string getFecha(){ return Fecha; };
		vector<string> getAllData(){ return Data; };
};
