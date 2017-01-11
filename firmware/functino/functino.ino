#include <TimerOne.h>

static int pin       = 13;   // LED pin
static int high      = 100;
static int low       = 100;
static int nPulses   = 0;

static bool run         = false;
static bool checkPulses = false;

void setup (void)
{
  Timer1.initialize(1000);  // 1ms timer
  Timer1.attachInterrupt(timer);
  Serial.begin(57600);
  pinMode(pin, OUTPUT);
}

void loop (void)
{
}

static size_t state   = 0;    // 0 = LOW, 1 = HIGH
static size_t counts  = 0;
static size_t trigger = 0;

void timer (void)
{  
  if(run)
    if(++counts == trigger)
    {
      counts = 0;
      
      trigger = state ? low : high;           
       
      if(!state && checkPulses)
      {
        if(!nPulses--)
          run = false;
      }
      
      state = !state;
      
      if(run)
        digitalWrite(pin, state); 
    }
}

void serialEvent (void)
{
  static char message[64] = {};
  static int n = 0;
  
  while(Serial.available())
  {
    char c = (char)Serial.read();
    
    Serial.flush();
    
    if(n >= sizeof(message))
      n = 0;
    
    if(c == '\n')
    {
      message[n++] = '\0';
      processMessage(message);
      n = 0;
      message[n] = '\0';
    }
    else
      message[n++] = c;
  }
}

void processMessage (char *message)
{  
  char *commandPtr = message;
  char *parameterPtr = strchr(message, ' ');
  char *valuePtr;
  size_t value;
  
  if(!parameterPtr)
  {
    Serial.println("No parameter");
    return;
  }
  
  *parameterPtr++ = '\0';  
  
  String commandStr(commandPtr);
  
  if(commandStr == "GET")
  {
    String parameterStr(parameterPtr);
    if(parameterStr == "PIN")          value = pin;
    else if(parameterStr == "HIGH")    value = high;
    else if(parameterStr == "LOW")     value = low;
    else if(parameterStr == "NPULSES") value = nPulses;
    else
    {
      Serial.println("Invalid parameter "+parameterStr);
      return;
    }
    
    Serial.println(value);
  }
  else if(commandStr == "SET")
  {    
    valuePtr = strchr(parameterPtr, ' ');
    if(!valuePtr)
    {
      Serial.println("No value");
      return;
    }
    
    *valuePtr++ = '\0';
    if(sscanf(valuePtr, "%d", &value) != 1)
    {
      Serial.println("Invalid value");
      return;
    }

    String parameterStr(parameterPtr);
    if(parameterStr == "PIN")          pin   = value >= 0 ? value : pin;
    else if(parameterStr == "HIGH")    high  = value >= 0 ? value : high;
    else if(parameterStr == "LOW")     low   = value >= 0 ? value : low;
    else if(parameterStr == "NPULSES") 
    {
      state = 1;
      counts = 0;
      trigger = high;
      
      nPulses = value;
      checkPulses = nPulses > 0;
      run = nPulses >= 0;
    }
    else
    {
      Serial.println("Invalid parameter "+parameterStr);
      return;
    }
    
    Serial.println("OK");
  }
  else
  {
    Serial.println("Invalid command "+commandStr);
    return;
  }
}
