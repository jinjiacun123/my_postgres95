#ifndef HEAPAM_H
#define HEAPAM_H

typedef struct HeapAccessStatisticsData{
  int global_openr;
  int global_RelationNameGetRelation;

  int local_openr;
  int local_RelationNameGetRelation;
} HeapAccessStatisticsData;

typedef HeapAccessStatisticsData *HeapAccessStatistics;

extern HeapAccessStatistics heap_access_stats;
#define IncrHeapAccessStat(x)                                   \
  (heap_access_stats == NULL ? 0 : (heap_access_stats->x)++)
#endif
