char *
heap_getattr(HeapTuple tup,
             Buffer    b,
             int       attnum,
             TupleDesc tupleDesc,
             bool      *isnull){
  bool localIsNull;

  Assert(tup != NULL);

  if(! PointerIsValid(isnull))
    isnull = &localIsValid;
  if(attnum > (int) tup->t_natts){
    *isnull = true;
    return ((char *)NULL);
  }

  if(attnum > 0){
    char *datum;
    datum = fastgetattr(tup, attnum, tupleDesc, isnull);
    return (datum);
  }

  *isnull = false;
  return heap_getsysattr(tup, b, attnum);
}
