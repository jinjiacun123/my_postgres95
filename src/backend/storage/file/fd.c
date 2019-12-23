long
FileSeek(File file, long offset, int whence){
  int returnCode;

  DO_DB(printf("DEBUG: FileSeek:%d (%s) %d %d\n", file, VfdCache[file].fileName, offset, whence));

  if(FileIsNotOpen(file)){
    switch(whence){
    case SEEK_SET:
      VfdCache[file].seekPos = offset;
      return offset;
    case SEEK_CUR:
      VfdCache[file].seekPos = VfdCache[file].seekPos + offset;
      return VfdCache[file].seekPos;
    case SEEK_END:
      FileAccess(file);
      returnCode = VfdCache[file].seekPos
        = lseek(VfdCache[file].fd, offset, whence);
      return returnCode;
    default:
      elog(WARN, "FileSeek: invalid whence: %d", whence);
      break;
    }
  } else {
    returnCode = VfdCache[file].seekPos
      = lseek(VfdCache[file].fd, offset, whence);
    return returnCode;
  }

  return (-1L);
}
