#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
//屏幕
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//气泵
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Servo.h>

Servo servo_2;   // servo 左1
Servo servo_3;   // servo 左2
Servo servo_4;   // servo 左3
Servo servo_5;   // servo 右3
Servo servo_6;   // servo 右2
Servo servo_7;   // servo 右1
Servo servo_8;   // 充气泵
Servo servo_9;   // 吸气泵
Servo servo_10;  // 电磁阀
Servo servo_11;  // 后servo右
Servo servo_12;  // 后servo左

int i;  // 用于循环中的角度变化

//屏幕
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayText(const char* text) {
  display.clearDisplay();
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println(text);
  display.display();
  delay(20);
}

void setup() {
  //servo 和气泵
  servo_2.attach(2);
  servo_3.attach(3);
  servo_4.attach(4);
  servo_5.attach(5);
  servo_6.attach(6);
  servo_7.attach(7);
  servo_8.attach(8);
  servo_9.attach(9);
  servo_10.attach(10);
  servo_11.attach(11);
  servo_12.attach(12);

  //屏幕
    Serial.begin(9600);
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1); // Halt execution on failure
   }
  }



void loop() {
  //屏幕文字
  const char* texts[] = {"Contradiction", "Hypocrisy", "Greed", "Deception", 
                         "Fantasy", "Doubt", "Simple", "Fickle", "Competitive", 
                         "Lonely", "Fragile", "Tolerant", "Furious", "Complex", 
                         "Annoying", "Jealous", "Sinister", "Contest", 
                         "Complain", "Selfish", "Boring"};
  int numTexts = sizeof(texts) / sizeof(texts[0]);

  for (int j = 0; j < numTexts; j++) {
    displayText(texts[j]); 
 }

  // 伺服电机控制
  for (i = 0; i < 180; i++) { 
    servo_2.write(i);     
    servo_3.write(i); 
    servo_4.write(i); 
    servo_5.write(i);     
    servo_6.write(i); 
    servo_7.write(i);     
    delay(20);                      
  }
  for (i = 180; i > 0; i--) { 
    servo_2.write(i);     
    servo_3.write(i); 
    servo_4.write(i); 
    servo_5.write(i);     
    servo_6.write(i); 
    servo_7.write(i);     
    delay(20);                       
  }

  //servo 触角
  for (i = 0; i < 45; i++) { 
  servo_11.write(i);              
  servo_12.write(i);          
  delay(20);                      
  }
  for (i = 45; i > 0; i--) { 
   servo_11.write(i);                
   servo_12.write(i);              
   delay(20);                      
  }

  // 充气
  servo_8.write(180);  // 打开充气泵
  servo_9.write(0);    // 关闭吸气泵
  delay(1500);         // 充气1500毫秒

  // 吸气前的准备
  servo_8.write(0);    // 关闭充气泵
  servo_9.write(0);    // 关闭吸气泵
  servo_10.write(180); // 打开电磁阀
  delay(500);          // 给电磁阀一点时间启动

  // 吸气
  servo_8.write(0);    // 关闭充气泵
  servo_9.write(180);  // 打开吸气泵
  delay(1500);         // 吸气1500毫秒

  // 完成动作，全部关闭
  servo_8.write(0);    // 关闭充气泵
  servo_9.write(0);    // 关闭吸气泵
  servo_10.write(0);   // 关闭电磁阀
  delay(500);          // 等待1500毫秒后再次循环
}

