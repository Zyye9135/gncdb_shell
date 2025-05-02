#ifndef SQL_RESULT_H
#define SQL_RESULT_H
// typedef struct TupleSchema{

// } TupleSchema;

typedef struct SqlResult
{
  // TupleSchema tupleSchema;
  int   returnCode;
  char *stateString;
} SqlResult;

#endif /* SQL_RESULT_H */
