#ifndef PG_CLASS_H
#define PG_CLASS_H

#define RelOid_pg_type      71
#define RelOid_pg_attribute 75
#define RelOid_pg_proc      81
#define RelOid_pg_class     83

#define RELKIND_INDEX       'i'
#define RELKIND_UNCATALOGED 'u'

CATALOG(pg_class) BOOTSTRAP {
  NameData relname;  //relation name
  Oid      reltype;  //relation type
  Oid      relam;    //relation access method
  char     relkind;  //
  int2     relnatts; //属性个数
  int2     relsmgr;
  bool     relhasrules;
} FormData_pg_class;

typedef FormData_pg_class *Form_pg_class;

#define CLASS_TUPLE_SIZE \
  (offsetof(FormData_pg_class, relhasrules) + sizeof(bool))

#define Anum_pg_class_relname 1

#endif
