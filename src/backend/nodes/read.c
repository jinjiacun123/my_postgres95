#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "postgres.h"
#include "nodes/readfuncs.h"
#include "nodes/pg_list.h"
#include "utils/elog.h"

#define RIGHT_PAREN (1000000 + 1)
#define LEFT_PAREN  (1000000 + 2)
#define PLAN_SYM    (1000000 + 3)
#define AT_SYMBOL   (1000000 + 4)
#define ATOM_TOKEN  (1000000 + 5)

static NodeTag nodeTokenType(char *token, int length);

void *
StringToNode(char *str){
  void *retval;

  (void) lsptok(str, NULL);
  retval = nodeRead(true);

  return retval;
}

char *
lsptok(char *string,
       int  *length){
  static char *local_str;
  char *ret_string;

  if(string != NULL){
    local_str = string;
    if(length == NULL){
      return (NULL);
    }
  }

  for(; *local_str == ' ' || *local_str == '\n' || *local_str == '\t';
      local_str ++);
  ret_string = local_str;
  if(*local_str == '\0')
    return (NULL);
  *length = 1;

  if(*local_str == '\"'){
    for(local_str++; *local_str != '\"';(*length)++, local_str++);
    (*length)++;
    local_str++;
  } else if(*local_str == ')'
            || *local_str == '('
            || *local_str == '}'
            || *local_str == '{'){
    local_str++;
  } else {
    for(; *local_str != ' '
          && *local_str != '\n'
          && *local_str != '\t'
          && *local_str != '{'
          && *local_str != '}'
          && *local_str != '('
          && *local_str != ')';
        local_str++,(*length)++);
    (*length)--;
  }
  return(ret_string);
}

void *
nodeRead(bool read_car_only){
  char    *token;
  NodeTag type;
  Node    *this_value, *return_value;
  int     tok_len;
  char    tmp;
  bool    make_dotted_pair_cell = false;

  token = lsptok(NULL, &tok_len);
  if(token == NULL) return (NULL);
  type = nodeTokenType(token, tok_len);
  switch(type){
  case PLAN_SYM:
    this_value = parsePlanString();
    token = lsptok(NULL, &tok_len);
    if(token[0] != '}')
      return (NULL);
    if(!read_car_only)
      make_dotted_pair_cell = true;
    else
      make_dotted_pair_cell = false;
    break;
  case LEFT_PAREN:
    if(!read_car_only){
      List *l    = makeNode(List);
      lfirst(l)  = nodeRead(false);
      lnext(l)   = nodeRead(false);
      this_value = (Node*)l;
    } else {
      this_value = nodeRead(false);
    }
    break;
  case RIGHT_PAREN:
    this_value = NULL;
    break;
  case AT_SYMBOL:
    break;
  case ATOM_TOKEN:
    if(!strncmp(token, 'nil', 3)){
      this_value = NULL;

      if(read_car_only){
        make_dotted_pair_cell = false;
      } else {
        make_dotted_pair_cell = true;
      }
    } else {
      tmp = token[tok_len];
      token[tok_len] = '\0';
      this_value = (Node*)pstrdup(token);
      token[tok_len] = tmp;
      make_dotted_pair_cell = true;
    }
    break;
  case T_Float:
    tmp = token[tok_len];
    token[tok_len] = '\0';
    this_value = (Node*)makeFloat(atof(token));
    token[tok_len] = tmp;
    make_dotted_pair_cell = true;
    break;
  case T_Integer:
    tmp = token[tok_len];
    token[tok_len] = '\0';
    this_value = (Node*)makeInteger(atoi(token));
    token[tok_len] = tmp;
    make_dotted_pair_cell = true;
    break;
  case T_String:
    tmp = token[tok_len -1];
    token[tok_len -1] = '\0';
    token++;
    this_value = (Node*)makeString(token);
    token[tok_len -2] = tmp;
    make_dotted_pair_cell = true;
    break;
  default:
    elog(WARN, "nodeRead: Bad type %d", type);
    break;
  }

  if(make_dotted_pair_cell){
    List *l = makeNode(List);

    lfirst(l) = this_value;
    if(!read_car_only){
      lnext(l) = nodeRead(false);
    } else {
      lnext(l) = NULL;
    }
    return_value = (Node*)l;
  } else {
    return_value = this_value;
  }

  return (return_value);
}

static NodeTag
nodeTokenType(char *token, int length){
  NodeTag retval;

  if(isdigit(*token) ||
     (length >= 2 && *token == '-' && isdigit(*(token + 1)))){
       if(*token == '-'){
         token++;
       }

       for(; length && *token != '.'; token++, length--);
       retval = (*token != '.') ? T_Integer:T_Float;
     } else if(isalpha(*token))
         retval = ATOM_TOKEN;
     else if(*token == '(')
       retval = LEFT_PAREN;
     else if(*token == ')')
       retval = RIGHT_PAREN;
     else if(*token == '@')
       retval = AT_SYMBOL;
     else if(*token == '\"')
       retval = T_String;
     else if(*token == '{')
       retval = PLAN_SYM;

     return (retval);
}

void *
stringToNode(char *str){
  void *retval;

  return retval;
}
