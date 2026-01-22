#define ZONAS 5
#define DIAS_HISTORICO 30
//LIMITES DE CALIDAD DE AIRE (OMS)
#define LIM_PM25 15
#define LIM_NO2 40
#define LIM_SO2 20
#define LIM_CO2 1000
//LIMITES DE CALIDAD DE AIRE
#define MIN_PM25  0
#define MAX_PM25  100 //15

#define MIN_NO2   0
#define MAX_NO2   200 //40

#define MIN_SO2   0
#define MAX_SO2   100 //20

#define MIN_CO2   300
#define MAX_CO2   2000 //1000

#define MIN_TEMP -10
#define MAX_TEMP 50
#define MIN_VIENTO 0
#define MAX_VIENTO 50
#define MIN_HUMEDAD 0
#define MAX_HUMEDAD 100

typedef struct {
    float pm25;
    float no2;
    float so2;
    float co2;
} Contaminantes;

typedef struct {
    float temperatura;
    float velocidad_viento;
    float humedad;
} FactoresClimaticos;

typedef struct {
    Contaminantes contaminantes[DIAS_HISTORICO];
    FactoresClimaticos factores[DIAS_HISTORICO];
    int dias_registrados;
    int indice_actual;
} HistoricoCompleto;

typedef struct {
    int idZona;
    int dia_actual;
    Contaminantes actual;
    FactoresClimaticos factores_actuales;
    HistoricoCompleto historico;
    Contaminantes prediccion;
} Zona;

/* Prototipos */
void inicializarZonas(Zona zonas[]);
void ingresarDatosActuales(Zona zonas[]);
void ingresarFactoresClimaticos(Zona zonas[]);
void mostrarDatosActuales(Zona zonas[]);
void calcularPromediosHistoricos(Zona zonas[]);
void actualizarHistorico(Zona zonas[]);
void predecirContaminacion(Zona zonas[]);
void mostrarPrediccion(Zona zonas[]);
void mostrarAlertas(Zona zonas[]);
void generarRecomendaciones(Zona zonas[]);
void generarReporte(Zona zonas[]);
void guardarReporteEnArchivo(Zona zonas[], const char* nombreArchivo);
void guardarHistoricoEnArchivo(Zona zonas[], const char* nombreArchivo);
void cargarHistoricoDesdeArchivo(Zona zonas[], const char* nombreArchivo);
const char* obtenerNivelGeneral(Zona z);
float calcularPromedioContaminante(HistoricoCompleto historico, int tipo_contaminante);
void mostrarHistorico(Zona zonas[]);
void generarDatos29YIngresar30(Zona zonas[]);
