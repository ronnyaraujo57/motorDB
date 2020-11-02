#include "SystemCatalog_lib.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

//implementacion de funciones auxiliares
vector<string> Split(string cadena, char separador){
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

int ToInt(string p_num){
	//variable local
	stringstream convert;
	int num;
	try{
		convert<<p_num;
		convert>>num;
		return num;
	}catch(...){
		return -1;
	}
}

bool ValidarFecha(string p_fecha){
	//variables locales
	string aux = "";
	string arreglo[3];
	int cont = 0;
	//proceso
	for(int i=0; i<p_fecha.length(); i++){
		if(p_fecha[i] == '/' || p_fecha[i] == '-'){
			arreglo[cont] = aux;
			aux = "";
			cont++;
		}else{
			aux += p_fecha[i];
		}
	}
	arreglo[cont] = aux;
	if(arreglo[0].length() == 2 & arreglo[1].length() == 2 & arreglo[2].length() == 4)
		return true;
	else
		return false;	
}

//implementacion de la Clase Colums
Colums::Colums(int p_ID,  int p_entityID, string p_nombre, string p_type){
	ID = p_ID;
	EntityID = p_entityID;
	Nombre = p_nombre;
	Type = p_type;
}

int Colums::getID(){
	return ID;
}

int Colums::getEntityID(){
	return EntityID;
}

string Colums::getNombre(){
	return Nombre;
}

string Colums::getType(){
	return Type;
}

//implementacion de la Clase Entity
Entity::Entity(string nombre){
	LeerCSV();	
	if(Busg(nombre))
		loadColums();
}

void Entity::Alta(vector<string> columnas){
	//fuera de sevicio
}

void Entity::Baja(string PK){
	//fuera de sevicio
}

bool Entity::Busg(string Criterio){
	vector<string> aux;
	for(int i=0; i<Data.size(); i++){
		aux = Split(Data[i],',');
		if(aux[1] == Criterio){
			AsignarEstados(Data[i]);
			return true;
		}
	}
	return false;
}

bool Entity::Acceso_A_DB(vector<string> p_datos){
	int correctas = 0;
	string aux,aux1;
	Colums columna = Colums(1,1,"","");
	for(int i=0; i<AllColums.size(); i++){
		columna = AllColums[i];
		if(columna.getType() == "int" && ToInt(p_datos[i]) > 0){
			correctas++;
		}else{
			aux = p_datos[i];
			aux1 = columna.getType();
			if(aux1.substr(0,7) == "Varchar" && aux.length() <= ToInt(aux1.substr(8,2))){
				correctas++;
			}else{
				if(aux1 == "date" && ValidarFecha(p_datos[i])){
					correctas++;
				}
			}
		}
	}
	if(correctas == AllColums.size())
		return true;
	else
		return false;
}

int Entity::getID(){
	return ID;
}

string Entity::getNombre(){
	return Nombre;
}

bool Entity::LeerCSV(){
	fstream lectura0;
	string aux;
	try{
		lectura0.open("C:\\DatoInfo\\SystemCatalog\\SystemEntity.csv",ios::in);
		if(!lectura0.is_open())//valido que el archivo esta abierto
			throw 'x';//provoco una exepcion si no lo esta
			
		while(lectura0.good()){
			getline(lectura0,aux);
			Data.push_back(aux);//cargo los datos en mi vector
		}
		lectura0.close();
		return true;
	}catch(...){
		return false;
	}
}
void Entity::loadColums(){
	fstream lectura1;
	string aux;
	vector<string> aux2;
	try{
		lectura1.open("C:\\DatoInfo\\SystemCatalog\\SystemColums.csv",ios::in);
		if(!lectura1.is_open())//valido que el archivo esta abierto
			throw 'x';//provoco una exepcion si no lo esta
			
		while(lectura1.good()){
			getline(lectura1,aux);
			aux2 = Split(aux,',');
			if(ToInt(aux2[1]) == ID)//filtro las columnas que pertenecen a esta tabla
				AllColums.push_back(Colums(ToInt(aux2[0]),ToInt(aux2[1]),aux2[2],aux2[3]));
		}
		lectura1.close();
	}catch(...){
	}
}

void Entity::AsignarEstados(string p_campos){
	//variable local
	vector<string> campos = Split(p_campos,',');
	//asignando
	ID = ToInt(campos[0]);
	Nombre = campos[1];
}
//implementacion de la Clase PK
PK::PK(int p_entityID, int p_columsID){
	EntityID = p_entityID;
	ColumsID = p_columsID;
}

int PK::getID(){
	return ID;
}

int PK::getEntityID(){
	return EntityID;
}

int PK::getColumsID(){
	return ColumsID;
}
//implementacion de la Clase FK
FK::FK(int p_entity_padre, int p_entity_hijo, int p_colums_padre, int p_colums_hijo){
	EntityPadreID = p_entity_padre;
	EntityHijoID = p_entity_hijo;
	ColumsPadreID = p_colums_padre;
	ColumsHijoID = p_colums_hijo;
}

int FK::getID(){
	return ID;
}

int FK::getEntityPadreID(){
	return EntityPadreID;
}

int FK::getEntityHijoID(){
	return EntityHijoID;
}

int FK::getColumsPadreID(){
	return ColumsPadreID;
}

int FK::getColumsHijoID(){
	return ColumsHijoID;
}
