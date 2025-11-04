#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_CONDUCTORES = 10;
const int MAX_VIAJES = 10;

// Validar que un valor sea positivo
double validarDato(const string& mensaje) {
    double valor;
    do {
        cout << mensaje;
        cin >> valor;
        if (valor < 0) {
            cout << "Error: El valor no puede ser negativo. Intente de nuevo.\n";
        }
    } while (valor < 0);
    return valor;
}

// Calcular el total ganado por conductor
double calcularTotal(double distancias[], double costos[], int numViajes) {
    double total = 0;
    for (int i = 0; i < numViajes; i++) {
        total += distancias[i] * costos[i];
    }
    return total;
}

// Calcular el promedio de distancia recorrida
double promedioDistancia(double distancias[], int numViajes) {
    if (numViajes == 0) return 0;
    double suma = 0;
    for (int i = 0; i < numViajes; i++) {
        suma += distancias[i];
    }
    return suma / numViajes;
}

int main() {
    int cantidadConductores;
    string nombres[MAX_CONDUCTORES];
    int numViajes[MAX_CONDUCTORES];
    double distancias[MAX_CONDUCTORES][MAX_VIAJES];
    double costos[MAX_CONDUCTORES][MAX_VIAJES];
    double totales[MAX_CONDUCTORES];
    double promedios[MAX_CONDUCTORES];

    // Entrada de cantidad de conductores
    do {
        cout << "Ingrese la cantidad de conductores (maximo " << MAX_CONDUCTORES << "): ";
        cin >> cantidadConductores;
        if (cantidadConductores <= 0 || cantidadConductores > MAX_CONDUCTORES) {
            cout << "Cantidad invalida. Intente de nuevo.\n";
        }
    } while (cantidadConductores <= 0 || cantidadConductores > MAX_CONDUCTORES);

    // Entrada de datos de cada conductor
    for (int i = 0; i < cantidadConductores; i++) {
        cout << "\nConductor #" << (i + 1) << "\n";
        cout << "Nombre: ";
        cin >> nombres[i];

        // Número de viajes
        do {
            cout << "Numero de viajes realizados (maximo " << MAX_VIAJES << "): ";
            cin >> numViajes[i];
            if (numViajes[i] < 0 || numViajes[i] > MAX_VIAJES) {
                cout << "Cantidad invalida. Intente de nuevo.\n";
            }
        } while (numViajes[i] < 0 || numViajes[i] > MAX_VIAJES);

        // Datos de cada viaje
        for (int j = 0; j < numViajes[i]; j++) {
            cout << " Viaje #" << (j + 1) << "\n";
            distancias[i][j] = validarDato("  Distancia (km): ");
            costos[i][j] = validarDato("  Costo por km: ");
        }

        totales[i] = calcularTotal(distancias[i], costos[i], numViajes[i]);
        promedios[i] = promedioDistancia(distancias[i], numViajes[i]);
    }

    // Determinar conductor con mayor ingreso
    int idxMayorIngreso = 0;
    double mayorIngreso = totales[0];
    for (int i = 1; i < cantidadConductores; i++) {
        if (totales[i] > mayorIngreso) {
            mayorIngreso = totales[i];
            idxMayorIngreso = i;
        }
    }

    // Salida: tabla resumen
    cout << "\nResumen de conductores:\n";
    cout << left << setw(15) << "Nombre"
        << setw(15) << "Total Ganado"
        << setw(20) << "Promedio Distancia\n";
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < cantidadConductores; i++) {
        cout << left << setw(15) << nombres[i]
            << setw(15) << fixed << setprecision(2) << totales[i]
            << setw(20) << fixed << setprecision(2) << promedios[i] << "\n";
    }
    cout << "\nEl conductor con mayor ingreso es: " << nombres[idxMayorIngreso] << "\n";
    return 0;
}