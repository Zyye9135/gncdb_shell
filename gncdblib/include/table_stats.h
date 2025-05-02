#ifndef TABLE_STATS_H
#define TABLE_STATS_H
#include "gncdb.h"
#include "varArrayList.h"
typedef struct TableStats {
    GNCDB*          db;
    int             IOCostPerPage;
    varArrayList*   histograms;
    HashMap*        fieldMax;
    HashMap*        fieldMin;
    int             tupleCount;
} TableStats;


// estimateScanCost
int tableStatsEstimateScanCost(TableStats* stats);
int tableStatsEstimateCardinality(TableStats* stats, double filterSelectivities);
#endif // TABLE_STATS_H