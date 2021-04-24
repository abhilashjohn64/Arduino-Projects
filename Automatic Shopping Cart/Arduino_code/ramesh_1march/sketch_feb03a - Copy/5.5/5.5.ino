#include <LiquidCrystal.h>
#include "SoftwareSerial.h"
SoftwareSerial client(13,12); 
const int rs = 6, en = 7,d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en,d4, d5, d6, d7);
boolean stringComplete=false;
String inputstring="";
int n=0,tmpn;
const int maxitem=15;
const int pushButton1 = 2; 
const int pushButton2 = 3;
const int pushButton3 = 4; 
String item, fullitem[maxitem][4];
char *titem;
volatile unsigned int price,count,total,icount;
char tmp[4],js[10],fjs[20];
void printitem();
void setup() 
{
  lcd.begin(16, 2);
  lcd.print("  SMART CART  ");
lcd.setCursor(0, 1);
lcd.print(" INTIALISING...."); 
  Serial.begin(9600);
   client.begin(9600);
  count=0;
  total=0;
inputstring.reserve(200);
 pinMode(pushButton1, INPUT);
 pinMode(pushButton2, INPUT);    
delay(3000);
lcd.clear();
lcd.print("  WELCOME ");
lcd.setCursor(0, 1);
lcd.print("HAPPY SHOPPING");
delay(3000);
}
void loop()
{   
lcd.clear();
lcd.print("Show your ");
lcd.setCursor(0, 1);
lcd.print("item");
delay(500);
   if(stringComplete)
      {
         if(inputstring.equals("27001707487F"))
         {
          item="PEN";
          price=17;
         }
         else if(inputstring.equals("270016726D2E"))
         {
          item="MILK";
          price=12;
          }
          else if (inputstring.equals("27001707B88F"))
          {
            item="BOX";
            price=100;
          }
          else if (inputstring.equals("270016859226"))
          {
            item="PEPSI";
            price=35;
          }
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(String(item) + ":Rs." + String(price));
          lcd.setCursor(0, 1);
          lcd.print("ADD / REMOVE");
          while(1)
          {
            if(digitalRead(pushButton1)==0 || digitalRead(pushButton2)==0)
            {
              break;
            }
          }
          if(digitalRead(pushButton1)==0)
          {
           total=total+price;
           tmpn=exist(item);
           if(tmpn>0)
           {
          icount=(fullitem[tmpn-1][3].toInt()/price)+1;
          fullitem[tmpn-1][2]=icount;
          fullitem[tmpn-1][3]=price*icount;
           }
           else
           {
          icount=1;
          fullitem[count][0]=item;
          fullitem[count][1]=price;
          fullitem[count][2]=icount;
          fullitem[count][3]=price*icount;
          count++;
           }
          
          lcd.clear();
          lcd.print(item +":"+ price);
          lcd.setCursor(0, 1);
          lcd.print("ADDED");
          delay(2000);
          lcd.clear();
          lcd.print("Now Total     ");
          lcd.setCursor(0, 1);
          strcpy(js,"Rs.");
          itoa(total,tmp,10);
          strcat(js,tmp);
          lcd.print(js);
          delay(2000);
          }
           if(digitalRead(pushButton2)==0)
          {
            if (total>0)
            {
              total=total-price;
            }
            else
            {
              total=0;
            }
           tmpn=exist(item);
           if(tmpn>0)
           {
          icount=(fullitem[tmpn-1][3].toInt()/price)-1;
          if(icount==0)
          {
            count--;
            removeitem(item);
          }
          else
          {
          fullitem[tmpn-1][2]=icount;
          fullitem[tmpn-1][3]=price*icount;
          }
           } 
          lcd.clear();
          lcd.print(item +":Rs"+ price);
          lcd.setCursor(0, 1);
          lcd.print("REMOVED");
          delay(2000);
          lcd.clear();
          lcd.print("Now Total");
          lcd.setCursor(0, 1);
          strcpy(js,"Rs.");
          itoa(total,tmp,10);
          strcat(js,tmp);
          lcd.print(js);
          delay(2000);
           }
            price=0;
         stringComplete=false;
         inputstring="";
      }
       if(digitalRead(pushButton3) ==0)
      {
          printitem();

          lcd.clear();
          lcd.print("Your Shopping");
          lcd.setCursor(0, 1);
          lcd.print("is completed");
          delay(1000);
          lcd.clear();
          lcd.print("Press again");
          lcd.setCursor(0, 1);
          lcd.print("to restart");
          while(digitalRead(pushButton3));
          total=0;
          count=0;
      }
}
void serialEvent()
{
  while(Serial.available())
  {
    n++;
    char inChar =(char) Serial.read();
   inputstring +=inChar;
    
    if(n>=12)
    { 
      n=0;
      stringComplete=true; 
    }
     }
 }
 unsigned int exist(String its)
 {
  for(int i=0;i<maxitem;i++)
  {
      if(fullitem[i][0].equals(its))
      {
        return(i+1);
      }
  }
  return(0);
 }

void removeitem(String its)
{
    
  for(int i=0;i<maxitem;i++)
  {
      if(fullitem[i][0].equals(its))
      {
      
        for (int c=i;c<maxitem;c++)
        {
          for(int k=0;k<4;k++)
           {
       
          fullitem[c][k]=fullitem[c+1][k].c_str();
           }
        }
        break;
      }
       
  }
}
void printitem()
{
     String webdata;
     webdata="<center><u><b>SMART&#160; &#160; SHOPPING&#160; &#160; CART </b></u></center><br/>";
     webdata="<hr/>";
     webdata="<br/>";
     webdata="<br/>";
webdata="<br/>";
       webdata="<b><i>Item &#160;&#160;&#160;    &#160;&#160;&#160;   Price   &#160;&#160;&#160;     Unit    &#160;&#160;&#160;    Total </i></b><br/>";
       webdata="<br/>";
       for(int i=0;i<count;i++)
        {
         webdata="<br/>";
webdata="<br/>";
         webdata+= fullitem[i][0] + " &#160;&#160;&#160;  &#160;&#160;&#160;     " + fullitem[i][1]+ "    &#160;&#160;&#160;    " + fullitem[i][2]+ "    &#160;&#160;&#160;    " + fullitem[i][3] + "<br />";

        }
        webdata="<br/>";
        webdata="<br/>";
       webdata+= "<b>          TOTAL :</b>" +String(total) + "<br/>";
       webdata="<br/>";
       webdata="<br/>";
       webdata="<br/>";
webdata="<br/>";
webdata="<p><marquee><b><i>HAPPY&#160;&#160;&#160; SHOPPING</i></b></marquee></p>";
       client.println(webdata);

        Serial.println("total                 rs." +String(total));

}
