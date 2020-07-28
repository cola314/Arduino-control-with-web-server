int in_data =0;
void setup(){
    Serial.begin(9600);
    Serial.print("hello");
    pinMode(13, OUTPUT);
}
 
void loop(){
    if(Serial.available()){
        in_data = Serial.parseInt();
      switch(in_data) {
        case 1 : digitalWrite(13, LOW); break;
        case 2 : digitalWrite(13, HIGH); break;
        default : break;
      }
    }
}
