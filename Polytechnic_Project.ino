#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,7,8,9,10); 

int servoPin = 2;
int g_input = 12; 
int main_count = 5;
Servo Servo_v;
const int buzzer = 11;
int input = A0;
int input2 = A1;
int LP_GAS = 0;
int eay_sensor = 0;
#define trigger 4
#define echo 3
float time=0;
int distance=0;

int d_s = 13;

int lp_gas_value = 150;  // Change value for LP GAS
int dis_input_value = 15; // Change Value For Distance
int eay_value = 115; // Change Value For Eay Sensor

void setup()
 {
                              
  Serial.begin(9600);
  lcd.begin(16, 2);
  Servo_v.attach(servoPin);                                                                                 
  pinMode(d_s,INPUT);
  pinMode(input,INPUT);
  pinMode(input2,INPUT);
  pinMode(g_input,INPUT);
  pinMode(buzzer, OUTPUT);
  delay(1000);
 Serial.println("AT+CMGD=1,4");
 Serial.print("AT+CMGF=1\r");
 delay(100);
 Serial.print("AT+CnMI=2,2,0,0,0\r");

 lcd.clear();
 lcd.print("      PABNA");
 lcd.setCursor(0,1);
 lcd.print("  POLYTECHNIC");
 Servo_v.write(0);
 delay(3000);
 lcd.clear();
 lcd.print("System Run");
 lcd.setCursor(0,1);
 lcd.print("STARTING...");
 Servo_v.write(0);
 delay(3000);
 }


void loop()
 {

  LP_GAS = analogRead(input);
  eay_sensor = analogRead(input2);
  int sw_pin = digitalRead(d_s);

  if (sw_pin == HIGH)
  {
    lcd.clear();
    lcd.print("System False");  
    lcd.setCursor(0,1);
    lcd.print("Quick Action");
    servo();
    main_count = 0;
    send_massage();
    ton2();
  }else
  {
    
  }
  
  distance_value();
  lcd.clear();
  lcd.print("Dis:  ");
  lcd.print(distance);
  lcd.print(" ");  
  lcd.setCursor(0,1);
  lcd.print("Alcohol:  ");
  lcd.print(LP_GAS);
  lcd.print(" ");
  
  if (LP_GAS >= lp_gas_value)
  {
    lcd.clear();
    lcd.print("Alcohol Deteced");  
    lcd.setCursor(0,1);
    lcd.print("Time OUT FOR");
    ton_signal();
    servo();
    main_count = 0;
    while (1)
    {
    }
  }else
  {
  
  }

  if(distance < dis_input_value)
  {
    lcd.clear();
    lcd.print("Distance OVER");  
    lcd.setCursor(0,1);
    lcd.print("RUN Time Error");
    ton_signal();
    servo();
    main_count = 0;
    while (1)
    {
    }
  }else
  {
    
  }

  int gravity = digitalRead(g_input);
  if (gravity == HIGH)
  {
    lcd.clear();
    lcd.print("System False");  
    lcd.setCursor(0,1);
    lcd.print("Quick Action");
    servo();
    main_count = 0;
    send_massage();
    ton2();
  }else
  {
  }

  if (eay_sensor >= eay_value)
  {
    lcd.clear();
    lcd.print("Sleep Now");  
    lcd.setCursor(0,1);
    lcd.print("STOP Driving");
    ton_signal();
    servo();
    main_count = 0;
    while (1)
    {
    }
  }
 
  delay(1000);
  }

void distance_value()
{
   //lcd.clear();
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
}

void send_massage() {
Serial.begin(9600);
Serial.print("\r");
delay(1000);
Serial.print("AT+CMGF=1\r");
delay(1000);
Serial.print("AT+CMGS=\"+8801724683548\"\r"); 
delay(1000);
Serial.print("This is an automatic device, please come to this location\r");
delay(1000);
Serial.write(0x1A);
delay(1000);
}

void servo()
{
   //Servo_v.write(0); 
   //delay(2000); 
   Servo_v.write(180); 
}

void ton_signal()

{
  tone(buzzer, 1000, 500);
  delay(1000);
  noTone(buzzer);
  //delay(1000);
}

void ton2()
{
  while (1)
  {
  tone(buzzer, 1200, 500);
  delay(300);
  noTone(buzzer);
  delay(1000); 
  }
}
