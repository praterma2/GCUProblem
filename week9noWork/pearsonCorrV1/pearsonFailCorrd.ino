#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

/*
  Topic 5: Writing a Function to Assess Physical Data

  matt prater
  04mar2025
  matt.prater@my.gcu.edu

  Answers to questions:
  

*/
//need array definition 
float pearsonCorr(int arr1[], int N1, int arr2[], int N2);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  CircuitPlayground.begin();
}

void loop() {
  //create variables
  int N = 100;
  int light[N];
  int accelZ[N];
  float r;

  //collect data
  for(int i = 0; i < N; i++){
    light[i] = CircuitPlayground.lightSensor();
    accelZ[i] = CircuitPlayground.motionZ();
    //print out values
    Serial.print(light[i]);
    Serial.print("     ");
    Serial.println(accelZ[i]);
    delay(50);
  }

  //run pearson on data
  r = pearsonCorr(light, N, accelZ, N);

  //display pearson results
  Serial.println();
  Serial.print("The Pearson Correlation coefficient (r) is: ");
  Serial.println(r);
  Serial.println();

}


float pearsonCorr(int arr1[], int N1, int arr2[], int N2){
  //create variables
  int j;
  float sumArr1 = 0, sumArr2 = 0;
  float avgArr1 = 0;
  float avgArr2 = 0;
  float num1 = 0, den1 = 0, den2 = 0;
  float R;

  //sum both arrays
  for(j = 0; j < N1; j++){
    sumArr1 +=  arr1[j];
    sumArr2 +=  arr2[j];
  }

  //determine averages for both arrays
  avgArr1 = sumArr1 / N1;
  avgArr2 = sumArr2 / N1;

  //determine number and density
  for(j = 0; j < N1; j++){
    num1 += (arr1[j] - avgArr1)*(arr2[j] - avgArr2);
    den1 += sq(arr1[j] - avgArr1);
    den2 += sq(arr2[j] - avgArr2);
  }

  //determine pearson
  R = num1/sqrt(den1*den2);

  //return pearson to outside
  return R;
}
