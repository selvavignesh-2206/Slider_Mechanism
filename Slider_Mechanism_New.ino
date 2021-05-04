const int IN2=5;
const int IN1=4;
const int PWM=6;

bool upperSen;
bool lowerSen;

String input;

int limitSwitch = 9;

void Motor_Down(int Speed) {
     digitalWrite(7, LOW);
     digitalWrite(8, LOW);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     analogWrite(PWM,Speed);
}
void Motor_Up(int Speed) {
     digitalWrite(7, LOW);
     digitalWrite(8, LOW);
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     analogWrite(PWM,Speed);
}
void Motor_Brake(){
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,LOW);
     digitalWrite(7, HIGH);
     digitalWrite(8, HIGH);
     analogWrite(PWM, 0);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(2 , INPUT);
  pinMode(3, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(limitSwitch, INPUT);

  Serial.begin(115200);

Motor_Brake();
delay(1000);
}

void loop() {
 
 if (Serial.available() > 0) {
      input = Serial.readStringUntil('.');
      Serial.println(input);

      if (input == "DOWN") {
          
          while (digitalRead(2)== HIGH) {    //until upperSen is low
            Motor_Up(200); delay(10);
          }
          Motor_Brake();
          Serial.println(1);
          upperSen = true;
          lowerSen = false;

      }

        if (input == "UP") {

            while(digitalRead(3) == HIGH) {//until lowerSen is LOW
                Motor_Down(200); delay(10);
            }

            Motor_Brake();
            upperSen = false;
            lowerSen = true;

            Serial.println(digitalRead(limitSwitch));
            
            if (digitalRead(limitSwitch)==0) {
              while (digitalRead(2) == HIGH) {
                Motor_Up(200);
              }
            
              Motor_Brake();
              Serial.println(0);
            } else {
              Serial.println(1);
            }
        }
}

}
