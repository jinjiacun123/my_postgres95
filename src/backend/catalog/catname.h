#ifndef CATANAME_H
#define CATANAME_H

#define AccessMethodRelationName          "pg_am"
#define AccessMethodOperatorRelationName  "pg_amop"
#define AccessMethodProcedureRelationName "pg_amproc"
#define AttributeRelationName             "pg_attribute"
#define DatabaseRelationName              "pg_database"
#define DefaultsRelationName              "pg_defaults"
#define DemonRelationName                 "pg_demon"
#define GroupRelationName                 "pg_group"
#define HostsRelationName                 "pg_hosts"
#define LogRelationName                   "pg_log"
#define MagicRelationName                 "pg_magic"
#define RelationRelationName              "pg_class"
#define RewriteRelationName               "pg_rewrite"
#define ProcedureRelationName             "pg_proc"
#define ServerRelationName                "pg_server"
#define TypeRelationName                  "pg_type"
#define TimeRelationName                  "pg_time"
#define VariableRelationName              "pg_variable"
#define OperatorRelationName              "pg_operator"
#define UserRelationName                  "pg_user"
#define IndexRelationName                 "pg_index"

extern char *SharedSystemRelationNames[];

/**function**/
extern bool IsSystemRelationName(char *relname);

#endif
