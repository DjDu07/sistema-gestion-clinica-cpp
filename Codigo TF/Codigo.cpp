#include <iostream>
#include <conio.h>
#include <string>
using namespace std;
struct paciente {
	int dni;
	string nombres;
	string apellidos;
	char sexo;
	int edad;
	char adiccion;
};
struct terapia {
	int codigo;
	string nombre;
	string descripcion;
	string localizacion;
	string adiccion;
	int duracion;
	float precio;
};
struct adquisicion {
	int dni;
	int codigo;
	int fechaInicial_dia;
	int fechaInicial_mes;
	int fechaInicial_ano;
	char formaPago;
	float precio;
};
struct internamiento {
	int dni;
	int codigo;
	string localizacion;
	string fechaHora;
	string observacion;
};

//VALIDACIONES

bool esBisiesto(int ano) {
	return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

bool fechaValida(int dia, int mes, int ano) {
	if (ano < 1900 || ano > 2050) {
		return false;
	}

	if (mes < 1 || mes > 12) {
		return false;
	}

	int diasEnElMes[] = { 31, 28 + esBisiesto(ano), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (dia < 1 || dia > diasEnElMes[mes - 1]) {
		return false;
	}

	return true;
}

bool horaValida(int hora, int minuto) {
	if (hora < 0 || hora > 23) {
		return false;
	}

	if (minuto < 0 || minuto > 59) {
		return false;
	}

	return true;
}

void tecla_retornar(char tecla) {
	char opcion;
	cout << "Presione '1' para volver al menu anterior: ";
	do {
		cin >> opcion;
		if (opcion != tecla) {
			cout << "Opcion incorrecta. Presione '1' para volver al menu anterior: ";
		}
	} while (opcion != tecla);
	cout << endl;
}

void validacion_fecha(int& dia, int& mes, int& ano) {
	do {
		cout << "Fecha de inicio: " << endl;
		cout << "Ingrese dia: ";
		cin >> dia;
		cout << "Ingrese mes (1 al 12): ";
		cin >> mes;
		cout << "Ingrese ano: ";
		cin >> ano;

		if (!fechaValida(dia, mes, ano)) {
			cout << "Fecha no valida. Por favor ingrese una fecha valida." << endl;
		}
	} while (!fechaValida(dia, mes, ano));
}

void validacion_hora(int& hora, int& minuto) {
	do {
		cout << "Hora de inicio: " << endl;
		cout << "Ingrese hora: ";
		cin >> hora;
		cout << "Ingrese minuto: ";
		cin >> minuto;

		if (!horaValida(hora, minuto)) {
			cout << "Hora no valida. Por favor ingrese una hora valida." << endl;
			tecla_retornar('1');
			return;
		}
	} while (!horaValida(hora, minuto));
}

//REGISTROS DE PACIENTES

void como_agendar() {
	cout << "Para agendar una cita, debe tener en consideracion que se necesita registrar varios datos pertenecientes al paciente para manifestar la seguridad de nuestros usuarios y garantizar la legitimidad de nuestro centro" << endl;
	cout << "Para este proceso usted requiere de ingresar: DNI, nombres y apellidos, sexo, edad y el tipo de adiccion que presenta" << endl;
	tecla_retornar('1');
}

bool verificar_dni_registrado(paciente* usuarios, int num_pacientes, int dni) {
	for (int i = 0; i < num_pacientes; i++) {
		if (usuarios[i].dni == dni) {
			return true;
		}
	}
	return false;
}

void registrar(paciente* usuario, int& num_paciente) {
	int paciente_actual = num_paciente;
	int dni;
	bool dni_registrado;

	if (num_paciente == 100) {
		cout << "Ya no puede ingresar más pacientes." << endl;
		tecla_retornar('1');
	}
	else {
		cout << "Complete los siguientes espacios: " << endl;
		do {
			cout << "Ingresar su DNI (debe tener 8 digitos): ";
			cin >> dni;
			if (dni < 10000000 || dni > 99999999) {
				cout << "DNI ingresado no valido. Debe tener 8 digitos. Intente nuevamente." << endl;
			}
		} while (dni < 10000000 || dni > 99999999);

		dni_registrado = verificar_dni_registrado(usuario, num_paciente, dni);

		if (dni_registrado) {
			cout << "Este paciente ya esta registrado. Por favor ingrese un DNI diferente." << endl;
			tecla_retornar('1');
		}
		else {
			usuario[paciente_actual].dni = dni;

			cout << "Ingresar su(s) nombre(s) (separados por '_'): ";
			cin >> usuario[paciente_actual].nombres;
			cout << "Ingresar su(s) apellido(s) (separados por '_'): ";
			cin >> usuario[paciente_actual].apellidos;

			do {
				cout << "Ingresar su sexo (M: masculino, F: femenino): ";
				cin >> usuario[paciente_actual].sexo;
				if (usuario[paciente_actual].sexo != 'F' && usuario[paciente_actual].sexo != 'M') {
					cout << "Error. Ingrese 'F' o 'M'." << endl;
				}
			} while (usuario[paciente_actual].sexo != 'F' && usuario[paciente_actual].sexo != 'M');

			do {
				cout << "Ingresar edad: ";
				cin >> usuario[paciente_actual].edad;
				if (usuario[paciente_actual].edad < 10 || usuario[paciente_actual].edad > 60) {
					cout << "Edad no valida/admitida. Ingrese nuevamente." << endl;
				}
			} while (usuario[paciente_actual].edad < 10 || usuario[paciente_actual].edad > 60);

			do {
				cout << "Ingresar su adiccion (V: videojuego, D: droga, A: alcohol): ";
				cin >> usuario[paciente_actual].adiccion;
				if (usuario[paciente_actual].adiccion != 'V' && usuario[paciente_actual].adiccion != 'D' && usuario[paciente_actual].adiccion != 'A') {
					cout << "Error. Ingrese 'V', 'D' o 'A'." << endl;
				}
			} while (usuario[paciente_actual].adiccion != 'V' && usuario[paciente_actual].adiccion != 'D' && usuario[paciente_actual].adiccion != 'A');

			num_paciente++;

			cout << "FELICIDADES, ha sido registrado exitosamente." << endl;
			tecla_retornar('1');
		}
	}
}


void terapias(terapia* registro, int& num_terapia) {
	cout << "Complete los siguientes espacios: " << endl;
	int codig;
	srand(time(NULL));
	codig = rand() % (999999 - 100000 + 1) + 100000;
	cout << "Codigo generado: " << codig << endl;
	do {
		cout << "Ingrese codigo de la terapia (6 digitos): ";
		cin >> registro[num_terapia].codigo;
		if (registro[num_terapia].codigo < 100000 || registro[num_terapia].codigo > 999999) {
			cout << "Codigo ingresado no valido, debe tener 6 digitos. Intente nuevamente" << endl;
		}

	} while (registro[num_terapia].codigo < 100000 || registro[num_terapia].codigo > 999999);
	cout << "Ingrese Nombre de la Terapia (separar palabras con '_'): ";
	cin >> registro[num_terapia].nombre;
	cout << "Ingrese Descripcion de la Terapia (separar palabras con '_'): ";
	cin >> registro[num_terapia].descripcion;
	do {
		cout << "Ingrese Localizacion (H: Huancayo, A: Ayacucho, P: Puno): ";
		cin >> registro[num_terapia].localizacion;
		if (registro[num_terapia].localizacion != "H" && registro[num_terapia].localizacion != "A" && registro[num_terapia].localizacion !=
			"P") {
			cout << "Localizacion ingresada no valida. Intente nuevamente." << endl;
		}
	} while (registro[num_terapia].localizacion != "H" && registro[num_terapia].localizacion != "A" && registro[num_terapia].localizacion !=
		"P");
	do {
		cout << "Ingrese Tipo de Adiccion (V: videojuego, D: droga, A: Alcohol): ";
		cin >> registro[num_terapia].adiccion;
		if (registro[num_terapia].adiccion != "V" && registro[num_terapia].adiccion != "D" && registro[num_terapia].adiccion != "A") {
			cout << "Tipo de adiccion ingresada no valida. Intente nuevamente." << endl;
		}
	} while (registro[num_terapia].adiccion != "V" && registro[num_terapia].adiccion != "D" && registro[num_terapia].adiccion != "A");
	do {
		cout << "Ingrese Duracion de la terapia en Semanas (menos de 25): ";
		cin >> registro[num_terapia].duracion;
		if (registro[num_terapia].duracion <= 0 || registro[num_terapia].duracion > 24) {
			cout << "Duracion no valida. Debe ser entre 1 y 24 semanas. Intente nuevamente." << endl;
		}
	} while (registro[num_terapia].duracion <= 0 || registro[num_terapia].duracion > 24);
	do {
		cout << "Ingrese Precio: ";
		cin >> registro[num_terapia].precio;
		if (registro[num_terapia].precio <= 0 || registro[num_terapia].precio > 300) {
			cout << "Precio no valido. Debe ser menor a 300. Intente nuevamente." << endl;
		}
	} while (registro[num_terapia].precio <= 0 || registro[num_terapia].precio > 300);
	num_terapia++;
	cout << "Terapia registrada correctamente." << endl;
	tecla_retornar('1');
}

void mostrar_terapias_por_adiccion(terapia* registro, int num_terapia, char tipo_adic) {
	cout << "Terapias disponibles para la adiccion: " << tipo_adic << endl;
	for (int i = 0; i < num_terapia; i++) {
		if (registro[i].adiccion[0] == tipo_adic) {
			cout << "Codigo: " << registro[i].codigo << ", Nombre: " << registro[i].nombre << ", Local: " << registro[i].localizacion << ", Precio: " << registro[i].precio << endl;
		}
	}
	cout << endl;
}

bool verificar_terapia_disponible(terapia* registro, int num_terapia, int codigo_terapia) {
	for (int i = 0; i < num_terapia; i++) {
		if (registro[i].codigo == codigo_terapia) {
			return true;
		}
	}
	return false;
}

bool verificar_paciente_en_terapia(adquisicion* terap, int num_adquis, int dni) {
	for (int i = 0; i < num_adquis; i++) {
		if (terap[i].dni == dni) {
			return true;
		}
	}
	return false;
}

void adquirir(adquisicion* terap, int& num_adquis, paciente* usuario, int num_paciente, terapia* registro, int num_terapia) {
	int dni;
	cout << "Ingrese DNI del Paciente: ";
	cin >> dni;

	bool dni_registrado = verificar_dni_registrado(usuario, num_paciente, dni);
	if (!dni_registrado) {
		cout << "El paciente no está registrado. Por favor registre al paciente primero." << endl;
		tecla_retornar('1');
		return;
	}

	cout << "Seleccione el tipo de adiccion: " << endl;
	cout << "V: Videojuegos" << endl;
	cout << "D: Drogas" << endl;
	cout << "A: Alcohol" << endl;
	char tipo_adic;
	cin >> tipo_adic;

	mostrar_terapias_por_adiccion(registro, num_terapia, tipo_adic);

	int codigo_terapia;
	cout << "Ingrese el codigo de la terapia deseada: ";
	cin >> codigo_terapia;

	bool terapia_disponible = verificar_terapia_disponible(registro, num_terapia, codigo_terapia);
	if (!terapia_disponible) {
		cout << "El código de terapia ingresado no es válido o no está disponible." << endl;
		tecla_retornar('1');
		return;
	}

	if (verificar_paciente_en_terapia(terap, num_adquis, dni)) {
		cout << "El paciente ya esta en otra terapia." << endl;
		tecla_retornar('1');
		return;
	}

	float costo = 0.0;

	for (int i = 0; i < num_terapia; i++) {
		if (registro[i].codigo == codigo_terapia) {
			terapia_disponible = true;
			costo = registro[i].precio;
			break;
		}
	}


	terap[num_adquis].dni = dni;
	terap[num_adquis].codigo = codigo_terapia;
	terap[num_adquis].precio = costo;

	int dia, mes, ano;
	validacion_fecha(dia, mes, ano);
	terap[num_adquis].fechaInicial_dia = dia;
	terap[num_adquis].fechaInicial_mes = mes;
	terap[num_adquis].fechaInicial_ano = ano;

	do {
		cout << "Seleccione la forma de pago (E: Efectivo, T: Tarjeta, Y: Yape): ";
		cin >> terap[num_adquis].formaPago;
		if (terap[num_adquis].formaPago != 'E' && terap[num_adquis].formaPago != 'T' && terap[num_adquis].formaPago != 'Y') {
			cout << "Error. Ingresar una forma de pago valida" << endl;
		}
	} while (terap[num_adquis].formaPago != 'E' && terap[num_adquis].formaPago != 'T' && terap[num_adquis].formaPago != 'Y');

	cout << "SERVICIO PROCEDE" << endl;
	cout << "DNI del paciente: " << dni << endl;
	cout << "Codigo de la terapia: " << codigo_terapia << endl;
	cout << "Fecha de inicio de la terapia: " << "dia: " << terap[num_adquis].fechaInicial_dia << " \t mes: " << terap[num_adquis].fechaInicial_mes << " \t ano: " << terap[num_adquis].fechaInicial_ano << endl;
	cout << "Costo: " << terap[num_adquis].precio << endl;
	num_adquis++;
	tecla_retornar('1');
}

bool verificar_paciente_en_internamiento(internamiento* inter, int num_intern, int dni) {
	for (int i = 0; i < num_intern; i++) {
		if (inter[i].dni == dni) {
			return true;
		}
	}
	return false;
}

void internar(internamiento* inter, int& num_intern, adquisicion* terap, int& num_adquis, paciente* usuario, int& num_paciente, terapia* registro, int& num_terapia) {
	int dni;
	cout << "Ingrese DNI del Paciente: ";
	cin >> dni;

	bool paciente_registrado = false;
	for (int i = 0; i < num_paciente; i++) {
		if (usuario[i].dni == dni) {
			paciente_registrado = true;
			inter[num_intern].dni = usuario[i].dni;
			break;
		}
	}
	if (!paciente_registrado) {
		cout << "El paciente no esta registrado. Por favor registre al paciente primero." << endl;
		tecla_retornar('1');
		return;
	}

	if (verificar_paciente_en_internamiento(inter, num_intern, dni)) {
		cout << "El paciente ya esta en otro internamiento." << endl;
		tecla_retornar('1');
		return;
	}

	int codigo;
	cout << "Ingrese codigo de la Terapia: ";
	cin >> codigo;

	bool codigo_registrado = false;
	for (int i = 0; i < num_terapia; i++) {
		if (terap[i].codigo == codigo) {
			codigo_registrado = true;
			break;
		}
	}
	if (!codigo_registrado) {
		cout << "el codigo es invalido, no existe este codigo de terapia. " << endl;
		tecla_retornar('1');
		return;
	}

	do {
		cout << endl << "Ingrese Localizacion (H: Huancayo, A: Ayacucho, P: Puno): ";
		cin >> registro[num_terapia].localizacion;
		if (registro[num_terapia].localizacion != "H" && registro[num_terapia].localizacion != "A" && registro[num_terapia].localizacion !=
			"P") {
			cout << "Localizacion ingresada no valida. Intente nuevamente." << endl;
		}
	} while (registro[num_terapia].localizacion != "H" && registro[num_terapia].localizacion != "A" && registro[num_terapia].localizacion != "P");

	int dia, mes, ano, minuto, hora;
	validacion_fecha(dia, mes, ano);
	validacion_hora(hora, minuto);


	cout << "Ingrese Observacion: (separa con '_'): ";
	cin >> inter[num_intern].observacion;

	num_intern++;
	cout << "Internamiento registrado correctamente." << endl;
	tecla_retornar('1');
}

//INFORMACION DE LOS REPORTES

void Imprimir(string adiccion, float monto) {
	cout << adiccion;

	for (int i = 1; i <= (int)monto / 100; i++)
	{
		cout << "*";
	}
	cout << "(" << monto << ")" << endl;
}
void Imprimir1(string adiccion, float monto) {
	cout << adiccion;

	for (int i = 1; i <= (int)monto / 100; i++)
	{
		cout << "+";
	}
	cout << "(" << monto << ")" << endl;
}
void Imprimir2(string adiccion, float monto) {
	cout << adiccion;

	for (int i = 1; i <= (int)monto / 100; i++)
	{
		cout << "#";
	}
	cout << "(" << monto << ")" << endl;
}
void Reporte_Recaudacion_Grafico(adquisicion* terap, int& num_adquis, terapia* registro, int& num_terapia) {
	float sumaV = 0, sumaD = 0, sumaA = 0;
	for (int i = 0; i < num_adquis; i++)
	{
		for (int j = 0; j < num_terapia; j++)
		{
			if (terap[i].codigo == registro[j].codigo)
			{
				if (registro[j].adiccion == "V")
				{
					sumaV += terap[i].precio;
				}
				if (registro[j].adiccion == "D")
				{
					sumaD += terap[i].precio;
				}
				if (registro[j].adiccion == "A")
				{
					sumaA += terap[i].precio;
				}
			}
		}
	}

	cout << "El monto total recaudado de las terapias para adiccion a VIDEOJUEGOS es: " << sumaV << " soles" << endl;
	cout << "El monto total recaudado de las terapias para adiccion a DROGAS es: " << sumaD << " soles" << endl;
	cout << "El monto total recaudado de las terapias para adiccion a ALCOHOL es: " << sumaA << " soles" << endl << endl;

	cout << "Grafico de barras de los montos recaudados por tipo de adiccion:" << endl << endl;
	Imprimir("VIDEOJUEGOS: ", sumaV);
	Imprimir1("DROGAS: ", sumaD);
	Imprimir2("ALCOHOL: ", sumaA);
	cout << endl;
	cout << "Leyenda: Cada * o + o # equivale a 100 soles" << endl;
	tecla_retornar('1');
}

void Reporte_PorcentajeInternamiento_Edad(internamiento* inter, int& num_intern, paciente* usuario, int& num_paciente) {
	int cont = 0, cont1 = 0, cont2 = 0;
	for (int i = 0; i < num_intern; i++)
	{
		for (int j = 0; j < num_paciente; j++)
		{
			if (inter[i].dni == usuario[j].dni)
			{
				if (usuario[j].edad >= 10 && usuario[j].edad <= 17)
					cont++;
				else
				{
					if (usuario[j].edad <= 30)
						cont1++;
					else
					{
						if (usuario[j].edad <= 60)
							cont2++;
					}
				}
			}
		}
	}

	cout << "El porcentaje de internamientos de pacientes en el rango de edad (10-17) es: " << ((double)cont / num_intern) * 100 << "%" << endl;
	cout << "El porcentaje de internamientos de pacientes en el rango de edad (18-30) es: " << ((double)cont1 / num_intern) * 100 << "%" << endl;
	cout << "El porcentaje de internamientos de pacientes en el rango de edad (31-60) es: " << ((double)cont2 / num_intern) * 100 << "%" << endl;
	tecla_retornar('1');
}

bool verificar_terapia_adquirida(adquisicion* terap, int num_adquis, int codigo_terapia) {
	for (int i = 0; i < num_adquis; i++) {
		if (terap[i].codigo == codigo_terapia) {
			return true;
		}
	}
	return false;
}
void Reporte_ListadoDescendente_Apellido(adquisicion* terap, int& num_adquis, paciente* usuario, int& num_paciente) {
	paciente aux;
	int codigo_terapia = 0;
	bool terapia_adquirida = false;
	do {
		cout << "Ingrese el codigo de la terapia para el listado: ";
		cin >> codigo_terapia;
		terapia_adquirida = verificar_terapia_adquirida(terap, num_adquis, codigo_terapia);
		if (!terapia_adquirida) {
			cout << "Codigo de terapia no valido. Intente nuevamente." << endl;
		}
	} while (!terapia_adquirida);
	int k = 0;
	for (int i = 0; i < num_adquis; i++) {
		if (terap[i].codigo == codigo_terapia) {
			k++;
		}
	}

	paciente* temp = new paciente[k];
	int index = 0;
	for (int i = 0; i < num_adquis; i++)
	{
		if (terap[i].codigo == codigo_terapia)
		{
			for (int j = 0; j < num_paciente; j++)
			{
				if (usuario[j].dni == terap[i].dni)
				{
					temp[index] = usuario[j];
					index++;
				}
			}
		}
	}

	for (int i = 0; i < k - 1; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (temp[i].apellidos < temp[j].apellidos)
			{
				aux = temp[i];
				temp[i] = temp[j];
				temp[j] = aux;
			}
		}
	}

	cout << "Listado de los datos de los pacientes ordenados por apellido en forma descendente:" << endl << endl;
	cout << "Nombres:\t\t" << "Apellidos:\t\t" << "DNI:\t\t" << "Sexo:\t" << "Edad:\t" << "Adiccion:" << endl;
	for (int i = 0; i < k; i++)
	{
		cout << temp[i].nombres << "\t\t" << temp[i].apellidos << "\t\t" << temp[i].dni << "\t\t" << temp[i].sexo << "\t" << temp[i].edad << "\t" << temp[i].adiccion << endl;
	}
	delete[]temp;
	tecla_retornar('1');
}

void Reporte_AdquisicionesLocal_Sexo(adquisicion* terap, int& num_adquis, terapia* registro, int& num_terapia, paciente* usuario, int& num_paciente) {
	string local;
	int contF = 0, contM = 0;
	do {
		cout << "Ingrese Localizacion (H: Huancayo, A: Ayacucho, P: Puno): ";
		cin >> local;
		if (local != "H" && local != "A" && local != "P") {
			cout << "Localizacion ingresada no valida. Intente nuevamente." << endl;
		}
	} while (local != "H" && local != "A" && local != "P");

	for (int i = 0; i < num_adquis; i++)
	{
		for (int j = 0; j < num_terapia; j++)
		{
			if (terap[i].codigo == registro[j].codigo && registro[j].localizacion == local)
			{
				for (int k = 0; k < num_paciente; k++)
				{
					if (terap[i].dni == usuario[k].dni && usuario[k].sexo == 'M')
					{
						contM++;
					}
					else
						if (terap[i].dni == usuario[k].dni && usuario[i].sexo == 'F')
						{
							contF++;
						}
				}
			}
		}
	}

	cout << "El numero de adquisiciones en el local " << local << " por sexo MASCULINO es: " << contM << endl;
	cout << "El numero de adquisiciones en el local " << local << " por sexo FEMENINO es: " << contF << endl;
	tecla_retornar('1');
}

void Reporte_MayorIntern_Sexo(internamiento* inter, int& num_intern, paciente* usuario, int& num_paciente) {
	int contM = 0, contF = 0;
	for (int i = 0; i < num_intern; i++)
	{
		for (int j = 0; j < num_paciente; j++)
		{
			if (inter[i].dni == usuario[j].dni)
			{
				if (usuario[j].sexo == 'M')
				{
					contM++;
				}
				if (usuario[j].sexo == 'F')
				{
					contF++;
				}
			}
		}
	}
	if (contM > contF)
	{
		cout << "El mayor numero de internamientos registrados es de personas del sexo MASCULINO" << endl;
	}
	if (contM == contF)
	{
		cout << "El numero de internamientos registrados es igual entre personas del sexo MASCULINO y del FEMENINO" << endl;
	}
	if (contM < contF)
	{
		cout << "El mayor numero de internamientos registrados es de personas del sexo FEMENINO" << endl;
	}
	tecla_retornar('1');
}

void Reporte_PromedioEdad_Local(adquisicion* terap, int& num_adquis, terapia* registro, int& num_terapia, paciente* usuario, int& num_paciente) {
	int sumaH = 0, sumaA = 0, sumaP = 0, contH = 0, contA = 0, contP = 0;
	double promedioH = 0, promedioA = 0, promedioP = 0;
	for (int i = 0; i < num_adquis; i++)
	{
		for (int j = 0; j < num_terapia; j++)
		{
			if (terap[i].codigo == registro[j].codigo);
			{
				for (int k = 0; k < num_paciente; k++)
				{
					if (terap[i].dni == usuario[k].dni)
					{
						if (registro[j].localizacion == "H")
						{
							sumaH += usuario[k].edad;
							contH++;
						}
						if (registro[j].localizacion == "A")
						{
							sumaA += usuario[k].edad;
							contA++;
						}
						if (registro[j].localizacion == "P")
						{
							sumaP += usuario[k].edad;
							contP++;
						}
					}
				}
			}
		}
	}

	if (contH > 0)
	{
		promedioH = (double)sumaH / contH;
	}
	if (contA > 0)
	{
		promedioA = (double)sumaA / contA;
	}
	if (contP > 0)
	{
		promedioP = (double)sumaP / contP;
	}

	cout << "El promedio de edad de los pacientes registrados en terapias en el local de HUANCAYO es de " << promedioH << " anos" << endl;
	cout << "El promedio de edad de los pacientes registrados en terapias en el local de AYACUCHO es de " << promedioA << " anos" << endl;
	cout << "El promedio de edad de los pacientes registrados en terapias en el local de PUNO es de " << promedioP << " anos" << endl;
	tecla_retornar('1');
}

//MENUS SECUNDARIOS

void informacion(paciente* usuario, int& num_paciente, terapia* registro, int& num_terapia, adquisicion* terap, int& num_adquis, internamiento* inter, int& num_intern) {
	int opc;
	do {
		cout << "1. Como agendar una cita?" << endl;
		cout << "2. Ingresar aqui para registrarse como usuario" << endl;
		cout << "3. Ingresar aqui para confirmar la adquisicion de terapias" << endl;
		cout << "4. Ingresar aqui para acceder al internamiento en el centro" << endl;
		cout << "5. Salir" << endl;
		cout << "Escoger una opcion: ";
		cin >> opc;
		switch (opc) {
		case 1:
			como_agendar();
			break;
		case 2:
			registrar(usuario, num_paciente);
			break;
		case 3:
			adquirir(terap, num_adquis, usuario, num_paciente, registro, num_terapia);
			break;
		case 4:
			internar(inter, num_intern, terap, num_adquis, usuario, num_paciente, registro, num_terapia);
			break;
		case 5:
			return;
			break;
		}
	} while (opc != 5);
}

void datos(paciente* usuario, int& num_paciente, terapia* registro, int& num_terapia, adquisicion* terap, int& num_adquis, internamiento* inter, int& num_intern) {
	int opc;
	do {
		cout << "1. Registrar codigos de terapias" << endl;
		cout << "2. Reporte de recaudacion " << endl;
		cout << "3. Reporte de porcentaje de internamientos de pacientes por rangos de edad " << endl;
		cout << "4. Reporte de listado de los datos de pacientes atendidos en una terapia especifica, ordenado de forma descendente por apellido " << endl;
		cout << "5. Reporte de numero de adquisiciones por sexo en un local especifico " << endl;
		cout << "6. Reporte del mayor numero de internamientos de pacientes segun el sexo (M o F). " << endl;
		cout << "7. Reporte del promedio de edad de pacientes registrados en las terapias por cada local (Huancayo, Ayacucho y Puno). " << endl;
		cout << "8. Salir" << endl;
		cout << "Escoger una opcion: ";
		cin >> opc;
		switch (opc) {
		case 1:
			terapias(registro, num_terapia);
			break;
		case 2:
			if (num_adquis > 0)
			{
				Reporte_Recaudacion_Grafico(terap, num_adquis, registro, num_terapia);
			}
			else
				cout << "No se encontro registro de adquisiciones. POR FAVOR, ingrese los datos de adquisicion de terapia de un paciente primero." << endl << endl;
			break;
		case 3:
			if (num_intern > 0)
			{
				Reporte_PorcentajeInternamiento_Edad(inter, num_intern, usuario, num_paciente);
			}
			else
				cout << "No se encontro registro de internamientos. POR FAVOR, ingrese los datos de internamiento de un paciente primero." << endl << endl;
			break;
		case 4:
			if (num_adquis > 0)
			{
				Reporte_ListadoDescendente_Apellido(terap, num_adquis, usuario, num_paciente);
			}
			else
				cout << "No se encontro registro de adquisiciones. POR FAVOR, ingrese los datos de adquisicion de terapia de un paciente primero." << endl << endl;
			break;
		case 5:
			if (num_adquis > 0)
			{
				Reporte_AdquisicionesLocal_Sexo(terap, num_adquis, registro, num_terapia, usuario, num_paciente);
			}
			else
				cout << "No se encontro registro de adquisiciones. POR FAVOR, ingrese los datos de adquisicion de terapia de un paciente primero." << endl << endl;
			break;
		case 6:
			if (num_intern > 0)
			{
				Reporte_MayorIntern_Sexo(inter, num_intern, usuario, num_paciente);
			}
			else
				cout << "No se encontro registro de internamientos. POR FAVOR, ingrese los datos de internamiento de un paciente primero." << endl << endl;
			break;
		case 7:
			if (num_adquis > 0)
			{
				Reporte_PromedioEdad_Local(terap, num_adquis, registro, num_terapia, usuario, num_paciente);
			}
			else
				cout << "No se encontro registro de adquisiciones. POR FAVOR, ingrese los datos de adquisicion de terapia de un paciente primero." << endl << endl;
			break;
		case 8:
			return;
			break;
		}
	} while (opc != 8);
	cout << endl;
}

//MENU PRINCIPAL

int main() {
	int N = 10;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			cout << " ";
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			cout << char(220);
		}
		cout << endl;
	}
	cout << "";
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < N - i - 1; j++) {
			cout << " ";
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			cout << char(220);
		}
		cout << endl;
	}
	paciente* usuario = new paciente[100];
	terapia* registro = new terapia[100];
	adquisicion* terap = new adquisicion[100];
	internamiento* inter = new internamiento[100];
	int num_paciente = 0, num_terapia = 0, num_adquis = 0, num_intern = 0;
	int menu;
	int presentacion;
	do {
		cout << "Asignacion: Fundamentos de Programacion" << endl;
		cout << "Ciclo Academico: 2024-I \t Docente: Lourdes Hilda Toledo Aller" << endl;
		cout << "Integrantes: " << endl;
		cout << "*Diego Alberto Aquino Chaccara (u202412440)" << endl;
		cout << "*Diego Joaquin Diaz Urday (u202410099)" << endl;
		cout << "Presionar '1' para comenzar, '2' para salir" << endl;
		cin >> presentacion;
		switch (presentacion) {
		case 1:
			do {
				cout << "Clinica Psicologica: Volver a vivir" << endl;
				cout << "1. Informacion de cliente" << endl;
				cout << "2. Acceder como administrador" << endl;
				cout << "3. Salir" << endl;
				cout << "Escoger una opcion: ";
				cin >> menu;
				switch (menu) {
				case 1:
					informacion(usuario, num_paciente, registro, num_terapia, terap, num_adquis, inter, num_intern);
					break;
				case 2:
					datos(usuario, num_paciente, registro, num_terapia, terap, num_adquis, inter, num_intern);
					break;
				case 3:
					delete[] usuario;
					delete[] registro;
					delete[] terap;
					delete[] inter;
					break;
				}
			} while (menu != 3);
			break;
		case 2:
			return 0;
			break;
		}
	} while (presentacion != 2);
	_getch();
	return 0;
}