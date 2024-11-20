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

TrafficLight carLight(4, 3, 2);

enum TrafficState {
  Green,
  Yellow,
  Red
};

TrafficState state = Green;

unsigned long lastChangeTime = 0;
unsigned long tGreen = 5000;
unsigned long tYellow = 2000;
unsigned long tRed = 5000;
int prevState = 0;

void setup() {}

void loop() {
  unsigned long currentTime = millis();
  unsigned long timeElapsed = currentTime - lastChangeTime;

  switch (state) {
    case Green:
      carLight.greenOn();
      if (timeElapsed >= tGreen) {
        state = Yellow;
        prevState = 0;
        lastChangeTime = currentTime;
      }
      break;

    case Yellow:
      carLight.yellowOn();
      if (timeElapsed >= tYellow) {
        state = (prevState == 0) ? Red : Green;
        lastChangeTime = currentTime;
      }
      break;

    case Red:
      carLight.redOn();
      if (timeElapsed >= tRed) {
        state = Yellow;
        prevState = 1;
        lastChangeTime = currentTime;
      }
      break;
  }
}
