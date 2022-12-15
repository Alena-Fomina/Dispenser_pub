// Сонар
#define PIN_TRIG 12 
#define PIN_ECHO 11
// Motor-shield, клеммы M1+ M1-
// Предположим, что для движка LOW - вниз, HIGH - вверх
#define SPEED_1       5 
#define DIR_1         4
const int pin_d = 8; //пин подключения нижнего концевика
const int pin_u = 13; //пин подключения верхнего концевика
long duration, cm;
int flag = 0;
void setup() {
  Serial.begin(9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(DIR_1, OUTPUT);
  pinMode(SPEED_1, OUTPUT);
  pinMode(pin_d, INPUT); 
  pinMode(pin_u, INPUT);
}

void loop(){
  if (flag == 0) { // Ждём человека
  	// Генерируем короткий импульс длительностью 2 микросекунды
  	digitalWrite(PIN_TRIG, LOW);
  	delayMicroseconds(2);
  	digitalWrite(PIN_TRIG, HIGH);
  	// Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц
  	delayMicroseconds(10);
  	digitalWrite(PIN_TRIG, LOW);
    //  Время задержки акустического сигнала на эхолокаторе
  	duration = pulseIn(PIN_ECHO, HIGH);
    // Преобразовываем время в расстояние
  	cm = duration / 58;
    Serial.println(cm);
    // Если расстояние менее 5см, начинаем движение вниз
    if (cm < 5) {
      Serial.println("down");
      flag = 1;
      // Устанавливаем направление мотора «M1» в одну сторону
      digitalWrite(DIR_1, LOW);
      // Включаем мотор
      analogWrite(SPEED_1, 125);
    }
  }
  if (flag == 1) { // Движемся вниз
    while (digitalRead(pin_d) == LOW) { // Пока не нажат нижний концевик, ждём
      delay(30);
    }
    // Вышли из цикла -> нижний концевик нажат -> начинаем движение вверх
    Serial.println("up");
    flag = 2;
    // Выключаем мотор
    analogWrite(SPEED_1, 0);
    // Устанавливаем направление мотора «M1» в другую сторону
    digitalWrite(DIR_1, HIGH);
    // Включаем мотор
    analogWrite(SPEED_1, 125);
  }
  if (flag == 2) { // Движемся вверх
    while (digitalRead(pin_u) == LOW) { // Пока не нажат верхний концевик, ждём
      delay(30);
  	}
    // Вышли из цикла -> верхний концевик нажат -> останавливаемся
    flag = 0;
    // Выключаем мотор
    analogWrite(SPEED_1, 0);
    Serial.println("-------");
  }
  delay(30);
}
