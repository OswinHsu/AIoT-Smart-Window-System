#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <Pixetto.h>
#define rxPin 0 //白色線接D1
#define txPin 1  //黃色線接D0

LiquidCrystal_I2C lcd_i2c(0x27);
Servo __myservo9;   //伺服馬達橘色線接到D9
DHT dht11_p2(2, DHT11);  //溫溼度感測器DATA腳接在D2
Pixetto ss(rxPin, txPin);
SoftwareSerial BT(3, 4); // RX接收腳接D3, TX傳送腳接D4

char Incoming_value=0;

void setup()
{
  __myservo9.attach(9);
  lcd_i2c.begin(16, 2);
  __myservo9.write(0);
  lcd_i2c.backlight();
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("welcome");
  delay(3000);
  lcd_i2c.begin(16, 2);
  lcd_i2c.clear();
  dht11_p2.begin();
  Serial.begin(9600);
  BT.begin(9600);
  //pixetto
  ss.begin();
  ss.enableFunc(Pixetto::FUNC_VOICE_COMMAND);

}

void loop()
{
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print((String("hum:")+String(dht11_p2.readHumidity())));
  lcd_i2c.setCursor(0,1);
  lcd_i2c.print((String("temp:")+String(dht11_p2.readTemperature())));
  delay(7000);
  if (dht11_p2.readHumidity() >= 60) {
    __myservo9.write(45);
    lcd_i2c.clear();
    lcd_i2c.setCursor(0,1);
    lcd_i2c.print("humid!");
    delay(3000);
  } else {
    __myservo9.write(0);
    lcd_i2c.clear();
    lcd_i2c.setCursor(0,1);
    lcd_i2c.print("humid<60");
  }
if (ss.isDetected()) 
  {
    //Serial.println("Detected");
    //Available voice commands are defined in Pixetto.h.
    if (ss.getFuncID() == Pixetto::FUNC_VOICE_COMMAND) 
    {
      if (ss.getTypeID() == Pixetto::VOICE_Open) 
      {
        myServo0.write(0);
        //Serial.println("open");
        
      }
      else if (ss.getTypeID() == Pixetto::VOICE_Close) 
      {
        myServo0.write(90);
        //Serial.println("close");
        
      }
    }
  }
if(BT.available()>0 )
  {
      Incoming_value= BT.read();
      if(Incoming_value == '1') 
      {
        //Serial.print(Incoming_value);
        myServo0.write(90);
      }   
      else if(Incoming_value == '2') 
      {
        //Serial.print(Incoming_value);
        myServo0.write(0);
      }
      //Serial.println(Incoming_value);
      else if(Incoming_value == '3') 
      {
        //Serial.print(Incoming_value);
        myServo0.write(45);
      }
 
  }
}



