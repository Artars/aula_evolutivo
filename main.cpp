#include <iostream>
#include <stdlib.h>
#include <time.h>

#define POP_SIZE 10
#define POP_SIZE_WITHOUT_BEST 9
#define VAR_COUNT 3
#define NUM_INTERATIONS 100
//Global variables

struct Indiv {
  int params[VAR_COUNT];
  int score;
};

Indiv population[POP_SIZE];
int pares[POP_SIZE_WITHOUT_BEST][2];
Indiv filhos[POP_SIZE_WITHOUT_BEST];

int theBestOfAll = -1;



int randomInt(int min, int max)
{
  int r = rand() % (max+1-min);
  return r+min;
}

// float randomFloat(float min, float);

/*
  inicia aleatoriamente
*/
void InitPop(int maxVal)
{
  int i,j;
  for(i = 0; i < POP_SIZE; i++)
  {
    for(j=0; j < VAR_COUNT; j++)
    {
      population[i].params[j] = randomInt(0,maxVal);
    }
  }
}

int EvaluationFormula(Indiv ind)
{
  return ind.params[0] + ind.params[1] + ind.params[2];
  // int x = ind.params[0];
  // if(x < 0)
  //   return 0;
  // else if(x < 5)
  //   return x*2;
  // else if(x < 10)
  //   return 10-(x-5)*2;
  // else
  //   return 0;
}

/*
  Deve ser sabida qual a formula de evaluação. Nesse caso é a soma
*/
void Evaluate()
{
  int aux, i,j;
  int best = -1;
  int bestValue = -100;
  for(i = 0; i < POP_SIZE; i++)
  {
    int score = EvaluationFormula(population[i]);
    population[i].score = score;
    if(score > bestValue)
    {
      bestValue = score;
      best = i;
    }
  }

  theBestOfAll = best;
}

/*
  Maneiras de selecionar pais
  1) Melhor reproduz com todos
  2) Roleta: Seleciona um aleatório usando pesos quanto melhor of fitness
  3) Torneio de 2: seleciona dois aleatoriamente, duela pelo melhor fitness. Esse é um dos pais
  Repete processo pro outro pai. Faz o mesmo até obter todos os filhos
*/

void Select()
{
  int idFilho, pai1, pai2;
  for(idFilho = 0; idFilho < POP_SIZE_WITHOUT_BEST; idFilho++)
  {
    int pai11,pai12,pai21,pai22;
    pai11 = randomInt(0, POP_SIZE_WITHOUT_BEST);
    pai12 = randomInt(0, POP_SIZE_WITHOUT_BEST);
    pai21 = randomInt(0, POP_SIZE_WITHOUT_BEST);
    pai22 = randomInt(0, POP_SIZE_WITHOUT_BEST);

    if(population[pai11].score > population[pai12].score)
      pares[idFilho][0] = pai11;
    else
      pares[idFilho][0] = pai12;

    if(population[pai21].score > population[pai22].score)
      pares[idFilho][1] = pai21;
    else
      pares[idFilho][1] = pai22;

    int i;
    for(i = 0; i < VAR_COUNT; i++)
    {
      filhos[idFilho].params[i] = (population[pares[idFilho][0]].params[i] + population[pares[idFilho][1]].params[i])/2;
    }
  }
}

/*
  Essa etapa não é necessária, mas pode ajudar
  Você pode trocar em qualquer ponto, ou a partir de um ponto
  Nesse caso, será feito uma troca de genes entre pais
*/
void CrossOver()
{

}

/*
  Realiza uma operação com todos os filhos (Nesse caso adicionar ou remover 1)

  Tres etapas
  a) Escolher qual filho vai mutar (nesse caso todos)
  b) Qual gene do filho vai ser mutado (nesse caso apenas 1)
  c) O quanto modifica o gene (nesse caso +- 0.1) 
*/
void Mutation()
{
  int childId;
  int paramToMutate = randomInt(0, VAR_COUNT-1);

  for(childId = 0; childId < POP_SIZE_WITHOUT_BEST; childId++)
  {
    filhos[childId].params[paramToMutate] += randomInt(-1, 1);
  }
}

/*
  Rearanjar população

  1) Pode matar todo mundo e substituir pelos filhos
  2) Pode manter os pais e filhos e matar depois dos limite de população passar

  POR FAVOR NÃO MATAR O MELHOR DE TODOS
*/
void Rearange()
{
  int i, aux = 0;
  for(i = 0; i < POP_SIZE; i++)
  {
    if(i != theBestOfAll)
    {
      population[i] = filhos[aux];
      aux++;
    }
  }
}

void Print()
{
  int i,j;
  for(i = 0; i < POP_SIZE; i++)
  {
    std::cout << "(" << population[i].score << " ) ";
    for(j = 0; j < VAR_COUNT; j++)
    {
      std::cout << population[i].params[j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Melhor: " << theBestOfAll << " (" << population[theBestOfAll].score << ")" << std::endl;
}


int main() {
  
  srand(time(NULL));
  InitPop(10);

  int i =0;
  for(i = 0; i < NUM_INTERATIONS; i++)
  {
    std::cout << "Geração " << i << std::endl;
    Evaluate();
    Select();
    CrossOver();
    Mutation();
    Print();
    Rearange();
  }
}