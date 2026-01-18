#include <stdio.h>
#include "funciones.h"

void inicializarZonas(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].idZona = i + 1;
    }
}

void ingresarDatosActuales(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d\n", zonas[i].idZona);

        do {
            printf("PM2.5 (0 - 500): ");
            scanf("%f", &zonas[i].actual.pm25);
            if (zonas[i].actual.pm25 < MIN_PM25 || zonas[i].actual.pm25 > MAX_PM25)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.pm25 < MIN_PM25 || zonas[i].actual.pm25 > MAX_PM25);

        do {
            printf("NO2 (0 - 400): ");
            scanf("%f", &zonas[i].actual.no2);
            if (zonas[i].actual.no2 < MIN_NO2 || zonas[i].actual.no2 > MAX_NO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.no2 < MIN_NO2 || zonas[i].actual.no2 > MAX_NO2);

        do {
            printf("SO2 (0 - 200): ");
            scanf("%f", &zonas[i].actual.so2);
            if (zonas[i].actual.so2 < MIN_SO2 || zonas[i].actual.so2 > MAX_SO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.so2 < MIN_SO2 || zonas[i].actual.so2 > MAX_SO2);

        do {
            printf("CO2 (300 - 5000): ");
            scanf("%f", &zonas[i].actual.co2);
            if (zonas[i].actual.co2 < MIN_CO2 || zonas[i].actual.co2 > MAX_CO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.co2 < MIN_CO2 || zonas[i].actual.co2 > MAX_CO2);
    }
}

void mostrarDatosActuales(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d -> PM2.5: %.2f NO2: %.2f SO2: %.2f CO2: %.2f",
               zonas[i].idZona,
               zonas[i].actual.pm25,
               zonas[i].actual.no2,
               zonas[i].actual.so2,
               zonas[i].actual.co2);
    }
}

void calcularPromediosHistoricos(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].historico.pm25 = zonas[i].actual.pm25 * 0.9;
        zonas[i].historico.no2  = zonas[i].actual.no2  * 0.9;
        zonas[i].historico.so2  = zonas[i].actual.so2  * 0.9;
        zonas[i].historico.co2  = zonas[i].actual.co2  * 0.9;
    }
    printf("\nPromedios historicos calculados correctamente.\n");
}

void predecirContaminacion(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].prediccion.pm25 =
            zonas[i].actual.pm25 * 0.6 + zonas[i].historico.pm25 * 0.4;
        zonas[i].prediccion.no2 =
            zonas[i].actual.no2 * 0.6 + zonas[i].historico.no2 * 0.4;
        zonas[i].prediccion.so2 =
            zonas[i].actual.so2 * 0.6 + zonas[i].historico.so2 * 0.4;
        zonas[i].prediccion.co2 =
            zonas[i].actual.co2 * 0.6 + zonas[i].historico.co2 * 0.4;
    }
    printf("\nPrediccion realizada correctamente.\n");
}

const char* obtenerNivelGeneral(Zona z) {
    if (z.prediccion.pm25 > LIM_PM25 ||
        z.prediccion.no2 > LIM_NO2 ||
        z.prediccion.so2 > LIM_SO2 ||
        z.prediccion.co2 > LIM_CO2) {
        return "ROJO";
    }

    if (z.prediccion.pm25 > 0.8 * LIM_PM25 ||
        z.prediccion.no2 > 0.8 * LIM_NO2 ||
        z.prediccion.so2 > 0.8 * LIM_SO2 ||
        z.prediccion.co2 > 0.8 * LIM_CO2) {
        return "AMARILLO";
    }

    return "VERDE";
}

void mostrarAlertas(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d - Nivel de alerta: %s",
               zonas[i].idZona,
               obtenerNivelGeneral(zonas[i]));
    }
}

void generarRecomendaciones(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        int mostrar = 0;
        printf("\n\nRecomendaciones Zona %d", zonas[i].idZona);

        if (zonas[i].prediccion.pm25 > 0.8 * LIM_PM25) {
            printf("\n- Reducir actividades al aire libre");
            mostrar = 1;
        }

        if (zonas[i].prediccion.no2 > 0.8 * LIM_NO2) {
            printf("\n- Limitar trafico vehicular");
            mostrar = 1;
        }

        if (zonas[i].prediccion.so2 > LIM_SO2) {
            printf("\n- Controlar emisiones industriales");
            mostrar = 1;
        }

        if (zonas[i].prediccion.co2 > LIM_CO2) {
            printf("\n- Reducir emisiones en espacios cerrados");
            mostrar = 1;
        }

        if (!mostrar) {
            printf("\n- No se requieren acciones correctivas");
        }
    }
}

void generarReporte(Zona zonas[]) {
    printf("\n===== REPORTE GENERAL =====\n");

    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d", zonas[i].idZona);
        printf("\nActual: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
               zonas[i].actual.pm25,
               zonas[i].actual.no2,
               zonas[i].actual.so2,
               zonas[i].actual.co2);

        printf("\nHistorico: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
               zonas[i].historico.pm25,
               zonas[i].historico.no2,
               zonas[i].historico.so2,
               zonas[i].historico.co2);

        printf("\nPrediccion: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
               zonas[i].prediccion.pm25,
               zonas[i].prediccion.no2,
               zonas[i].prediccion.so2,
               zonas[i].prediccion.co2);

        printf("\nNivel de alerta: %s\n",
               obtenerNivelGeneral(zonas[i]));
    }
}
