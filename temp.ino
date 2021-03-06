// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>

//This identifies the primary pin output to be read by the DHT sensor
#define DHTPIN D5    

//Defines what the type of the DHT sensor we are using is.
#define DHTTYPE DHT11        

DHT dht(DHTPIN, DHTTYPE);

bool humid = false;

TCPClient client;

//Identifies what ThingSpeak channel and specific channel set to send the data to and write to
unsigned long ThingSpeakChannelNum = 1244806;
const char * APIWriteKey = "TDB5CCVLGVT70DBN";


void setup() 
{
    ThingSpeak.begin(client);
    
 pinMode(D5, OUTPUT);
 pinMode(D7, OUTPUT);
  Serial.begin(9600); 
    dht.begin();

 Particle.subscribe("Group 45 IOT project", handler);
}


void loop() 
{
    delay(5000);

        float humidity = dht.getHumidity();
        //This instructs the argon to take a measurement of the relative humidity as reported by the DHT11 Sensor
 
        float temperature = dht.getTempFarenheit();
        //This instructs the argon to take a measurement of the temperature in Farenheit as reported by the DHT11 Sensor

    //Sends the data recorded by the argon for relative humidity and temperature to the cloud for retrieval by partner's argon
   Particle.publish("G45 Iot project Humid", String (humidity), PRIVATE);
   Particle.publish("G45 Iot project Temp", String (temperature), PRIVATE);

    //This tells what graph plot to send what data to for ThingSpeak
    ThingSpeak.setField(1,humidity);
    ThingSpeak.setField(3,temperature);
    
  
  
  Serial.print(dht.getHumidity());
    Serial.println("humidity");
  Serial.print(dht.getTempFarenheit());
    Serial.println("temperature");

  
  ThingSpeak.writeFields(ThingSpeakChannelNum, APIWriteKey);  
}

//This code confirms that the devices are achieving two-way communicatin by received an LED ping when the partner argon has successfully received exported data
 void handler(const char *event, const char *data)
{
        digitalWrite(D7, HIGH);
             delay(2000);
        digitalWrite(D7, LOW);
             delay(500);
}
    
   