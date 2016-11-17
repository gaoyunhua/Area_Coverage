#ifndef ERRH_H
#define ERRH_H
#include "types.h"
#include "CONF.h"

typedef enum Errortype
{
	ERROR_COMH_COMPASS_NC = 0x00,
	ERROR_ENCOD_ENCODER_NC = 0X01,
	ERROR_MOVE_MOTORS_NC = 0X02,
	ERROR_ULSH_ULSL_NC = 0X03,
	ERROR_ULSH_ULSR_NC = 0X04,
	ERROR_NONE_FRONT_BUMPER_NC = 0X05,
	ERROR_MOVE_UPDATE_POSITION = 0X06,
	ERROR_MOVE_MOVEFORWARD_FAIL = 0X07,
	ERROR_MOVE_MOVEBACKWARD_FAIL = 0x08,
	ERROR_COMH_INVALID_HEADING = 0x09,
	ERROR_COMH_MEASURE_FAIL = 0x0A,
	WARNING_ENCOD_NOT_COMPLETE_STEP = 0x0B,
	ERROR_MAP_ACCESS_OUT_OF_BOUND = 0x0C,
	ERROR_SCAN_LINEARSCAN_FAIL = 0x0D,
	ERROR_SCAN_VALIDATION_DISTANCE_FAIL = 0x0E,
	ERROR_GTSP_READ_SENSORS_ALL_VIEW_FAIL = 0x0F,
	ERROR_GTSP_READ_SENSORS_SOUTH_VIEW_FAIL = 0x10,
	ERROR_GTSP_READ_SENSORS_NORTH_VIEW_FAIL = 0x11,
	ERROR_GTSP_READ_SENSORS_WEST_VIEW_FAIL = 0x12,
	ERROR_GTSP_READ_SENSORS_EAST_VIEW_FAIL = 0x13,
	ERROR_GTSP_DEFAULT_CASE = 0x14,
	ERROR_MOVE_UT_RIGHT_DEFAULT_CASE = 0x15,
	ERROR_MOVE_UT_LEFT_DEFAULT_CASE = 0x16,
	ERROR_MOVE_UT_DEFAULT_CASE = 0x17,
	ERROR_ZGZG_DEFAULT_CASE = 0x18,
	ERROR_ZGZG_FIX_ROBOT_DEFAULT_CASE = 0x19
}ErrorClass;


class ERRH
{
private:

public:
	static void Error_logErrorClass(Errortype ErrorClass);
};

#endif
