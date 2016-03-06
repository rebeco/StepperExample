#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

#define BUTTON1 2
#define BUTTON2 3

int Step = 0;

int Direction = 1;

// Full Step
int Sequence [ 4 ][ 4 ] =
 {   {1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 1, 1},
     {1, 0, 0, 1}
 };

// Wave Drive
//int Sequence [ 4 ][ 4 ] =
//{   {1, 0, 0, 0},
//    {0, 1, 0, 0},
//    {0, 0, 1, 0},
//    {0, 0, 0, 1}
//};

// Half Step
//int Sequence [ 8 ][ 4 ] =
//{   {1, 0, 0, 0},
//    {1, 1, 0, 0},
//    {0, 1, 0, 0},
//    {0, 1, 1, 0},
//    {0, 0, 1, 0},
//    {0, 0, 1, 1},
//    {0, 0, 0, 1},
//    {1, 0, 0, 1}
//};


int sizeOfSequence = sizeof(Sequence)/8;

float stepPause;

unsigned long milliseconds;
bool justPrinted;


void setup()
{
    Serial.begin(9600);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    
    stepPause = 3.00;
    justPrinted = false;
    
}


void loop()
{
    
   while(true) {
       
        milliseconds = millis();
       
        stepper();
       
        if(digitalRead(BUTTON1) == HIGH) stepPause = stepPause - 0.001;
        if(digitalRead(BUTTON2) == HIGH) stepPause = stepPause + 0.001;
        if (stepPause < 0) stepPause = 0;
       
        if (milliseconds % 1000 > 500) {
            if (!justPrinted) {
                Serial.println(stepPause);
                justPrinted = true;
            }
       }
        else justPrinted = false;
    }
    
    
}


void stepper() {
    
    delay(stepPause);
    
    digitalWrite( IN1, Sequence[Step][0]);
    digitalWrite( IN2, Sequence[Step][1]);
    digitalWrite( IN3, Sequence[Step][2]);
    digitalWrite( IN4, Sequence[Step][3]);

    
    if(Direction > 0) Step++;
    else Step--;
    
    Step = ( Step + sizeOfSequence) % sizeOfSequence;
}



