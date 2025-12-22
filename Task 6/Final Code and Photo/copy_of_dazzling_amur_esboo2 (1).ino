class PedestrianLight {
  private:
    int GREEN, RED;

  public:
    PedestrianLight(int green, int red) : GREEN(green), RED(red) {
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

PedestrianLight pedLight(8, 9);

void setup() {
  Serial.begin(9600);
  pedLight.redOn();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'G':
        pedLight.greenOn();
        break;

      case 'R':
        pedLight.redOn();
        break;

      default:
        break;
    }
  }
}
