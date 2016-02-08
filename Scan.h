//#define SCAN_H
#ifndef SCAN_H
#define SCAN_H

#include "Robot.h"
#include "CONF.h"
#include "OBJD.h"

class Scan
{
private:
	L_R_Dist Distancelist[FULL_SCAN_NUM];

	Scan(){}
public:

	static Scan& getInstanceScan();

	void Init(void);
	/*Scan 360 degree while staying in the same coordinates*/
	void CirclScanRoutine(Robot rob, L_R_Dist* scanlist);
	/*taking the reading while moving linearly and Calculating average*/
	return_type LinearScan(Point& newpoint, SensorID side, Robot rob);
};

#endif
