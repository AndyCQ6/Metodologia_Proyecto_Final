#include <iostream>
#include <string>

using namespace std;

// 1. Estructura requerida
struct Producto {
    string nombre;
    float precio;
    int cantidad;
};

// Constante para el tamaño máximo del arreglo
const int MAX_PROD = 100;

// Prototipos de funciones
void registrarProductos(Producto productos[], int &cantidadActual);
void mostrarProductos(const Producto productos[], int cantidadActual);
void ordenarProductosBurbuja(Producto productos[], int cantidadActual);   // Ordenará por PRECIO
void ordenarProductosSeleccion(Producto productos[], int cantidadActual); // Ordenará por NOMBRE
void ordenarProductosInsercion(Producto productos[], int cantidadActual); // Ordenará por CANTIDAD
void buscarProducto(const Producto productos[], int cantidadActual);
void actualizarProducto(Producto productos[], int cantidadActual);
void generarReporte(const Producto productos[], int cantidadActual);

int main() {
    Producto inventario[MAX_PROD]; 
    int cantidadProductos = 0;     
    int opcion;

    do {
        // Menú Principal
        cout << "\n===== SISTEMA BASICO DE GESTION DE PRODUCTOS =====" << endl;
        cout << "1. Registrar productos" << endl;
        cout << "2. Mostrar productos" << endl;
        cout << "3. Ordenar productos" << endl;
        cout << "4. Buscar producto" << endl;
        cout << "5. Actualizar producto" << endl;
        cout << "6. Generar reporte final" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarProductos(inventario, cantidadProductos);
                break;
            case 2:
                mostrarProductos(inventario, cantidadProductos);
                break;
            case 3:
                if (cantidadProductos > 0) {
                    int metodo;
                    cout << "\nSeleccione criterio de ordenamiento:" << endl;
                    cout << "1. Por Precio (Metodo Burbuja)" << endl;
                    cout << "2. Por Nombre (Metodo Seleccion)" << endl;
                    cout << "3. Por Cantidad (Metodo Insercion)" << endl;
                    cout << "Opcion: ";
                    cin >> metodo;
                    
                    if (metodo == 1) ordenarProductosBurbuja(inventario, cantidadProductos);
                    else if (metodo == 2) ordenarProductosSeleccion(inventario, cantidadProductos);
                    else if (metodo == 3) ordenarProductosInsercion(inventario, cantidadProductos);
                    else cout << "Opcion no valida." << endl;
                } else {
                    cout << "No hay productos para ordenar." << endl;
                }
                break;
            case 4:
                buscarProducto(inventario, cantidadProductos);
                break;
            case 5:
                actualizarProducto(inventario, cantidadProductos);
                break;
            case 6:
                generarReporte(inventario, cantidadProductos);
                break;
            case 7:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 7);

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void registrarProductos(Producto productos[], int &cantidadActual) {
    int num;
    cout << "\nCuantos productos desea registrar? ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        if (cantidadActual >= MAX_PROD) {
            cout << "El inventario esta lleno." << endl;
            break;
        }

        cout << "\nProducto " << (cantidadActual + 1) << ":" << endl;
        cout << "Nombre: ";
        cin >> productos[cantidadActual].nombre;

        do {
            cout << "Precio: ";
            cin >> productos[cantidadActual].precio;
            if (productos[cantidadActual].precio <= 0) cout << "El precio debe ser mayor a 0." << endl;
        } while (productos[cantidadActual].precio <= 0);

        do {
            cout << "Cantidad: ";
            cin >> productos[cantidadActual].cantidad;
            if (productos[cantidadActual].cantidad < 0) cout << "La cantidad no puede ser negativa." << endl;
        } while (productos[cantidadActual].cantidad < 0);

        cantidadActual++;
    }
    cout << "Productos registrados exitosamente." << endl;
}

void mostrarProductos(const Producto productos[], int cantidadActual) {
    if (cantidadActual == 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    cout << "\n===== LISTA DE PRODUCTOS =====" << endl;
    cout << "Nombre\t\tPrecio\t\tCantidad" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < cantidadActual; i++) {
        cout << productos[i].nombre << "\t\t" 
             << productos[i].precio << "\t\t" 
             << productos[i].cantidad << endl;
    }
}

// 1. Método Burbuja -> Ordena por PRECIO
void ordenarProductosBurbuja(Producto productos[], int cantidadActual) {
    for (int i = 0; i < cantidadActual - 1; i++) {
        for (int j = 0; j < cantidadActual - i - 1; j++) {
            if (productos[j].precio > productos[j + 1].precio) {
                Producto temp = productos[j];
                productos[j] = productos[j + 1];
                productos[j + 1] = temp;
            }
        }
    }
    cout << "Productos ordenados por PRECIO (Burbuja)." << endl;
    mostrarProductos(productos, cantidadActual);
}

// 2. Método Selección -> Ordena por NOMBRE (Alfabéticamente)
void ordenarProductosSeleccion(Producto productos[], int cantidadActual) {
    for (int i = 0; i < cantidadActual - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < cantidadActual; j++) {
            // Compara cadenas strings (A < Z)
            if (productos[j].nombre < productos[min_idx].nombre)
                min_idx = j;
        }
        Producto temp = productos[min_idx];
        productos[min_idx] = productos[i];
        productos[i] = temp;
    }
    cout << "Productos ordenados por NOMBRE (Seleccion)." << endl;
    mostrarProductos(productos, cantidadActual);
}

// 3. Método Inserción -> Ordena por CANTIDAD
void ordenarProductosInsercion(Producto productos[], int cantidadActual) {
    for (int i = 1; i < cantidadActual; i++) {
        Producto key = productos[i];
        int j = i - 1;

        // Compara por cantidad
        while (j >= 0 && productos[j].cantidad > key.cantidad) {
            productos[j + 1] = productos[j];
            j = j - 1;
        }
        productos[j + 1] = key;
    }
    cout << "Productos ordenados por CANTIDAD (Insercion)." << endl;
    mostrarProductos(productos, cantidadActual);
}

void buscarProducto(const Producto productos[], int cantidadActual) {
    string nombreBusqueda;
    cout << "\nIngrese el nombre a buscar: ";
    cin >> nombreBusqueda;

    bool encontrado = false;
    for (int i = 0; i < cantidadActual; i++) {
        if (productos[i].nombre == nombreBusqueda) {
            cout << "\nProducto encontrado:" << endl;
            cout << "Nombre: " << productos[i].nombre << endl;
            cout << "Precio: " << productos[i].precio << endl;
            cout << "Cantidad: " << productos[i].cantidad << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "Producto no encontrado." << endl;
}

void actualizarProducto(Producto productos[], int cantidadActual) {
    if (cantidadActual == 0) {
        cout << "No hay productos para actualizar." << endl;
        return;
    }
    mostrarProductos(productos, cantidadActual);

    int indice;
    cout << "\nIngrese el indice del producto a actualizar (1 a " << cantidadActual << "): ";
    cin >> indice;

    int i = indice - 1;
    if (i >= 0 && i < cantidadActual) {
        int opcionActualizar;
        cout << "¿Que desea actualizar?" << endl;
        cout << "1. Precio" << endl;
        cout << "2. Cantidad" << endl;
        cout << "Opcion: ";
        cin >> opcionActualizar;

        if (opcionActualizar == 1) {
            cout << "Nuevo precio: ";
            cin >> productos[i].precio;
        } else if (opcionActualizar == 2) {
            cout << "Nueva cantidad: ";
            cin >> productos[i].cantidad;
        } else {
            cout << "Opcion invalida." << endl;
        }
        cout << "Producto actualizado." << endl;
    } else {
        cout << "Indice fuera de rango." << endl;
    }
}

// Esta es la función del REPORTE FINAL que pedías
void generarReporte(const Producto productos[], int cantidadActual) {
    if (cantidadActual == 0) {
        cout << "No hay datos para el reporte." << endl;
        return;
    }

    float valorTotalInventario = 0;
    int indiceMayorCantidad = 0;

    for (int i = 0; i < cantidadActual; i++) {
        // Cálculo del valor total
        valorTotalInventario += (productos[i].precio * productos[i].cantidad);
        
        // Búsqueda del producto con mayor stock
        if (productos[i].cantidad > productos[indiceMayorCantidad].cantidad) {
            indiceMayorCantidad = i;
        }
    }

    cout << "\n===== REPORTE FINAL =====" << endl;
    cout << "Total de productos registrados: " << cantidadActual << endl;
    cout << "Valor total en inventario: $ " << valorTotalInventario << endl;
    cout << "Producto con mayor cantidad: " << productos[indiceMayorCantidad].nombre 
         << " (" << productos[indiceMayorCantidad].cantidad << ")" << endl;
}