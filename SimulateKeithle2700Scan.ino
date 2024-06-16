#include <Arduino.h>

// 記憶するチャンネルリストの最大数
#define MAX_CHANNELS 10

// 記憶するチャンネルリスト
int channels[MAX_CHANNELS];
int channelCount = 0;

// 受信バッファのサイズ
#define BUFFER_SIZE 64
char inputBuffer[BUFFER_SIZE];
int bufferIndex = 0;

void setup() {
  // シリアル通信を開始
  Serial.begin(9600);
  // 入力バッファをクリア
  clearBuffer();
}

void loop() {
  // シリアルからデータを受信
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    
    // 改行文字を受信したらコマンドを処理
    if (receivedChar == '\n' || receivedChar == '\r') {
      if (bufferIndex > 0) {
        inputBuffer[bufferIndex] = '\0';
        processCommand(inputBuffer);
        clearBuffer();
      }
    } else {
      // バッファに文字を追加
      if (bufferIndex < BUFFER_SIZE - 1) {
        inputBuffer[bufferIndex++] = receivedChar;
      }
    }
  }
}

void processCommand(char* command) {
  // "SET" コマンドの処理
  if (strncmp(command, "SET ", 4) == 0) {
    setChannels(command + 4);
  }
  // "READ?" コマンドの処理
  else if (strcmp(command, "READ?") == 0) {
    readChannels();
  }
}

void setChannels(char* channelList) {
  // チャンネルリストを初期化
  channelCount = 0;

  // チャンネルリストの先頭を確認し、「@」、「(」をスキップ
  while (*channelList == '@' || *channelList == '(' || *channelList == ' ') {
    channelList++;
  }
  
  // チャンネルリストの終わりの「)」を削除
  char* endPtr = strchr(channelList, ')');
  if (endPtr != NULL) {
    *endPtr = '\0';
  }
  
  // チャンネルリストを解析して記憶
  char* token = strtok(channelList, ",");
  while (token != NULL && channelCount < MAX_CHANNELS) {
    Serial.println(token); // 中身確認用
    channels[channelCount++] = atoi(token);
    token = strtok(NULL, ",");
  }
}

void readChannels() {
  for (int i = 0; i < channelCount; i++) {
    if (i > 0) {
      Serial.print(',');
    }
    float randomValue = random(0, 100) / 100.0;
    Serial.print(randomValue, 2);
    Serial.print(',');
    Serial.print(channels[i]);
  }
  Serial.println();
}

void clearBuffer() {
  memset(inputBuffer, 0, BUFFER_SIZE);
  bufferIndex = 0;
}
