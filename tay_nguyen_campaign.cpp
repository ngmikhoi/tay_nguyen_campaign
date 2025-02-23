#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }

  // TODO: Extract values from the `data` array and store them in respective variables
  for (int i = 0; i < 2; i++){
    string line(data[i]);
    int len = line.size();
    if(line[0] != '['|| line[len-1] != ']'){
      return false;
    }
    line = line.substr(1, len - 2);
    stringstream ss(line);
    string digits;
    int pos = 0;
    while(getline(ss, digits, ',')){
      if(pos > 16){
        return false;
      }
      int start = 0; 
      if(digits[0] == '-'){
        start = 1;
      }
      for (int k = start; k < digits.size(); k++){
        if(!isdigit(digits[k])){
          return false;
        }
      }
      int number = stoi(digits);
      if (number > 1000){
        number = 1000;
      }
      else if (number < 0){
        number = 0;
      }
      if(i == 0){
        LF1[pos] = number;
      }
      else{
        LF2[pos] = number;
      }
      pos++;   
    }
  }

  for (int i = 2; i < 4; i++){
    string line(data[i]);
    stringstream ss(line);
    string digits;
    int pos = 0;
    while(getline(ss, digits, ' ')){
      if(pos > 1){
        return false;
      }
      int start = 0; 
      if(digits[0] == '-'){
        start = 1;
      }
      for (int k = start; k < digits.size(); k++){
        if(!isdigit(digits[k])){
          return false;
        }
      }
      int number = stoi(digits);
      
      if(i == 2){
        if (number > 600){
          number = 600;
        }
        else if (number < 0){
          number = 0;
        }
        if (pos == 0){
          EXP1 = number;
        }
        else{
          EXP2 = number;
        }
      }
      else{
        if (number > 3000){
          number = 3000;
        }
        else if (number < 0){
          number = 0;
        }
        if (pos == 0){
          T1 = number;
        }
        else{
          T2 = number;
        }
      }
      pos++;   
    }
  }

  string digits(data[4]);
  int start = 0; 
  if(digits[0] == '-'){
    start = 1;
  }
  for (int k = start; k < digits.size(); k++){
    if(!isdigit(digits[k])){
      return false;
    }
  }
  int number = stoi(digits);
  if(number > 99){
    number = 99;
  }
  else if (number < 0){
    number = 0;
  }
  E = number;
  return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function
  int weight[17] = {1,2,3,4,5,7,8,9,10,12,15,18,20,30,40,50,70};
  int LF = 0;
  for(int i = 0; i < 17; i++){
    LF += LF1[i]*weight[i] + LF2[i]*weight[i];
  }
  return LF;
}

// Task 2
string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  int x[3];
  int count = 0;
  int idx = 0;
  while(idx < target.size()){
    while(idx < target.size() && !isdigit(target[idx])){
      idx++;
    }
    string digits = "";
    while(idx < target.size() && isdigit(target[idx])){
      digits += target[idx];
      idx++;
    }
    if (digits != ""){
      if(count > 2){
        return "INVALID";
      }
      int number = stoi(digits);
      x[count++] = number;
    }
  }
  if (count == 0){
    return "INVALID";
  }
  int ID;
  string primaryTarget[5] = {
    "Buon Ma Thuot",
    "Duc Lap",
    "Dak Lak",
    "National Route 21",
    "National Route 14"
  };
  if (count == 1){
    if (x[0] < 3){
      return "DECOY";
    }
    else if (x[0] > 7){
      return "INVALID";
    }
    else{
      ID = x[0];
      return primaryTarget[ID - 3];
    }
  }
  else if(count == 2){
    ID = (x[0] + x[1])%5 + 3;
    return primaryTarget[ID - 3];
  }
  else{
    ID = x[0];
    if (x[1] > ID){
      ID = x[1];
    }
    if(x[2] > ID){
      ID = x[2];
    }
    ID = ID%5 + 3;
    return primaryTarget[ID - 3];
  }
  return "INVALID";
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  string decoded = "";
  if (EXP1 >= 300 && EXP2 >= 300) {
    int shift = (EXP1 + EXP2)%26;
    for (char c: message){
      if(!isdigit(c) && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') && (c != ' ')){
        return "INVALID";
      }
      char newChar = c;
      if(c >= 'a' && c <= 'z'){
        newChar = (c - 'a' + shift)%26 + 'a';
      }
      else if(c >= 'A' && c <= 'Z'){
        newChar = (c - 'A' + shift)%26 + 'A';
      }      
      decoded += newChar;
    }
  }
  else {
    for (char c: message){
      decoded = c + decoded;
    }
  }
  string primaryTargetlower[5] = {
    "buon ma thuot",
    "duc lap",
    "dak lak",
    "national route 21",
    "national route 14"
  };
  string primaryTarget[5] = {
    "Buon Ma Thuot",
    "Duc Lap",
    "Dak Lak",
    "National Route 21",
    "National Route 14"
  };
  for (char& c: decoded){
    if (c >= 'A' && c <= 'Z'){
      c += 32;
    }
  }
  for (int i = 0; i < 5; i++){
    if(decoded.compare(primaryTargetlower[i]) == 0){
      return primaryTarget[i];
    }
  }
  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  if (E == 0){
    float deltaT1 = (float(LF1)/float(LF1 + LF2) * float(T1 + T2)) * (1.0 + float(EXP1 - EXP2)/100.0);
    float deltaT2 = float(T1 + T2) - deltaT1;
    int updeltaT1 = ceil(deltaT1);
    int updeltaT2 = ceil(deltaT2);
    T1 += updeltaT1;
    T2 += updeltaT2;
  }
  else if(E >= 1 && E <= 9){
    float tmpT1 = float(T1) -  float(E) * 0.01 * float(T1);
    T1 = ceil(tmpT1);
    float tmpT2 = float(T2) -  float(E) * 0.005 * float(T2);
    T2 = ceil(tmpT2);
  }
  else if(E >= 10 && E <= 29){
    T1 += E*50;
    T2 += E*50;
  }
  else if(E >= 30 && E <= 59){
    float tmpT1 = float(T1) +  float(E) * 0.005 * float(T1);
    T1 = ceil(tmpT1);
    float tmpT2 = float(T2) +  float(E) * 0.002 * float(T2);
    T2 = ceil(tmpT2);
  }
  if (T1 > 3000){
    T1 = 3000;
  }
  else if (T1 < 0){
    T1 = 0;
  }
  if (T2 > 3000){
    T2 = 3000;
  }
  else if (T2 < 0){
    T2 = 0;
  }
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  float S = (LF1 + LF2) + (EXP1 + EXP2)*5 + (T1 + T2)*2;
  float odd = 0.0, even = 0.0;
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      if(i%2 == 1){
        odd += battleField[i][j];
      }
      else{
        even += battleField[i][j];
      }
    }
  }
  S -= odd*3.0/2.0;
  S -= even*2.0/3.0;
  int res = ceil(S);
  return res;
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int res = 3000;
  for (int a = 4; a < 25; a++){
    for (int b = 3; b < a; b++){
      for (int c = 2; c < b; c++){
        for (int d = 1; d < c; d++){
          for (int e = 0; e < d; e++){
            int sum = supply[a/5][a%5] + supply[b/5][b%5] + supply[c/5][c%5] + supply[d/5][d%5] + supply[e/5][e%5];
            if (sum >= shortfall && sum < res){
              res = sum;
            }
          }
        }
      }
    }
  }
  return res;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////