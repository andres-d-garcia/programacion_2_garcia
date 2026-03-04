  #include <iostream>
  #include <fstream>
  #include <sstream>
  #include <string>
  #include <cstring>

  using namespace std;

  struct header{
  int cantidadderegistros;
  int proximoID;
  int registrosactivos;
  int version;
  };


  struct Producto {
      int id;
      char codigo[20];
      char nombre[50];
      char descripcion[100];
      int idProveedor;
      float precio; 
      int stock; 
      char fecharegistro[20];
      bool activo;
  };


  int main(){
      
      ifstream archivo("csv_productos.csv");
          Producto* productos = new Producto[60];
          string linea; 
          int i = 0;
          // Saltar primera linea
          getline(archivo, linea);

          // Leer datos
          while (getline(archivo, linea))
          {
              if (linea.empty()){
                  continue;
              }
              

              stringstream ss(linea);
              string temp;

              getline(ss, temp, ',');
              productos[i].id = stoi(temp);

              getline(ss, temp, ',');
              strncpy(productos[i].codigo, temp.c_str(), sizeof(productos[i].codigo) - 1);
              productos[i].codigo[sizeof(productos[i].codigo) - 1] = '\0';
              
              getline(ss, temp, ',');
              strncpy(productos[i].nombre, temp.c_str(), sizeof(productos[i].nombre) -1);
              productos[i].nombre[sizeof(productos[i].nombre) - 1] = '\0';

              getline(ss, temp, ',');
              strncpy(productos[i].descripcion, temp.c_str(), sizeof(productos[i].descripcion) -1);
              productos[i].descripcion[sizeof(productos[i].descripcion) - 1] = '\0';

              getline(ss, temp, ',');
              productos[i].idProveedor = stoi(temp);

              getline(ss, temp, ',');
              productos[i].precio = stof(temp);

              getline(ss, temp, ',');
              productos[i].stock = stoi(temp);

              getline(ss, temp, ',');
              strncpy(productos[i].fecharegistro, temp.c_str(), sizeof(productos[i].fecharegistro) -1);
              productos[i].fecharegistro[sizeof(productos[i].fecharegistro) - 1] = '\0';

              productos[i].activo=true;

              // cout << "ID: " << productos[i].id << " ";
              // cout << "COD: " << productos[i].codigo << " ";
              // cout << "Nombre: " << productos[i].nombre << " ";
              // cout << "Descripción: " << productos[i].descripcion << " ";
              // cout << "ID Proveedor: " << productos[i].idProveedor << " ";
              // cout << "Precio: " << productos[i].precio << " ";
              // cout << "Stock" << productos[i].stock << " ";
              i++;
          }
          archivo.close(); // Cerramos el CSV

      // --- CONFIGURACIÓN DEL HEADER ---
      header miHeader;
      miHeader.cantidadderegistros = i;       
      miHeader.registrosactivos = i;          
      miHeader.proximoID = i + 1;             
      miHeader.version = 1;

      // --- GUARDADO ---
ofstream archivoBinario("productos.bin", ios::binary | ios::out);

if (archivoBinario.is_open()) {
    // ¡IMPORTANTE! Primero escribimos el header
    archivoBinario.write(reinterpret_cast<char*>(&miHeader), sizeof(header));

    // Luego los productos
    for (int j = 0; j < i; j++) {
        archivoBinario.write(reinterpret_cast<char*>(&productos[j]), sizeof(Producto));
    }
    archivoBinario.close();
    cout << "\nArchivo binario guardado con exito." << endl;
}

  // 1. Abrir el archivo binario para lectura
  ifstream lecturaBin("productos.bin", ios::binary);

  if (lecturaBin.is_open()) {
    header hAux;
      lecturaBin.read(reinterpret_cast<char*>(&hAux), sizeof(header));
      
      cout << "Registros en archivo: " << hAux.cantidadderegistros << endl;

      Producto pAux;
      // .read() devuelve true si la lectura fue exitosa
      while (lecturaBin.read(reinterpret_cast<char*>(&pAux), sizeof(Producto))) {
          
          // 3. Imprimir los datos en pantalla
          cout << "ID: " << pAux.id 
              << " | Codigo: " << pAux.codigo 
              << " | Nombre: " << pAux.nombre 
              << " | Precio: $" << pAux.precio << endl;
      }

      lecturaBin.close(); // Siempre cerrar al terminar
  }

  //se libera la memoria
  delete[] productos;
  productos = nullptr;
          
          
      return 0;
  }