char Receive;//射频无线串口接收到的字符变量定义为“Receive”
const int M0 = 2;//射频无线串口M0接口
const int M1 = 3;//射频无线串口M1接口
const int KM = 4;//IO-4口连接交流接触器辅助常开触点
const int DelayTime = 1000;//程序消抖延迟时间
void setup() { //初始化设备
  pinMode(M0, OUTPUT);//定义M0口为输出
  pinMode(M1, OUTPUT);//定义M1口为输出
  pinMode(M0, HIGH);//射频无线串口M0接口，高电位
  pinMode(M1, HIGH);//射频无线串口M1接口，高电位
  pinMode(KM, INPUT_PULLUP);//将KM设置为输入接口，并使用内部上拉电阻拉高电位
  Serial.begin(9600);//射频无线串口TTL波特率
}
void loop() {//主程序
  Receive = Serial.read();//定义Receive的内容为射频无线串口接收到的字符
  if (digitalRead(KM) == LOW) {//如果交流接触器常开触点闭合
    Serial.println("F");//则通过射频无线串口发送字符"F"
    delay(DelayTime * 10);//程序消抖延迟时间
  } else if (digitalRead(KM) == HIGH) {//如果交流接触器常开触点打开
    Serial.println("N");//则通过射频无线串口发送字符"N"
    delay(DelayTime * 10); //程序消抖延迟时间
  }
}
