
//Projeto#01 - Regador



//bibliotecas externas
#include <LiquidCrystal.h>;

//declaração da função do LCD 
//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

//leds umidade
#define pinLedSeco 9
#define pinLedUmido 10

#define pinLedLuminosidade 2
#define pinLedSemLuminosidade 7

#define valvulaSolenoide 6

#define pinBotao 13

#define leitorLuminosidade A0
#define leitorUmidade A1

//fazer depois
#define serialRS 12
#define serialE 11
#define serialDB4 6
#define serialDB5 5
#define serialDB6 4
#define serialDB7 3

//variaveis
char Str[8] = " ";

bool botaoAtual;
bool botaoAnterior;

int contagemBotao = 0;

//estipulado - umidade
float valorUmidade;
float padraoMolhado = 400;
float padraoSeco = 150;

//estipulado - luz
float valorLuminosidade;
float limiarEscuro = 300;

float minimoFotoresistor = 85;
float maximoFotoresistor = 1023;

int tempoAberto = 300000;
int tempoFechado = 300000;

float lerUmidade(leitorUmidade);
float lerLuminosidade(leitorLuminosidade);


void setup() {
	pinMode(pinLedSeco, OUTPUT);
	pinMode(pinLedUmido, OUTPUT);

	pinMode(pinLedLuminosidade, OUTPUT);
	pinMode(pinLedSemLuminosidade, OUTPUT);

	pinMode(serialRS, OUTPUT);
	pinMode(serialE, OUTPUT);
	pinMode(serialDB4, OUTPUT);
	pinMode(serialDB5, OUTPUT);
	pinMode(serialDB6, OUTPUT);
	pinMode(serialDB7, OUTPUT);

	pinMode(pinBotao, INPUT);

	pinMode(valvulaSolenoide, OUTPUT);
	
	pinMode(leitorLuminosidade, INPUT);
	pinMode(leitorUmidade, INPUT);
	
	lcd.begin(16, 2);
	lcd.setCursor(0, 1);
	lcd.print("hello, world!");

	//Serial.begin(9600);

	//Desligar tudo (pré loop)
	digitalWrite(pinLedSeco, LOW);
	digitalWrite(pinLedUmido, LOW);
	digitalWrite(valvulaSolenoide, HIGH);
	digitalWrite(pinBotao, HIGH);
}


void loop() {


	//LEITURAS

	float lerLuminosidade(leitorLuminosidade) {
		valorFotoresistor = analogRead(fotoResistor), delay(100000);
		luminosidade = (valorFotoresistor - minimoFotoresistor) / (maximoFotoresistor - minimoFotoresistor) * 10; //variar de 0 até 10 
		luminosidade = (luminosidade - 10) * -1; //inverter as propriedades da tensão e luminosidade  
		Str[8] = valorFotoresistor;
		lcd.write(Str[8]);
	}

	//ler umidade
	float lerUmidade(umidade) {
		valorUmidade = analogRead(leitorUmidade), delay(100000);
		Str[7] = valorUmidade;
		lcd.write(Str[7);
	}


	//LEEEEEEED


	if (valorUmidade <= padraoSeco) {
		digitalWrite(pinLedSeco, HIGH);
		digitalWrite(pinLedUmido, LOW);
	}
	else {
		digitalWrite(pinLedSeco, LOW);
		digitalWrite(pinLedUmido, HIGH);

		Serial.println(valorUmidade);
		delay(1000);
	}

	//função condicional para ativar o led que informa a luminosidade
	if (leitorLuminosidade <= limiarEscuro) {
		digitalWrite(pinLedLuminosidade, LOW);
		digitalWrite(pinLedSemLuminosidade, HIGH);
	}
	else {
		digitalWrite(pinLedLuminosidade, HIGH);
		digitalWrite(pinLedSemLuminosidade, LOW);
	}


	//FUNÇÕES DE VERDADE (após o led)

	//Função para começar a regar caso a terra esteja seca
	while (valorUmidade < padraoSeco) {

		lcd.setCursor(0, 1);
		lcd.print("Regando...");
		digitalWrite(valvulaSolenoide, LOW);            //low -> abrir
		delay(tempoAberto);
		digitalWrite(valvulaSolenoide, HIGH);           //high -> fechar
		delay(tempoFechado);
		valorUmidade = analogRead(leitorUmidade);
	}


	//Função botão - Serial
	botaoAtual = digitalRead(pinBotao);

	if (botaoAtual && !botaoAnterior) {

		if (contagemBotao % 2 == 0)
		{
			lcd.setCursor(0, 1);
			lcd.print("Umi: ");
			lcd.print(Str[7]);
		}
		else
		{
			lcd.setCursor(1, 1);
			lcd.print("Lum: ");
			lcd.print(Str[8]);
		}

		botaoAnterior = botaoAtual;
		contagemBotao++;
	}
}
