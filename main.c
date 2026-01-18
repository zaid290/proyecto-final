#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[ZONAS];
    int opcion;
    int datosIngresados = 0;
    int prediccionRealizada = 0;

    inicializarZonas(zonas);

    do {
        printf("\n\n===== MENU PRINCIPAL =====");
        printf("\n1. Ingresar datos actuales");
        printf("\n2. Mostrar datos actuales");
        printf("\n3. Calcular promedios historicos");
        printf("\n4. Predecir contaminacion");
        printf("\n5. Mostrar alertas");
        printf("\n6. Mostrar recomendaciones");
        printf("\n7. Generar reporte");
        printf("\n0. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatosActuales(zonas);
                datosIngresados = 1;
                break;

            case 2:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    mostrarDatosActuales(zonas);
                break;

            case 3:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    calcularPromediosHistoricos(zonas);
                break;

            case 4:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else {
                    predecirContaminacion(zonas);
                    prediccionRealizada = 1;
                }
                break;

            case 5:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    mostrarAlertas(zonas);
                break;

            case 6:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    generarRecomendaciones(zonas);
                break;

            case 7:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    generarReporte(zonas);
                break;

            case 0:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
//gcc main.c funciones.c -o ambiente.exe
//./ambiente.exe