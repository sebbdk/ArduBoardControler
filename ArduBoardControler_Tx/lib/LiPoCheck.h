#ifndef _LIPOCHECK_h
	#define _LIPOCHECK_h

	#if defined(ARDUINO) && ARDUINO >= 100
		#include "arduino.h"
	#else
		#include "WProgram.h"
	#endif

	#ifndef _CONFIG_h
		#include "Config.h"
	#endif

	#define CELL_LIPO	0
	#define LIPO_MINVOLRANGE	3.3
	#define	LIPO_MAXVOLRANGE	4.2
	#define CELL_LIION	1
	#define LIION_MINVOLRANGE	2.5
	#define	LIION_MAXVOLRANGE	4.2

	const float lipoDc[2][11] = { { 3.2, 3.680,3.740,3.780,3.810,3.850,3.870,3.960,4.02,4.100,4.200 } ,{ 0.000, 0.100,0.200,0.300,0.400,0.500,0.600,0.700,0.800,0.900,1.000 } };
	const float liionDc[2][7] = { {2.5, 3.4, 3.6, 3.68, 3.75, 3.88, 4.2} ,{ 0.000, 0.100, 0.200,0.400,0.600,0.800, 1.000} }; //source: http://www.ibt-power.com/bkencel/Graphs/LiIonDischGph.JPG

	int CountCells(float voltage, int celltype);
	int CapCheckPerc(float voltage, int cells, int celltype);
#endif

