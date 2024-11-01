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

TrafficLight carLight(4, 3, 7);
PedestrianLight pedLight(8, 9);

enum TrafficState {
  Green,
  Yellow,
  Red
};

TrafficState carState = Green;

unsigned long lastChangeTime = 0;
volatile bool pedestrianWaiting = false;
int StateDetector;

void handleButtonPress() {
  if (carState == Green) {
    pedestrianWaiting = true;
  }
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), handleButtonPress, FALLING);
}

const unsigned long tGreen = 5000;
const unsigned long tYellow = 2000;
const unsigned long tRed = 5000;

int click;

void loop() {   
    mainPart();
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
      pedLight.redOn();
    
      if (TimeCheck >= tGreen) {
        carState = Yellow;
        lastChangeTime = currentTime;
      }
      
      if(waiting){
          
          carState = Yellow;
          click = 5;
      }
      StateDetector = 0;
      break;

    case Yellow:
      carLight.yellowOn();
      pedLight.redOn();
    
      if (TimeCheck >= tYellow) {
        carState = (StateDetector == 0) ? Red : Green;
        lastChangeTime = currentTime;
      }
      
      break;

    case Red:
      
      if(click == 5)
      {
          carLight.redOn();
          pedLight.greenOn();
      }
      else 
      {
          carLight.redOn();
          
      }
      
    
      if (TimeCheck >= tRed) {
        carState = Yellow;
        lastChangeTime = currentTime;
      }
      StateDetector = 1;
      click = 6;
      break;
  }
}
