void scenar1()
{
  verejne();
  SEM2(0);
  SEM3(0);
  SEM4(0);
  SEM1(0);
  SEM5(0);
  delay(cas);
  handleButtons();
  SEM1(1);
  SEM5(1);
  delay(cas);
  handleButtons();
  chodec1(1);
  SEM1(2);
  SEM5(2);
  delay(cas1);
  handleButtons();
  chodec1(0);
  SEM5(1);
  delay(cas);
  handleButtons();
}

void scenar2()
{
  verejne();
  SEM5(0);
  delay(cas);
  SEM2(1);
  SEM4(1);
  verejne();
  delay(cas);
  SEM2(2);
  SEM4(2);
  verejne();
  delay(cas1);
  SEM1(1);
  SEM2(1);
  verejne();
  delay(cas);
  SEM1(0);
  SEM2(0);
  verejne();
  delay(cas);
}

void scenar3()
{
  verejne();
  SEM3(1);
  chodec2(1);
  delay(cas);
  SEM3(2);
  verejne();
  delay(cas1);
  SEM3(1);
  SEM4(1);
  verejne();
  delay(cas);
  SEM3(0);
  SEM4(0);
  verejne();
  chodec2(0);
}

void blik()
{
  clear();
  verejne();
  delay(cas);
  SEM1(1);
  SEM2(1);
  SEM3(1);
  SEM4(1);
  SEM5(1);
  digitalWrite(28,HIGH);          //Digitalny zapis, High= Vysoka jednotka, zapina sa 
  digitalWrite(29,HIGH);
  delay(cas);
}

void clear()
{
  for(int i = 27; i < 46;i++)
  {
    digitalWrite(i,LOW);
  }
}



void SEM1(int stav)
{
  if(stav == 0)
  {
    digitalWrite(31,HIGH);
    digitalWrite(32,LOW);
    digitalWrite(33,LOW);
  }
  if(stav == 1)
  {
    digitalWrite(31,LOW);
    digitalWrite(32,HIGH);
    digitalWrite(33,LOW);
  }
  if(stav == 2)
  {
    digitalWrite(31,LOW);
    digitalWrite(32,LOW);
    digitalWrite(33,HIGH);
  }
}

void SEM2(int stav)
{
  if(stav == 0)
  {
    digitalWrite(34,HIGH);
    digitalWrite(35,LOW);
    digitalWrite(36,LOW);
  }
  if(stav == 1)
  {
    digitalWrite(34,LOW);
    digitalWrite(35,HIGH);
    digitalWrite(36,LOW);
  }
  if(stav == 2)
  {
    digitalWrite(34,LOW);
    digitalWrite(35,LOW);
    digitalWrite(36,HIGH);
  }
}

void SEM3(int stav)
{
  if(stav == 0)
  {
    digitalWrite(37,HIGH);
    digitalWrite(38,LOW);
    digitalWrite(39,LOW);
  }
  if(stav == 1)
  {
    digitalWrite(37,LOW);
    digitalWrite(38,HIGH);
    digitalWrite(39,LOW);
  }
  if(stav == 2)
  {
    digitalWrite(37,LOW);
    digitalWrite(38,LOW);
    digitalWrite(39,HIGH);
  }
}

void SEM4(int stav)
{
  if(stav == 0)
  {
    digitalWrite(40,HIGH);
    digitalWrite(41,LOW);
    digitalWrite(42,LOW);
  }
  if(stav == 1)
  {
    digitalWrite(40,LOW);
    digitalWrite(41,HIGH);
    digitalWrite(42,LOW);
  }
  if(stav == 2)
  {
    digitalWrite(40,LOW);
    digitalWrite(41,LOW);
    digitalWrite(42,HIGH);
  }
}

void SEM5(int stav)
{
  if(stav == 0)
  {
    digitalWrite(43,HIGH);
    digitalWrite(44,LOW);
    digitalWrite(45,LOW);
  }
  if(stav == 1)
  {
    digitalWrite(43,LOW);
    digitalWrite(44,HIGH);
    digitalWrite(45,LOW);
  }
  if(stav == 2)
  {
    digitalWrite(43,LOW);
    digitalWrite(44,LOW);
    digitalWrite(45,HIGH);
  }
}

void chodec1(int stav)
{
  if(stav1 || stav0)
  {  
    if(stav == 1)
    {
      digitalWrite(27,HIGH);
      digitalWrite(28,LOW);
    }
    else
    {
      digitalWrite(27,LOW);
      digitalWrite(28,HIGH);
      stav0 = false;
      stav1 = false;
    }
  }
}

void chodec2(int stav)
{
  if(stav2 || stav3)
  {
    SEM4(1);
    delay(cas);
    SEM4(0);

    if(stav == 1)
    {
      Serial.print("a");
      digitalWrite(30,HIGH);
      digitalWrite(29,LOW);
    }
    else
    {
      digitalWrite(30,LOW);
      digitalWrite(29,HIGH);
      stav2 = false;
      stav3 = false;
    }
  }
}

void verejne()
{
  if(analogRead(A8) > 500)
  {
    digitalWrite(22,HIGH);
    digitalWrite(23,HIGH);
    digitalWrite(24,HIGH);
    digitalWrite(25,HIGH);
    digitalWrite(26,HIGH);    
  }
  else
  {
    digitalWrite(22,LOW);
    digitalWrite(23,LOW);
    digitalWrite(24,LOW);
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);    
  }
}