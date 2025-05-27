#include <stdio.h>
#include <math.h>
#define RANGO_NO_AGRUPADOS 20
#define RANGO_AGRUPADOS 50
#define COLUMNAS 2
#define FILAS 10

struct poblacion {	
	
	int datos;
	
} cantidad;

struct datosNoAgrupados {
	
	double datosNoAgrupados[RANGO_NO_AGRUPADOS];
	double mediaNoAgrupados;
	double medianaNoAgrupados;
	double desviacionEstandarNoAgrupados;
	double varianzaNoAgrupados;
	
} datosNo;

struct datosAgrupados {
	
	int medianaAgrupados;
	double datosAgrupados[RANGO_AGRUPADOS];
	double rangoAgrupados;
	double mediaAgrupados;
	double intervalosAgrupados;
	double anchoClaseAgrupados;
	
} datosAg;

struct tablasDatosAgrupados {
	
	double intervalosClase[FILAS][COLUMNAS];
	double limites[FILAS][COLUMNAS];
	double Xi[FILAS];
	int Fi[FILAS];
	double Fr[FILAS];
	double FiXi[FILAS];
	double XiX1[FILAS];
	double XiX2[FILAS];
	double XiX3[FILAS];
	double XiX4[FILAS];
	
} tablas;

struct medidasTendenciaCentralAgrupados {
	
	double claseMediana;
	double claseModal;
	double medianaAgrupados;
	double modaAgrupados;
	double momentoEstadistico1;
	double momentoEstadistico2; /* Es la varianza. */
	double momentoEstadistico3;
	double momentoEstadistico4;
	double sesgo; /* Variables para determinar el tipo de sesgo. */
	double curva; /* Variables para determinar el tipo de curva. */
	
} medidas;



int main() {
	
	/* Prototipo de funciones locales generales. */
	int validarDatos(void);
	void capturarDatos(void);
	void ordenarDatos(int const);
	
	/* Prototipos de funciones locales para los datos no agrupados. */
	void calcularMediaDatosNoAgrupados(void);
	void calcularVarianzaDesviacionEstandarNoAgrupados(void);
	void imprimirDatosNoAgrupados(void);
	
	/* Prototipos de funciones locales para los datos agrupados. */
	void calcularRangoIntervalosAnchoClase(void);
	void construirTablaIntervalosDeClase(void);
	void construirTablaLimites(void);
	void construirTablaXi(void);
	void construirTablaFi(void);
	void construirTablaFr(void);
	void construirTablaFiXi(void);
	void calcularMediaDatosAgrupados(int const);
	void construirTablasXiX(void);
	void identificarClaseMediana(void);
	void identificarClaseModal(void);
	void calcularMedianaDatosAgrupados(void);
	void calcularModaDatosAgrupados(void);
	void calcularMomentosEstadisticos(void);
	void imprimirMedidasDeTendenciaCentral(void);
	void imprimirTablasDeFrecuencia(void);
	void imprimirTablasMomentosEstadisticos(void);
	void imprimirMomentosEstadisticos(void);
	void imprimirTipoSesgoCurva(void);
	
	
	int identificador;
	
	identificador = validarDatos();
	
	switch (identificador) {
		case 1:
			capturarDatos();
			calcularMediaDatosNoAgrupados();
			calcularVarianzaDesviacionEstandarNoAgrupados();
			ordenarDatos(1);
			imprimirDatosNoAgrupados();
		break;
		case 2:
			capturarDatos();
			ordenarDatos(2);
			calcularRangoIntervalosAnchoClase();
			construirTablaIntervalosDeClase();
			construirTablaLimites();
			construirTablaXi();
			construirTablaFi();
			construirTablaFr();
			construirTablaFiXi();
			calcularMediaDatosAgrupados(2);
			construirTablasXiX();
			identificarClaseMediana();
			identificarClaseModal();
			calcularMedianaDatosAgrupados();
			calcularModaDatosAgrupados();
			calcularMomentosEstadisticos();
			imprimirMedidasDeTendenciaCentral();
			imprimirTablasDeFrecuencia();
			imprimirTablasMomentosEstadisticos();
			imprimirMomentosEstadisticos();
			imprimirTipoSesgoCurva();
		break;
		default:
			printf("\nHa ocurrido un error inesperado.\n");
	}
	
	return 0;
}

/* Función que valida la población ingresada por el usuario y determina si son datos agrupados o no agrupados.*/
int validarDatos(void) {

	do {
		printf("Ingrese la cantidad de datos: ");
		scanf("%d", &cantidad.datos);
			
		if (cantidad.datos < 1 || cantidad.datos > 50) {
			printf("\nPoblacion ingresada no permitida. Intentelo de nuevo.\n\n");
			
		} else if (cantidad.datos > 0 && cantidad.datos < 21) {
			return 1;
			
		} else if (cantidad.datos > 20 && cantidad.datos < 51) {
			return 2;
		}
		
	} while (cantidad.datos < 1 || cantidad.datos > 50);
}

/* Función que captura los datos para datos no agrupados y datos agrupados. */
void capturarDatos(void) {
	
	printf("\nIngrese los datos:\n\n");
	
	if (cantidad.datos > 0 && cantidad.datos < 21) {
		
		for (int posicion = 0; posicion < cantidad.datos; posicion++) {
			scanf("%lf", &datosNo.datosNoAgrupados[posicion]);
		}
		
	} else if (cantidad.datos > 20 && cantidad.datos < 51) {
		
		for (int posicion = 0; posicion < cantidad.datos; posicion++) {
			scanf("%lf", &datosAg.datosAgrupados[posicion]);
		}
	}
}

/* Función que calcula la mediana unicamente para datos no agrupados. */
void calcularMediaDatosNoAgrupados(void) {

	double sumatoria = 0.0;
	
	for (int posicion = 0; posicion < cantidad.datos; posicion++) {
		sumatoria += datosNo.datosNoAgrupados[posicion];
	}
	
	datosNo.mediaNoAgrupados = sumatoria / cantidad.datos;
}

/* Función que calcula la varianza y desviación estándar para datos no agrupados. */ 
void calcularVarianzaDesviacionEstandarNoAgrupados(void) {
	
	double sumatoria = 0.0, diferencia = 0.0, cuadrado = 0.0;
	
	for (int posicion = 0; posicion < cantidad.datos; posicion++) {
		diferencia = datosNo.datosNoAgrupados[posicion] - datosNo.mediaNoAgrupados;
		cuadrado = pow(diferencia, 2);
		sumatoria += cuadrado;
	}
	
	datosNo.varianzaNoAgrupados = sumatoria / (cantidad.datos - 1);
	datosNo.desviacionEstandarNoAgrupados = sqrt(datosNo.varianzaNoAgrupados);
}

/* Función que ordena los datos de forma ascendente mediante el método burbúja. */
void ordenarDatos(int const id)  {
	
	double auxiliar;
	
	switch (id) {
		case 1:
			for (int pasada = 0; pasada <= cantidad.datos - 1; pasada++) {
				
				for (int posicion = 0; posicion <= cantidad.datos - 2; posicion++) {
					
					if (datosNo.datosNoAgrupados[posicion] > datosNo.datosNoAgrupados[posicion + 1]) {
						auxiliar = datosNo.datosNoAgrupados[posicion];
						datosNo.datosNoAgrupados[posicion] = datosNo.datosNoAgrupados[posicion + 1];
						datosNo.datosNoAgrupados[posicion + 1] = auxiliar;
					}
				}
			}
		break;
		case 2:
			for (int pasada = 0; pasada <= cantidad.datos - 1; pasada++) {
				
				for (int posicion = 0; posicion <= cantidad.datos - 2; posicion++) {
					
					if (auxiliar = datosAg.datosAgrupados[posicion] > datosAg.datosAgrupados[posicion + 1]) {
						auxiliar = datosAg.datosAgrupados[posicion];
						datosAg.datosAgrupados[posicion] = datosAg.datosAgrupados[posicion + 1];
						datosAg.datosAgrupados[posicion + 1] = auxiliar;
					}
				}
			}
		break;
		default:
			printf("\nHa ocurrido un error inesperado.\n");
	}
}

/* Función que calcula la mediana para datos no agrupados y datos agrupados. */
void calcularMediana(int const id) {

	int x1, x2;
	double x3, mediana;

	if (id == 1) {

		if (cantidad.datos % 2 == 0) {
			x1 = cantidad.datos / 2;
			x2 = (cantidad.datos / 2) + 1;
			x3 = datosNo.datosNoAgrupados[x1 - 1] + datosNo.datosNoAgrupados[x2 - 1];
			datosNo.medianaNoAgrupados = x3 / 2;

		} else if (cantidad.datos % 2 != 0) {
			x1 = (cantidad.datos + 1) / 2;
			datosNo.medianaNoAgrupados = datosNo.datosNoAgrupados[x1 - 1];
		}	
		
	} else if (id == 2) {

		if (cantidad.datos % 2 == 0) {
			datosAg.medianaAgrupados = cantidad.datos / 2;

		} else if (cantidad.datos % 2 != 0) {
			datosAg.medianaAgrupados = (cantidad.datos + 1) / 2;
		}
	}
}

/* Función que imprime los resultados de las medidas de tendencia central para datos no agrupados. */
void imprimirDatosNoAgrupados(void) {
	
	printf("\nDatos ordenados: ");
	
	for (int posicion = 0; posicion < cantidad.datos; posicion++) {
		printf("%lf ", datosNo.datosNoAgrupados[posicion]);
	}
	
	printf("\n\nLa media es: %lf\n", datosNo.mediaNoAgrupados);
	printf("\nLa varianza es: %lf\n", datosNo.varianzaNoAgrupados);
	printf("\nLa desviacion estandar es: %lf\n", datosNo.desviacionEstandarNoAgrupados);
}

/* Función que calcula el rango, el número de subintervalos y el ancho de clase para datos agrupados. */
void calcularRangoIntervalosAnchoClase(void) {
	
	datosAg.rangoAgrupados = datosAg.datosAgrupados[cantidad.datos - 1] - datosAg.datosAgrupados[0];
	datosAg.intervalosAgrupados = ceil(sqrt(cantidad.datos));
	datosAg.anchoClaseAgrupados = (datosAg.rangoAgrupados / datosAg.intervalosAgrupados);
}

/* Función que construye la primer tabla de la distribución de frecuencias. */
void construirTablaIntervalosDeClase(void) {
	
	double temporal_1, temporal_2;

	tablas.intervalosClase[0][0] = datosAg.datosAgrupados[0];
	tablas.intervalosClase[0][1] = tablas.intervalosClase[0][0] + datosAg.anchoClaseAgrupados;
	temporal_1 = tablas.intervalosClase[0][0];
	temporal_2 = tablas.intervalosClase[0][1];

	for (int i = 1; i <= datosAg.intervalosAgrupados - 1; i++) {
		tablas.intervalosClase[i][0] = datosAg.anchoClaseAgrupados + temporal_1 + 0.01;
		temporal_1 = tablas.intervalosClase[i][0];
	}

	for (int j = 1; j <= datosAg.intervalosAgrupados - 1; j++) {
		tablas.intervalosClase[j][1] = datosAg.anchoClaseAgrupados + temporal_2 + 0.01;
		temporal_2 = tablas.intervalosClase[j][1];
	}
}

/* Función que construye la segunda tabla de limites inferiores y superiores. */
void construirTablaLimites(void) {
	
	double diferencia = 0.005;
	double temporal_1;

	for (int i = 0; i <= datosAg.intervalosAgrupados - 1; i++) {

		for (int j = 0; j <= 1; j++) {
			temporal_1 = tablas.intervalosClase[i][j];

			if (j == 0) {
				tablas.limites[i][j] = temporal_1 - diferencia;

			} else if (j == 1) {
				tablas.limites[i][j] = temporal_1 + diferencia;
			}
		}
	}
}

/* Función que construye la tercera tabla de las marcas de clase para los datos agrupados. */
void construirTablaXi(void) {

	double sumaLimites;

	for (int i = 0; i <= datosAg.intervalosAgrupados - 1; i++) {
		sumaLimites = 0.0;

		for (int j = 0; j <= 1; j++) {
			sumaLimites += tablas.limites[i][j];
			tablas.Xi[i] = sumaLimites / (double) 2;
		}
	}
}

/* Función que construye la cuarta tabla de frecuencia absoluta para los datos agrupados. */
void construirTablaFi(void) {
    
	int contador2 = 0;
    double epsilon = 0.00001;
    double auxIntervalos1, auxIntervalos2, auxDatos;

    for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
        contador2 = 0;

        for (int j = 0; j < 2; j++) {
            auxIntervalos1 = tablas.intervalosClase[i][j];
            auxIntervalos2 = tablas.intervalosClase[i][j + 1];

            for (int k = 0; k < cantidad.datos; k++) {
                auxDatos = datosAg.datosAgrupados[k];

                if (auxDatos >= auxIntervalos1 && auxDatos < auxIntervalos2) {
                    contador2++;
                }
            }
        }
        tablas.Fi[i] = contador2;
    }
}

/* Función que calcula la quinta tabla de frecuencia relativa para datos agrupados. */
void construirTablaFr(void) {
	
	double auxiliar;
	
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		auxiliar = tablas.Fi[i];
		tablas.Fr[i] = auxiliar / cantidad.datos;
	}
}

/* Función que calcula la sexta tabla de frecuencia absoluta por marca de clase para datos agrupados. */
void construirTablaFiXi(void) {
	
	double temporal_1, temporal_2;
	
	for(int i = 0; i < datosAg.intervalosAgrupados; i++) {
		temporal_1 = tablas.Fi[i];
		temporal_2 = tablas.Xi[i];
		tablas.FiXi[i] = temporal_1 * temporal_2;
	}
}

/* Función que calcula la media (promedio) para datos agrupados. */
void calcularMediaDatosAgrupados(int const id) {

	double sumatoria = 0.0;
		
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		sumatoria += tablas.FiXi[i];
	}
	
	datosAg.mediaAgrupados = sumatoria / cantidad.datos;
}

/* Función que construye las tablas de marca de clase - media para los datos agrupados. */
void construirTablasXiX(void) {
	
	double temporal_1, temporal_2, auxiliar;
	
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		temporal_1 = tablas.Xi[i];
		tablas.XiX1[i] = temporal_1 - datosAg.mediaAgrupados;
		
		temporal_2 = tablas.Xi[i];
		auxiliar = temporal_2 - datosAg.mediaAgrupados;
		tablas.XiX2[i] = pow(auxiliar, 2);
		tablas.XiX3[i] = pow(auxiliar, 3);
		tablas.XiX4[i] = pow(auxiliar, 4);
	}
}

/* Función que identifica y apunta a la clase mediana. */
void identificarClaseMediana(void) {
	
	int posicionTabla = 0, auxiliar = 0;
	
	while (datosAg.intervalosAgrupados >= auxiliar) {
		auxiliar = tablas.Fi[posicionTabla];
		posicionTabla++;
	}	
	
	medidas.claseMediana = posicionTabla;
}

/* Función que identifica y apunta a la clase modal. */
void identificarClaseModal(void) {
	
	int claseModal, auxiliar = 0;
	
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		
		if (tablas.Fi[i] > auxiliar) {
			auxiliar = tablas.Fi[i];
			claseModal = i;
		}
	}
	
	medidas.claseModal = claseModal;
}

/* Función que calcula la media para los datos agrupados. */
void calcularMedianaDatosAgrupados(void) {
	
	int sumaFrecuencias, frecuenciaClaseMediana, posicion;
	double limiteInferior, division;

	posicion = medidas.claseMediana;
	limiteInferior = tablas.limites[posicion][0];
	frecuenciaClaseMediana = tablas.Fi[posicion];
	
	for (int i = posicion; i >= 0; i--) {
		
		if (posicion == 0) {
			sumaFrecuencias = 0;
			
		} else if (posicion == 1) {
			sumaFrecuencias = tablas.Fi[0];
			
		} else if (posicion > 1) {
			sumaFrecuencias += tablas.Fi[i];
		}
	}
	
	division = cantidad.datos / 2;
	medidas.claseMediana = limiteInferior + (((division + sumaFrecuencias) / frecuenciaClaseMediana) * datosAg.anchoClaseAgrupados);
}

/* Función que calcula la moda para datos agrupados. */
void calcularModaDatosAgrupados(void) {
	
	int posicion = medidas.claseModal;
	double limiteInferior = tablas.limites[posicion][0];
	int delta1, delta2; 
	
	if (posicion == 0) {
		delta1 = tablas.Fi[0];
		delta2 = tablas.Fi[posicion] - tablas.Fi[posicion + 1];
		
	} else if (posicion == datosAg.intervalosAgrupados) {
		delta1 = tablas.Fi[posicion] - tablas.Fi[posicion - 1];
		delta2 = tablas.Fi[posicion];
		
	} else if (posicion > 0 && posicion < datosAg.intervalosAgrupados) {
		delta1 = tablas.Fi[posicion] - tablas.Fi[posicion - 1];
		delta2 = tablas.Fi[posicion] - tablas.Fi[posicion + 1];
	}
	
	medidas.claseModal = limiteInferior + (((double)delta1 / ((double)delta1 + (double)delta2))) * datosAg.anchoClaseAgrupados;
}

/* Función que calcula los momentos estadísticos para datos agrupados. */
void calcularMomentosEstadisticos(void) {
	
	double raiz3, raiz4, k3, k4;
	double auxiliar1, auxiliar2, auxiliar3, auxiliar4;
	double sumatoria1, sumatoria2, sumatoria3, sumatoria4, sumatoria5, sumatoria6, sumatoria7, sumatoria8;
	
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
			auxiliar1 = tablas.Fi[i] * tablas.XiX1[i];
			auxiliar2 = tablas.Fi[i] * tablas.XiX2[i];
			auxiliar3 = tablas.Fi[i] * tablas.XiX3[i];
			auxiliar4 = tablas.Fi[i] * tablas.XiX4[i];
					
		if (auxiliar1 < 0.0) {
			sumatoria1 += auxiliar1;
			
		} else if (auxiliar1 > 0.0) {
			sumatoria2 += auxiliar1;
		}
		
		if (auxiliar2 < 0.0) {
			sumatoria3 += auxiliar2;
			
		} else if (auxiliar2 > 0.0) {
			sumatoria4 += auxiliar2;
		}
		
		if (auxiliar3 < 0.0) {
			sumatoria5 += auxiliar3;
			
		} else if (auxiliar3 > 0.0) {
			sumatoria6 += auxiliar3;
		}
		
		if (auxiliar4 < 0.0) {
			sumatoria7 += auxiliar4;
			
		} else if (auxiliar4 > 0.0) {
			sumatoria8 += auxiliar4;
		}
	}
	
	medidas.momentoEstadistico1 = ((sumatoria1 + sumatoria2) / cantidad.datos);
	medidas.momentoEstadistico2 = ((sumatoria3 + sumatoria4) / cantidad.datos);
	
	/* Calcula el tipo de sesgo que tiene la distribución. */
	medidas.momentoEstadistico3 = ((sumatoria5 + sumatoria6) / cantidad.datos);
	raiz3 = sqrt(medidas.momentoEstadistico2);
	k3 = medidas.momentoEstadistico3 / raiz3;
	medidas.sesgo = k3;
	
	/* Calcula el tipo de curva que tiene la distribución. */
	medidas.momentoEstadistico4 = ((sumatoria7 + sumatoria8) / cantidad.datos);
	raiz4 = sqrt(medidas.momentoEstadistico2);
	k4 = (medidas.momentoEstadistico4 / raiz4);
	medidas.curva = k4 - 3.0;
}

/* Función que imprime las medidas de tendencia central. */
void imprimirMedidasDeTendenciaCentral(void) {
	
	printf("\n\nEl rango es: %lf\n", datosAg.rangoAgrupados);
	printf("\nEl numero de subintervalos son: %lf\n", datosAg.intervalosAgrupados);
	printf("\nEl ancho de clase es: %lf\n", datosAg.anchoClaseAgrupados);
	
	printf("\nDatos ordenados:\n\n");
	for (int posicion = 0; posicion < cantidad.datos; posicion++) {
		printf("%lf ", datosAg.datosAgrupados[posicion]);
	}
}

/* Función que imprime las tablas de distribución de frecuencias. */
void imprimirTablasDeFrecuencia(void) {
	
	printf("\n\n");
	printf(" Intervalos de clase     Li        Ls     Fi     Fr        Xi        FiXi");	
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		printf("\n");
		
		for (int j = 0; j < 2; j++) {
			printf("%10lf", tablas.intervalosClase[i][j]);
		}
		
		for (int j = 0; j < 2; j++) {
			printf("%10lf", tablas.limites[i][j]);
		}
		
		printf("%4d", tablas.Fi[i]);
		printf("%10lf", tablas.Fr[i]);
		printf("%10lf", tablas.Xi[i]);
		printf("%11lf", tablas.FiXi[i]);
	}
}

/* Función que imprime las tablas de los momentos estadísticos. */
void imprimirTablasMomentosEstadisticos(void) {
	
	printf("\n\n");
	printf("   Fi-X(1)   Fi-X(2)    Fi-X(3)     Fi-X(4)");
	for (int i = 0; i < datosAg.intervalosAgrupados; i++) {
		printf("\n");
		printf("%10lf", tablas.XiX1[i]);
		printf("%10lf", tablas.XiX2[i]);
		printf("%12lf", tablas.XiX3[i]);
		printf("%12lf", tablas.XiX4[i]);
	}
}

void imprimirMomentosEstadisticos(void) {
	
	printf("\n\n");
	printf("La media es: %lf\n", datosAg.mediaAgrupados);
	printf("\nLa mediana es: %lf\n", medidas.claseMediana);
	printf("\nLa moda es: %lf\n", medidas.claseModal);
	printf("\nEl momento estadistico de primer grado es: %lf\n", medidas.momentoEstadistico1);
	printf("\nEl momento estadistico de segundo grado (varianza) es: %lf\n", medidas.momentoEstadistico2);
	printf("\nEl momento estadistico de tercer grado es: %lf\n", medidas.momentoEstadistico3);
	printf("\nK3 = %lf\n", medidas.sesgo);
	printf("\nEl momento estadistico de cuarto grado es: %lf\n", medidas.momentoEstadistico4);
	printf("\nK4 - 3 = %lf\n", medidas.curva);
}

void imprimirTipoSesgoCurva(void) {
	
	if (medidas.sesgo < 0) {
		printf("\nLa distribucion tiene una asimetria hacia la izquierda.\n");
		printf("\nLa distribucion tiene un sesgo negativo.\n");
		
	} else if (medidas.sesgo == 0) {
		printf("\nLa distribucion es simetrica.\n");
		
	} else if (medidas.sesgo > 0) {
		printf("\nLa distribucion tiene una asimetria hacia la derecha.\n");
		printf("\nLa distribucion tiene un sesgo positivo.\n");
	}
	
	if (medidas.curva < 0) {
		printf("\nLa curva es platocurtica.\n");
		
	} else if (medidas.curva == 0) {
		printf("\nLa curva es mesocurtica.\n");
		
	} else if (medidas.curva > 0)  {
		printf("\nLa curva es leptocurtica.\n");
	}
}