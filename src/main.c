#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

int qtd_primos;
int numero;
char caracter;
pthread_mutex_t trava;

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

void* funcao_thread(void *arg) {
  int* N = (int*)arg;
  int M = (*N);

  printf("Estou na thread %d!\n", M);

  pthread_mutex_lock(&trava);

  // printf("Numero %d!\n", numero);
  qtd_primos += num_primo(numero);

  pthread_mutex_unlock(&trava);

  printf("Saindo da thread %d!\n", M);
  return NULL;
}

int main() {
  pthread_t threads[4];
  int thread_id[4];
  int aux = 0;
  int num_processos = 0;

  qtd_primos =0;

  for (int i = 0; i < 4; i++) {
    thread_id[i] = i;
  }

  while (aux == 0){
    if (num_processos < 4){
      pthread_mutex_lock(&trava);
      scanf("%d%c", &numero, &caracter);
      // printf("Numero lido %d!\n", numero);

      pthread_create(&(threads[num_processos]), NULL, funcao_thread, &(thread_id[num_processos]));

      pthread_mutex_unlock(&trava);
      for (int p = 0; p<800000; p++);
      num_processos++;

      if (caracter == '\n'){
        aux = 1;
        break;
      }
    }else {
      pthread_join(threads[num_processos-1], NULL);
      num_processos--;
    }
  }


  /* Esperando threads terminarem! */
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Primos: %d!\n", qtd_primos);

  return 0;
}
