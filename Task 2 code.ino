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

    void allOff() {
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
    }
};

class PedestrianLight {
  private:
    int RED, GREEN;

  public:
    PedestrianLight(int red, int green) {
      RED = red;
      GREEN = green;
      pinMode(RED, OUTPUT);
      pinMode(GREEN, OUTPUT);
    }

    void greenOn() {
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
    }

    void redOn() {
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
    }

    void allOff() {
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
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
PedestrianLight pedLight(9, 8);  
PedestrianButton button(7);      

int carState = 0;
bool pedestrianWaiting = false;
unsigned long lastChangeTime = 0;

void setup() {
}

void loop() {
  unsigned long currentTime = millis();

  if (button.isPressed() && carState == 0) {
    pedestrianWaiting = true;
  }

  switch (carState) {
    case 0:
      if (currentTime - lastChangeTime >= 10000 || pedestrianWaiting) {
        carLight.yellowOn();
        carState = 1;
        lastChangeTime = currentTime;
        pedestrianWaiting = false;
      } else {
        carLight.greenOn();
        pedLight.redOn();
      }
      break;

    case 1:
      if (currentTime - lastChangeTime >= 2000) {
        carLight.redOn();
        pedLight.greenOn();
        carState = 2;
        lastChangeTime = currentTime;
      } else {
        carLight.yellowOn();
      }
      break;

    case 2:
      if (currentTime - lastChangeTime >= 5000) {
        carLight.yellowOn();
        pedLight.redOn();
        carState = 3;
        lastChangeTime = currentTime;
      } else {
        carLight.redOn();
        pedLight.greenOn();
      }
      break;

    case 3:
      if (currentTime - lastChangeTime >= 2000) {
        carLight.greenOn();
        carState = 0;
        lastChangeTime = currentTime;
      } else {
        carLight.yellowOn();
      }
      break;
  }
}
