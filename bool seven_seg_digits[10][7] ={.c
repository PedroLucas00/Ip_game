bool seven_seg_digits[10][7] = { 

bool seven_seg_digits[10][7] = { 
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,0,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}, //9
};

int i = 0;
int salva_botao = 2;
int soma_botao = 3;
void setup(){
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, OUTPUT);  
    pinMode(5, OUTPUT); 
    pinMode(6, OUTPUT);  
    pinMode(7, OUTPUT); 
    pinMode(8, OUTPUT); 
    pinMode(9, OUTPUT);   
    pinMode(10,OUTPUT);
    Serial.begin(9600);
}

void display(int i){
    digitalWrite(4,seven_seg_digits[i][0]);
    digitalWrite(5,seven_seg_digits[i][1]);
    digitalWrite(8,seven_seg_digits[i][2]);
    digitalWrite(9,seven_seg_digits[i][3]);
    digitalWrite(10,seven_seg_digits[i][4]);
    digitalWrite(6,seven_seg_digits[i][5]);
    digitalWrite(7,seven_seg_digits[i][6]);
}
void loop(){
int count = 0;
int vetor[4] = {0};
int inteiro = 0;
int L = 0; 

display(inteiro);
for(int j = 0; j < 4;){
    if(!digitalRead(soma_botao)){
        inteiro++;
        display(inteiro);
        delay(200);
        if(inteiro == 10){
            inteiro = 0;
            display(inteiro);
        }
    }

    if(!digitalRead(salva_botao)){
        vetor[j] = inteiro;
        inteiro = 0;
        display(inteiro);
        j++;
        delay(200);
    }


}
    for(int L = 0; L < 4; L++){
        Serial.print(vetor[L]); 
    }
}