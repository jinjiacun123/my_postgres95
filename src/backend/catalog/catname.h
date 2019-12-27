#ifndef CATANAME_H
#define CATANAME_H

#define AccessMethodRelationName          "pg_am"
#define RelationRelationName              "pg_class"
#define RewriteRelationName               "pg_rewrite"
#define AttributeRelationName             "pg_attribute"
#define ProcedureRelationName             "pg_proc"
#define TypeRelationName                  "pg_type"
#define VariableRelationName              "pg_variable"
#define OperatorRelationName              "pg_operator"
#define AccessMethodOperatorRelationName  "pg_amop"
#define AccessMethodProcedureRelationName "pg_amproc"
#define IndexRelationName                 "pg_index"

extern char *SharedSystemRelationNames[];

#endif
