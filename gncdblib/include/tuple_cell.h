#ifndef TUPLE_CELL_H
#define TUPLE_CELL_H
typedef struct TupleCellSpec{
    char *tableName;
    char *fieldName;
    char *alias;
} TupleCellSpec;

TupleCellSpec *TupleCellSpecCreate(const char *tableName, const char *fieldName, const char *alias);
TupleCellSpec *TupleCellSpecCreateByName(const char *alias);

void TupleCellSpecDestroy(TupleCellSpec* spec);
void TupleCellSpecPointerDestroy(void* data);
TupleCellSpec* TupleCellSpecMove(TupleCellSpec** spec);
#endif