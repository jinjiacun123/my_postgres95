void *
StringToNode(char *str){
  void *retval;

  (void) lsptok(str, NULL);
  retval = nodeRead(true);

  return retval;
}
