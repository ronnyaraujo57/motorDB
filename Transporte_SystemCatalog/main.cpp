#include <iostream>
#include "Transporte.h"
using namespace std;

//protoripos
void MenuPrincipal();
void ScreenPersona();
void ScreenRuta();
void ScreenMarca();
void ScreenModelo();
void ScreenVehiculo();
void ScreenUnidad();
void SeleccionMarca(string& _p);
void SeleccionModelo(string& _p);

int main() {
	MenuPrincipal();
	return 0;
}

//Cuerpos
void MenuPrincipal(){
	system("cls");
	int op;
	cout<<"========================"<<endl;
	cout<<"Menu Principal"<<endl;
	cout<<"========================\n"<<endl;
	cout<<"1. Nueva Ruta"<<endl;
	cout<<"2. Nueva Persona"<<endl;
	cout<<"3. Nueva Marca"<<endl;
	cout<<"4. Nuevo Modelo"<<endl;
	cout<<"5. Nuevo Vehiculo"<<endl;
	cout<<"6. Nueva Unidad"<<endl;
	cout<<"7. Salir\n>";
	cin>>op;
	switch(op){
		case 1:
			ScreenRuta();
			break;
		case 2:
			ScreenPersona();
			break;
		case 3:
			ScreenMarca();
			break;
		case 4:
			ScreenModelo();
			break;
		case 5:
			ScreenVehiculo();
			break;
		case 6:
			ScreenUnidad();
			break;
		case 7:
			break;
		default:
			cout<<endl<<"Opcion no Valida!!";
			MenuPrincipal();
			
	}
}

void ScreenPersona(){
	system("cls");
	//variables
	Persona *ObjPers;
	int op;
	string dato[4] = {"","","",""};
	string licData[2];
	//proceso
	cout<<"========================"<<endl;
	cout<<"Nueva Persona"<<endl;
	cout<<"========================\n"<<endl;
	cout<<"Oficio: [1.Chofer, 2.Cliente]\n>";
	cin>>op;
	switch(op){
		case 1:
			dato[0] = "Chofer";
			break;
		case 2:
			dato[0] = "Cliente";
			break;
		default:
			ScreenPersona();
	}
	cout<<"Nombres: "; cin>>dato[1];
	cout<<"Apellidos: "; cin>>dato[2];
	cout<<"Cedula: "; cin>>dato[3];
	if(dato[0] == "Chofer"){
		cout<<"\n(Datos Licencia)"<<endl;
		cout<<"Nivel Categoria: "; cin>>licData[0];
		cout<<"Fecha Vencimiento: "; cin>>licData[1];
		Licencia ObjLic = Licencia(ToInt(licData[0]), licData[1]);
		ObjLic.Grabar();
		ObjPers = new Persona(dato[0], dato[1], dato[2], dato[3], ObjLic.getID());
	}else{
		ObjPers = new Persona(dato[0], dato[1], dato[2], dato[3]);
	}
	cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
	cin>> op;
	switch(op){
		case 1:
			if(ObjPers->Grabar())
				cout<<"Guardado!!";
			else
				cout<<"No Pude Guardar!!";
			system("pause>nul");
			MenuPrincipal();
			break;
		case 2:
			MenuPrincipal();
			break;
		default:
			MenuPrincipal();
	}
}

void ScreenRuta(){
	system("cls");
	//variables
	Persona ObjPers = Persona("","","","");
	Unidad ObjUnd = Unidad(1,1);
	Direccion *ObjDI;
	Direccion *ObjDF;;
	Sector *ObjSec;
	Municipio *ObjMunic;
	Provincia *ObjProv;
	int op;
	string dato[5] = {"","","","",""};
	vector<string> aux;
	//proceso
	cout<<"========================"<<endl;
	cout<<"Nueva Ruta"<<endl;
	cout<<"========================\n"<<endl;
	cout<<"Direccion Inicial: "; 
	cin.ignore();
	getline(cin,dato[0]);
	cout<<"Direccion Final: "; getline(cin,dato[1]);
	cout<<"ID Unidad: "; getline(cin,dato[2]);
	cout<<"Nombre Cliente: "; getline(cin,dato[3]);
	cout<<"Fecha: "; getline(cin,dato[4]);
	//validando o creando la direccion inicial
	aux = Split(dato[0],',');
	ObjProv= new Provincia(aux[3]); ObjProv->Grabar();
	ObjMunic= new Municipio(aux[2],ObjProv->getID()); ObjMunic->Grabar();
	ObjSec = new Sector(aux[1],ObjMunic->getID()); ObjSec->Grabar();
	ObjDI = new Direccion(aux[0],ObjSec->getID()); ObjDI->Grabar();
	//validando o creando la direccion Final
	aux = Split(dato[1],',');
	ObjProv= new Provincia(aux[3]); ObjProv->Grabar();
	ObjMunic= new Municipio(aux[2],ObjProv->getID()); ObjMunic->Grabar();
	ObjSec = new Sector(aux[1],ObjMunic->getID()); ObjSec->Grabar();
	ObjDF = new Direccion(aux[0],ObjSec->getID()); ObjDI->Grabar();
	cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
	cin>> op;
	if(ObjPers.Busg(dato[3]) && ObjUnd.Busg(ToInt(dato[0]))){
		Ruta ObjRuta = Ruta(ObjDI->getID(), ObjDF->getID(), ObjUnd.getID(),ObjPers.getID(),dato[4]);
		switch(op){
			case 1:
				if(ObjUnd.Grabar())
					cout<<"Guardado!!";
				else
					cout<<"No Pude Guardar!!";
				system("pause>nul");
				MenuPrincipal();
				break;
			case 2:
				MenuPrincipal();
				break;
			default:
				MenuPrincipal();
		}
	}else{
		cout<<endl<<"La Persona o el Vehiculo no registrado!!"<<endl;
		system("pause>nul");
		MenuPrincipal();
	}
}

void ScreenMarca(){
	system("cls");
	//variables
	int op;
	string dato[2];
	//proceso
	cout<<"========================"<<endl;
	cout<<"Nueva Marca"<<endl;
	cout<<"========================\n"<<endl;
	cout<<"Nombre: ";
	cin>> dato[0];
	cout<<"Year: ";
	cin>> dato[1];
	Marca ObjMarca = Marca(dato[0], dato[1]);
	cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
	cin>> op;
	switch(op){
		case 1:
			if(ObjMarca.Grabar())
				cout<<"Guardado!!";
			else
				cout<<"No Pude Guardar!!";
			MenuPrincipal();
			break;
		case 2:
			MenuPrincipal();
			break;
		default:
			MenuPrincipal();
	}
}

void ScreenModelo(){
	system("cls");
	//variables
	int op;
	string dato[3];
	SeleccionMarca(dato[2]);
	Marca ObjMarca = Marca("", "");
	ObjMarca.Busg(dato[2]);
	//proceso
	if(dato[2] != ""){
		cout<<"========================"<<endl;
		cout<<"Nueva Modelo De "<<ObjMarca.getNombre()<<endl;
		cout<<"========================\n"<<endl;
		cout<<"Nombre: ";
		cin>> dato[0];
		cout<<"Year: ";
		cin>> dato[1];
		cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
		Modelo ObjModelo = Modelo(dato[0], dato[1], ObjMarca.getID());
		cin>> op;
		switch(op){
			case 1:
				if(ObjModelo.Grabar())
					cout<<"Guardado!!";
				else
					cout<<"No Pude Guardar!!";
					system("pause>nul");
				MenuPrincipal();
				break;
			case 2:
				MenuPrincipal();
				break;
			default:
				MenuPrincipal();
		}
	}else{
		MenuPrincipal();
	}
}

void ScreenVehiculo(){
		system("cls");
	//variables
	int op;
	string dato[4];
	SeleccionModelo(dato[3]);
	Modelo ObjModelo = Modelo("", "",1);
	ObjModelo.Busg(dato[3]);
	//proceso
	if(dato[3] != ""){
		cout<<"================================"<<endl;
		cout<<"Nueva Vehiculo De "<<ObjModelo.getNombre()<<endl;
		cout<<"================================\n"<<endl;
		cout<<"Year: ";
		cin>> dato[0];
		cout<<"Placa: ";
		cin>> dato[1];
		cout<<"Color: ";
		cin>> dato[2];
		cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
		Vehiculo ObjVeh = Vehiculo(ObjModelo.getID(), dato[0], dato[1], dato[2]);
		cin>> op;
		switch(op){
			case 1:
				if(ObjVeh.Grabar())
					cout<<"Guardado!!";
				else
					cout<<"No Pude Guardar!!";
				system("pause>nul");
				MenuPrincipal();
				break;
			case 2:
				MenuPrincipal();
				break;
			default:
				MenuPrincipal();
		}
	}else{
		MenuPrincipal();
	}
}

void ScreenUnidad(){
	system("cls");
	//variables
	Persona ObjPers = Persona("","","","");
	Vehiculo ObjVeh = Vehiculo(1,"","","");
	int op;
	string dato[2] = {"",""};
	//proceso
	cout<<"========================"<<endl;
	cout<<"Nueva Unidad"<<endl;
	cout<<"========================\n"<<endl;
	cout<<"ID Vehiculo: "; cin >>dato[0];
	cout<<"Nombre Chofer: "; cin>>dato[1];
	cout<<endl<<"Desea Guardar? [1.Si, 2.No]\n>";
	cin>> op;
	if(ObjPers.Busg(dato[1]) && ObjVeh.Busg(ToInt(dato[0]))){
		Unidad ObjUnd = Unidad(ObjPers.getID(), ObjVeh.getID());
		switch(op){
			case 1:
				if(ObjUnd.Grabar())
					cout<<"Guardado!!";
				else
					cout<<"No Pude Guardar!!";
				system("pause>nul");
				MenuPrincipal();
				break;
			case 2:
				MenuPrincipal();
				break;
			default:
				MenuPrincipal();
		}
	}else{
		cout<<endl<<"La Persona o el Vehiculo no registrado!!"<<endl;
		system("pause>nul");
		MenuPrincipal();
	}
}

void SeleccionMarca(string& _p){
	system("cls");
	//variables
	Marca ObjMarca = Marca("","");
	int aux = ObjMarca.getAllData().size();
	//proceso
	cout<<"========================"<<endl;
	cout<<"Seleccion Marca"<<endl;
	cout<<"========================\n"<<endl;
	if(aux > 0){
		for(int i=0; i<aux; i++){
			cout<<i+1<<"-"<<Split(ObjMarca.getAllData()[i],',')[1]<<endl;
		}
		cout<<"\n->"; cin>>aux;
		ObjMarca.Busg(aux);
		_p = ObjMarca.getNombre();
	}else{
		cout<<"No Hay Registros."<<endl;
		_p = "";
		system("pause>nul");
	}
	system("cls");		
}

void SeleccionModelo(string& _p){
	system("cls");
	//variables
	Modelo ObjModelo = Modelo("", "",1);
	int aux = ObjModelo.getAllData().size();
	//proceso
	cout<<"========================"<<endl;
	cout<<"Seleccion Modelo"<<endl;
	cout<<"========================\n"<<endl;
	if(aux > 0){
		for(int i=0; i<aux; i++){
			ObjModelo.Busg(i+1);
			cout<<i+1<<"-"<<ObjModelo.getNombre()<<","<<ObjModelo.getMarca().getNombre()<<endl;
		}
		cout<<"\n->"; cin>>aux;
		ObjModelo.Busg(aux);
		_p = ObjModelo.getNombre();
	}else{
		cout<<"No Hay Registros."<<endl;
		_p = "";
		system("pause>nul");
	}
	system("cls");
}
