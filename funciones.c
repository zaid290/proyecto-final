#include <stdio.h>
#include "funciones.h"
#include <stdlib.h>
#include <time.h>

void inicializarZonas(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        zonas[i].idZona = i + 1;
        zonas[i].dia_actual = 1;
        zonas[i].historico.dias_registrados = 0;
        zonas[i].historico.indice_actual = 0;
        
        for (int j = 0; j < DIAS_HISTORICO; j++) {
            zonas[i].historico.contaminantes[j].pm25 = 0;
            zonas[i].historico.contaminantes[j].no2 = 0;
            zonas[i].historico.contaminantes[j].so2 = 0;
            zonas[i].historico.contaminantes[j].co2 = 0;
            
            zonas[i].historico.factores[j].temperatura = 0;
            zonas[i].historico.factores[j].velocidad_viento = 0;
            zonas[i].historico.factores[j].humedad = 0;
        }
    }
}

void ingresarDatosActuales(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d - Dia %d\n", zonas[i].idZona, zonas[i].dia_actual);

        do {
            printf("PM2.5 (0 - 100): ");
            scanf("%f", &zonas[i].actual.pm25);
            if (zonas[i].actual.pm25 < MIN_PM25 || zonas[i].actual.pm25 > MAX_PM25)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.pm25 < MIN_PM25 || zonas[i].actual.pm25 > MAX_PM25);

        do {
            printf("NO2 (0 - 200): ");
            scanf("%f", &zonas[i].actual.no2);
            if (zonas[i].actual.no2 < MIN_NO2 || zonas[i].actual.no2 > MAX_NO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.no2 < MIN_NO2 || zonas[i].actual.no2 > MAX_NO2);

        do {
            printf("SO2 (0 - 100): ");
            scanf("%f", &zonas[i].actual.so2);
            if (zonas[i].actual.so2 < MIN_SO2 || zonas[i].actual.so2 > MAX_SO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.so2 < MIN_SO2 || zonas[i].actual.so2 > MAX_SO2);

        do {
            printf("CO2 (300 - 2000): ");
            scanf("%f", &zonas[i].actual.co2);
            if (zonas[i].actual.co2 < MIN_CO2 || zonas[i].actual.co2 > MAX_CO2)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].actual.co2 < MIN_CO2 || zonas[i].actual.co2 > MAX_CO2);
    }
}

void ingresarFactoresClimaticos(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d - Factores Climaticos (Dia %d)\n", zonas[i].idZona, zonas[i].dia_actual);

        do {
            printf("Temperatura (-10 a 50 C): ");
            scanf("%f", &zonas[i].factores_actuales.temperatura);
            if (zonas[i].factores_actuales.temperatura < MIN_TEMP || zonas[i].factores_actuales.temperatura > MAX_TEMP)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].factores_actuales.temperatura < MIN_TEMP || zonas[i].factores_actuales.temperatura > MAX_TEMP);

        do {
            printf("Velocidad del viento (0 - 50 m/s): ");
            scanf("%f", &zonas[i].factores_actuales.velocidad_viento);
            if (zonas[i].factores_actuales.velocidad_viento < MIN_VIENTO || zonas[i].factores_actuales.velocidad_viento > MAX_VIENTO)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].factores_actuales.velocidad_viento < MIN_VIENTO || zonas[i].factores_actuales.velocidad_viento > MAX_VIENTO);

        do {
            printf("Humedad (0 - 100 %%): ");
            scanf("%f", &zonas[i].factores_actuales.humedad);
            if (zonas[i].factores_actuales.humedad < MIN_HUMEDAD || zonas[i].factores_actuales.humedad > MAX_HUMEDAD)
                printf("Valor invalido. Intente nuevamente.\n");
        } while (zonas[i].factores_actuales.humedad < MIN_HUMEDAD || zonas[i].factores_actuales.humedad > MAX_HUMEDAD);
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
        printf("\n         Temp: %.2f C | Viento: %.2f m/s | Humedad: %.2f %%",
               zonas[i].factores_actuales.temperatura,
               zonas[i].factores_actuales.velocidad_viento,
               zonas[i].factores_actuales.humedad);
    }
}

float calcularPromedioContaminante(HistoricoCompleto historico, int tipo_contaminante) {
    float suma = 0;
    int dias = historico.dias_registrados > 0 ? historico.dias_registrados : 1;
    
    for (int i = 0; i < historico.dias_registrados; i++) {
        switch(tipo_contaminante) {
            case 0: suma += historico.contaminantes[i].pm25; break;
            case 1: suma += historico.contaminantes[i].no2; break;
            case 2: suma += historico.contaminantes[i].so2; break;
            case 3: suma += historico.contaminantes[i].co2; break;
        }
    }
    
    return suma / dias;
}

void actualizarHistorico(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        int indice = zonas[i].historico.indice_actual;
        
        zonas[i].historico.contaminantes[indice] = zonas[i].actual;
        zonas[i].historico.factores[indice] = zonas[i].factores_actuales;
        
        if (zonas[i].historico.dias_registrados < DIAS_HISTORICO) {
            zonas[i].historico.dias_registrados++;
        }
        
        zonas[i].historico.indice_actual = (indice + 1) % DIAS_HISTORICO;
        zonas[i].dia_actual++;
        if (zonas[i].dia_actual > DIAS_HISTORICO) {
            zonas[i].dia_actual = 1;
        }
    }
    printf("\nHistorico actualizado correctamente.\n");
}

void calcularPromediosHistoricos(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        if (zonas[i].historico.dias_registrados > 0) {
            float pm25_prom = calcularPromedioContaminante(zonas[i].historico, 0);
            float no2_prom = calcularPromedioContaminante(zonas[i].historico, 1);
            float so2_prom = calcularPromedioContaminante(zonas[i].historico, 2);
            float co2_prom = calcularPromedioContaminante(zonas[i].historico, 3);
            
            printf("\n\nZona %d - Promedios de %d dias:", zonas[i].idZona, zonas[i].historico.dias_registrados);
            printf("\nPM2.5: %.2f | NO2: %.2f | SO2: %.2f | CO2: %.2f", pm25_prom, no2_prom, so2_prom, co2_prom);
        } else {
            printf("\nZona %d - Sin datos historicos aun.\n", zonas[i].idZona);
        }
    }
    printf("\n\nPromedios historicos calculados correctamente.\n");
}

void predecirContaminacion(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        float factor_viento = 1.0 - (zonas[i].factores_actuales.velocidad_viento / MAX_VIENTO) * 0.3;
        float factor_humedad = 1.0 + (zonas[i].factores_actuales.humedad / MAX_HUMEDAD) * 0.1;
        float factor_temperatura = zonas[i].factores_actuales.temperatura > 25 ? 1.1 : 0.9;
        
        if (zonas[i].historico.dias_registrados > 0) {
            float pm25_prom = calcularPromedioContaminante(zonas[i].historico, 0);
            float no2_prom = calcularPromedioContaminante(zonas[i].historico, 1);
            float so2_prom = calcularPromedioContaminante(zonas[i].historico, 2);
            float co2_prom = calcularPromedioContaminante(zonas[i].historico, 3);
            
            zonas[i].prediccion.pm25 = (zonas[i].actual.pm25 * 0.6 + pm25_prom * 0.4) * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.no2  = (zonas[i].actual.no2 * 0.6 + no2_prom * 0.4) * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.so2  = (zonas[i].actual.so2 * 0.6 + so2_prom * 0.4) * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.co2  = (zonas[i].actual.co2 * 0.6 + co2_prom * 0.4) * factor_viento * factor_humedad * factor_temperatura;
        } else {
            zonas[i].prediccion.pm25 = zonas[i].actual.pm25 * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.no2  = zonas[i].actual.no2 * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.so2  = zonas[i].actual.so2 * factor_viento * factor_humedad * factor_temperatura;
            zonas[i].prediccion.co2  = zonas[i].actual.co2 * factor_viento * factor_humedad * factor_temperatura;
        }
    }
    printf("\nPrediccion realizada correctamente con factores climaticos.\n");
}

void mostrarPrediccion(Zona zonas[]) {
    printf("\n===== PREDICCION DE CONTAMINACION (PROXIMAS 24 HORAS) =====\n");
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona %d -> PM2.5: %.2f | NO2: %.2f | SO2: %.2f | CO2: %.2f",
               zonas[i].idZona,
               zonas[i].prediccion.pm25,
               zonas[i].prediccion.no2,
               zonas[i].prediccion.so2,
               zonas[i].prediccion.co2);
        printf("\nNivel de alerta predicho: %s", obtenerNivelGeneral(zonas[i]));
        printf("\n");
    }
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
        printf("\nDatos Actuales: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
               zonas[i].actual.pm25,
               zonas[i].actual.no2,
               zonas[i].actual.so2,
               zonas[i].actual.co2);
        
        printf("\nFactores Climaticos: Temp %.2f C | Viento %.2f m/s | Humedad %.2f %%",
               zonas[i].factores_actuales.temperatura,
               zonas[i].factores_actuales.velocidad_viento,
               zonas[i].factores_actuales.humedad);

        if (zonas[i].historico.dias_registrados > 0) {
            float pm25_prom = calcularPromedioContaminante(zonas[i].historico, 0);
            float no2_prom = calcularPromedioContaminante(zonas[i].historico, 1);
            float so2_prom = calcularPromedioContaminante(zonas[i].historico, 2);
            float co2_prom = calcularPromedioContaminante(zonas[i].historico, 3);
            
            printf("\nPromedios de %d dias: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
                   zonas[i].historico.dias_registrados, pm25_prom, no2_prom, so2_prom, co2_prom);
        }

        printf("\nPrediccion: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f",
               zonas[i].prediccion.pm25,
               zonas[i].prediccion.no2,
               zonas[i].prediccion.so2,
               zonas[i].prediccion.co2);

        printf("\nNivel de alerta: %s\n",
               obtenerNivelGeneral(zonas[i]));
    }
}

void guardarReporteEnArchivo(Zona zonas[], const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error: No se puede crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "===== REPORTE GENERAL DE CONTAMINACION DEL AIRE =====\n\n");

    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "\nZona %d\n", zonas[i].idZona);
        fprintf(archivo, "===============================================\n");
        fprintf(archivo, "Datos Actuales: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f\n",
               zonas[i].actual.pm25,
               zonas[i].actual.no2,
               zonas[i].actual.so2,
               zonas[i].actual.co2);
        
        fprintf(archivo, "Factores Climaticos: Temp %.2f C | Viento %.2f m/s | Humedad %.2f %%\n",
               zonas[i].factores_actuales.temperatura,
               zonas[i].factores_actuales.velocidad_viento,
               zonas[i].factores_actuales.humedad);

        if (zonas[i].historico.dias_registrados > 0) {
            float pm25_prom = calcularPromedioContaminante(zonas[i].historico, 0);
            float no2_prom = calcularPromedioContaminante(zonas[i].historico, 1);
            float so2_prom = calcularPromedioContaminante(zonas[i].historico, 2);
            float co2_prom = calcularPromedioContaminante(zonas[i].historico, 3);
            
            fprintf(archivo, "Promedios de %d dias: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f\n",
                   zonas[i].historico.dias_registrados, pm25_prom, no2_prom, so2_prom, co2_prom);
        }

        fprintf(archivo, "Prediccion: PM2.5 %.2f NO2 %.2f SO2 %.2f CO2 %.2f\n",
               zonas[i].prediccion.pm25,
               zonas[i].prediccion.no2,
               zonas[i].prediccion.so2,
               zonas[i].prediccion.co2);

        fprintf(archivo, "Nivel de alerta: %s\n\n",
               obtenerNivelGeneral(zonas[i]));
    }

    fclose(archivo);
    printf("Reporte guardado exitosamente en %s\n", nombreArchivo);
}

void guardarHistoricoEnArchivo(Zona zonas[], const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error: No se puede crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "===== HISTORICO DE CONTAMINACION =====\n");
    fprintf(archivo, "Zonas: %d | Dias por zona: %d\n\n", ZONAS, DIAS_HISTORICO);

    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "\nZona %d - Dias registrados: %d\n", zonas[i].idZona, zonas[i].historico.dias_registrados);
        fprintf(archivo, "Dia | PM2.5 | NO2 | SO2 | CO2 | Temp | Viento | Humedad\n");
        fprintf(archivo, "----+-------+-----+-----+-----+------+--------+--------\n");

        for (int j = 0; j < zonas[i].historico.dias_registrados; j++) {
            fprintf(archivo, "%3d | %.2f | %.2f | %.2f | %.2f | %.2f | %.2f | %.2f\n",
                   j + 1,
                   zonas[i].historico.contaminantes[j].pm25,
                   zonas[i].historico.contaminantes[j].no2,
                   zonas[i].historico.contaminantes[j].so2,
                   zonas[i].historico.contaminantes[j].co2,
                   zonas[i].historico.factores[j].temperatura,
                   zonas[i].historico.factores[j].velocidad_viento,
                   zonas[i].historico.factores[j].humedad);
        }
    }

    fclose(archivo);
    printf("Historico guardado exitosamente en %s\n", nombreArchivo);
}

void cargarHistoricoDesdeArchivo(Zona zonas[], const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Advertencia: No se encontro archivo de historico %s\n", nombreArchivo);
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), archivo);

    for (int i = 0; i < ZONAS; i++) {
        int dias_leidos = 0;
        float temp_pm25, temp_no2, temp_so2, temp_co2;
        float temp_temperatura, temp_viento, temp_humedad;
        int temp_dia;

        while (fscanf(archivo, "%d | %f | %f | %f | %f | %f | %f | %f\n",
               &temp_dia, &temp_pm25, &temp_no2, &temp_so2, &temp_co2,
               &temp_temperatura, &temp_viento, &temp_humedad) == 8 && dias_leidos < DIAS_HISTORICO) {

            zonas[i].historico.contaminantes[dias_leidos].pm25 = temp_pm25;
            zonas[i].historico.contaminantes[dias_leidos].no2 = temp_no2;
            zonas[i].historico.contaminantes[dias_leidos].so2 = temp_so2;
            zonas[i].historico.contaminantes[dias_leidos].co2 = temp_co2;

            zonas[i].historico.factores[dias_leidos].temperatura = temp_temperatura;
            zonas[i].historico.factores[dias_leidos].velocidad_viento = temp_viento;
            zonas[i].historico.factores[dias_leidos].humedad = temp_humedad;

            dias_leidos++;
        }

        zonas[i].historico.dias_registrados = dias_leidos;
        zonas[i].historico.indice_actual = dias_leidos % DIAS_HISTORICO;
    }

    fclose(archivo);
    printf("Historico cargado exitosamente desde %s\n", nombreArchivo);
}

void mostrarHistorico(Zona zonas[]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\n\nZona %d - Historico (%d dias registrados)\n", zonas[i].idZona, zonas[i].historico.dias_registrados);
        printf("========================================\n");
        printf("Dia | PM2.5  | NO2    | SO2    | CO2     | Temp   | Viento | Humedad\n");
        printf("----+--------+--------+--------+---------+--------+--------+--------\n");

        for (int j = 0; j < zonas[i].historico.dias_registrados; j++) {
            printf("%3d | %6.2f | %6.2f | %6.2f | %7.2f | %6.2f | %6.2f | %6.2f\n",
                   j + 1,
                   zonas[i].historico.contaminantes[j].pm25,
                   zonas[i].historico.contaminantes[j].no2,
                   zonas[i].historico.contaminantes[j].so2,
                   zonas[i].historico.contaminantes[j].co2,
                   zonas[i].historico.factores[j].temperatura,
                   zonas[i].historico.factores[j].velocidad_viento,
                   zonas[i].historico.factores[j].humedad);
        }
    }
}

void generarDatos29YIngresar30(Zona zonas[]) {
    srand(time(NULL));
    
    printf("\n===== GENERANDO DATOS DIAS 1-29 =====\n");
    
    // Generar 29 días automáticamente
    for (int dia = 0; dia < 29; dia++) {
        for (int i = 0; i < ZONAS; i++) {
            // Generar datos aleatorios
            zonas[i].actual.pm25 = (float)(rand() % 100 + 1);
            zonas[i].actual.no2 = (float)(rand() % 200 + 1);
            zonas[i].actual.so2 = (float)(rand() % 100 + 1);
            zonas[i].actual.co2 = (float)(rand() % 1700 + 300);
            
            zonas[i].factores_actuales.temperatura = (float)(rand() % 60 - 10);
            zonas[i].factores_actuales.velocidad_viento = (float)(rand() % 50 + 1);
            zonas[i].factores_actuales.humedad = (float)(rand() % 100 + 1);
            
            // Guardar en histórico
            int indice = zonas[i].historico.indice_actual;
            zonas[i].historico.contaminantes[indice] = zonas[i].actual;
            zonas[i].historico.factores[indice] = zonas[i].factores_actuales;
            
            if (zonas[i].historico.dias_registrados < DIAS_HISTORICO) {
                zonas[i].historico.dias_registrados++;
            }
            
            zonas[i].historico.indice_actual = (indice + 1) % DIAS_HISTORICO;
        }
        printf("Día %d generado correctamente.\n", dia + 1);
    }
    
    printf("\n===== INGRESAR DATOS DIA 30 MANUALMENTE =====\n");
    
    // Ingresar día 30 manualmente
    ingresarDatosActuales(zonas);
    ingresarFactoresClimaticos(zonas);
    
    // Guardar día 30 en histórico
    for (int i = 0; i < ZONAS; i++) {
        int indice = zonas[i].historico.indice_actual;
        zonas[i].historico.contaminantes[indice] = zonas[i].actual;
        zonas[i].historico.factores[indice] = zonas[i].factores_actuales;
        
        if (zonas[i].historico.dias_registrados < DIAS_HISTORICO) {
            zonas[i].historico.dias_registrados++;
        }
        
        zonas[i].historico.indice_actual = (indice + 1) % DIAS_HISTORICO;
        zonas[i].dia_actual = 1;
    }
    
    printf("\nDatos de los 30 dias cargados correctamente.\n");
}
