/*Criado por Raphael Cardoso Fernandes
10/03/2016*/

/*Inicio dos includes*/
#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <random>
#include <sys/time.h> 
#include <fstream>
#include "src/individual.hpp"
/*Termino includes*/

/*Inicio defines*/
#define Tcross 80
#define Population 200
#define populationCol 12
#define repeticoes 1000
#define geracoes 100
#define Tmutacao 20
#define Telitismo 20
using namespace std;




const int populationLine = Population + (Tcross*Population)/100;
int Rtorneio=3;
int _fitness=100000;
int _round=0;
typedef struct{
    int value,location;
}Father;
/*Termino defines*/

/*Inicio funcoes*/
int Fitness(vector<int> myint);
int compare(const void *a, const void *b);
void print_matrix(int matrix[populationLine][populationCol],int linha);
void gerarPopInicial(vector<int> myint,int population[populationLine][populationCol]);
void somaAcumulativa(int population[populationLine][populationCol]);
void torneio(int population[populationLine][populationCol],int fathers_chosen[populationLine][populationCol]);
void print_matrix(int matrix[populationLine][populationCol],int linha);
void CreateRoulette(int population[populationLine][populationCol],int fathers_chosen[][populationCol]);
void cyclicCrossOver(int fathers_chosen[populationLine][populationCol],int population[populationLine][populationCol]);
void mutacao(int population[populationLine][populationCol],int lin);
void PMX(int fathers_chosen[populationLine][populationCol],int population[populationLine][populationCol]);
void elitismo(int population[populationLine][populationCol]);   
void reinsercaoOrdenada(int population[populationLine][populationCol]);
void testes(int population[populationLine][populationCol],int fathers_chosen[populationLine][populationCol]);
int binSearchOnMatrix(int matrix[][populationCol], int key);
int FitnessByLetter(vector<int> myint);
/*Termino funcoes*/

int main(){
    std::srand(std::time(0));
    setbuf(stdout, NULL);
    int population[populationLine][populationCol]={0},fathers_chosen[(Tcross*Population)/100][populationCol]={0};
    vector<int>myint;
    myint.clear();
    int loop=0,g=0,execucoes=0;
    float cont=0;
    while(g<repeticoes){
        myint.clear();
        for(int i=0;i<10;i++)myint.push_back(i);
        gerarPopInicial(myint,population);
        loop=0;
        while(loop<geracoes){
            CreateRoulette(population,fathers_chosen);
            //torneio(population,fathers_chosen);
            PMX(fathers_chosen,population);
            //cyclicCrossOver(fathers_chosen,population);
            reinsercaoOrdenada(population);
            //elitismo(population);
           loop++;
           if(population[0][10]==0){
                cont++;
                break; 
            }
        }
        g++;
    }        
    cout<<cont/10<<"%"<<endl;
    return 0;
}

void gerarPopInicial(vector<int> myint,int population[populationLine][populationCol]){
    int i=0;
    do{//Generate Initial Population
        random_shuffle(myint.begin(),myint.begin()+10);
        next_permutation(myint.begin(),myint.begin()+10);
        for(int j=0;j<10;++j)
            population[i][j]=myint[j];
        population[i][10]=FitnessByLetter(myint);
        i++;
    }while(i<Population);
}

int FitnessByLetter(vector<int> myint){
    int carryOn=0,soma=0,total;
    /* S E N D M O R Y _ _ _______
       0 1 2 3 4 5 6 7 8 9 Fitness */
    if(_round==0){
        if(myint[3]+myint[1]>=10){//D+E
            carryOn=1;
            soma+=abs((myint[3]+myint[1]-10)-myint[7]);
        }
        else
            soma+=abs((myint[3]+myint[1])-myint[7]);
        if((myint[2]+myint[6]+carryOn)>=10){//N+R
            soma+=abs((myint[2]+myint[6]+carryOn-10)-myint[1]);
            carryOn=1;
        }
        else{
            soma+=abs(myint[2]+myint[6]+carryOn-myint[1]);
            carryOn=0;
        }
        if((myint[1]+myint[5]+carryOn)>=10){//E+O
            soma+=abs((myint[1]+myint[5]+carryOn-10)-myint[2]);
            carryOn=1;
        }
        else{
            soma+=abs(myint[1]+myint[5]+carryOn-myint[2]);
            carryOn=0;
        }
        if((myint[0]+myint[4]+carryOn)>=10){//S+M
            soma+=abs((myint[0]+myint[4]+carryOn-10)-myint[5]);
            carryOn=1;
        }
        else{
            soma+=abs(myint[0]+myint[4]+carryOn-myint[5]);
            carryOn=0;
        }
        soma+=abs(myint[4]-carryOn);
    }
    /* E A T H P L _ _ _ _ _______
       0 1 2 3 4 5 6 7 8 9 Fitness */
    if(_round==1){
        if(myint[2]*2>=10){//T+T
            carryOn=1;
            soma+=abs(((myint[2]*2)-10)-myint[0]);
        }
        else
            soma+=abs((myint[2]*2)-myint[0]);
        if((myint[1]*2)+carryOn>=10){//A+A
            soma+=abs(((carryOn+(myint[1]*2))-10)-myint[5]);
            carryOn=1;
        }
        else{
            soma+=abs((carryOn+(myint[1]*2))-myint[5]);
            carryOn=0;
        }
        if((myint[0]+myint[3]+carryOn)>=10){//E+H
            soma+=abs(((myint[0]+myint[3]+carryOn)-10)-myint[4]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[0]+myint[3]+carryOn)-myint[4]);
            carryOn=0;
        }
        if(myint[2]+carryOn>=10){
            soma+=abs(((myint[2]+carryOn)-10)-myint[4]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[2]+carryOn)-myint[4]);
            carryOn=0;
        }
        soma+=abs(myint[1]-carryOn);
    }
    /* C R O S A D N G E _ _______
       0 1 2 3 4 5 6 7 8 9 Fitness */
    if(_round==2){
        if(myint[3]*2>=10){//S+S
            carryOn=1;
            soma+=abs(((myint[3]*2)-10)-myint[1]);
        }
        else
            soma+=abs((myint[3]*2)-myint[1]);
        if(myint[3]+myint[5]+carryOn>=10){//S+D
            soma+=abs(((myint[3]+myint[5]+carryOn)-10)-myint[8]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[3]+myint[5]+carryOn)-myint[8]);
            carryOn=0;
        }
        if(myint[2]+myint[4]+carryOn>=10){//O+A
            soma+=abs(((myint[2]+myint[4]+carryOn)-10)-myint[7]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[2]+myint[4]+carryOn)-myint[7]);
            carryOn=0;
        }
        if(myint[1]+myint[2]+carryOn>=10){//R+O
            soma+=abs(((myint[1]+myint[2]+carryOn)-10)-myint[6]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[1]+myint[2]+carryOn)-myint[6]);
            carryOn=0;
        }
        if(myint[0]+myint[1]+carryOn>=10){//C+R
            soma+=abs(((myint[1]+myint[0]+carryOn)-10)-myint[4]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[1]+myint[0]+carryOn)-myint[4]);
            carryOn=0;
        }
        soma+=abs(myint[5]-carryOn);
    }
    /* C O A L S I _ _ _ _ _______
       0 1 2 3 4 5 6 7 8 9 Fitness */
    if(_round==3){
        if(myint[2]*2>=10){//A+A
            carryOn=1;
            soma+=abs(((myint[2]*2)-10)-myint[4]);
        }
        else
            soma+=abs((myint[2]*2)-myint[4]);
        if(myint[0]+myint[3]+carryOn>=10){//C+L
            soma+=abs(((myint[0]+myint[3]+carryOn)-10)-myint[5]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[0]+myint[3]+carryOn)-myint[5]);
            carryOn=0;
        }
        if((myint[1]*2)+carryOn>=10){//O+O
            if((myint[1]*2)+carryOn>=10){
                soma+=abs((((myint[1]*2)+carryOn)-10)-myint[4]);
                carryOn=1;
            }
        }
        else{
            soma+=abs(((myint[1]*2)+carryOn)-myint[4]);
            carryOn=0;
        }
        if((myint[0]*2)+carryOn>=10){//C+C
            if((myint[0]*2)+carryOn>=10){
                soma+=abs((((myint[0]*2)+carryOn)-10)-myint[2]);
                carryOn=1;
            }
        }
        else{
            soma+=abs(((myint[0]*2)+carryOn)-myint[2]);
            carryOn=0;
        }
        soma+=abs(myint[1]-carryOn);
    }
    /* D O N A L G E R T B _______
       0 1 2 3 4 5 6 7 8 9 Fitness */
    if(_round==4){
        if(myint[0]*2>=10){//D+D
            carryOn=1;
            soma+=abs(((myint[0]*2)-10)-myint[8]);
        }
        else
            soma+=abs((myint[0]*2)-myint[8]);
        if((myint[4]*2)+carryOn>=10){//L+L
            soma+=abs((((myint[4]*2)+carryOn)-10)-myint[7]);
            carryOn=1;
        }
        else{
            soma+=abs(((myint[4]*2)+carryOn)-myint[7]);
            carryOn=0;
        }
        if((myint[3]*2)+carryOn>=10){//A+A
            soma+=abs((((myint[3]*2)+carryOn)-10)-myint[6]);
            carryOn=1;
        }
        else{
            soma+=abs(((myint[3]*2)+carryOn)-myint[6]);
            carryOn=0;
        }
        if(myint[2]+myint[7]+carryOn>=10){//N+R
            soma+=abs(((myint[2]+myint[7]+carryOn)-10)-myint[9]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[2]+myint[7]+carryOn)-myint[9]);
            carryOn=0;
        }
        if(myint[1]+myint[6]+carryOn>=10){//O+E
            soma+=abs(((myint[1]+myint[6]+carryOn)-10)-myint[1]);
            carryOn=1;
        }
        else{
            soma+=abs((myint[1]+myint[6]+carryOn)-myint[1]);
            carryOn=0;
        }
        if(myint[0]+myint[5]+carryOn>=10){//D+G
            soma+=abs(((myint[0]+myint[5]+carryOn)-10)-myint[7])+20;
            carryOn=1;
        }
        else
            soma+=abs((myint[0]+myint[5]+carryOn)-myint[7]);
    }
    return soma;
}

void print_matrix(int matrix[populationLine][populationCol],int linha){
    for(int i=0;i<linha;i++){
        for(int j=0;j<populationCol;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int binSearchOnMatrix(int matrix[][populationCol], int key){
    int ini=0,end=Population-1,middle;
    while(ini<=end){
        middle=floor(ini+end)/2;
        if(matrix[middle][11] >= key && key > matrix[middle-1][11])
            return middle;
        else if(matrix[middle][11] < key)
            ini=middle+1;
        else
            end=middle-1;
    }
    return 0;
}

void reinsercaoOrdenada(int population[populationLine][populationCol]){
    qsort(&population[0][0],populationLine,populationCol*sizeof(int),compare);
}

void PMX(int fathers_chosen[populationLine][populationCol],int population[populationLine][populationCol]){
    int pc1,pc2,vet_troca[10]={0},lin=populationLine-(Tcross*Population)/100,i=0,j=0,k=0,h;
    int *vetP1,*vetP2;
    bool flag;
    string str1,str2;
    vector<int> myint2,myint;
    for(i=0;i<(Tcross*Population)/100;i+=2){
        pc1=rand()%10;
        pc2=rand()%10;
        while(pc2==pc1)
            pc2=rand()%10;
        if(pc1>pc2)
            swap(pc1,pc2);
        vetP1 = (int*)calloc((pc2-pc1)+1,sizeof(int));
        vetP2 = (int*)calloc((pc2-pc1)+1,sizeof(int));
        memset(vet_troca,0,sizeof(vet_troca));
        memset(vetP1,-1,(pc2-pc1)+1);
        memset(vetP2,-1,(pc2-pc1)+1);
        str1.clear();
        str2.clear();
        for(j=pc1;j<=pc2;j++){//Determina a troca do Crossover
            population[lin][j]=fathers_chosen[i+1][j];
            population[lin+1][j]=fathers_chosen[i][j];
            vet_troca[j]=-1;
            if(population[lin][j]!=population[lin+1][j]){
                str1+=to_string(population[lin][j]);
                str2+=to_string(population[lin+1][j]);
            }   
        }
        for(k=0;k<10;k++){//Copia os pais para os filhos
            if(vet_troca[k]!=-1){
                population[lin][k]=fathers_chosen[i][k];
                population[lin+1][k]=fathers_chosen[i+1][k];
            }   
        }
        if(!str1.empty()){//se houve troca de material
            k=0;
            for(h=pc1;h<=pc2;h++){//Insere no vetor 1 os swaps de gene
                flag=false;
                for(j=pc1;j<=pc2;j++){
                    if(population[lin][h]==population[lin+1][j]){
                        flag=true;
                        break;
                    }
                }
                if(!flag){
                    vetP1[k]=population[lin][h];
                    k++;
                }
            }
            k=0;
            for(h=pc1;h<=pc2;h++){//Insere no vetor 2 os swaps de gene
                flag=false;
                for(j=pc1;j<=pc2;j++){
                    if(population[lin+1][h]==population[lin][j]){
                        flag=true;
                        break;
                    }
                }
                if(!flag){
                    vetP2[k]=population[lin+1][h];
                    k++;
                }
            }
            for(k=0;k<10;k++){//Troca os genes repetidos no filho 1
                if(k==pc1)
                    k+=(pc2-pc1)+1;
                if(str1.find(to_string(population[lin][k]))!=std::string::npos){
                    for(j=0;j<=(pc2-pc1)+1;j++){
                        if(vetP1[j]==population[lin][k]){
                            population[lin][k]=vetP2[j];
                            break;
                        }   
                    }
                }
                if(str2.find(to_string(population[lin+1][k]))!=std::string::npos){
                    for(j=0;j<=(pc2-pc1)+1;j++){
                        if(vetP2[j]==population[lin+1][k]){
                            population[lin+1][k]=vetP1[j];
                            break;
                        }
                    }
                }
            }
        }
        free(vetP1);
        free(vetP2);
        mutacao(population,lin);
        mutacao(population,lin+1);
        myint.clear();
        myint2.clear();
        for (int k=0;k<11;k++){
            myint.push_back(population[lin][k]);
            myint2.push_back(population[lin+1][k]);
        }
        population[lin][10]=FitnessByLetter(myint);
        population[lin+1][10]=FitnessByLetter(myint2);
        lin+=2;
    }
}

void mutacao(int population[populationLine][populationCol],int lin){
    int aux,mut1,mut2;
    aux=rand()%100;
    if(aux<=Tmutacao){
        mut1=rand()%10;
        mut2=rand()%10;
        while(mut2==mut1)
            mut2=rand()%10;
        aux=population[lin][mut1];
        population[lin][mut1]=population[lin][mut2];
        population[lin][mut2]=aux;
    }
}

void CreateRoulette(int population[populationLine][populationCol],int fathers_chosen[][populationCol]){
    int total,n=0,pos=Population-1;
    int aux;
    somaAcumulativa(population);
    total=population[pos][11];
    while(n<(Tcross*Population)/100){
        aux=((total-1)*(float)rand()/RAND_MAX);
        pos=binSearchOnMatrix(population,aux);
        for(int j=0;j<12;j++)
            fathers_chosen[n][j]=population[pos][j];
        n++;
    }
}//Otimiza

int compare(const void *a, const void *b) {
    int *e1 = (int *)a;
    int *e2 = (int *)b;
    return e1[10] - e2[10];
}

void somaAcumulativa(int population[populationLine][populationCol]){
    int i=0;
    while(i<Population){
        if(i==0)
            population[i][11]=population[i][10];
        else
            population[i][11]=(population[i-1][11]+population[i][10]);
        i++;
    }
}

void torneio(int population[populationLine][populationCol],int fathers_chosen[][populationCol]){
    int n=0,melhor,aux,pos;
    Father y;
    Father vet[Rtorneio];
    //print_matrix(population,populationLine);fflush(stdout);outfile<<endl;
    while(n<(Tcross*Population)/100){//Torneio
        melhor=1000;
        for(int j=0;j<Rtorneio;j++){
            aux=((Population)*(float)rand()/RAND_MAX);
            y.value=population[aux][10];
            y.location=aux;
            vet[j]=y;
        }
        for(int j=0;j<Rtorneio;j++){
            if(vet[j].value<melhor){
                melhor=vet[j].value;
                pos=j;
            }
        }
        for(int i=0;i<11;i++)
            fathers_chosen[n][i]=population[vet[pos].location][i];
        n++;
    }
}

void cyclicCrossOver(int fathers_chosen[][populationCol],int population[populationLine][populationCol]){
    int aux,trocado,vet_troca[10]={0},pos,lin=populationLine-(Tcross*Population)/100,j;
    vector<int> myint2,myint;
    for(int i=0;i<(Tcross*Population)/100;i+=2){
        pos=rand()%10;
        aux=fathers_chosen[i][pos];
        trocado=-1;
        memset(vet_troca,0,sizeof(vet_troca));
        while(aux!=trocado){
            trocado=fathers_chosen[i+1][pos];
            population[lin][pos]=trocado;//Filho 1
            population[lin+1][pos]=fathers_chosen[i][pos];//Filho 2
            vet_troca[pos]=-1;
            for(j=0;fathers_chosen[i][j]!=trocado;j++);
            pos=j;
        }
        for(int k=0;k<10;k++)
            if(vet_troca[k]!=-1){
                population[lin][k]=fathers_chosen[i][k];
                population[lin+1][k]=fathers_chosen[i+1][k];
        }
        mutacao(population,lin);
        mutacao(population,lin+1);
        myint.clear();
        myint2.clear();
        for (int k=0;k<11;k++){
            myint.push_back(population[lin][k]);
            myint2.push_back(population[lin+1][k]);
        }
        population[lin][10]=FitnessByLetter(myint);
        population[lin+1][10]=FitnessByLetter(myint2);
        lin+=2;
    }
}//Funcao Corrigida

void elitismo(int population[populationLine][populationCol]){
    qsort(&population[0][0],Population,populationCol*sizeof(int),compare);
    for(int i=(Telitismo*Population)/100;i<Population;i++)
        population[i][10]=1000;
    qsort(&population[0][0],populationLine,populationCol*sizeof(int),compare);
}
