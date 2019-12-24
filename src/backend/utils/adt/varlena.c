char *
textout(struct varlena *vlena){
  int  len;
  char *result;

  if(vlena == NULL){
    result = (char *)palloc(2);
    result[0] = '-';
    result[1] = '\0';
    return (result);
  }
  len    = VARSIZE(vlena) - VARHDRSZ;
  result = (char *) palloc(len + 1);
  memmove(result , VARDATA(vlena), len);
  result[len] = '\0';
  return (result);
}
