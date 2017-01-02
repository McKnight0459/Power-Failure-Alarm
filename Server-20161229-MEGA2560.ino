#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);
char Receive;//射频无线串口接收到的字符变量定义为“Receive”
const int M1 = 2;//射频无线串口M1接口
const int M0 = 3;//射频无线串口M0接口
const int DelayTime = 500;//程序消抖延迟时间
const int delayGSM = 1000;//发短信用延迟时间
const int LedDelayTime = 1000; // LCD液晶屏延迟时间
boolean SendGSM;//定义布尔类型变量“SendGSM”
void GSMOFF() {//断电报警函数
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM" );
  Serial1.println("AT");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM." );
  Serial1.println("AT+CMGF=1");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM.." );
  Serial1.println("AT+CSMP=17,167,2,25");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM..." );
  Serial1.println("AT+CSCS=\"UCS2\"");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM...." );
  Serial1.println("AT+CMGS=\"00310033003800300034003600360039003300390036\"");//改成需要接收报警的手机号码
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM....." );
  Serial1.println("76D189C670B965AD7535FF0C4F4D7F6EFF1A4E09538267D077FF67D0961F67D04E95");//监视点断电，位置：三厂某矿某队某井
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM......." );
  Serial1.println((char)26);
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM.....Done" );
  delay(delayGSM * 2);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "                    " );
}
void GSMON() {//恢复供电短信函数
  Serial1.println("AT");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM." );
  Serial1.println("AT+CMGF=1");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM.." );
  Serial1.println("AT+CSMP=17,167,2,25");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM..." );
  Serial1.println("AT+CSCS=\"UCS2\"");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM...." );
  Serial1.println("AT+CMGS=\"00310033003800300034003600360039003300390036\"");
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM....." );
  Serial1.println("4F9B75355DF26062590D");//供电已恢复
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM......." );
  Serial1.println((char)26);
  delay(delayGSM);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "Sending GSM.....Done" );
  delay(delayGSM * 2);
  lcd.setCursor( 0, 3 );
  lcd.printstr( "                    " );
}
void setup() {//初始化设备
  lcd.init();
  lcd.backlight();
  lcd.setCursor( 0, 1 );
  lcd.printstr( "Power Failure Alarm." );
  delay( LedDelayTime * 3 );
  lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd.printstr( "Power Failure Alarm." );
  lcd.setCursor( 1, 2 );
  lcd.printstr( "Booting" );
  for ( int Boot = 9; Boot <= 17; Boot += 2 )
  {
    lcd.setCursor( Boot, 2 );
    lcd.printstr( ".." );
    delay(LedDelayTime * 2);
  }
  lcd.clear();
  Serial.begin(9600);//射频无线串口TTL波特率
  Serial1.begin(119400);//GSM软串口TTL波特率
  pinMode(M0, OUTPUT);//定义M0口为输出
  pinMode(M1, OUTPUT);//定义M1口为输出
  pinMode(M1, HIGH);//射频无线串口M1接口，高电位
  pinMode(M0, HIGH);//射频无线串口M1接口，高电位
  SendGSM = true;//默认设置为真，可解读为：发送那种属性短信？真=报警，假=消警
  Serial1.println("AT");
  delay(delayGSM);
  Serial1.println("AT");
  lcd.setCursor( 0, 0 );
  lcd.printstr( "Power Failure Alarm " );
  lcd.setCursor( 0, 1 );
  lcd.printstr( "Loc-1:" );
  lcd.setCursor( 0, 2 );
  lcd.printstr( "Loc-2:" );
  lcd.setCursor( 10, 1 );
  lcd.printstr( "Loc-3:" );
  lcd.setCursor( 10, 2 );
  lcd.printstr( "Loc-4:" );
}
void loop() {//主程序
  Receive = Serial.read();//定义Receive的内容为射频无线串口接收到的字符
  if (Receive == 'F' && SendGSM == true ) { //接收到射频无线串口发来的字符是"F"并且SendGSM为真
    lcd.setCursor( 6, 1 );
    lcd.printstr("OFF");//状态更新：停电中
    GSMOFF();//执行断电短信报警函数
    SendGSM = !SendGSM;//重新定义SendGSM为反状态（假"false"）
    Serial.println("OFF AND GSM");//通过射频无线串口发送字符"A"
  } else if (Receive == 'F') { //接收到射频无线串口发来的字符是"F"
    Serial.println("OFF");//通过射频无线串口发送字符"A"
    lcd.setCursor( 6, 1 );
    lcd.printstr("OFF");//状态更新：停电中
  } else if (Receive == 'N' && SendGSM == false )  { //接收到射频无线串口发来的字符是"N"并且SendGSM为假"false"
    lcd.setCursor( 6, 1 );
    lcd.printstr("ON ");//状态更新：通电中
    GSMON();//恢复供电短信函数
    SendGSM = !SendGSM;//重新定义SendGSM为反状态（真"true"）
    Serial.println("ON AND GSM");//"A"
  } else if (Receive == 'N')  { //接收到射频无线串口发来的字符是"N"
    Serial.println("ON ");//"A"
    lcd.setCursor( 6, 1 );
    lcd.printstr("ON ");//状态更新：通电中
  }
  for ( int i = 0; i <= 19; i ++ )//第四行待机动画
  {
    lcd.setCursor( i, 3 );
    lcd.printstr( "." );
    delay(20);
  }
  for ( int i = 0; i <= 19; i ++ )//第四行待机动画
  {
    lcd.setCursor( i, 3 );
    lcd.printstr( " " );
    delay(20);
  }
}
