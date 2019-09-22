#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>
#define MQ135 A0
#define RLOAD 1.0
#define r0Air 1
#define scaleFactorCO 662.9382
#define exponentCO 4.0241
#define scaleFactorCO2 116.6020682
#define exponentCO2 2.769034857
#define scaleFactorEthanol 75.3103
#define exponentEthanol 3.1459
#define scaleFactorNH4 102.694
#define exponentNH4 2.48818
#define scaleFactorToluene 43.7748
#define exponentToluene 3.42936
#define scaleFactorAcetone 33.1197
#define exponentAcetone 3.36587
#define atmCO 1
#define atmCO2 350
#define atmEthanol 22.5
#define atmNH4 15
#define atmToluene 2.9
#define atmAcetone 16

byte mac[] = {0x0A, 0x1B, 0x2C, 0x3D, 0x4E, 0x5F };
int port = 1778;
IPAddress server(116,90,239,3);
IPAddress ip(192,168,24,178);
EthernetClient client;

float r0CO,r0CO2,r0Ethanol,r0NH4,r0Toluene,r0Acetone;
float ppmCO, ppmCO2,ppmEthanol,ppmNH4,ppmToulene,ppmAcetone;
int mPin=7; 
int ledp=6; 
int samplet=280;
int deltat=40;
int sleept=9680;
float vo;
float calv=0;
float dust;
float a=0,b=0,c=0,d=0,e=0,f=0,g=0;
float aa,bb,cc,dd,ee,ff;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	Serial.begin(9600);
	lcd.begin(16, 2);
	while (!Serial) {
	Serial.println("connecting");  }
	// start the Ethernet connection:
	lcd.print("Ethernet Setting");
	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
		// try to congifure using IP address instead of DHCP:
		IPAddress server (192,168,24,177);
		int port =80;
		Ethernet.begin(mac, ip);
	}
	delay(1000);
	Serial.println("connecting...");
	Serial.print("My IP address: ");
	Serial.println(Ethernet.localIP());
	delay(1000);
	lcd.clear();
	pinMode(ledp,OUTPUT);
	pinMode(mPin,INPUT);
	lcd.setCursor(0,0);
	lcd.print("Calibration");
	Serial.print("Calibrating please wait.........");
for(int i=0;i<1000;i++){
    r0CO=getResistance() * pow((atmCO/scaleFactorCO), (1./exponentCO));
    r0CO2=getResistance() * pow((atmCO2/scaleFactorCO2), (1./exponentCO2));
    r0Ethanol=getResistance() * pow((atmEthanol/scaleFactorEthanol), (1./exponentEthanol));
    r0NH4=getResistance() * pow((atmNH4/scaleFactorNH4), (1./exponentNH4));
    r0Toluene=getResistance() * pow((atmToluene/scaleFactorToluene), (1./exponentToluene));
    r0Acetone=getResistance() * pow((atmAcetone/scaleFactorAcetone), (1./exponentAcetone));
    delay(100);
}
	delay(5000);
	lcd.clear();
	Serial.print("\n Calibration for RZero value of respective Gases in ohm  \n");
	Serial.print(" \n   ");  
	Serial.print("CO RZero Value: ");
	Serial.print(getResistance() * pow((atmCO/scaleFactorCO), (1./exponentCO)));
	Serial.print( "ohm" );
	Serial.print("  CO2 RZero Value:  ");
	Serial.print(getResistance() * pow((atmCO2/scaleFactorCO2), (1./exponentCO2)));
	Serial.print( "ohm" );
	Serial.print("  Ethanol RZero Value:  ");
  Serial.print(getResistance() * pow((atmEthanol/scaleFactorEthanol), (1./exponentEthanol)));
  Serial.print( "ohm" );
  Serial.print("  NH4 RZero Value:  ");
  Serial.print(getResistance() * pow((atmNH4/scaleFactorNH4), (1./exponentNH4)));
  Serial.print( "ohm" );  
  Serial.print("  Toluene RZero Value:   ");
  Serial.print(getResistance() * pow((atmToluene/scaleFactorToluene), (1./exponentToluene)));
  Serial.print( "ohm" );
  Serial.print("  Acetone RZero Value:   ");
  Serial.print(getResistance() * pow((atmAcetone/scaleFactorAcetone), (1./exponentAcetone)));
  Serial.print( "ohm" );
  lcd.setCursor(0,1);
  lcd.print("Complete");delay(2000);
  lcd.clear();
  Serial.print("\n Respective Gases with PPM  \n");
  delay(2000);
}

void loop() {
   for (int i=1; i<=10;i++){
   ppmCO=scaleFactorCO * pow((getResistance()/r0CO), -exponentCO);
   aa=ppmCO; a=a+aa;
   ppmCO2=scaleFactorCO2 * pow((getResistance()/r0CO2), -exponentCO2);
   bb=ppmCO2;  b=b+bb;
   ppmEthanol=scaleFactorEthanol * pow((getResistance()/r0Ethanol), -exponentEthanol);
   cc=ppmEthanol;  c=c+cc;
   ppmNH4=scaleFactorNH4 * pow((getResistance()/r0NH4), -exponentNH4);
   dd=ppmNH4;  d=d+dd;
   ppmToulene=scaleFactorToluene * pow((getResistance()/r0Toluene),-exponentToluene);
   ee=ppmToulene;  e=e+ee;
   ppmAcetone=scaleFactorAcetone * pow((getResistance()/r0Acetone), -exponentAcetone);
   ff=ppmAcetone;  f=f+ff;

   digitalWrite(ledp,LOW);
   delayMicroseconds(samplet);
   vo=analogRead(mPin);
   calv=vo*(5.0/1024.0);
   delayMicroseconds(deltat);
   digitalWrite(ledp,HIGH);
   delayMicroseconds(sleept);
   dust=0.17*calv-0.1;
   g=g+dust;




lcd.setCursor(0,0);
lcd.print("AQM");
lcd.setCursor(0,1);
lcd.print("CO : ");  lcd.print(aa); lcd.print("ppm"); delay(2000);
lcd.setCursor(0,0);
lcd.print("CO2 : ");    lcd.print(bb);    lcd.print("ppm");
lcd.setCursor(0,1);
lcd.print("ETHANOL: ");  lcd.print(cc);delay(2000);
lcd.setCursor(0,0);
lcd.print("NH4 : ");      lcd.print(dd);lcd.print("ppm"); 
lcd.setCursor(0,1);
lcd.print("TOULENE: ");  lcd.print(ee); delay(2000);
lcd.setCursor(0,0);
lcd.print("ACETONE: ");  lcd.print(ff);  
lcd.setCursor(0,1);
lcd.print("DUST:");         lcd.print(dust);  lcd.print("mg/m^3");  delay(2000);
lcd.clear();
}

ppmCO=a/10;
ppmCO2=b/10;
ppmEthanol=c/10;
ppmNH4=d/10;
ppmToulene=e/10;
ppmAcetone=f/10;
g=g/10;

    lcd.setCursor(0,0);
    lcd.print("AQM");
    lcd.setCursor(0,1);
    lcd.print("CO : ");      lcd.print(a); lcd.print("ppm"); delay(2000);
    lcd.setCursor(0,0);
    lcd.print("CO2 : ");     lcd.print(b);    lcd.print("ppm");
    lcd.setCursor(0,1);
    lcd.print("ETHANOL: ");  lcd.print(c);delay(2000);
    lcd.setCursor(0,0);
    lcd.print("NH4 : ");     lcd.print(d);lcd.print("ppm"); 
    lcd.setCursor(0,1);
    lcd.print("TOULENE: ");  lcd.print(e);delay(2000);
    lcd.setCursor(0,0);
    lcd.print("ACETONE: ");  lcd.print(f);  
    lcd.setCursor(0,1);
    lcd.print("DUST:");      lcd.print(g);  lcd.print("mg/m^3");  delay(2000);
 lcd.clear();


if (client.connect(server,port)) {
      Serial.println("connected");   
      client.print("GET /write_data1.php?");
      client.print("Dust=");
      client.print(g);
      client.print("&NH4=");
      client.print(ppmNH4);
      client.print("&Ethanol=");
      client.print(ppmEthanol);
      client.print("&Acetone=");
      client.print(ppmAcetone);
      client.print("&Toulene=");
      client.print(ppmToulene);
      client.print("&CO=");
      client.print(ppmCO);
      client.print("&CO2=");
      client.print(ppmCO2);
      client.println(" HTTP/1.1"); // Part of the GET request
      client.println("Host: 192.168.24.177");
      client.println("Connection: close");
      client.println(); // Empty line
      client.println(); // Empty line
      client.stop();    // Closing connection to server
  }
  else {
    Serial.println("--> connection failed\n");
  }
a=0;	b=0;	c=0;	d=0;	e=0;	f=0;	g=0;
delay(1000);
}

float getResistance() {
    int val = analogRead(MQ135);
    return ((1024./(float)val) * 5. - 1.)*RLOAD;
}
