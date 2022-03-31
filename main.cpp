#include <bits/stdc++.h>

using namespace std;

class Character{
  public:
    int number;
    string hexNumber;
    int bytesCount;
    int mask;
    string hexUTF;
    char symbol[4];

    void HowManyBytes(){
        if(number<=127)
            bytesCount = 1;
        else if(number>127&&number<=2047)
            bytesCount = 2;
        else if(number>2047&&number<=65535)
            bytesCount = 3;
        else if(number>65535)
            bytesCount = 4;

        cout<<bytesCount<<" bytes"<<endl;
    }
    void ChooseMask(){
        switch(bytesCount){
            case 1:
                mask = 0b00000000;
                break;
            case 2:
                mask = 0b1100000010000000;
                break;
            case 3:
                mask = 0b111000001000000010000000;
                break;
            case 4:
                mask = 0b11110000100000001000000010000000;
                break;

        }
    }
    void ConvertToHex(){
        int temp = number;
 
        ostringstream ss;
        ss << hex << temp;
        hexNumber = ss.str();
    }

    int GetDecForm(string x){
        // returns int value of char or char+char
        //cout<<"Sent char: "<<x<<endl;
        int temp=0;
        map<char, int> hexTable = { {'0',0},
                                    {'1',1},
                                    {'2',2},
                                    {'3',3},
                                    {'4',4},
                                    {'5',5},
                                    {'6',6},
                                    {'7',7},
                                    {'8',8},
                                    {'9',9},
                                    {'a',10},
                                    {'b',11},
                                    {'c',12},
                                    {'d',13},
                                    {'e',14},
                                    {'f',15}};
    
        if(x.size()==1)
            temp = hexTable[x[0]];
        
        else{
            for(int i=0; i<x.size(); i++)
                temp+=hexTable[x[x.size()-i-1]] * pow(16,i);
            
        }

        //cout<<"Char in (int) form: "<<temp<<endl;
        return temp;
    }

    void CalcUTF(){
        //bitset<16> y1(mask);
        //cout<<y1<<endl;

        int binUTF;
        int tempMask;
        int temp, temp1, temp2, temp3;

        switch(bytesCount){
            case 1:
                binUTF = mask | number;
                break;
            case 2:
                tempMask = 0b0000000000111111;
                temp = tempMask & number;
                mask = mask | temp;

                tempMask = 0b0000011111000000;
                temp1 = tempMask & number;
                temp2 = temp1<<2;
            
                mask = mask | temp2;

                binUTF = mask;
                break;
            case 3:
                tempMask = 0b000000000000000000111111;
                temp = tempMask & number;
                mask = mask | temp;

                tempMask = 0b000000000000111111000000;
                temp1 = tempMask & number;
                temp2 = temp1<<2;
                mask = mask | temp2;

                tempMask = 0b000000001111000000000000;
                temp1 = tempMask & number;  
                temp2 = temp1<<4;
                mask = mask | temp2;

                binUTF = mask;
                break;

            case 4:
                tempMask = 0b00000000000000000000000000111111;
                temp = tempMask & number;
                mask = mask | temp;

                tempMask = 0b00000000000000000000111111000000;
                temp1 = tempMask & number;
                temp2 = temp1<<2;
                mask = mask | temp2;

                tempMask = 0b00000000000000111111000000000000;
                temp1 = tempMask & number;
                temp2 = temp1<<4;
                mask = mask | temp2;

                tempMask = 0b00000000000111000000000000000000;
                temp1 = tempMask & number;
                temp2 = temp1<<6;
                mask = mask | temp2;
                
                binUTF = mask;
                break;
        }

        temp = binUTF;

        bitset<32> y(binUTF);
        //cout<<y<<endl;
 
        ostringstream ss;
        ss << hex << temp;
        hexUTF = ss.str();


    }

    void CalcChar(){
        int n = hexUTF.size();
        int j=0;
        for(int i=0; i<n; i+=2){
            if(i==0&&hexUTF.size()%2!=0){
                string temp;
                temp+="0";
                temp+=hexUTF[i];
                symbol[j] = GetDecForm(temp);
                i--;
            }
            else{
                string temp;
                temp+=hexUTF[i];
                temp+=hexUTF[i+1];
                symbol[j] = GetDecForm(temp);
            }
            j++;
        }

    }

    void PrintUnicode(){

        switch(hexNumber.size()){
            case 1:
                cout<<"UNICODE: U+000"<<hexNumber<<endl;
                break;
            case 2:
                cout<<"UNICODE: U+00"<<hexNumber<<endl;
                break;
            case 3:
                cout<<"UNICODE: U+0"<<hexNumber<<endl;
                break;
            default:
                cout<<"UNICODE: U+"<<hexNumber<<endl;
                break;

        }
    }

    void PrintUTF8(){
        cout<<"UTF-8: ";

        for(int i=0; i<hexUTF.size(); i+=2){
            cout<<hexUTF[i]<<hexUTF[i+1]<<" ";
        }
        cout<<endl;
    }

    void PrintChar(){
        ofstream fcout("output.txt");

        fcout<<"CHAR: "<<(char *)symbol;
        cout<<"CHAR: "<<(char *)symbol;
        fcout.close();
    }

};

void CalculateClass(Character x);

int main() {
  Character a;
  cout<<"Input the character number: ";
  cin>>a.number;

  CalculateClass(a);
}

void CalculateClass(Character x){
    x.HowManyBytes();
    x.ChooseMask();
    x.ConvertToHex();
    x.CalcUTF();
    x.CalcChar();
    x.PrintUnicode();
    x.PrintUTF8();
    x.PrintChar();
}

