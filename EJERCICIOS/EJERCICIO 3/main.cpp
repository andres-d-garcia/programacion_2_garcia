#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring> // Para strcpy

using namespace std;

struct Producto {
    int id;
    char codigo[10];
    char nombre[40];
    char descripcion[200];
    int idProveedor;
    float precio; 
    int stock; 
    char fecharegistro[11]; // Cambiado a char array para la fecha
    bool activo;
};

struct Header {
    int cantidadRegistrar;
    int proximaId;
    int registrosActivos;
    int version;
};

int main(){ 
    ifstream archivo("csv_productos.csv");
    const int MAX_PRODUCTOS = 60;
    Producto* productos = new Producto[MAX_PRODUCTOS];

    if (!archivo.is_open()) {
        cout << "NO ABRIO EL ARCHIVO" << endl;
        delete[] productos;
        return 1; 
    }
    
    string linea; 
    int cantidadProductos = 0; // Cambié i a cantidadProductos para ser más claro
    
    // Saltar primera linea (cabecera)
    getline(archivo, linea);

    // Leer datos
    while (getline(archivo, linea) && cantidadProductos < MAX_PRODUCTOS) {
        if (linea.empty()) {
            continue;
        }
        
        stringstream ss(linea);
        string temp;

        // Leer ID
        getline(ss, temp, ',');
        productos[cantidadProductos].id = stoi(temp);

        // Leer código
        getline(ss, temp, ',');
        strcpy(productos[cantidadProductos].codigo, temp.c_str());

        // Leer nombre
        getline(ss, temp, ',');
        strcpy(productos[cantidadProductos].nombre, temp.c_str());

        // Leer descripción
        getline(ss, temp, ',');
        strcpy(productos[cantidadProductos].descripcion, temp.c_str());

        // Leer ID Proveedor
        getline(ss, temp, ',');
        productos[cantidadProductos].idProveedor = stoi(temp);

        // Leer precio
        getline(ss, temp, ',');
        productos[cantidadProductos].precio = stof(temp);

        // Leer stock
        getline(ss, temp, ',');
        productos[cantidadProductos].stock = stoi(temp);

        // Leer fecha
        getline(ss, temp, ',');
        strcpy(productos[cantidadProductos].fecharegistro, temp.c_str());
        
        // Establecer como activo por defecto
        productos[cantidadProductos].activo = true;

        // Mostrar datos
        cout << "ID: " << productos[cantidadProductos].id << " | ";
        cout << "COD: " << productos[cantidadProductos].codigo << " | ";
        cout << "Nombre: " << productos[cantidadProductos].nombre << " | ";
        cout << "Descripción: " << productos[cantidadProductos].descripcion << " | ";
        cout << "ID Proveedor: " << productos[cantidadProductos].idProveedor << " | ";
        cout << "Precio: " << productos[cantidadProductos].precio << " | ";
        cout << "Stock: " << productos[cantidadProductos].stock << " | ";
        cout << "Fecha: " << productos[cantidadProductos].fecharegistro << " | ";
        cout << "Activo: " << (productos[cantidadProductos].activo ? "Sí" : "No") << endl;
        
        cantidadProductos++;
    }
    
    // Crear header
    Header header;
    header.cantidadRegistrar = cantidadProductos;
    header.proximaId = cantidadProductos + 1;  // Próximo ID disponible
    header.registrosActivos = cantidadProductos;
    header.version = 1;  // Versión 1 del formato
    
    // Guardar en archivo binario
    ofstream archivoBinario("Productos.bin", ios::binary | ios::out);
    
    if (!archivoBinario.is_open()) {
        cout << "ERROR: No se pudo crear el archivo binario" << endl;
        delete[] productos;
        return 1;
    }
    
    // Guardar header
    archivoBinario.write(reinterpret_cast<const char*>(&header), sizeof(Header));
    
    // Guardar productos
    for (int j = 0; j < cantidadProductos; j++) {
        archivoBinario.write(reinterpret_cast<const char*>(&productos[j]), sizeof(Producto));
    }
    
    archivoBinario.close();
    
    cout << "\n=== RESUMEN ===" << endl;
    cout << "Total de productos leídos: " << cantidadProductos << endl;
    cout << "Archivo binario guardado: Productos.bin" << endl;
    cout << "Header guardado:" << endl;
    cout << "  - Cantidad de registros: " << header.cantidadRegistrar << endl;
    cout << "  - Próximo ID: " << header.proximaId << endl;
    cout << "  - Registros activos: " << header.registrosActivos << endl;
    cout << "  - Versión: " << header.version << endl;
    
    cout << "\n--- VERIFICANDO LECTURA DEL BINARIO ---" << endl;
    ifstream archivoLectura("Productos.bin", ios::binary | ios::in);
    
    if (archivoLectura.is_open()) {
        Header headerLeido;
        archivoLectura.read(reinterpret_cast<char*>(&headerLeido), sizeof(Header));
        
        cout << "Header leído del binario:" << endl;
        cout << "  - Cantidad de registros: " << headerLeido.cantidadRegistrar << endl;
        cout << "  - Próximo ID: " << headerLeido.proximaId << endl;
        cout << "  - Registros activos: " << headerLeido.registrosActivos << endl;
        cout << "  - Versión: " << headerLeido.version << endl;
        
        archivoLectura.close();
    }
    
    archivo.close();
    delete[] productos;
    
    return 0;
}