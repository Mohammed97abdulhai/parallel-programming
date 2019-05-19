// MPI1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Include\mpi.h"
#include "time.h"

using namespace std;
int main()
{
	int scores[3];
	MPI_Init(NULL, NULL);
	MPI_Status stat;


	int number_of_tasks;
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_tasks);

	cout << number_of_tasks;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	scores[rank] = 10;

	cout << "rank" << rank;


	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	
	int result;
	scores[rank] = 10;
	
	int win = 1;
	int lose = 0;
	int recwin;

	while (scores[0] != 0 && scores[1] != 0 && scores[2] != 0 && scores[3]!=0)
	{
		if (rank%2 == 0)
		{
			MPI_Send(&win, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
			MPI_Recv(&recwin, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD, &stat);
			printf("task %d recieved %d from task %d \n",rank, recwin, rank+1);
			if (recwin == 0)
			{
				scores[rank]++;
				scores[rank+1]--;
			}
		}
		else if (rank%2 == 1)
		{
			MPI_Recv(&recwin, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &stat);
			MPI_Send(&win, 0, MPI_INT, rank-1, 1, MPI_COMM_WORLD);
			printf("taks %d recieved %d from task %d \n", rank, recwin, rank-1);
			
			if (recwin == 1)
			{
				scores[rank]--;
				scores[rank-1]++;
			}

			cout << "score : " << scores[1] << endl;
		}
	}
	cout << "hello" << endl;

	for (int i = 0; i < 2; i++)
	{
		if (scores[i] == 0)
			cout << "player" << i << "is the loser" << endl;
	}

	MPI_Finalize();

	return 0;

	/*int count = 0;
		while (count != players / 2)
		{
			
			for (int i = 0; i < players; i++)
			{
				if (players_points[i] == 0)
					count++;
			}
			if (rank % 2 == 0)
			{
				int win = 1;
				MPI_Send(&win, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
			}
			else
			{
				MPI_Recv(&result, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &stat);
				printf("recieved %d from %d task", result, rank - 1);
			}
			
	}*/
	/*int dest, source, rc , count;
	char inmsg, outmsg = 'x';




	if (rank == 0)
	{
		dest = 1;
		source = 1;
		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, 1, MPI_COMM_WORLD);
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, 1, MPI_COMM_WORLD, &stat);
		printf("the proccess is with the rank 0");
	}
	else if (rank == 1)
	{
		dest = 0;
		source = 0;
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, 1, MPI_COMM_WORLD, &stat);
		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, 1, MPI_COMM_WORLD);
	}

	rc = MPI_Get_count(&stat, MPI_CHAR, &count);
	printf("task %d: recieved %d char(s) from task %d with tag %d \n", rank, count, stat.MPI_SOURCE, stat.MPI_TAG);
	*/
}

