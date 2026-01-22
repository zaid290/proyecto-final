#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[ZONAS];
    int opcion;
    int datosIngresados = 0;
    int prediccionRealizada = 0;
    char nombreArchivoReporte[100];

    inicializarZonas(zonas);
    cargarHistoricoDesdeArchivo(zonas, "historico.dat");

    do {
        printf("\n\n===== MENU PRINCIPAL - SISTEMA DE CONTAMINACION =====");
        printf("\n1. Ingresar datos actuales de contaminacion");
        printf("\n2. Ingresar factores climaticos");
        printf("\n3. Mostrar datos actuales");
        printf("\n4. Actualizar historico diario");
        printf("\n5. Calcular promedios historicos (30 dias)");
        printf("\n6. Mostrar historico completo");
        printf("\n7. Predecir contaminacion (proximas 24h)");
        printf("\n8. Mostrar prediccion");
        printf("\n9. Mostrar alertas");
        printf("\n10. Mostrar recomendaciones");
        printf("\n11. Generar reporte en pantalla");
        printf("\n12. Guardar reporte en archivo");
        printf("\n13. Guardar historico en archivo");
        printf("\n14. Generar 29 dias aleatorios e ingresar dia 30 manualmente");
        printf("\n0. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatosActuales(zonas);
                datosIngresados = 1;
                break;

            case 2:
                if (!datosIngresados) {
                    printf("Debe ingresar primero los datos actuales.\n");
                } else {
                    ingresarFactoresClimaticos(zonas);
                }
                break;

            case 3:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    mostrarDatosActuales(zonas);
                break;

            case 4:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    actualizarHistorico(zonas);
                break;

            case 5:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    calcularPromediosHistoricos(zonas);
                break;

            case 6:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else
                    mostrarHistorico(zonas);
                break;

            case 7:
                if (!datosIngresados)
                    printf("Debe ingresar primero los datos actuales.\n");
                else {
                    predecirContaminacion(zonas);
                    prediccionRealizada = 1;
                }
                break;

            case 8:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    mostrarPrediccion(zonas);
                break;

            case 9:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    mostrarAlertas(zonas);
                break;

            case 10:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    generarRecomendaciones(zonas);
                break;

            case 11:
                if (!prediccionRealizada)
                    printf("Debe realizar primero la prediccion.\n");
                else
                    generarReporte(zonas);
                break;

            case 12:
                if (!prediccionRealizada) {
                    printf("Debe realizar primero la prediccion.\n");
                } else {
                    printf("Ingrese nombre del archivo (ej: reporte.txt): ");
                    scanf("%99s", nombreArchivoReporte);
                    guardarReporteEnArchivo(zonas, nombreArchivoReporte);
                }
                break;

            case 13:
                printf("Ingrese nombre del archivo (ej: historico.dat): ");
                scanf("%99s", nombreArchivoReporte);
                guardarHistoricoEnArchivo(zonas, nombreArchivoReporte);
                break;

            case 14:
                generarDatos29YIngresar30(zonas);
                datosIngresados = 1;
                break;

            case 0:
                printf("Guardando datos antes de salir...\n");
                guardarHistoricoEnArchivo(zonas, "historico.dat");
                printf("Saliendo del sistema\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
//gcc main.c funciones.c -o ambiente.exe
//./ambiente.exe
