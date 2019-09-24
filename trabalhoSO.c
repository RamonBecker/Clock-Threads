#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *horario(void *args);
void *alarmeFuncao(void *args);

typedef struct{

    int segundos;
    int minutos;
    int horas;

}Relogio;

Relogio *timeinfo;

int auxSegundosCronometro = 0;
int auxMinutosCronometro = 0;
int auxHorasCronometro = 0;
int despertar = 0;




Relogio *relogio;

int main(){

    Relogio *cronometro;
    Relogio *alarme;

    pthread_t threadRelogio;
    pthread_t threadAlarme;
    pthread_t threadCronometro;

    int op;
    relogio = malloc(sizeof(relogio));
    relogio->horas = 0;
    relogio->minutos = 0;
    relogio->segundos = 0;

    pthread_create(&threadRelogio, NULL, horario, (void *) relogio);

    while(1){

    printf("\n1) Ajustar horario\n");
    printf("2) Visualizar horario\n");
    printf("3) Iniciar cronometro\n");
    printf("4) Parar cronometro\n");
    printf("5) Zerar cronometro\n");
    printf("6) Definir alarme\n");
    printf("Digite uma opcao: ");

    scanf(" %d", &op);

    switch(op){
    case 1:

        pthread_cancel(threadRelogio);

        int segundos, minutos, horas;
        printf("\n\nAjustar horario\n\n");
        printf("\n");
        printf("Digite as segundos: ");
        scanf(" %d", &relogio->segundos);
        printf("Digite os minutos: ");
        scanf(" %d", &relogio->minutos);
        printf("Digite as horas:");
        scanf(" %d", &relogio->horas);
        printf("\n\n");
        pthread_create(&threadRelogio, NULL, horario, (void *)relogio);

        break;

    case 2:
        printf("\n\nHorario atual\n\n");
        printf("Horas: %d, Minutos: %d, Segundos: %d\n\n", relogio->horas, relogio->minutos, relogio->segundos);
        break;

    case 3:

        printf("\nCronometro inciado \n\n");

        cronometro = malloc(sizeof(cronometro));

        cronometro->horas = auxHorasCronometro;
        cronometro->minutos = auxMinutosCronometro;
        cronometro->segundos = auxSegundosCronometro;

        pthread_create(&threadCronometro, NULL, horario,(void *) cronometro);
        break;


    case 4:
        printf("\n\nCronometro parado !\n\n");
        printf("\n\nHoras: %d, Minutos: %d, Segundos: %d\n\n", cronometro->horas, cronometro->minutos, cronometro->segundos);
         auxHorasCronometro = cronometro->horas;
         auxMinutosCronometro = cronometro->minutos;
         auxSegundosCronometro = cronometro->segundos;
         pthread_cancel(threadCronometro);
       break;

    case 5:

      cronometro->horas = 0;
      cronometro->segundos = 0;
      cronometro->minutos = 0;
      auxSegundosCronometro = 0;
      auxMinutosCronometro = 0;
      auxHorasCronometro = 0;
      printf("\n\nCronometro zerado\n\n");
      printf("Horas: %d, Minutos: %d, Segundos: %d", cronometro->horas, cronometro->minutos, cronometro->segundos);
    break;

    case 6:
          printf("\n\n---------- Alarme -------\n\n");
          alarme = malloc(sizeof(alarme));

          printf("Digite a hora:");
          scanf(" %d", &alarme->horas);

          printf("Digite os minutos:");
          scanf(" %d", &alarme->minutos);
          pthread_create(&threadAlarme, NULL, alarmeFuncao, (void *)alarme);
          break;
   }
  }
  return 0;
}

void *horario(void *args){

  Relogio *relogio = (Relogio *) args;

  while(1){
    for(int i = relogio->segundos; i < 60; i++){
        sleep(1);
        relogio->segundos = i;
    }

    if(relogio->horas == 23 && relogio->minutos == 59 && relogio->segundos == 59){
        relogio->segundos = 0;
        relogio->minutos = 0;
        relogio->horas = 0;
    }

    if(relogio->segundos == 59){
        relogio->minutos++;
        relogio->segundos = 0;
    }

    if(relogio->minutos == 59){
         relogio->horas++;
         relogio->minutos = 0;
    }


 }
}

void *alarmeFuncao(void *args){

  Relogio *alarme = (Relogio *) args;

  while(1){
    sleep(1);
    if(alarme->horas == relogio->horas && alarme->minutos == relogio->minutos){
       printf("\n\nTa na hora de acordar\n\n");
       break;
     }
  }
    return (NULL);
}
