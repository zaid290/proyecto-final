#define ZONAS 5

#define LIM_PM25 50
#define LIM_NO2 100
#define LIM_SO2 20
#define LIM_CO2 1000
//LIMITES DE CALIDAD DE AIRE
#define MIN_PM25  0
#define MAX_PM25  500

#define MIN_NO2   0
#define MAX_NO2   400

#define MIN_SO2   0
#define MAX_SO2   200

#define MIN_CO2   300
#define MAX_CO2   5000

typedef struct {
    float pm25;
    float no2;
    float so2;
    float co2;
} Contaminantes;

typedef struct {
    int idZona;
    Contaminantes actual;
    Contaminantes historico;
    Contaminantes prediccion;
} Zona;

/* Prototipos */
void inicializarZonas(Zona zonas[]);
void ingresarDatosActuales(Zona zonas[]);
void mostrarDatosActuales(Zona zonas[]);
void calcularPromediosHistoricos(Zona zonas[]);
void predecirContaminacion(Zona zonas[]);
void mostrarAlertas(Zona zonas[]);
void generarRecomendaciones(Zona zonas[]);
void generarReporte(Zona zonas[]);
const char* obtenerNivelGeneral(Zona z);


