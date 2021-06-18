// put the adress of Data Foundry here
const char* datafoundry = "data.id.tue.nl";

// create connection to dataset with server address, dataset id, and the access token
DFDataset iot(datafoundry, DATASETID, DATASETTOKEN);

// name for connecting with OOCSI (unique handle)
const char* OOCSIName = "2021_DED_TEAM_MOOD_11_B";
// put the adress of your OOCSI server here, can be URL or IP address string
const char* hostserver = "oocsi.id.tue.nl";


OOCSI oocsi = OOCSI();

int currentMood = -1;


int LED = 5;

int yellow_slider = 33;
int black_slider = 34;

int yellowValue = -1;
int blackValue = -1;

unsigned long previousMillis = 0;
const long interval = ((1000 * 60) * 15);



int PIRPin = 35;
bool PIRDetected = false;




int smallValue = 0;
int smallRotA = 19;
int smallRotB = 23;
int smallRotBtn = 21;

int smallRotACurrent = LOW;
int smallRotALast = smallRotACurrent;

int bigValue = 0;
int bigRotA = 12;
int bigRotB = 14;
int bigRotBtn = 22;

int bigRotACurrent = LOW;
int bigRotALast = bigRotACurrent;

bool bigRotPressed = false;
bool smallRotPressed = false;


int mood_btn_1 = 2;
int mood_btn_2 = 4;
int mood_btn_3 = 16;
int mood_btn_4 = 17;


bool sendDataOut = false;
