#define Grey 12

class TrafficLight {
  private:
    int GREEN, YELLOW, RED;

  public:
    TrafficLight(int green, int yellow, int red) : GREEN(green), YELLOW(yellow), RED(red) {
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

TrafficLight carLight(4, 3, 7);
TrafficLight d3(8, 9, 10);

enum TrafficState {
  Green,
  Yellow,
  Red
};

TrafficState carState = Green;

unsigned long lastChangeTime = 0;
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 50;
bool isGreyOn = false;

volatile bool pedestrianWaiting = false;
int StateDetector;

void handleButtonPress() {
  if (carState == Green) {
    pedestrianWaiting = true;
  }
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(Grey, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), handleButtonPress, FALLING);
  Serial.begin(9600);
}

const unsigned long tGreen = 2000;
const unsigned long tYellow = 500;
const unsigned long tRed = 2000;

int click;
int yelClick;

void loop() {   
  mainPart();
  blinkGreyLight();
}

void mainPart() {
  unsigned long currentTime = millis();
  int TimeCheck = currentTime - lastChangeTime;

  noInterrupts();
  bool waiting = pedestrianWaiting;
  if (waiting) {
    pedestrianWaiting = false;  
  }
  interrupts();

  switch (carState) {
    case Green:
      carLight.greenOn();
      d3.redOn();
    
      if (TimeCheck >= tGreen) {
        carState = Yellow;
        lastChangeTime = currentTime;
      }
      yelClick = 0;
      if (waiting) {
        carState = Yellow;
        click = 5;
        yelClick = 5;
        lastChangeTime = currentTime;
      }
      StateDetector = 0;
      break;

    case Yellow:
      carLight.yellowOn();
      if (yelClick == 0)
        d3.yellowOn();
    
      if (TimeCheck >= tYellow) {
        carState = (StateDetector == 0) ? Red : Green;
        lastChangeTime = currentTime;
        
        if (StateDetector == 0 && click == 5) {
          Serial.write('G');
          d3.redOn();
          isGreyOn = true;
        } else if (StateDetector == 1 || click != 5) {
          Serial.write('R');
          d3.greenOn();
          isGreyOn = false;
          digitalWrite(Grey, LOW);
        }
      }
      break;

    case Red:
      carLight.redOn();
      
      if (TimeCheck >= tRed) {
        carState = Yellow;
        lastChangeTime = currentTime;
        Serial.write('R');
        isGreyOn = false;
        digitalWrite(Grey, LOW);
      }
      
      StateDetector = 1;
      click = 6;
      break;
  }
}

void blinkGreyLight() {
  if (isGreyOn) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentTime;
      digitalWrite(Grey, !digitalRead(Grey));
    }
  }
}
