#include "HX711.h"
#include "soc/rtc.h"

// test using 4 point Load cell // +- 11 gram

#define LC_data 33
#define LC_SCK  32 // not i2c
#define LC_data2 25
#define LC_SCK2  32

HX711 scale;
HX711 scale2;

bool set = true;
long ref1,ref2,ref_Scale2,ref2_Scale2; // Ref = 1 With reference Load // ref 2 Withotu Reference Load 

int ref_W= 414; // the real reference Load weight
int ref_W2= 414;

void setup() {
  Serial.begin(115200);
  scale.begin(LC_data, LC_SCK );
  scale2.begin(LC_data2, LC_SCK2);
}

void loop() {

  if (scale.is_ready() && scale2.is_ready()) {
    if(set== true){
    Serial.println("Add Weight");
      delay(4000);
    Serial.println("HX711 Found");
      scale.set_scale();
      scale2.set_scale();
    Serial.println("Remove Weight");
      delay(5000);

    Serial.println("Calibrate");
        scale.tare();
        scale2.tare();
    Serial.println(" Tare Done");
    Serial.println("Weight Ref1");
      delay(1000);
      
        for(int i = 0 ; i < 10;  i++){
          ref1 = scale.read_average(10);
          ref_Scale2 = scale2.read_average(10);
          delay(100);
        }

    Serial.println("add Weight");
      delay(2000);

        for (int i = 0; i < 10; i++){
          ref2 = scale.read_average(10);
          ref2_Scale2 = scale2.read_average(10);
        }
    
    Serial.println("Weight ref2");
    Serial.println("Remove Weight");
      delay(2000);
    Serial.print("Done");
        set = false;
    }
    else{ 
  Serial.println("Put Weight");
   delay(10);
   long reading = scale.read_average(10);
  long reading2 = scale2.read_average(10);
   Serial.print("gram 1 : ");
   Serial.println((reading-ref1)/((ref2-ref1)/ref_W)); // +- 11 gram // base using acrylic
   Serial.print("gram 2 : ");
    Serial.println((reading2-ref_Scale2)/((ref2_Scale2-ref_Scale2)/ref_W2));
   //(Reading- Weight without Load)/ (Weight with load-weight without load/ref_W)

   //Serial.println(reading);

    }
  } else {
    Serial.println("HX711 not found.");
  }

 delay(500);
  
}
