// демо-пример: инициализация и настройки
// крупный приёмник SYN480R [VCC: 3.3-5.5V, logic: VCC]
// или MX-RM-5V (RF-5V) [VCC: 5V, logic: 5V]

// дефайны перед подключением библиотеки
//#define G433_MANCHESTER   // интерфейс Manchester Coding для экспериментов =)
//#define G433_SPEED 1000   // скорость 100-8000 бит/с, по умолч. 2000 бит/с

#include <Gyver433.h>
//Gyver433_RX<пин> rx;
//Gyver433_RX<пин, буфер> rx;
//Gyver433_RX<пин, буфер, CRC> rx;

// пин: цифровой пин
// буфер: размер буфера в байтах. По умолч. 64
// CRC: проверка целостности данных: G433_CRC8 (надёжный), G433_XOR (лёгкий), G433_NOCRC (отключено). По умолч. G433_CRC8

Gyver433_RX<2, 20> rx;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // "тик" опрашивает радио и вернёт количество успешно принятых байт
  // tick принимает асинхронно, но может ловить ошибки при загруженном коде
  // tickWait блокирует выполнение, но принимает данные чётко

  //if (rx.tick()) {
  if (rx.tickWait()) {
    // принятые данные доступны в .buffer
    // и имеют размер .size
    Serial.write(rx.buffer, rx.size);

    // выведем также качество связи
    Serial.print(", RSSI: ");
    Serial.println(rx.getRSSI());
  }
}
