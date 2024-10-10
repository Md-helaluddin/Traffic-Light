class TrafficLight {
    
    private: 
    int redLED;
    int orangeLED;
    int greenLED;
    
    int redPadLED;
    int greenPadLED;
    int pushBUTTON;

    public:
    
    TrafficLight(int red, int orange, int green, int redpad, int greenpad, int button)
    {
        redLED = red;
        orangeLED = orange;
        greenLED = green;
        redPadLED = redpad;
        greenPadLED = greenpad;
        pushBUTTON = button;
        
        pinMode(redLED, OUTPUT);
        pinMode(orangeLED, OUTPUT);
        pinMode(greenLED, OUTPUT);
        pinMode(greenPadLED, OUTPUT);
        pinMode(redPadLED, OUTPUT);
        pinMode(pushBUTTON, INPUT);
        
        digitalWrite(redLED, LOW);
        digitalWrite(orangeLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(redPadLED, LOW);
        digitalWrite(greenPadLED, LOW);
    }
    
    void carTraffic()
    {
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
        digitalWrite(orangeLED, LOW);
        digitalWrite(redPadLED, HIGH);
        digitalWrite(greenPadLED, LOW);
    }
    
    void pedestrianCrossing()
    {
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(orangeLED, HIGH);
        digitalWrite(redPadLED, HIGH);
        digitalWrite(greenPadLED, LOW);
        delay(3000);
        
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
        digitalWrite(orangeLED, LOW);
        digitalWrite(redPadLED, LOW);
        digitalWrite(greenPadLED, HIGH);
        delay(8000);
        
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(orangeLED, HIGH);
        digitalWrite(redPadLED, HIGH);
        digitalWrite(greenPadLED, LOW);
        delay(3000);
        
        carTraffic();
    }
        
    void StartingPoint()
    {
        int readPushButton = digitalRead(pushBUTTON);
        
        if(readPushButton == LOW)
        {
            carTraffic();
        }
        else if(readPushButton == HIGH)
        {
            pedestrianCrossing();
        }
    }
};

int rot = 10;
int gelb = 9;
int grune = 8;
int rotpad = 6;
int grunepad = 5;
int pushHabibi = 7;

TrafficLight light(rot, gelb, grune, rotpad, grunepad, pushHabibi);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    light.StartingPoint();
}
