#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 7
#define sensorOut 8

Servo myser1; // Micro servo 1
Servo myser2; // Micro servo 2

// Menyimpan frekuensi warna yang dibaca oleh color sensor
int red = 0;
int green = 0;
int blue = 0;
int benar=0, warna=0;

void setup() {
  myser2.attach(5);
  myser1.attach(6);
  
  // Set S0-S3 sebagai output
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set output sensor sebagai input
  pinMode(sensorOut, INPUT);
  
  // Set Pulse Width scaling menjadi 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  myser1.write(90); // Micro servo 1 menulis menggeser lengan ke 90
  delay(3000);
  
  while(benar==0) {
    detectcolor(); // Deteksi warna
    posservo(); // Posisi servo
    delay(3000);
  }

  myser1.write(60);
  delay(500);
  myser1.write(30);
  delay(500);
  myser1.write(0);
  delay(1000);
  myser1.write(30);
  delay(500);
  myser1.write(60);
  delay(500);
  
  benar=0;
}

// Fungsi detectcolor
void detectcolor() {
  // Set sensor untuk baca RED saja
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Read output Pulse Width
  red = pulseIn(sensorOut, LOW);
  // Print output
  Serial.print("R = ");
  Serial.print(red);
  delay(100);
  
  // Set sensor untuk baca GREEN saja
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Read output Pulse Width
  green = pulseIn(sensorOut, LOW);
  // Print output 
  Serial.print(" G = ");
  Serial.print(green);
  delay(100);
  
  // Set sensor untuk baca BLUE saja
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Read output Pulse Width
  blue = pulseIn(sensorOut, LOW);
  // Print output 
  Serial.print(" B = ");
  Serial.println(blue);
  delay(100);

  /*
    ripe      --> red(41-51), green(100-167), blue(113-140)
    halfripe  --> red(52-62), green(54-77), blue(100-112)
    unripe    --> red(63-80), green(69-99), blue(67-99)
  */
  
  int ripe=0, halfripe=0, unripe=0;
  
  if((41<=red)&&(red<=51)) ripe = ripe + 1;
  else if((52<=red) && (red<=62)) halfripe = halfripe + 1;
  else if((63<=red) && (red<=80)) unripe = unripe + 1;

  if((100<=green) && (green<=167)) ripe = ripe + 1;
  else if((54<=green) && (green<=77)) halfripe = halfripe + 1;
  else if((69<=green) && (green<=99)) unripe = unripe + 1;

  if((113<=blue) && (blue<=140)) ripe = ripe + 1;
  else if((100<=blue) && (blue<=112)) halfripe = halfripe + 1;
  else if((67<=blue) && (blue<=99)) unripe = unripe + 1;
    
  // Kesimpulan
  if((halfripe>ripe) && (halfripe>unripe)) {
    warna=1;
    Serial.println("Setengah matang");
  } else if((unripe>ripe) && (unripe>halfripe)) {
    warna=2;
    Serial.println("Tidak matang");
  } else {
    warna=3;
    Serial.println("Matang");
  }
}

void posservo() {
  if(warna==1) { // jika warna oranye (setengah matang)
    myser2.write(135);
    benar=1;
  } else if(warna==2) { // jika warna hijau (tidak matang)
    myser2.write(90);
    benar=1;
  } else if(warna==3) { // jika warna merah (matang)
    myser2.write(45);
    benar=1;
  }
}
