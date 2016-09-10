#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_AUTOMATIC); 
#endif

//button pins
int button3 = D17;
int button5 = D16;
int button2 = D15;
int button4 = D14;
int button1 = D13;
int button6 = D12;

//button states
int b1[3] = {0, 0, 0};
int b2[3] = {0, 0, 0};
int b3[3] = {0, 0, 0};
int b4[3] = {0, 0, 0};
int b5[3] = {0, 0, 0};
int b6[3] = {0, 0, 0};

//debouncing timming
unsigned long db1 = 0;
unsigned long db2 = 0;
unsigned long db3 = 0;
unsigned long db4 = 0;
unsigned long db5 = 0;
unsigned long db6 = 0;

//debouncing variables
int debounceDelay = 50;
int buttonDelay = 1000;

//main function wait
unsigned long timer = 0;
unsigned long inputDelay = 500;

//char array
char letters[42] = " etnaslporugdwyqihmbcvkzfxj      ., ?   !";

// MAIN //
void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLDOWN);
  pinMode(button2, INPUT_PULLDOWN);
  pinMode(button3, INPUT_PULLDOWN);
  pinMode(button4, INPUT_PULLDOWN);
  pinMode(button5, INPUT_PULLDOWN);
  pinMode(button6, INPUT_PULLDOWN);

}
void loop() {
  int result = 0;
  bool p = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  int e = 0;
  int f = 0;
  b1[0] = digitalRead(button1);
  b2[0] = digitalRead(button2);
  b3[0] = digitalRead(button3);
  b4[0] = digitalRead(button4);
  b5[0] = digitalRead(button5);
  b6[0] = digitalRead(button6);
  if (debounce(b1[0], b1[1], b1[2], button1, db1)) {a = 1;}
  if (debounce(b2[0], b2[1], b2[2], button2, db2)) {b = 1;}
  if (debounce(b3[0], b3[1], b3[2], button3, db3)) {c = 1;}
  if (debounce(b4[0], b4[1], b4[2], button4, db4)) {d = 1;}
  if (debounce(b5[0], b5[1], b5[2], button5, db5)) {e = 1;}
  if (debounce(b6[0], b6[1], b6[2], button6, db6)) {f = 1;}
  if ((a+b+c+d+e+f) != 0) {
    timer = millis();
    p = 1;
    while ((millis() - timer) < inputDelay) {
      b1[0] = digitalRead(button1);
      b2[0] = digitalRead(button2);
      b3[0] = digitalRead(button3);
      b4[0] = digitalRead(button4);
      b5[0] = digitalRead(button5);
      b6[0] = digitalRead(button6);
      
      if (debounce(b1[0], b1[1], b1[2], button1, db1)) {a = 1;}
      if (debounce(b2[0], b2[1], b2[2], button2, db2)) {b = 1;}
      if (debounce(b3[0], b3[1], b3[2], button3, db3)) {c = 1;}
      if (debounce(b4[0], b4[1], b4[2], button4, db4)) {d = 1;}
      if (debounce(b5[0], b5[1], b5[2], button5, db5)) {e = 1;}
      if (debounce(b6[0], b6[1], b6[2], button6, db6)) {f = 1;}
    }
    if (a) {result += 1;}
    if (b) {result += 2;}
    if (c) {result += 4;}
    if (d) {result += 8;}
    if (e) {result += 16;}
    if (f) {result += 32;}
    
    //Here for decoding purposes
    //Serial.println(a);
    //Serial.println(b);
    //Serial.println(c);
    //Serial.println(d);
    //Serial.println(e);
    //Serial.println(f);
    Serial.print(letters[result]);
    result = 0;
  }
}

bool debounce(int &b, int &b_pre, int &b_low, int button, unsigned long &test) {
  bool result = 0;
  b = digitalRead(button);
  if (b != b_pre) {
    test = millis();
    b_pre = b;
  }
  if ((millis() - test) > debounceDelay) {
    if (b != b_low) {
      if (b == HIGH) { result = 1;}
      b_low = b;
    }
  }
  return result;
}
