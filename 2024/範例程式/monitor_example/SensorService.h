
#ifndef ARDUINO_SENSORSERVICE_H
#define ARDUINO_SENSORSERVICE_H
#include <Arduino.h>
#include <SoftwareSerial.h>

#define JSON_BUFFER_LEN 256

//
typedef String (*FUNC_AXIS_DECLARATION)();

class SensorService
{
private:
	SoftwareSerial *pBT;
	FUNC_AXIS_DECLARATION func_on_start;

public:
	bool b_started = false;

	SensorService(SoftwareSerial *pBT, FUNC_AXIS_DECLARATION f);
	~SensorService();

	void listen();

	bool on_start();
	bool send_data(String data_json);
	bool on_stop();
};
#endif
