import processing.serial.*;   //library for communicating with arduino serial
import themidibus.*;          //library for reading the midi data for virtual midi bus
import javax.sound.midi.*; //required for the function 'midimessage'

//Create the objects of the libraries we imported 
MidiBus midi;
Serial myPort;
int counter=0;

boolean IsVelocitySensitive=true;

int lights_mode = 0;                       // base preset of desired light pattern we are using
Boolean velocity_brightness = true;         //should the brightness of the leds be mapped to velocity
int frameCounter=0;
float startTime;



String SerialIncoming;

Pair LastRecordedCC=new Pair(0,0);

ArrayList<Pair> ActiveNotes = new ArrayList<Pair>();

ArrayList<Pair>ControlChangeList=new ArrayList<Pair>();



void setup()
{  
     midi=new MidiBus(this,"VBUS_A",-1);            //the third argument specifies the output port, set to -1 if you dont need it
  // midi=new MidiBus(this,"LKMK3 MIDI",-1);
  
  startTime=millis();
  String portName=Serial.list()[0];
  println(Serial.list());
  myPort=new Serial(this,portName,4800);            //9600 baudrate gives stable data, other values are erratic
  delay(1000);  //Mega takes some time to setup the port
}

void draw()
{

 
    float endTime = millis();
    float elapsedTime = (endTime - startTime) / 1000.0;  // Convert milliseconds to seconds
   // println(ActiveNotes.size());
   // println(elapsedTime);
  
    
    
 //we dont want a stagnant string of CC values forever, so we clear the list after 2 seconds if no change is happening 
 
 if(elapsedTime>2)   
 ControlChangeList.clear();
  
  //println(frameCounter%60);
  
  
  
  //if(ActiveNotes.size()>0)
 // displayList(ActiveNotes);
 
// if(ControlChangeList.size()>0)
  //displayList(ControlChangeList);
 //println(ControlChange_SerialString());
  
  myPort.write(FinalSerialString());
  myPort.write('\n');
  
  //lets add a delay otherwise serial data becomes very erratic
  delay(90);
  
  if(myPort.available()>0){
   
    SerialIncoming=myPort.readStringUntil('\n');
    
    
    if( !(SerialIncoming instanceof String))  //flag to check if the serial data got corrupted or not
    { 
     SerialReset();
     println("serial data corrupting!RESETTING"+counter);
    
    }
    
  
    print(SerialIncoming);
  }
  myPort.clear();
  //println(ActiveNotes_SerialString());
  
}

String ActiveNotes_SerialString()
{
  //set first value to 'A' so arduino can detect startpoint of active string in serial string data
   String ActiveNotes_string="A";    
 
   
       for(Pair item:ActiveNotes)
         {     
               if(IsVelocitySensitive)
               ActiveNotes_string=ActiveNotes_string+str(item.x)+"a"+str(item.y)+"v";
               else
               ActiveNotes_string=ActiveNotes_string+str(item.x)+"a";
         }
       
    
     
     
  return ActiveNotes_string;
}


//SubString version of ControlChangeList to be sent to MicroController

String ControlChange_SerialString()
{
  String ControlChange_string="C";
    
    for(Pair item:ControlChangeList)
   {
     ControlChange_string=ControlChange_string+str(item.x)+"c"+str(item.y)+"v";
   }
    
    return ControlChange_string;
}



//the function thats strings together all the substrings which will finally be sent as serial data to microcontroller

String FinalSerialString()
{
   counter=(counter+1)%10;
  
  String FinalString=str(counter)+ControlChange_SerialString() + ActiveNotes_SerialString();
  

  return(FinalString);
}

void SerialReset()
{
  ControlChangeList.clear();
  ActiveNotes.clear();
  myPort.clear();
  SerialIncoming="";
  
  myPort.stop();
   String portName=Serial.list()[0];
  myPort=new Serial(this,portName,4800); 
   delay(1000);
  startTime=millis();
  println("new port created");
  
}
  

//Note on and noteOff functions are called when midi keys or polyphonic touch squares are pressed, the values are stored in ActiveNotes List
void noteOn(int channel, int pitch, int velocity) {
//println("Note On - Channel: " + channel + ", Pitch: " + pitch + ", Velocity: " + velocity);
 
  Pair note_info = new Pair(pitch,velocity);
  
  if(!note_info.IsAlreadyPresentinArrayList(ActiveNotes))  //if too many notes are present at once, serial data becomes erratic
 {   
   ActiveNotes.add(note_info);
 }
}

void noteOff(int channel, int pitch, int velocity) {
  //println("Note Off - Channel: " + channel + ", Pitch: " + pitch + ", Velocity: " + velocity);

    Pair note_info = new Pair(pitch,velocity);
  
  if(note_info.IsAlreadyPresentinArrayList(ActiveNotes))
  {
     int noteindex = indexof(note_info,ActiveNotes);
     ActiveNotes.remove(noteindex);        
  }
  

}


//this function is called whenever you move a slider or knob and stores the values in ControlChangeList 

void controllerChange(int channel, int number, int value) {
  //println("Controller Change - Channel: " + channel + ", Number: " + number + ", Value: " + value);
 
// if(frameCounter%240>0 && frameCounter%240<10)
 if(number==26) //novation keyboard is showing erratic values at knob, we must ignore this knob for now.
 return;
 
 startTime=millis();
 
 Pair CC_info=new Pair(number,value);
 
 
 if(CC_info.IsAlreadyPresentinArrayList(ControlChangeList)){
    
     int controller_index= indexof(CC_info,ControlChangeList);
  
     ControlChangeList.get(controller_index).y=value;
     LastRecordedCC.x=ControlChangeList.get(controller_index).x;
     LastRecordedCC.y=ControlChangeList.get(controller_index).y;
 
 }
 else
 {
   ControlChangeList.add(CC_info);
 }
  switch(number)
  { case 11:  if(value==127)
              lights_mode = 1; else
              lights_mode = 0;
              break;
              
    case 12:  if(value==127)
              lights_mode = 2; else
              lights_mode = 0;
              break;
    
    case 13:  if(value == 127)
              lights_mode = 3; else
              lights_mode = 0;
              break;
    
    case 14:  if(value == 127)
              lights_mode = 4; else
              lights_mode = 0;
              break;
   
    case 18:  if(value == 127)
              lights_mode = 4; else
              lights_mode = 0;
              break;
              
              
    default:  break;
              
  }
}



int indexof(Pair target,ArrayList<Pair> source){
   for(int i=0; i<source.size();i++)
   {
      if(source.get(i).x==target.x)
      return i;
   }
  
    return -1;
}

void displayList(ArrayList<Pair> list)
{
  for(Pair item: list)
  {
    print(item.x+" "+item.y+" ");
  }
  print("\n");
}

class Pair {
  int x;
  int y;
  
  Pair(int x, int y) {
    this.x = x;
    this.y = y;
  }
  
  boolean IsAlreadyPresentinArrayList(ArrayList<Pair> list)
  {
    for(Pair listItem : list){
      
      if(listItem.x==this.x)
        return true;
    }
    return false;
  }  
    
}
