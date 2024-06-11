


void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );     // シリアル通信を初期化する。通信速度は9600bps
}

void loop() {
  // 入力された文字列が完了した場合
  if(Serial.available()>0){
    String input = Serial.readStringUntil('\n');
    //Serial.print("Input is "); Serial.println(input);
      if(strcmp(input.c_str(), "READ?") == 0){
        Serial.println(random(20));
      }else if(strcmp(input.c_str(), "*IDN?") == 0){
        Serial.println("Company,2700,xxx123,0");
      }else{
        Serial.println("N/A");
      }
  }
}

