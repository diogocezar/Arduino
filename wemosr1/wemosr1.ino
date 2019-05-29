 
void setup() {
pinMode(LED_BUILTIN, OUTPUT); // Inicializa LED_BUILTIN como saída
}
void loop() {
digitalWrite(LED_BUILTIN, LOW); // Liga o led
delay(1000); // espera 1 segundo
digitalWrite(LED_BUILTIN, HIGH); // Desliga o led
delay(2000); // espera 2 segundos
}
