// Сонар
#define PIN_TRIG 12 
#define PIN_ECHO 11

long duration, cm;

void setup() {
  Serial.begin(9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}
void loop() {
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
    delay(30);
}
