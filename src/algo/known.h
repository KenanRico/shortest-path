#ifndef KNOWN_H
#define KNOWN_H

typedef struct KnownVertices{
	int* set;
	int N;
} KnownVertices;

void InitKnown(KnownVertices*, int, int);
int Pop(KnownVertices*, int const *);
void AddTo(KnownVertices*, int dest);
void FreeKnown(KnownVertices*);

#endif
