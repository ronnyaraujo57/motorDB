#include <string>
#include <vector>
using namespace std;

class IConnection{
	private:
		string NombreBD;
	public:
		IConnection(string);
		void Agregar(string);
		vector<string[]> getData();
		vector<string[]> getData(string);
};
