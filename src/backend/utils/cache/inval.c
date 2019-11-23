void
DiscardInvalid(){
  elog(DEBUG, "Discardinvalid called");

  InvalidateShareInvalid(CacheInvalidate, ResetSystemCaches);
}
