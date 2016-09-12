/*
 * Mini T9 Keyboard Controller
 * 2016/9/11
 * By Scarlett (Sijia Teng)
 * CS294-84 Interactive Device Design HW2, UC Berkeley
 */

#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_AUTOMATIC); 
#endif
/*
 * Definitions
 */
int k[10],led=D7;//turn on LED when a key is being pressed
char cat[10][3]={{44,46,63},{'a','b','c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'},{'p','q','r'},{'s','t','u'},{'v','w','x'},{'y','z',32}};
int sta[10][3];//each key has 3 states, ie, 3 letters

/*
 * Setup
 */
void setup() {
  k[1]=D6;
  k[2]=D5;
  k[3]=D4;
  k[4]=D3;
  k[5]=D2;
  k[6]=D1;
  k[7]=D0;
  k[8]=D8;
  k[9]=D9;
  k[0]=D10;
  for(int i=0; i<10; i++)
    pinMode(k[i], INPUT_PULLDOWN);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(9600);
}

/*
 * Detect one time of pressing a key and let go
 */
int detect_key(){
  for(int i=0;i<10;i++){
    if (digitalRead(k[i]) == HIGH){
    delay(50);
    while(digitalRead(k[i]) == HIGH) digitalWrite(led, HIGH);
    digitalWrite(led, LOW);
    delay(50);
    return i;
  }
  }
  return -1;
}

/*
 * Scan the 9 keys and update the status and see if need to output according to time slot
 */
void loop() {
  int key_index_new=-1,key_index_old=-1;
  int letter_index=0;
  while((key_index_new=detect_key()) && key_index_new!=-1){
    if(key_index_old==-1){
      key_index_old=key_index_new;
    }
    else if(key_index_new!=key_index_old){
      Serial.print(cat[key_index_old][letter_index]);
      key_index_old=key_index_new;
    }
    else{
      letter_index=(letter_index+1)%3;
    }
    delay(200);
  }
  if(key_index_old!=-1){
    Serial.print(cat[key_index_old][letter_index]);
    key_index_old=-1;
    letter_index=0;
  }
}


