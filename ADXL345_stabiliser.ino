
#include <Wire.h>
#include <ADXL345.h>

ADXL345 accelerometer;

void showRange(void)
{
  Serial.print("Selected measurement range: "); 

  switch(accelerometer.getRange())
  {
    case ADXL345_RANGE_16G: Serial.println("+/- 16 g"); break;
    case ADXL345_RANGE_8G:  Serial.println("+/- 8 g");  break;
    case ADXL345_RANGE_4G:  Serial.println("+/- 4 g");  break;
    case ADXL345_RANGE_2G:  Serial.println("+/- 2 g");  break;
    default: Serial.println("Bad range"); break;
  }
}

void showDataRate(void)
{
  Serial.print("Selected data rate: "); 

  switch(accelerometer.getDataRate())
  {
    case ADXL345_DATARATE_3200HZ: Serial.println("3200 Hz"); break;
    case ADXL345_DATARATE_1600HZ: Serial.println("1600 Hz"); break;
    case ADXL345_DATARATE_800HZ:  Serial.println("800 Hz");  break;
    case ADXL345_DATARATE_400HZ:  Serial.println("400 Hz");  break;
    case ADXL345_DATARATE_200HZ:  Serial.println("200 Hz");  break;
    case ADXL345_DATARATE_100HZ:  Serial.println("100 Hz");  break;
    case ADXL345_DATARATE_50HZ:   Serial.println("50 Hz");   break;
    case ADXL345_DATARATE_25HZ:   Serial.println("25 Hz");   break;
    case ADXL345_DATARATE_12_5HZ: Serial.println("12.5 Hz"); break;
    case ADXL345_DATARATE_6_25HZ: Serial.println("6.25 Hz"); break;
    case ADXL345_DATARATE_3_13HZ: Serial.println("3.13 Hz"); break;
    case ADXL345_DATARATE_1_56HZ: Serial.println("1.56 Hz"); break;
    case ADXL345_DATARATE_0_78HZ: Serial.println("0.78 Hz"); break;
    case ADXL345_DATARATE_0_39HZ: Serial.println("0.39 Hz"); break;
    case ADXL345_DATARATE_0_20HZ: Serial.println("0.20 Hz"); break;
    case ADXL345_DATARATE_0_10HZ: Serial.println("0.10 Hz"); break;
    default: Serial.println("Bad data rate"); break;
  }
}

void setup(void) 
{
  pinMode(2,OUTPUT); //motor 1
  pinMode(3,OUTPUT); //motor 1
  pinMode(4,OUTPUT); //motor 2
  pinMode(5,OUTPUT); //motor 2
  Serial.begin(9600);

  // Initialize ADXL345
  Serial.println("Initialize ADXL345");
  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }
  // Set measurement range
  // +/-  2G: ADXL345_RANGE_2G
  // +/-  4G: ADXL345_RANGE_4G
  // +/-  8G: ADXL345_RANGE_8G
  // +/- 16G: ADXL345_RANGE_16G
  accelerometer.setRange(ADXL345_RANGE_16G);
  // Show current setting
  showRange();
  showDataRate();
}

void loop(void) 
{
  // Read normalized values
  Vector raw = accelerometer.readRaw();

  // Read normalized values
  Vector norm = accelerometer.readNormalize();
  float val=raw.XAxis;
  // Output raw
  Serial.print(" Xraw = ");
  Serial.println(val);
  while (val<=1000)
  {
    Vector raw = accelerometer.readRaw();
    // Read normalized values
    Vector norm = accelerometer.readNormalize();
    float valnew=raw.XAxis;
    Serial.print(" Xaxis = ");
    Serial.print(valnew);
    Serial.print(" Yaxis = ");
    Serial.print(raw.YAxis);
    Serial.print(" Zaxis = ");
    Serial.println(raw.ZAxis);
    if (valnew>=val+10)
    {
      //digitalWrite(3,LOW);
      digitalWrite(2,HIGH);
      delay(2000);
      //digitalWrite(3,LOW);
      digitalWrite(2,LOW);
      //motor 1 is ON for 1sec
      //motor 1 is OFF for 4secs
    }
    else if (valnew<=val-10)
    {
      //digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      delay(2000);
      //digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      //motor 2 is ON for 1sec
      //motor 2 is OFF for 4secs
    }
    else
    {
      digitalWrite(2,LOW);
      //digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      //digitalWrite(5,LOW);
      //both motors are off
    }
    delay(1000);
  }
  //Serial.print(" Yraw = ");
  //Serial.print(raw.YAxis);
  //Serial.print(" Zraw: ");
  //Serial.print(raw.ZAxis); 
  // Output normalized m/s^2
  //Serial.print(" Xnorm = ");
  //Serial.print(norm.XAxis);
  //Serial.print(" Ynorm = ");
  //Serial.print(norm.YAxis);
  //Serial.print(" Znorm = ");
  //Serial.print(norm.ZAxis);

  //Serial.println();

  
}
