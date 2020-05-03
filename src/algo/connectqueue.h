#ifndef CONNECT_QUEUE_H
#define CONNECT_QUEUE_H

typedef struct{
	int* data;
	int capacity;
	int size;
} Queue;

void InitCQ(Queue* q, int);
void AddToCQ(Queue*, int);
_Bool EmptyCQ(Queue*);
int PopCQ(Queue*);
_Bool FoundInCQ(Queue*, int);
void FreeCQ(Queue*);

#endif
