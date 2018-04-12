#define switchPin 0
#define pwmPin 1
int powerLevel = 0;
unsigned long lastTime = 0;

void setup()
{
	//Use input pullup resistors to filter noise, and switch ground for the signal to the switchPin
	pinMode(switchPin, INPUT_PULLUP);
	pinMode(pwmPin, OUTPUT);
}

void loop()
{
	unsigned long currentTime = millis();

	while (isSwitchOn()) {
		setPowerLevel(powerLevel);

		unsigned long millisecondsOff = currentTime - lastTime;

		if (millisecondsOff > 10000) {
			reset();
		}
		else if (millisecondsOff > 200) {
			powerLevel++;
		}

		if (isLowestSetting(powerLevel)) {
			powerLevel = output.length - 1;
		}

		lastTime = millis();
	}

	//when the switchPin goes high and the while loop exits, immediately turn the PWM off
	setPowerLevel(0);
}

bool isSwitchOn() {
	return digitalRead(switchPin) == LOW;
}

bool isLowestSetting(int level) {
	return level >= output.length - 1;
}

void reset() {
	powerLevel = 0;
}

void setPowerLevel(int level) {
	//Output levels for the PWM: 100%, 80%, 60% and 30%
	const int output[] = { 255, 204, 153, 77 };
	analogWrite(pwmPin, output[level]);
}
