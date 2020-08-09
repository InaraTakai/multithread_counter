#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

int qtd_primos;
int numero;
char caracter;

int num_primo(int x){ /* Função que determina se número é primo */
  int i, num_dividores;

  num_dividores = 0;

  for (i=1;i<=x;i++){
    if (x % i == 0){
      num_dividores++; /* Caso o numero seja divisivel pelo índice i, incrementa número de divisores */
    }
  }

  if (num_dividores == 2){ /* Número tem 2 divisores (1 e ele mesmo) */
    return 1;
  }else{
    return 0;
  }
}

void* funcao_thread(void *arg) { /* No parâmetro *arg é passado o inteiro que será verificado */
  int* N = (int*)arg;
  int M = (*N);

  for (unsigned int j=0; j<5000000; j++); /* Pode ser trocado pelo sleep, porém aumenta tempo de execução */
  /* sleep(1); */

  qtd_primos += num_primo(M);

  return NULL;
}

int main() {
  pthread_t threads[4];
  int aux = 0;
  int num_processos = 0;

  qtd_primos = 0;

  while (aux == 0){
    if (num_processos < 4){  /* Se o numero de threads é menor que 4, realiza a leitura da entrada e cria uma thread */
      scanf("%d%c", &numero, &caracter);

      pthread_create(&(threads[num_processos]), NULL, funcao_thread, &numero);

      for (int p = 0; p<800000; p++); /* Pode ser trocado pelo sleep, porém aumenta tempo de execução */
      /* sleep(1); */

      num_processos++;

      if (caracter == '\n'){
        aux = 1;
        break;
      }
    }else { /* Caso o número de threads abertas seja 4, aguarda até uma thread terminar */
      pthread_join(threads[num_processos-1], NULL);
      num_processos--;
    }
  }

  /* Esperando todas as threads terminarem */
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("%d\n", qtd_primos);

  return 0;
}
