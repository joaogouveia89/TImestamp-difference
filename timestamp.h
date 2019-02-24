#ifndef TIMESTAMP_H
#define TIMESTAMP_H

typedef struct timestamp timestamp;

struct timestamp
{
	int *hour;
	int *minute;
	int *second;
};

typedef struct timestampList TList;

struct timestampList
{
	timestamp t;
	TList* next;
};

#endif