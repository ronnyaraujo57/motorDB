#include "Transporte.h"
#include <sstream>
#include <fstream>

//implementacion de VinculoDB
bool VinculoDB::Escribir(string p_registro){
	fstream archivo;
	string ruta = "C:\\DatoInfo\\" + Nombre;
	try{
		archivo.open(ruta.c_str(),ios::out|ios::app);			
		archivo<<p_registro<<endl;		
		archivo.close();
		return true;
	}catch(...){
		return false;
	}
}

vector<string> VinculoDB::getData(){
	fstream lectura;
	string linea;
	string ruta = "C:\\DatoInfo\\" + Nombre;
	vector<string> registros;
	try{
		lectura.open(ruta.c_str(),ios::in);
		if(!lectura.is_open())//valido que el archivo esta abierto
			throw 'x';//provoco una execcion si no lo esta
			
		while(lectura.good()){
			getline(lectura,linea);
			if(linea != "")
				registros.push_back(linea);//cargo los datos en mi vector
		}
		lectura.close();
		return registros;
	}catch(...){
		return registros;
	}
}

vector<string> VinculoDB::getData(string p_criterio, int p_campo){
	fstream lectura;
	string linea;
	string ruta = "C:\\DatoInfo\\" + Nombre;
	vector<string> registros;
	try{
		lectura.open(ruta.c_str(),ios::in);
		if(!lectura.is_open())//valido que el archivo esta abierto
			throw 'x';//provoco una execcion si no lo esta
			
		while(lectura.good()){
			getline(lectura,linea);
			if(Split(linea,',')[p_campo-1] == p_criterio)
				registros.push_back(linea);//cargo los datos filtrados en mi vector
		}
		lectura.close();
		return registros;
	}catch(...){
		return registros;
	}
}

vector<string> VinculoDB::Split(string cadena, char separador){
	//variables locales
	string aux = "";
	vector<string> arreglo;
	//proceso
	for(int i=0; i<cadena.length(); i++){
		if(cadena[i] == separador){
			arreglo.push_back(aux);
			aux = "";
		}else{
			aux += cadena[i];
		}
	}
	arreglo.push_back(aux);
	return arreglo;
}

int VinculoDB::ToInt(string p_num){
	//variable local
	stringstream convert;
	int num;
	//proceso
	convert<<p_num;
	convert>>num;
	return num;
}

string VinculoDB::ToString(int p_num){
	//variable local
	stringstream convert;
	//proceso
	convert<<p_num;
	return convert.str();
}

int VinculoDB::getMaxID(){
	fstream archivo,apoyo;
	string aux;
	int indice = 0;
	string ruta = "C:\\DatoInfo\\" + Nombre;
	archivo.open(ruta.c_str(),ios::in);
	if(!archivo.is_open()){//valido que el archivo No esta abierto
		apoyo.open(ruta.c_str(),ios::out);//crea el archivo, si no existe
		apoyo.close();
		archivo.open(ruta.c_str(),ios::in);
	}

	getline(archivo,aux);
	if(aux != ""){
		while(archivo.good()){
			getline(archivo,aux);
			indice++;
		}
		return indice;
	}
	archivo.close();
	return 1;
}

//implementacion de Provincia
Provincia::Provincia(string p_nombre):VinculoDB("ProvinciaDB.txt"){
	if(!Busg(p_nombre)){
		ProvID = getMaxID();
		Nombre = p_nombre;
	}
	Leer();
}

void Provincia::AsignarEstado(vector<string> p_campos){
	ProvID = ToInt(p_campos[0]);
	Nombre = p_campos[1];
}

bool Provincia::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Provincia::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;	
}

bool Provincia::Grabar(){
	Entity Check = Entity("Provincia");
	int begineCont = Data.size();
	string NewRegistro = ToString(ProvID) + ",";
	NewRegistro += Nombre;
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Provincia::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Municipio
Municipio::Municipio(string p_nombre, int p_prov_id):VinculoDB("MunicipioDB.txt"){
	MunicID = getMaxID();
	Nombre = p_nombre;
	ProvID = new Provincia("");
	ProvID->Busg(p_prov_id);
	Leer();
}

void Municipio::AsignarEstado(vector<string> p_campos){
	MunicID = ToInt(p_campos[0]);
	Nombre = p_campos[1];
	ProvID->Busg(ToInt(p_campos[2]));
}

bool Municipio::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Municipio::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Municipio::Grabar(){
	Entity Check = Entity("Municipio");
	int begineCont = Data.size();
	string NewRegistro = ToString(MunicID) + ",";
	NewRegistro += Nombre;
	NewRegistro += ToString(ProvID->getID());
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Municipio::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Sector
Sector::Sector(string p_nombre, int p_munic_id):VinculoDB("SectorDB.txt"){
	SectID = getMaxID();
	Nombre = p_nombre;
	MunicID = new Municipio("",1);
	MunicID->Busg(p_munic_id);
	Leer();
}

void Sector::AsignarEstado(vector<string> p_campos){
	SectID = ToInt(p_campos[0]);
	Nombre = p_campos[1];
	MunicID->Busg(ToInt(p_campos[2]));
}

bool Sector::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Sector::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Sector::Grabar(){
	Entity Check = Entity("Sector");
	int begineCont = Data.size();
	string NewRegistro = ToString(SectID) + ",";
	NewRegistro += Nombre;
	NewRegistro += ToString(MunicID->getID());
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Sector::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Direccion
Direccion::Direccion(string p_descrip, int _secID):VinculoDB("DireccionDB.txt"){
	DirecID = getMaxID();
	Descripcion = p_descrip;
	SecID = new Sector("",1);
	SecID->Busg(_secID);
	Leer();
}

void Direccion::AsignarEstado(vector<string> p_campos){
	DirecID = ToInt(p_campos[0]);
	Descripcion = p_campos[1];
	SecID->Busg(ToInt(p_campos[2]));
}

bool Direccion::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Direccion::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Direccion::Grabar(){
	Entity Check = Entity("Direccion");
	int begineCont = Data.size();
	string NewRegistro = ToString(DirecID) + ",";
	NewRegistro += Descripcion + ",";
	NewRegistro += ToString(SecID->getID());
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Direccion::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Marca
Marca::Marca(string p_nombre, string p_year):VinculoDB("Marca.txt"){
	MarcaID = getMaxID();
	Marc_Nombre = p_nombre;
	Marc_Year = p_year;
	Leer();
}

void Marca::AsignarEstado(vector<string> p_campos){
	MarcaID = ToInt(p_campos[0]);
	Marc_Nombre = p_campos[1];
	Marc_Year = p_campos[2];
}

bool Marca::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Marca::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Marca::Grabar(){
	Entity Check = Entity("Marca");
	int begineCont = Data.size();
	string NewRegistro = ToString(MarcaID) + ",";
	NewRegistro += Marc_Nombre + ",";
	NewRegistro += Marc_Year;
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Marca::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Modelo
Modelo::Modelo(string p_nombre, string p_year, int p_marca_id):VinculoDB("ModeloDB.txt"){
	ModeloID = getMaxID();
	Mod_Nombre = p_nombre;
	Mod_Year = p_year;
	MarcaID = new Marca("","");
	MarcaID->Busg(p_marca_id);
	Leer();
}

void Modelo::AsignarEstado(vector<string> p_campos){
	ModeloID = ToInt(p_campos[0]);
	Mod_Nombre = p_campos[1];
	Mod_Year = p_campos[2];
	MarcaID->Busg(ToInt(p_campos[3]));
}

bool Modelo::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Modelo::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Modelo::Grabar(){
	Entity Check = Entity("Modelo");
	int begineCont = Data.size();
	string NewRegistro = ToString(ModeloID) + ",";
	NewRegistro += Mod_Nombre + ",";
	NewRegistro += Mod_Year + ",";
	NewRegistro += ToString(MarcaID->getID());
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Modelo::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Vehiculo
Vehiculo::Vehiculo(int p_modelo, string p_year, string p_placa, string p_color):VinculoDB("Vehiculo.txt"){
	VehID = getMaxID();
	ModeloID = new Modelo("","",1);
	ModeloID->Busg(p_modelo);
	Veh_Year = p_year;
	PlacaNum = p_placa;
	Color = p_color;
	Leer();
}

void Vehiculo::AsignarEstado(vector<string> p_campos){
	ModeloID->Busg(ToInt(p_campos[0]));
	Veh_Year = p_campos[1];
	PlacaNum = p_campos[2];
	Color = p_campos[3];
}

bool Vehiculo::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Vehiculo::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Vehiculo::Grabar(){
	Entity Check = Entity("Vehiculo");
	int begineCont = Data.size();
	string NewRegistro = ToString(VehID) + ",";
	NewRegistro += ToString(ModeloID->getID()) + ",";
	NewRegistro += Veh_Year + ",";
	NewRegistro += PlacaNum;
	NewRegistro += Color;
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Vehiculo::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Licencia
Licencia::Licencia(int p_categoria, string p_fechaV):VinculoDB("LicenciaDB.txt"){
	LicID = getMaxID();
	Categoria = p_categoria;
	FechaVencimiento = p_fechaV;
	Leer();
}

void Licencia::AsignarEstado(vector<string> p_campos){
	LicID = ToInt(p_campos[0]);
	Categoria = ToInt(p_campos[1]);
	FechaVencimiento = p_campos[2];
}

bool Licencia::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Licencia::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Licencia::Grabar(){
	Entity Check = Entity("Licencia");
	int begineCont = Data.size();
	string NewRegistro = ToString(LicID) + ",";
	NewRegistro += ToString(Categoria) + ",";
	NewRegistro += FechaVencimiento;
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Licencia::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Persona
Persona::Persona(string p_oficio, string p_nombre, string p_apellido, string p_cedula, int p_licId):VinculoDB("PersonaDB.txt"){
	PersID = getMaxID();
	Oficio = p_oficio;
	Pers_Nombre = p_nombre;
	Pers_Apellido = p_apellido;
	Pers_Cedula = p_cedula;
	LicID = new Licencia(0,"");
	LicID->Busg(p_licId);
	Leer();
}

Persona::Persona(string p_oficio, string p_nombre, string p_apellido, string p_cedula):VinculoDB("PersonaDB.txt"){
	PersID = getMaxID();
	Oficio = p_oficio;
	Pers_Nombre = p_nombre;
	Pers_Apellido = p_apellido;
	Pers_Cedula = p_cedula;
	LicID = NULL;
}

void Persona::AsignarEstado(vector<string> p_campos){
	PersID = ToInt(p_campos[0]);
	Oficio = p_campos[1];
	Pers_Nombre = p_campos[2];
	Pers_Apellido = p_campos[3];
	Pers_Cedula = p_campos[4];
	if(p_campos.size() == 6){
		LicID = new Licencia(0,"");
		LicID->Busg(p_campos[5]);
	}
}

bool Persona::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Persona::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Persona::Grabar(){
	Entity Check = Entity("Persona");
	int begineCont = Data.size();
	string NewRegistro = ToString(PersID) + ",";
	NewRegistro += Oficio + ",";
	NewRegistro += Pers_Nombre + ",";
	NewRegistro += Pers_Apellido + ",";
	if(Oficio == "Chofer"){
		NewRegistro += Pers_Cedula + ",";
		NewRegistro += ToString(LicID->getID());
	}else
		NewRegistro += Pers_Cedula;	
			
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Persona::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Unidad
Unidad::Unidad(int p_veh, int p_pers):VinculoDB("UnidadDB.txt"){
	UnidID = getMaxID();
	VehID = new Vehiculo(1,"","","");
	VehID->Busg(p_veh);
	PersID = new Persona("","","","",1);
	PersID->Busg(p_pers);
	Leer();
}

void Unidad::AsignarEstado(vector<string> p_campos){
	UnidID = ToInt(p_campos[0]);
	VehID = new Vehiculo(1,"","","");
	VehID->Busg(ToInt(p_campos[1]));
	PersID = new Persona("","","","",1);
	PersID->Busg(ToInt(p_campos[2]));
}

bool Unidad::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Unidad::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Unidad::Grabar(){
	Entity Check = Entity("Unidad");
	int begineCont = Data.size();
	string NewRegistro = ToString(UnidID) + ",";
	NewRegistro += ToString(VehID->getID()) + ",";
	NewRegistro += ToString(PersID->getID());
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Unidad::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
//implementacion de Ruta
Ruta::Ruta(int p_direc_id1, int p_direc_id2, int p_unid_id, int p_pers_id, string p_fecha):VinculoDB("RutaDB.txt"){
	RutaID = getMaxID();
	PuntoInicio =  new Direccion("",1);
	PuntoInicio->Busg(p_direc_id1);;
	PuntoFinal =  new Direccion("",1);
	PuntoFinal->Busg(p_direc_id2);
	UnidID = new Unidad(1,1);
	UnidID->Busg(p_unid_id);
	PersID = new Persona("","","","",1);
	PersID->Busg(p_pers_id);
	Fecha = p_fecha;
	Leer();
}

void Ruta::AsignarEstado(vector<string> p_campos){
	RutaID = ToInt(p_campos[0]);
	PuntoInicio =  new Direccion("",1);
	PuntoInicio->Busg(ToInt(p_campos[1]));;
	PuntoFinal =  new Direccion("",1);
	PuntoFinal->Busg(ToInt(p_campos[2]));
	UnidID = new Unidad(1,1);
	UnidID->Busg(ToInt(p_campos[3]));
	PersID = new Persona("","","","",1);
	PersID->Busg(ToInt(p_campos[4]));
	Fecha = p_campos[5];
}

bool Ruta::Busg(string p_criterio){
	for(int i=0; i<Data.size(); i++){
		if(Split(Data[i],',')[1] == p_criterio){
			AsignarEstado(Split(Data[i],','));
			return true;
		}			
	}
	return false;
}

bool Ruta::Busg(int p_criterio){
	if(p_criterio <= Data.size() && p_criterio > 0){
		AsignarEstado(Split(Data[p_criterio-1],','));
		return true;
	}else
		return false;
}

bool Ruta::Grabar(){
	Entity Check = Entity("Ruta");
	int begineCont = Data.size();
	string NewRegistro = ToString(RutaID) + ",";
	NewRegistro += ToString(PuntoInicio->getID()) + ",";
	NewRegistro += ToString(PuntoFinal->getID()) + ",";
	NewRegistro += ToString(UnidID->getID()) + ",";
	NewRegistro += ToString(PersID->getID()) + ",";
	NewRegistro += Fecha;
	
	if(Check.Acceso_A_DB(Split(NewRegistro,','))){
		Escribir(NewRegistro);
		return true;
	}else
		return false;
}

bool Ruta::Leer(){
	Data = getData();
	if(Data.size() == 0)
		return false;
	else
		return true;
}
