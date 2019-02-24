#ifndef TIMESTAMP_H
#define TIMESTAMP_H

typedef struct timestamp timestamp;

struct timestamp
{
	int hour;
	int min;
	int sec;
};

typedef struct timestampFields timestampFields;

struct timestampFields
{
	GObject *hour;
	GObject *minute;
	GObject *second;
};

typedef struct timestampFieldsList TList;

struct timestampFieldsList
{
	timestampFields t;
	TList* next;
};

TList* addTimestampFields(TList* root, timestampFields t){
	TList* aux = (TList*) malloc(sizeof(TList));
	aux->t = t;
	aux->next = NULL;
	if(root == NULL)
		root = aux;
	else{
		TList* aux2 = root;
		while(aux2->next != NULL){
			aux2 = aux2->next;
		}
		aux2->next = aux;
	}
	return root;
}

int timeStrToInt(const gchar *c){
	int n;
	if(*(c+1) == '\0'){
		return gCharToInt(*c);
	}else{
		return (gCharToInt(*c) * 10) + (gCharToInt(*(c+1)));
	}
}

timestamp difference(timestamp ts1, timestamp ts2){
  timestamp res;
  if(ts1.sec < ts2.sec){
  	ts1.min--;
  	ts1.sec += 60;
  }

  if(ts1.min < ts2.min){
  	ts1.hour--;
  	ts1.min += 60;
  }

  res.sec = ts1.sec - ts2.sec;
  res.min = ts1.min - ts2.min;
  res.hour = ts1.hour - ts2.hour;

  return res;
}

#endif