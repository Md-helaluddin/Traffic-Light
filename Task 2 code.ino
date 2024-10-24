class TrafficLight {
  private:
    int GREEN, YELLOW, RED;

  public:
    TrafficLight(int green, int yellow, int red) {
      GREEN = green;
      YELLOW = yellow;
      RED = red;

      pinMode(GREEN, OUTPUT);
      pinMode(YELLOW, OUTPUT);
      pinMode(RED, OUTPUT);
    }

    void greenOn() {
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
    }

    void yellowOn() {
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW);
    }

    void redOn() {
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, HIGH);
    }
};

class PedestrianLight {
  private:
    int GREEN, RED;

  public:
    PedestrianLight(int green, int red) {
      GREEN = green;
      RED = red;

      pinMode(GREEN, OUTPUT);
      pinMode(RED, OUTPUT);
    }

    void greenOn() {
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
    }

    void redOn() {
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
    }
};

class PedestrianButton {
  private:
    int buttonPin;

  public:
    PedestrianButton(int button) {
      buttonPin = button;
      pinMode(buttonPin, INPUT);
    }

    bool isPressed() {
      return digitalRead(buttonPin) == HIGH;
    }
};

TrafficLight carLight(4, 3, 2);
PedestrianLight pedLight(8, 9);
PedestrianButton button(7);

int carState = 0;
bool pedestrianWaiting = false;
unsigned long lastChangeTime = 0;

void setup() {
}

void loop() {
  unsigned long currentTime = millis();

  switch (carState) {
    case 0:
      carLight.greenOn();
      pedLight.redOn();

      if (lastChangeTime == 0) {
        lastChangeTime = currentTime;
      }

      if (button.isPressed()) {
        carLight.redOn();
        pedLight.greenOn();
        delay(5000);
        carState = 2;
        lastChangeTime = 0;
        break;
      }

      if (currentTime - lastChangeTime >= 10000) {
        carState = 1;
        lastChangeTime = currentTime;
      }
      break;

    case 1:
      carLight.yellowOn();
      pedLight.redOn();
      delay(2000);
      carState = 2;
      lastChangeTime = 0;
      break;

    case 2:
      carLight.redOn();
      pedLight.greenOn();
      delay(5000);
      carState = 3;
      lastChangeTime = 0;
      break;

    case 3:
      carLight.yellowOn();
      pedLight.redOn();
      delay(2000);
      carState = 0;
      lastChangeTime = 0;
      break;
  }
}

