
#ifndef ARDUINO_SENSORSERVICE_H
#define ARDUINO_SENSORSERVICE_H
#include <Arduino.h>
#include <SoftwareSerial.h>

#define JSON_BUFFER_LEN 256

class SensorService
{
private:
	SoftwareSerial *pBT;

public:
	bool b_started = false;

	SensorService(SoftwareSerial *pBT);
	~SensorService();

	void listen();

	bool on_start();
	bool send_data(String data_json);
	bool on_stop();
};
#endif
