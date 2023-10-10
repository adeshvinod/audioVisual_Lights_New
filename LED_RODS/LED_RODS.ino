//set appropriate baudrate depending on whether you are using mega or uno

//#include <SoftwareSerial.h>. //uncomment this line for winodws
#include <FastLED.h>
#include <string.h>  // for C-style string functions
#include <String.h>  // for C++ string class
#include <math.h>


DEFINE_GRADIENT_PALETTE(achilles_heel){
 0,2,0,0,
 66,255,10,10,
 74,255,12,13,
 186,255,12,13,
 240,255,40,58,
 255,246,238,210

};

/*
DEFINE_GRADIENT_PALETTE( 3d_Smiley_gp ) {
    0, 252, 18,  1,
  124, 255, 92,  1,
  255, 255,255,  0};
*/


// Gradient palette "ib_jul24_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul24.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib_jul24_gp ) {
    0,  49, 62,158,
    0, 171,213,242,
   43,  49, 62,158,
  104, 137,131,194,
  201, 206,203,242,
  255,  35, 45, 68};


// Gradient palette "cw5_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/5/tn/cw5-068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( red_gradient ) {
    0, 203, 21,  1,
  255,  83,  1,  2};

  // Gradient palette "i8_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds9/tn/i8.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 64 bytes of program space.

// Gradient palette "ib_jul22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( i8_gp ) {
    0, 255,  3,  1,
   69, 247, 55, 31,
   99, 237,184,153,
  140,   6, 33,  1,
  146,  12, 42,  1,
  163,  21, 54,  1,
  234,  14, 36,  1,
  255,  14, 36,  1};

// Gradient palette "scoutie_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/scoutie.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( scoutie_gp ) {
   0,   255, 156,  0,  // Orange
    42,  255, 156,  0,  // Orange (unchanged)
    63,  255, 156,  0,  // Orange (unchanged)
    85,  127, 175, 9,   // Lighter Orange
    95,  127, 175, 9,   // Lighter Orange (unchanged)
    127, 0,   195, 18,  // Green
    140, 0,   195, 18,  // Green (unchanged)
    159, 0,   195, 18,  // Green (unchanged)
    176, 0,   97,  28,  // Darker Green
    190, 0,   97,  28,  // Darker Green (unchanged)
    216, 1,   0,   39,  // Dark Blue
    219, 1,   0,   39,  // Dark Blue (unchanged)
    223, 1,   0,   39,  // Dark Blue (unchanged)
    240, 0,   0,   50,  // Darker Blue
    255, 0,   0,   50   // Darker Blue (unchanged)
};

CRGBPalette16 goldenPalette = CRGBPalette16(
    CRGB(255, 255, 0),  // Golden color
    CRGB(255, 192, 0),  // Slightly dimmer gold
    CRGB(192, 128, 0),  // Even dimmer gold
    CRGB(128, 64, 0)    // Very dim gold
);

  // Gradient palette "passionfruit_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/flor/tn/passionfruit.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 128 bytes of program space.

DEFINE_GRADIENT_PALETTE( passionfruit_gp ) {
    0,   0,  1,  0,
   35,   1,  3,  0,
   70,   1, 15,  0,
   73,   1, 16,  0,
   75,   1, 17,  0,
   78,   1, 19,  0,
   80,   2, 20,  0,
   83,   3, 22,  0,
   85,   4, 23,  0,
   88,   5, 25,  0,
   90,   7, 26,  0,
   93,   8, 27,  0,
   95,  10, 29,  0,
   98,  13, 31,  0,
  100,  16, 33,  0,
  103,  20, 34,  0,
  105,  24, 36,  0,
  108,  27, 36,  0,
  110,  29, 34,  0,
  112,  30, 32,  0,
  115,  32, 30,  0,
  117,  34, 28,  0,
  120,  35, 26,  0,
  122,  38, 23,  0,
  125,  39, 21,  0,
  127,  42, 19,  0,
  130,  44, 16,  0,
  132,  46, 14,  0,
  135,  48, 12,  0,
  137,  50, 10,  0,
  198, 128, 88,  0,
  255, 255,255,  0};




//float x1,y1,x2,y2,persistence;
//int octaves;

int LaunchKey_IndexList[25];
//int AkaiMini_Indexlist[25];
CRGBPalette16 current_palette=red_gradient;
TBlendType    currentBlending;



char FinalSerialWriteString[100] = "";  
#define NUM_LEDS  60
#define NUM_LEDS_2 1
#define NUM_LEDS_3 1

#define LED_PIN   3

#define NUM_STRIPS 4
#define NUM_STRIPS_2 2
#define NUM_STRIPS_3 1

#define NUM_LEDS_PER_STRIP 60


#define NUM_STRIPS_2 2 //no of 90LED strips
#define NUM_STRIPS_3 1//no of 144LED strips

CRGB ledstrips[NUM_STRIPS][60];
CRGB ledstrips_2[NUM_STRIPS_2][NUM_LEDS_2];
CRGB ledstrips_3[NUM_STRIPS_3][NUM_LEDS_3];



//CRGB leds[NUM_LEDS];


//variables for debugging
int counter=0;
int baudrate=9600;  //set to 4800 for mega and 9600 for uno

int global_mod1=0;
int global_mod2=1;
String debugString="";
int chaseindex=0;

//for pulse beams
int beam_in_progress=0;
int i=0;
int pulse=0;   //pulse from quasar
int pulse_node[4]={0,0,0,0}; //keeps track of the delta y coordinate of pulse beam.starts from the centre
int pulse_in_progress[4]={0,0,0,0};
int pulse_node_index=0; //array index of pulse node
int pulse_in_progress_index=0; //array index of pulse_progress
int counter2=0; //used in gaussian pendulam

int lightMode=0;
int fadeValue=100; 

class ActiveNote {  
  public:
    int value_;
    int noteNum;
    
     ActiveNote() {
      // Default constructor with no arguments
      noteNum=0;
      value_=0;
    }  
    // Other member functions and operations can be defined here
};

class CCnote{
  public:
  int CCindex;
  int CCvalue;

  CCnote(){
    CCindex=0;
    CCvalue=0;
  }
void initializevalue(int x, int y)
  {
    CCindex=x;
    CCvalue=y;
  }

  void SetCCvalue(int x)
  {
    CCvalue=x;
  }
};

CCnote CCnotes[26];

ActiveNote ActiveNotes[10];

void setup() {
 
  // tell FastLED there's 60 NEOPIXEL leds on pin 2
  FastLED.addLeds<WS2812B, 3, GRB>(ledstrips[0], 60);

  // tell FastLED there's 60 NEOPIXEL leds on pin 3
  FastLED.addLeds<WS2812B, 4,GRB>(ledstrips[1], NUM_LEDS_PER_STRIP);

   //tell FastLED there's 60 NEOPIXEL leds on pin 4
  FastLED.addLeds<WS2812B, 5,GRB>(ledstrips[2], NUM_LEDS_PER_STRIP);

  FastLED.addLeds<WS2812B, 6,GRB>(ledstrips[3], NUM_LEDS_PER_STRIP);

  
  FastLED.addLeds<WS2812B, 7,GRB>(ledstrips_2[0],NUM_LEDS_2);
   FastLED.addLeds<WS2812B, 8,GRB>(ledstrips_2[1],NUM_LEDS_2);

FastLED.addLeds<WS2812B,9,GRB>(ledstrips_3[0],NUM_LEDS_3);
 

  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 
 // FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  //fill_solid(leds, NUM_LEDS, CRGB::Black);
  for(int i=0;i<NUM_STRIPS;i++)
  {
    fill_solid(ledstrips[i],NUM_LEDS,CRGB::Black);
  }
/*
   for(int i=0;i<NUM_STRIPS_2;i++)
  {
    fill_solid(ledstrips_2[i],NUM_LEDS_2,CRGB::Black);
  }

  
   for(int i=0;i<NUM_STRIPS_3;i++)
  {
    fill_solid(ledstrips_3[i],NUM_LEDS_3,CRGB::Black);
  }

*/
  digitalWrite(LED_BUILTIN, LOW);


  Serial.begin(baudrate);

  //initialize the CC note values
  for(int i=0;i<26;i++)
  CCnotes[i].initializevalue(i,0);

initializeLaunchkeyIndexList();

 
}

void initializeLaunchkeyIndexList()
{
LaunchKey_IndexList[0]=11;
LaunchKey_IndexList[1]=12;
LaunchKey_IndexList[2]=13;
LaunchKey_IndexList[3]=14;
LaunchKey_IndexList[4]=15;
LaunchKey_IndexList[5]=16;
LaunchKey_IndexList[6]=17;
LaunchKey_IndexList[7]=18;

//knob values
LaunchKey_IndexList[8]=21;
LaunchKey_IndexList[9]=22;
//LaunchKey_IndexList[10]=23; 
//LaunchKey_IndexList[11]=24;
LaunchKey_IndexList[12]=25;
LaunchKey_IndexList[13]=26;
LaunchKey_IndexList[14]=23;  //  27 and 28 replaced with 23 and 24 since ableton sends 27 and 28 on whenever we move curson
LaunchKey_IndexList[15]=24;

//slider values
//LaunchKey_IndexList[16]=71;
LaunchKey_IndexList[16]=72;  //ableton sends out 71 when we hit play button or move around the cursor
LaunchKey_IndexList[17]=72;
LaunchKey_IndexList[18]=73;
LaunchKey_IndexList[19]=74;
LaunchKey_IndexList[20]=75;
LaunchKey_IndexList[21]=76;
LaunchKey_IndexList[22]=77;
LaunchKey_IndexList[23]=78;
LaunchKey_IndexList[24]=79;



}


void loop() 
 {
   
    
    
//Sending serial data back to processing so we can monitor the serial string arduino is working with 
   memset(FinalSerialWriteString, '\0', sizeof(FinalSerialWriteString));
   
    if (Serial.available() > 0) 
  {

  digitalWrite(LED_BUILTIN, HIGH);
   
    size_t byteCount = Serial.readBytesUntil('\n', FinalSerialWriteString, sizeof(FinalSerialWriteString) - 1); 
    FinalSerialWriteString[byteCount] = '\n';
    
    Serial.print(FinalSerialWriteString);
    //delay(40);
   // debugFunction();
 // Serial.print(debugString+'\n');
      
   MessageDecoder(FinalSerialWriteString);
   //for(int i=0;i<10;i++)
  // Serial.print(debugString+'\n');
 // debugString="";

  //for(int i=0;i<25;i++)
   //debugString= debugString+String(CCnotes[i].CCvalue);
   
   //debugFunction();
  // Serial.print(debugString+'\n');
   //Serial.print(String(ActiveNotes[0].noteNum)+" "+" "+String(ActiveNotes[0].value_)+" "+" "+String(ActiveNotes[1].noteNum)+" "+" "+String(ActiveNotes[1].value_)+" "+String(ActiveNotes[2].noteNum)+" "+" "+String(ActiveNotes[2].value_)+" "+String(counter)+" "+FinalSerialWriteString+'\n');
     
  } 
  else
  {
     digitalWrite(LED_BUILTIN, LOW);
  }
//delay(100);

  lightMode=modeSelector(CCnotes);
  
   digitalWrite(LED_BUILTIN, LOW);
  
 switch(lightMode)
 {
   case 0: FullStripFlash(ActiveNotes,CCnotes);
            break;
    
    case 1: sparklingLights(ActiveNotes,CCnotes);
            break;

    case 2: quasar(ActiveNotes,CCnotes);
            break;

    case 3:  FullStripFlash(ActiveNotes,CCnotes);
            break;

    default: break;
    

 }


 for(int s=0;s<NUM_STRIPS;s++)
 {
   fadeToBlackBy(ledstrips[s],NUM_LEDS,fadeValue);
 }
  for(int s=0;s<NUM_STRIPS_2;s++)
 {
   fadeToBlackBy(ledstrips_2[s],NUM_LEDS_2,fadeValue);
 }
  for(int s=0;s<NUM_STRIPS_3;s++)
 {
   fadeToBlackBy(ledstrips_3[s],NUM_LEDS_3,fadeValue);
 }
  FastLED.show();
  
}

int modeSelector(CCnote _CCnotes[])
{ int i;
  int  assigned_flag=0;
  for(i=0;i<8;i++)
  {
    //if(_CCnotes[i].CCvalue==127) //this only holds for the launch key since it has toggle buttons for on and off but wont work for akai mini since theres no toggle button. we have to use knobs as the toggle
    if(_CCnotes[i].CCvalue>0) //if knob is not on zero value
    {lightMode=i+1;
      assigned_flag=1;    
    }
  }
  
  if(assigned_flag==0)lightMode=0;

  return lightMode;

}
void debugFunction()
{
  debugString="hey bitch";
   // for(int i=0;i<10;i++)
   //debugString= debugString+String(ActiveNotes[i].noteNum);

  //  for(int i=0;i<25;i++)
  // debugString= debugString+String(CCnotes[i].CCvalue);
  //debugString=String(val);
  
}
void MessageDecoder(String serialdata)
{
  //lets reset the ActiveNotes to so that the array empties out when we stop pressing the keys
 ReinitializeActiveNotes();
 
 
 
  //Lets parse the AN( active Notes) string info to int values
  
  bool CCregion=true; //flag which detects if we are analzing CC region or Active notes region in serial data 
  int ANstartpoint=0;  
  String activeNote="";
  int totalNotes=0;
  
  int CCstartpoint=0;
  String CCnote_string="";
  int totalCCnotes=0; 
  
  //variable to to store the note number and values of the current CC note being analyzed  
  //debugString="hi bro";
  int temp_CCnum=-1;
  int temp_CCval=-1;
  for(int i=0;i<serialdata.length();i++)
  {
    if(serialdata[i]=='C')
    {
      CCstartpoint=i+1; 
     // debugString="hi bro";
    
      
    }
    else if(serialdata[i]=='c')
    {
      
      CCnote_string=serialdata.substring(CCstartpoint,i);
      temp_CCnum=CCnote_string.toInt();
      CCstartpoint=i+1;
    }
    else if(serialdata[i]=='v' && CCregion==true)
    {
         CCnote_string=serialdata.substring(CCstartpoint,i);
         //debugString=String(ReturnIndex(LaunchKey_IndexList,temp_CCnum))+String(temp_CCnum);
        
         //debugString="hi bro";
         temp_CCval=CCnote_string.toInt();
          CCstartpoint=i+1;
         CCnotes[ReturnIndex(LaunchKey_IndexList,sizeof(LaunchKey_IndexList)/sizeof(LaunchKey_IndexList[0]),temp_CCnum)].CCvalue=temp_CCval;       
    }
    else if(serialdata[i]=='A') //A signals that the following data are active midi notes
    {
      ANstartpoint=i+1;
      CCregion=false;
    }

    else if(serialdata[i]=='a')
    {counter=counter+1;
      activeNote=serialdata.substring(ANstartpoint,i);
       if(activeNote.toInt()/10>0)
       ActiveNotes[totalNotes].noteNum=activeNote.toInt();
      
       ANstartpoint=i+1;
         
    }
    
    else if(serialdata[i]=='v' && CCregion==false)
    {
      activeNote=serialdata.substring(ANstartpoint,i);
       if(activeNote.toInt()/10>0)
      ActiveNotes[totalNotes].value_=activeNote.toInt();
      ANstartpoint=i+1;
      totalNotes++;
      
    }
   
    

  }
  //leds[30]=CHSV(100,255,255);
  //leds[30]=CHSV(100,255,255);
 
}

void ReinitializeActiveNotes()
{
  
  for(int i=0;i<10;i++)
  { ActiveNotes[i].noteNum=0;
    ActiveNotes[i].value_=0;
  }
  

}

int ReturnIndex(int targetlist[],int length, int value)
{
  for(int i=0;i<length;i++)
  {  //debugString=String(sizeof(targetlist));
    if(targetlist[i]==value)
    {
    return i;
    }
  }
  return 25;
}

void sparklingLights(ActiveNote _ActiveNotes[],CCnote _CCnotes[])
{
  int brightness=map(_CCnotes[9].CCvalue,0,127,0,255);
  current_palette=achilles_heel;
    EVERY_N_MILLISECONDS(25){

     for(int s=0;s<NUM_STRIPS;s++)
     {
        ledstrips[s][random8(0,NUM_LEDS/3-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND);
     ledstrips[s][random8(NUM_LEDS/3,2*NUM_LEDS/3-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND);
     ledstrips[s][random8(2*NUM_LEDS/3,NUM_LEDS-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND); 
     }
     
     
     //leds[random8(0,NUM_LEDS/3-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND);
     //leds[random8(NUM_LEDS/3,2*NUM_LEDS/3-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND);
     //leds[random8(2*NUM_LEDS/3,NUM_LEDS-1)]=ColorFromPalette(current_palette,random8(),brightness,LINEARBLEND); 
    }

    fadeValue=10;
}

void  quasar(ActiveNote _ActiveNotes[],CCnote _CCnotes[])
{
    int flicker=map(_CCnotes[14].CCvalue,0,127,15,0);;
    int delta_fade=12;
    int quasar_brightness=255;
    int quasar_midpoint=map(_CCnotes[15].CCvalue,0,127,0,NUM_LEDS-1);
    int hue=map(_CCnotes[8].CCvalue,0,127,0,360);

    for(int i=0;i<10;i++) //since there are max 10 elements in ActiveNotes at once
    {
      if(_ActiveNotes[i].noteNum==96)
      delta_fade=3;
      else if(_ActiveNotes[i].noteNum==36)
       pulse_in_progress[pulse_in_progress_index]=1;
    }
    for(int i=0;i<NUM_LEDS;i++)
    {
        quasar_brightness=quasar_brightness-delta_fade-random(0,flicker);
        if(quasar_brightness>=0 )
        {
          for(int s=0;s<NUM_STRIPS;s++)
          {
            if((quasar_midpoint+i)<NUM_LEDS)
          ledstrips[s][quasar_midpoint+i]=CHSV(hue,255,quasar_brightness);
          if((quasar_midpoint-i)>0)
          ledstrips[s][quasar_midpoint-i]=CHSV(hue,255,quasar_brightness);
          }
          
          /*
          if((quasar_midpoint+i)<NUM_LEDS)
          leds[quasar_midpoint+i]=CHSV(hue,255,quasar_brightness);
          if((quasar_midpoint-i)>0)
          leds[quasar_midpoint-i]=CHSV(hue,255,quasar_brightness);
          */
        }
        else
        break;
    }
//trigger different light segmants on the rod when keys are pressed
     for(int j=0;j<10;j++)
  { if(_ActiveNotes[j].noteNum<65 && _ActiveNotes[j].noteNum>36)
    {   for(int i=0;i<5;i++)
        {  
          for(int s=0;s<NUM_STRIPS;s++)
          {
              ledstrips[s][_ActiveNotes[j].noteNum-i-12]=CHSV(map(_ActiveNotes[j].noteNum,36,65,0,255),255,255);
              ledstrips[s][_ActiveNotes[j].noteNum+i-12]=CHSV(map(_ActiveNotes[j].noteNum,36,65,0,255),255,255);
          }
          // leds[_ActiveNotes[j].noteNum-i-12]=CHSV(map(_ActiveNotes[j].noteNum,36,65,0,255),255,255);
         //  leds[_ActiveNotes[j].noteNum+i-12]=CHSV(map(_ActiveNotes[j].noteNum,36,65,0,255),255,255);

        }
    }
  }

  quasar_beam();
    fadeValue=50;
      
}

void quasar_beam()
{
  if(pulse_in_progress[0]>0)                    //NEEDS MODIFICATION, MOVE ALONG WITH QUASAR MIDPOINT!
  { 
    if(pulse_node[0]>=20)
    {
      pulse_in_progress[0]=0;
      pulse_node[0]=0;
      pulse_in_progress_index=0;
    }
    else{
    
      if(quasar)
      { 
        for(int s=0;s<NUM_STRIPS;s++)
        {
         ledstrips[s][40+pulse_node[0]]=CHSV(36,214,245);
        ledstrips[s][20-pulse_node[0]]=CHSV(36,214,245);      
        }
      
      //leds[40+pulse_node[0]]=CHSV(36,214,245);
      //leds[20-pulse_node[0]]=CHSV(36,214,245);
      }
      pulse_node[0]++;
    
    }

    
  }
}

void FullStripFlash(ActiveNote _ActiveNotes[],CCnote _CCnotes[])
{
    int gaussianSpeed= map(_CCnotes[12].CCvalue,0,127,2,20);
    int brightness=map(_CCnotes[16].CCvalue,0,127,255,0);
    int hue=map(_CCnotes[8].CCvalue,0,127,255,0);
    
   
    float offset;  //variables must be declared outside switchstatement or else the  higher switch cases dont work for some reason
    float c;

  for(int i=0;i<10;i++) //since there are max 10 elements in ActiveNotes at once
    {
      switch(_ActiveNotes[i].noteNum)
      {
        case 36:    for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                      // ledstrips[s][i]=CHSV(189,255,255); 
                     // ledstrips[s][i]=CRGB(255,0,0); 
                     ledstrips[s][i]=CHSV(0,255,brightness);
                    }
/*
                     for(int i=0;i<NUM_LEDS_2;i++)
                    { for(int s=0;s<NUM_STRIPS_2;s++)
                      // ledstrips[s][i]=CHSV(189,255,255); 
                     // ledstrips[s][i]=CRGB(255,0,0); 
                     ledstrips_2[s][i]=CRGB::Red;
                    }

                      for(int i=0;i<NUM_LEDS_3;i++)
                    { for(int s=0;s<NUM_STRIPS_3;s++)
                      // ledstrips[s][i]=CHSV(189,255,255); 
                     // ledstrips[s][i]=CRGB(255,0,0); 
                     ledstrips_3[s][i]=CRGB::Red;
                    }
  */
                   fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 38:   
                   for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                      // ledstrips[s][i]=CHSV(20,255,255); 
                         //  ledstrips[s][i]=CRGB(0,255,0);
                         ledstrips[s][i]=CHSV(85,255,brightness); 
                         
                   }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;
        
        case 40: // for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(27,171,230); fadeValue=1;
                 // break; //(27,67/100*255,9/10*255)

                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(27,171,brightness); 
                    }
                   fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;
        
        case 41:   // for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(36,214,245); fadeValue=1;
                 // break;
                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(36,214,brightness); 
                    }
                 fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 43:  //  for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(354,230,255); fadeValue=100;
                 // break;

                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(354,230,brightness); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 45 : // for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(74,255,230);fadeValue=1;
                 // break;
                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(74,255,brightness); 
                    }
                   fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 47 :  //for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(63,255,255); fadeValue=1;
                 // break;
                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(63,255,brightness); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 48 :  //for(int i=0;i<NUM_LEDS;i++)leds[i]=CHSV(6,230,255); fadeValue=1;
                 // break;
                  for(int i=0;i<NUM_LEDS;i++)
                    { for(int s=0;s<NUM_STRIPS;s++)
                       ledstrips[s][i]=CHSV(6,230,brightness); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

        case 50: for(int i=0;i<NUM_LEDS;i++)
                    {
                       ledstrips[0][i]=CHSV(6,230,brightness); 
                    }
                   // fadeValue=20;
                    break;

         case 52: for(int i=0;i<NUM_LEDS;i++)
                    {
                       ledstrips[1][i]=CHSV(6,230,brightness); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

          case 53:   for(int i=0;i<NUM_LEDS;i++)
                    {
                       ledstrips[2][i]=CHSV(6,230,brightness); 
                    }
                 fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

           case 55: for(int i=0;i<NUM_LEDS;i++)
                    {
                       ledstrips[3][i]=CHSV(6,230,brightness); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;

            case 56:EVERY_N_MILLISECONDS(100){
                   
                    for(int s=0;s<NUM_STRIPS;s++)
                    { int hue=random8(0,255);
                      int sat=random8(0,255);
                      for(int i=0;i<NUM_LEDS;i++)
                       ledstrips[s][i]=CHSV(hue,255,brightness) ;
                    }
                   fadeValue=20;
      }
                    break;

          
           case 57:   
                   floatingOrbs(_CCnotes,hue);
                   fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                  break;

          
          case 58:    counter2=counter2+1;
                      if(counter2%gaussianSpeed==0)
                      chaseindex=(chaseindex+1)%NUM_LEDS;
                      GaussianPendulam(chaseindex,_CCnotes);
           // Calculate Gaussian parameters
                
                  
                  
                            fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                     break;                    


       
    
  
        
                  // floatingOrbs();
                  // fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                  //break;

        
        
        

           case 59:    alternating_segmants_2();
           fadeValue=100;
                        break;

           /*for(int i=0;i<NUM_LEDS;i++)
                    {
                       ledstrips[3][i]=CHSV(6,230,255); 
                    }
                  fadeValue=map(_CCnotes[15].CCvalue,0,127,20,100);
                    break;
*/
            case 60:counter2=counter2+1;                             
                   ChasingOrbs(_CCnotes,counter2,hue);
                    break;

             case 61: alternating_segmants_1();
             fadeValue=100;
             break;

             /*
                   
                    for(int s=0;s<NUM_STRIPS_2;s++)
                    {
                      for(int i=0;i<NUM_LEDS_2;i++)
                       ledstrips_2[s][i]=CHSV(76,255,255) ;
                    }
                   fadeValue=100;
                    break;
*/

              case 64: 
                      EVERY_N_MILLISECONDS(200){
                      twinkle();
                      fadeValue=10;
                      }
              break;


              /*
                   
                    for(int s=0;s<NUM_STRIPS_3;s++)
                    {
                      for(int i=0;i<NUM_LEDS_3;i++)
                       ledstrips_3[s][i]=CHSV(140,255,255) ;
                    }
                   fadeValue=100;
                    break;
*/
              case 63: 
                    //  int midpoint=(inoise8(millis()/30));
                      current_palette=  scoutie_gp;
                     // current_palette=passionfruit_gp;
                       //int t=millis()/20;
                       int scale=30;
                        counter2=counter2+1;
                        
                       
                      for(int s=0;s<NUM_STRIPS;s++)
                      {
                        for(int i=0;i<NUM_LEDS;i++)
                        {
                          int noise=inoise8(100*s,counter2);
                          
                          ledstrips[s][i]=ColorFromPalette(current_palette,map(int(i+counter2+15*s)%NUM_LEDS,0,NUM_LEDS,0,255),brightness,LINEARBLEND);
                          
                          ledstrips[s][i]=ColorFromPalette(current_palette,i+noise,brightness,LINEARBLEND);
                          //  ledstrips[s][i]=CHSV(noise,255,255);
                        }
                        //for(i=0;i<4;i++)
                       // blur1d(ledstrips[s],NUM_LEDS,50);
                      }   
                        fadeValue=20;
                        
                        
                    break;
     
        default:  break;
        
      }
            

      /*
      if(_ActiveNotes[i].noteNum==36)
      {
        for(int i=0;i<NUM_LEDS;i++)
        {
          leds[i]=CHSV(189,255,255);
        }
      }
      else if(_ActiveNotes[i].noteNum==38)
      {
         for(int i=0;i<NUM_LEDS;i++)
        {
          leds[i]=CHSV(20,255,255);
        }
      }*/
    }


   
}

void GaussianPendulam(int chaseindex,CCnote _CCnotes[])
{
     float a = 59.0;     // Amplitude
                      float b = NUM_LEDS / 2.0;   // Mean (center position)
                       float c = map(_CCnotes[14].CCvalue,0,127,12,50);    // Standard deviation
                      //float c=12;
                      float x1=chaseindex;
                     // float exponent = -((x - b) * (x - b)) / (2 * c * c);

                     //the speed parameters are not actually indicative of speed but rather the y function of the gaussian distribution f(x)
                      float speed1 = a * exp(-((x1 - b) * (x1 - b)) / (2 * c * c));
                      float x2=(chaseindex+(NUM_LEDS/4))%NUM_LEDS;
                      float speed2=a * exp(-((x2 - b) * (x2 - b)) / (2 * c * c));

                       float x3=(chaseindex+(NUM_LEDS/2))%NUM_LEDS;
                      float speed3=a * exp(-((x3 - b) * (x3 - b)) / (2 * c * c));

                        float x4=(chaseindex+(3*NUM_LEDS/4))%NUM_LEDS;
                      float speed4=a * exp(-((x4 - b) * (x4 - b)) / (2 * c * c));

                        chaseLED(int(speed1),int(speed2),int(speed3),int(speed4));
}
void chaseLED(int speed1, int speed2, int speed3, int speed4)
{
   
  
  
   // fill_solid(ledstrips[s],NUM_LEDS,CRGB::Black);
    ledstrips[0][int(speed1)]=CRGB::Blue;
    ledstrips[1][int(speed2)]=CRGB::Blue;
    ledstrips[2][int(speed3)]=CRGB::Blue;
    ledstrips[3][int(speed4)]=CRGB::Blue;

      if((speed1+1)<60)
     ledstrips[0][(int(speed1)+1)]=CRGB::Blue;
    if((speed2+1)<60)
    ledstrips[1][(int(speed2)+1)]=CRGB::Blue;
    if((speed3+1)<60)
    ledstrips[2][(int(speed3)+1)]=CRGB::Blue;
    if((speed4+1)<60)
    ledstrips[3][(int(speed4)+1)]=CRGB::Blue;
  
}

void floatingOrbs(CCnote _CCnotes[],int hue)  //group of consecutive LEDS move about freely across the strip
{
  /* 
 for(int i=0;i<60;i++){
   // float brightness = sin((PI/60)*i);

    // Scale brightness to fit within the LED brightness range (0-255)
   // brightness = map(brightness, 0.0, 1, 0, 255);
    
   
     double brightness=255*sin((PI/30)*i+offset);
     //brightness = map(brightness, 0.0, 1, 0, 255);
if(brightness<0)
brightness=0;
    // Set LED color based on brightness
    ledstrips[0][i] = CRGB(brightness,brightness, brightness);
    ledstrips[1][i] = CRGB(brightness,brightness, brightness);
    ledstrips[2][i] = CRGB(brightness,brightness,brightness);
    ledstrips[3][i] = CRGB(brightness,brightness,brightness);
       

      
    }
    */
    int delta_fade=15;
    int orb_brightness=map(_CCnotes[17].CCvalue,0,127,255,0);
    int orb_midpoint[4]={30,30,30,30};
    float speed=map(_CCnotes[15].CCvalue,0,127,20,3);
    uint8_t noise1= inoise8(float(millis())/speed);
     uint8_t noise2= inoise8(float(millis())/speed+1000);
      uint8_t noise3= inoise8(float(millis())/speed+2000);
       uint8_t noise4= inoise8(float(millis())/speed+3000);

    //debugFunction(noise1);
    orb_midpoint[0]= map(noise1,0,255,0,60);
    orb_midpoint[1]= map(noise2,0,255,0,60);
    orb_midpoint[2]= map(noise3,0,255,0,60);
    orb_midpoint[3]= map(noise4,0,255,0,60);



     for(int i=0;i<NUM_LEDS;i++)
    {
        orb_brightness=orb_brightness-delta_fade;
        if(orb_brightness>=0 )
        {
          for(int s=0;s<NUM_STRIPS;s++)
          {
            if((orb_midpoint[s]+i)<NUM_LEDS)
          ledstrips[s][orb_midpoint[s]+i]=CHSV(hue,255,orb_brightness);
          if((orb_midpoint[s]-i)>0)
          ledstrips[s][orb_midpoint[s]-i]=CHSV(hue,255,orb_brightness);
          }
          
        }
        else
        break;
    }
}

void ChasingOrbs(CCnote _CCnotes[],int mp_index,int hue)
{
    int delta_fade=8;
    int orb_brightness=map(_CCnotes[17].CCvalue,0,127,255,0);
    int orb_midpoint[4]={30,30,30,30};
    int orb_midpoint2[4]={0,0,0,0};
    float speed=map(_CCnotes[15].CCvalue,0,127,20,3);

    //debugFunction(noise1);
    orb_midpoint[0]= (mp_index)%NUM_LEDS;
orb_midpoint2[0]=(mp_index+NUM_LEDS/2)%NUM_LEDS;    
    orb_midpoint[1]= (mp_index+15)%NUM_LEDS;
orb_midpoint2[1]=(mp_index+20+NUM_LEDS/2)%NUM_LEDS;
    orb_midpoint[2]= (mp_index+30)%NUM_LEDS;
    orb_midpoint2[2]=(mp_index+30+NUM_LEDS/2)%NUM_LEDS;
    orb_midpoint[3]= (mp_index+45)%NUM_LEDS;
     orb_midpoint2[3]=(mp_index+45+NUM_LEDS/2)%NUM_LEDS;



     for(int i=0;i<NUM_LEDS;i++)
    {
        orb_brightness=orb_brightness-delta_fade;
        if(orb_brightness>=0 )
        {
          for(int s=0;s<NUM_STRIPS;s++)
          {
            if((orb_midpoint[s]+i)<NUM_LEDS)
         // ledstrips[s][orb_midpoint[s]+i]=CHSV(255,0,orb_brightness);
          if((orb_midpoint[s]-i)>0)
            { ledstrips[s][orb_midpoint[s]-i]=CHSV(hue,255,orb_brightness);
             // ledstrips[s][orb_midpoint2[s]-i]=CHSV(255,0,orb_brightness);
            }
          }
          
        }
        else
        break;
    }
}
 void twinkle(){
   
 current_palette=  scoutie_gp;
    // Create a white segment that fades in and out
  int whiteSegmentStart = random(NUM_LEDS);
  int whiteSegmentLength = random(1, 10); // Adjust the length as needed
  int whiteSegmentBrightness = random(100, 255); // Adjust brightness as needed
//for(int s=0;s<4;s++)
//fill_palette(ledstrips[s], NUM_LEDS, 0, 255, goldenPalette, 100, LINEARBLEND);
  // Fade in. 
  
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < whiteSegmentLength; j++) {
      int index = (whiteSegmentStart + j) % NUM_LEDS;
      for(int s=0;s<NUM_STRIPS;s++)
      {  
        ledstrips[s][index] = CRGB::Gold;
     // ledstrips[s][index].fadeToBlackBy(20);
      }
    }
   
    
  }

  // Fade out
  /*
  for (int i = 255; i >= 0; i--) {
    for (int j = 0; j < whiteSegmentLength; j++) {
      int index = (whiteSegmentStart + j) % NUM_LEDS;
      for(int s=0;s<NUM_STRIPS;s++)
      {
      ledstrips[s][index] = CRGB::White;
      //ledstrips[s][index].fadeToBlackBy(255 - i);
      }
    }
   
    //delay(10); // Adjust the speed of the fade
  } */            


 }

 void alternating_segmants_1()
 {
    current_palette=achilles_heel;
    for(int i =0;i<NUM_LEDS/4;i++)
    {
      ledstrips[0][i]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[0][NUM_LEDS-i-1]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

       ledstrips[3][i]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[3][NUM_LEDS-i-1]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

       ledstrips[1][i+(NUM_LEDS/4)]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[1][i+NUM_LEDS/2]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

       ledstrips[2][i+(NUM_LEDS/4)]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[2][i+NUM_LEDS/2]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);


    }
 
 }

 void alternating_segmants_2()
 {
   current_palette=achilles_heel;

    for(int i =0;i<NUM_LEDS/4;i++)
    {
      
      ledstrips[1][i]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[1][NUM_LEDS-i-1]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

       ledstrips[2][i]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[2][NUM_LEDS-i-1]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

       ledstrips[3][i+(NUM_LEDS/4)]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[3][i+NUM_LEDS/2]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);

         ledstrips[0][i+(NUM_LEDS/4)]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);
      ledstrips[0][i+NUM_LEDS/2]=ColorFromPalette(current_palette,i*(NUM_LEDS/2),255,LINEARBLEND);


    }
 
 }

void resetAllValues()
{

}


