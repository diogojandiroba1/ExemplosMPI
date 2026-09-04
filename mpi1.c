#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void) {
    int comm_sz;       /* Número de processos */
    int my_rank;       /* Rank do processo */

    int a = 2;
    int b = 3;
    int temp;
    int somador = 0;
    /*
     * Rank 0 --- Soma tudo
     * Rank 1 --- b + a
     * Rank 2 --- a * b
     * Rank 3 --- a - b
     */

    /* Inicia MPI */
    MPI_Init(NULL, NULL);

    /* Obter número de processos */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Obter rank do processo */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    switch (my_rank) {

        case 0:
            /* Processo centralizador */
            printf("Processo centralizador em execução: %d de %d!\n", my_rank, comm_sz);

            for (int q = 1; q < comm_sz; q++) {
                MPI_Recv(&temp, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                printf("O processo %d enviou o resultado: %d\n", q, temp);
                somador =+ temp;
                
            }

            /* Processo 0 executa a soma, somando o que já tinha */
            printf("O processo %d somou tudo e deu = %d\n", my_rank, somador);
            
            break;

        case 1:
            /* Processo 1 executa b + a */
            temp = b + a;
            printf("O processo %d executou: b + a = %d\n", my_rank, temp);
            MPI_Send(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            break;

        case 2:
            /* Processo 2 executa a * b */
            temp = a * b;
            printf("O processo %d executou: a * b = %d\n", my_rank, temp);
            MPI_Send(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            break;

        case 3:
            /* Processo 3 executa a - b */
            temp = a - b;
            printf("O processo %d executou: a - b = %d\n", my_rank, temp);
            MPI_Send(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            break;
    }

    /* Encerra MPI */
    MPI_Finalize();

    return 0;
}
