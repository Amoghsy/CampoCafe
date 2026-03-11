#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {A0,A1,A2,A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int total = 0;
bool waitingConfirmation = false;

void showMenu()
{
lcd.clear();
lcd.print("1 Tea 10");
lcd.setCursor(0,1);
lcd.print("2 Coffee 15");
delay(2000);

lcd.clear();
lcd.print("3 Sandwich30");
lcd.setCursor(0,1);
lcd.print("4 Juice 25");
delay(2000);

lcd.clear();
lcd.print("Select Item:");
lcd.setCursor(0,1);
lcd.print("#Bill *Reset");

Serial.println("----- MENU -----");
Serial.println("1 Tea 10");
Serial.println("2 Coffee 15");
Serial.println("3 Sandwich 30");
Serial.println("4 Juice 25");
Serial.println("# Generate Bill");
Serial.println("* Reset Order");
}

void processChoice(char choice)
{

if(waitingConfirmation)
{
if(choice=='A')
{
lcd.clear();
lcd.print("Order Confirmed");
Serial.println("Order Confirmed");

delay(3000);

total = 0;
waitingConfirmation = false;
showMenu();
}

else if(choice=='B')
{
lcd.clear();
lcd.print("Order Cancelled");
Serial.println("Order Cancelled");

delay(3000);

total = 0;
waitingConfirmation = false;
showMenu();
}

return;
}

switch(choice)
{

case '1':
total += 10;
Serial.println("Tea Added");
break;

case '2':
total += 15;
Serial.println("Coffee Added");
break;

case '3':
total += 30;
Serial.println("Sandwich Added");
break;

case '4':
total += 25;
Serial.println("Juice Added");
break;

case '#':
showBill();
return;

case '*':
total = 0;
lcd.clear();
lcd.print("Order Reset");
Serial.println("Order Reset");
delay(1500);
showMenu();
return;

default:
Serial.println("Invalid Choice");
return;
}

lcd.clear();
lcd.print("Item Added");
lcd.setCursor(0,1);
lcd.print("Total Rs ");
lcd.print(total);

Serial.print("Current Total = Rs ");
Serial.println(total);

delay(1500);
showMenu();
}

void showBill()
{
lcd.clear();
lcd.print("Final Bill:");
lcd.setCursor(0,1);
lcd.print("Rs ");
lcd.print(total);

Serial.println("----- FINAL BILL -----");
Serial.print("Total = Rs ");
Serial.println(total);

delay(3000);

lcd.clear();
lcd.print("Confirm?");
lcd.setCursor(0,1);
lcd.print("A Yes B No");

Serial.println("Confirm Order?");
Serial.println("Press A for YES");
Serial.println("Press B for NO");

waitingConfirmation = true;
}

void setup()
{
Serial.begin(9600);
lcd.begin(16,2);

lcd.print("CANTEEN SYSTEM");
Serial.println("CANTEEN SYSTEM");

delay(2000);

showMenu();
}

void loop()
{
char key = keypad.getKey();

if(key)
{
processChoice(key);
}

if(Serial.available())
{
char input = Serial.read();
processChoice(input);
}
}