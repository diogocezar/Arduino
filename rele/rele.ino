
 

int rele1 = 7;
int rele2 = 8;
int rele3=9;
 
int estadorele1 = 1;
int estadorele2 = 1;
int estadorele3 = 1;
 
void setup()
{
  //Define pinos para o rele como saida
  pinMode(rele1, OUTPUT); 
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  
  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);
   digitalWrite(rele2, LOW);
}
 
void loop()
{
  
    digitalWrite(rele1, estadorele1);  
    
  
}
