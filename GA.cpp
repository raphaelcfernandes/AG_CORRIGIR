/*Criado por Raphael Cardoso Fernandes
10/03/2016*/

/*Inicio dos includes*/
#include <iostream>
#include <time.h>
#include <sys/time.h> 
#include <fstream>
#include "src/population.hpp"

/*Termino includes*/

/*Inicio defines*/
#define Tcross 80
// #define Population 200
#define populationCol 12
#define repeticoes 1000
#define geracoes 100
#define Tmutacao 20
#define Telitismo 20
using namespace std;

// const int populationLine = Population + (Tcross*Population)/100;
// int Rtorneio = 3;
// int _fitness = 100000;
// int _round = 0;
// typedef struct {
//     int value,location;
// }Father;
// /*Termino defines*/

// /*Inicio funcoes*/
// int Fitness(vector<int> myint);
// int compare(const void *a, const void *b);
// void print_matrix(int matrix[populationLine][populationCol],int linha);
// void gerarPopInicial(vector<int> myint,int population[populationLine][populationCol]);
// void somaAcumulativa(int population[populationLine][populationCol]);
// void torneio(int population[populationLine][populationCol],int fathers_chosen[populationLine][populationCol]);
// void print_matrix(int matrix[populationLine][populationCol],int linha);
// void CreateRoulette(int population[populationLine][populationCol],int fathers_chosen[][populationCol]);
// void cyclicCrossOver(int fathers_chosen[populationLine][populationCol],int population[populationLine][populationCol]);
// void mutacao(int population[populationLine][populationCol],int lin);
// void PMX(int fathers_chosen[populationLine][populationCol],int population[populationLine][populationCol]);
// void elitismo(int population[populationLine][populationCol]);   
// void reinsercaoOrdenada(int population[populationLine][populationCol]);
// void testes(int population[populationLine][populationCol],int fathers_chosen[populationLine][populationCol]);
// int binSearchOnMatrix(int matrix[][populationCol], int key);
// int FitnessByLetter(vector<int> myint);
/*Termino funcoes*/

int main(){
    std::srand(std::time(0));
    Population population(200);
    population.createInitialPopulation();
    // setbuf(stdout, NULL);
    // int population[populationLine][populationCol]={0},fathers_chosen[(Tcross*Population)/100][populationCol]={0};
    // vector<int>myint;
    // myint.clear();
    // int loop=0,g=0,execucoes=0;
    // float cont=0;
    // while(g<repeticoes){
    //     myint.clear();
    //     for(int i=0;i<10;i++)myint.push_back(i);
    //     gerarPopInicial(myint,population);
    //     loop=0;
    //     while(loop<geracoes){
    //         CreateRoulette(population,fathers_chosen);
    //         //torneio(population,fathers_chosen);
    //         PMX(fathers_chosen,population);
    //         //cyclicCrossOver(fathers_chosen,population);
    //         reinsercaoOrdenada(population);
    //         //elitismo(population);
    //        loop++;
    //        if(population[0][10]==0){
    //             cont++;
    //             break; 
    //         }
    //     }
    //     g++;
    // }        
    // cout<<cont/10<<"%"<<endl;
    // return 0;
}
