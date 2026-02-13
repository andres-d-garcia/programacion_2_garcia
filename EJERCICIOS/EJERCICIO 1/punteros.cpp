/*
 * EJERCICIO CLASE 1 - PUNTEROS Y MEMORIA DINÁMICA
 * ================================================
 * 
 * ENUNCIADO SIMPLIFICADO:
 * Implementar un programa que permita:
 * 1. Crear un arreglo dinámico de números enteros
 * 2. Llenar el arreglo con valores ingresados por el usuario
 * 3. Mostrar todos los números del arreglo
 * 4. Encontrar el número mayor en el arreglo
 * 5. Calcular el promedio de todos los números
 * 6. Liberar la memoria correctamente
 * 
 * REQUISITOS OBLIGATORIOS:
 * - Usar punteros y memoria dinámica (new/delete)
 * - Usar paso por referencia donde sea apropiado
 * - Validar entrada del usuario (tamaño del arreglo)
 * - Liberar toda la memoria asignada
 * - Asignar nullptr después de delete
 * 
 * FUNCIONES QUE DEBE IMPLEMENTAR:
 * 1. int* crearArreglo(int tamanio)
 * 2. void llenarArreglo(int* arreglo, int tamanio)
 * 3. void mostrarArreglo(int* arreglo, int tamanio)
 * 4. int encontrarMayor(int* arreglo, int tamanio)
 * 5. float calcularPromedio(int* arreglo, int tamanio)
 * 6. void liberarArreglo(int*& arreglo)
 * 
 * MENÚ SIMPLE:
 * 1. Crear y llenar arreglo
 * 2. Mostrar arreglo
 * 3. Encontrar número mayor
 * 4. Calcular promedio
 * 5. Salir
 * 
 * NOTAS IMPORTANTES:
 * - Validar que el tamaño del arreglo sea positivo
 * - Verificar que new no retorne nullptr
 * - Usar buenas prácticas de programación
 * - Comentar el código apropiadamente
 * 
 * CRITERIOS DE EVALUACIÓN:
 * - Correcta implementación de punteros (50%)
 * - Manejo correcto de memoria (30%)
 * - Funcionalidad del programa (20%)
 * 
 * TIEMPO ESTIMADO: 1-2 horas
 * DIFICULTAD: Básica-Medio
 */

#include <iostream>
#include <locale>
#include <iomanip>
using namespace std;

// Función para crear un arreglo dinámico
float* crearArreglo(int tamanio) {
    while (tamanio < 0) // validacion del tamaño 
    {
        cout << "Error: El tamaño debe ser positivo. Ingrese nuevamente: ";
        cin >> tamanio; 
    } 
   float *Arreglo = new float[tamanio]; // asignacion dinamica de memoria
   if (Arreglo == nullptr){
        cout << "Error: No se pudo asignar memoria para el arreglo, coloca de nuevo el tamaño." << endl;
        cin >> tamanio;
   }
   return Arreglo;
}

// Función para llenar el arreglo con valores del usuario
void llenarArreglo(float* arreglo, int tamanio) {
    if (arreglo == nullptr) {
        cout << "Error: El arreglo no ha sido creado." << endl;
        return; // Verifica que arreglo no sea nullptr
    }
    for (int i = 0; i < tamanio; i++) {
        cout << "Ingrese el valor para el elemento " << i + 1 << ": ";
        cin >> *(arreglo + i);
    } // ciclo que llena el arreglo usando punteros
}

// Función para mostrar todos los elementos del arreglo
void mostrarArreglo(float* arreglo, int tamanio) {
    if (tamanio == 0) {
        cout << "El arreglo está vacío." << endl; //verifica si el arreglo esta vacio
    } 
    if (arreglo == nullptr) {
        cout << "Error: El arreglo no ha sido creado." << endl;
        return; // Verifica que arreglo no sea nullptr
    }
    cout << "Elementos del arreglo: [";
    for(int i = 0; i < tamanio; i++) {
        cout << *(arreglo + i); // muestra el elemento usando punteros (*)
        if (i < tamanio - 1) {
            cout << ", "; // separa los elementos con coma, hasta que sea el ultimo (por eso el -1)
        }
        if (i == tamanio - 1) {
            cout << "]"; // cierra el corchete al final se coloca -1 para que se imprima al final (cuando llega a i == tamanio ya se cierra)
        }
    }
    cout << endl; 
}

// Función para encontrar el número mayor
float encontrarMayor(float* arreglo, int tamanio) {
    // TODO: Implementar esta función
    if (arreglo == nullptr || tamanio <= 0) {
        cout << "Error: El arreglo no ha sido creado o está vacío." << endl; //verifica si el arreglo es nulo o esta vacio
        return -1; // Valor de error
    }
    float mayor = *(arreglo); 
    for (int i = 0; i < tamanio; i++) {
        if (*(arreglo + i) > mayor) {
            mayor = *(arreglo + i); //itera entre todos los elementos del arreglo y actualiza el mayor mediante punteros
        }
    }
    return mayor;
}

// Función para calcular el promedio
float calcularPromedio(float* arreglo, int tamanio) {
    // TODO: Implementar esta función
    if (arreglo == nullptr || tamanio <= 0) {
        cout << "Error: El arreglo no ha sido creado o está vacío." << endl;
        return 67; // Valor de error
    }
    float suma = 0;
    for (int i = 0; i < tamanio; i++) {
        suma += *(arreglo + i); //suma todos los elementos del arreglo usando punteros
    }
    return suma / tamanio; //devuelve promedio
    }

// Función para liberar la memoria del arreglo
void liberarArreglo(float*& arreglo) {
    if (arreglo != nullptr) { //verifica que el arreglo no sea nulo para despues anularlo
        delete[] arreglo;
        arreglo = nullptr; 
    }
    else {
        cout << "El arreglo ya está liberado o no fue creado." << endl;
    }
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n=== GESTIÓN DE ARREGLOS DINÁMICOS ===" << endl;
    cout << "1. Crear y llenar arreglo" << endl;
    cout << "2. Mostrar arreglo" << endl;
    cout << "3. Encontrar número mayor" << endl;
    cout << "4. Calcular promedio" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    
    // Variables principales
    float* arreglo = nullptr;
    int tamanio = 0;
    
    cout << "=== GESTIÓN DE ARREGLOS DINÁMICOS ===" << endl;
    cout << "Implemente las funciones marcadas con TODO para completar el ejercicio." << endl;
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                // Crear y llenar arreglo
                cout << "Ingrese el tamaño del arreglo: ";
                cin >> tamanio;
                
                arreglo = crearArreglo(tamanio);
                if (arreglo != nullptr) {
                    llenarArreglo(arreglo, tamanio);
                    cout << "Arreglo creado y llenado correctamente." << endl;
                } else {
                    cout << "Error al crear el arreglo." << endl;
                }
                break;
            }
            
            case 2: {
                // Mostrar arreglo
                if (arreglo != nullptr) {
                    mostrarArreglo(arreglo, tamanio);
                } else {
                    cout << "No hay arreglo creado. Use la opción 1 primero." << endl;
                }
                break;
            }
            
            case 3: {
                // Encontrar número mayor
                if (arreglo != nullptr && tamanio > 0) {
                    int mayor = encontrarMayor(arreglo, tamanio);
                    cout << "El número mayor es: " << mayor << endl;
                } else {
                    cout << "No hay arreglo creado o está vacío." << endl;
                }
                break;
            }
            
            case 4: {
                // Calcular promedio
                if (arreglo != nullptr && tamanio > 0) {
                    float promedio = calcularPromedio(arreglo, tamanio);
                    cout << "El promedio es: " << fixed << setprecision(2) << promedio << endl;
                } else {
                    cout << "No hay arreglo creado o está vacío." << endl;
                }
                break;
            }
            
            case 5: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            
            default: {
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
            }
        }
    } while (opcion != 5);
    
    // Liberar memoria antes de salir
    liberarArreglo(arreglo);
    
    cout << "Programa finalizado. Memoria liberada." << endl;
    return 0;
}

/*
 * PISTAS PARA LA IMPLEMENTACIÓN:
 * 
 * 1. crearArreglo(int tamanio):
 *    - Verificar que tamanio > 0
 *    - Crear arreglo con: int* nuevoArreglo = new int[tamanio];
 *    - Verificar que new no retorne nullptr
 *    - Retornar puntero al arreglo
 * 
 * 2. llenarArreglo(int* arreglo, int tamanio):
 *    - Verificar que arreglo != nullptr
 *    - Usar un ciclo for para pedir valores
 *    - Usar cin para leer cada valor
 *    - Asignar a arreglo[i]
 * 
 * 3. mostrarArreglo(int* arreglo, int tamanio):
 *    - Verificar que arreglo != nullptr
 *    - Usar un ciclo for para mostrar valores
 *    - Mostrar cada elemento con cout
 * 
 * 4. encontrarMayor(int* arreglo, int tamanio):
 *    - Verificar que arreglo != nullptr y tamanio > 0
 *    - Inicializar variable mayor con arreglo[0]
 *    - Usar ciclo for para comparar con el resto
 *    - Actualizar mayor si encuentra uno más grande
 *    - Retornar mayor
 * 
 * 5. calcularPromedio(int* arreglo, int tamanio):
 *    - Verificar que arreglo != nullptr y tamanio > 0
 *    - Inicializar variable suma = 0
 *    - Usar ciclo for para sumar todos los elementos
 *    - Dividir suma entre tamanio
 *    - Retornar promedio como float
 * 
 * 6. liberarArreglo(int*& arreglo):
 *    - Verificar que arreglo != nullptr
 *    - Usar: delete[] arreglo;
 *    - Asignar: arreglo = nullptr;
 * 
 * CONCEPTOS CLAVE:
 * - new int[tamanio] crea un arreglo dinámico
 * - delete[] libera memoria de arreglos
 * - nullptr indica que un puntero no apunta a nada
 * - Paso por referencia (&) permite modificar el puntero
 * - Siempre verificar punteros antes de usar
 */
