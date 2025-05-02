/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_H_INCLUDED
# define YY_YY_YACC_SQL_H_INCLUDED
/* Debug traces.  */
#include "parse_defs.h"
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    CALC = 264,                    /* CALC  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    DATE_T = 279,                  /* DATE_T  */
    DATETIME_T = 280,              /* DATETIME_T  */
    TEXT_T = 281,                  /* TEXT_T  */
    STRING_T = 282,                /* STRING_T  */
    FLOAT_T = 283,                 /* FLOAT_T  */
    HELP = 284,                    /* HELP  */
    EXIT = 285,                    /* EXIT  */
    DOT = 286,                     /* DOT  */
    INTO = 287,                    /* INTO  */
    VALUES = 288,                  /* VALUES  */
    FROM = 289,                    /* FROM  */
    WHERE = 290,                   /* WHERE  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    SET = 293,                     /* SET  */
    ON = 294,                      /* ON  */
    LOAD = 295,                    /* LOAD  */
    DATA = 296,                    /* DATA  */
    INFILE = 297,                  /* INFILE  */
    EXPLAIN = 298,                 /* EXPLAIN  */
    PRIMARY = 299,                 /* PRIMARY  */
    KEY = 300,                     /* KEY  */
    NOT = 301,                     /* NOT  */
    LIKE = 302,                    /* LIKE  */
    NULL_T = 303,                  /* NULL_T  */
    EQ = 304,                      /* EQ  */
    LT = 305,                      /* LT  */
    GT = 306,                      /* GT  */
    LE = 307,                      /* LE  */
    GE = 308,                      /* GE  */
    NE = 309,                      /* NE  */
    INNER = 310,                   /* INNER  */
    JOIN = 311,                    /* JOIN  */
    AGGR_MAX = 312,                /* AGGR_MAX  */
    AGGR_MIN = 313,                /* AGGR_MIN  */
    AGGR_SUM = 314,                /* AGGR_SUM  */
    AGGR_AVG = 315,                /* AGGR_AVG  */
    AGGR_COUNT = 316,              /* AGGR_COUNT  */
    ORDER_T = 317,                 /* ORDER_T  */
    GROUP = 318,                   /* GROUP  */
    BY = 319,                      /* BY  */
    ASC = 320,                     /* ASC  */
    HAVING = 321,                  /* HAVING  */
    AS = 322,                      /* AS  */
    IN = 323,                      /* IN  */
    EXISTS = 324,                  /* EXISTS  */
    LIMIT = 325,                   /* LIMIT  */
    OFFSET = 326,                  /* OFFSET  */
    IF = 327,                      /* IF  */
    DISTINCT = 328,                /* DISTINCT  */
    NUMBER = 329,                  /* NUMBER  */
    FLOAT = 330,                   /* FLOAT  */
    ID = 331,                      /* ID  */
    DATE_TIME_STR = 332,           /* DATE_TIME_STR  */
    DATE_STR = 333,                /* DATE_STR  */
    SSS = 334,                     /* SSS  */
    UMINUS = 335                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 178 "yacc_sql.y"

  ParsedSqlNode *                   sqlNode;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  relAttr;
  varArrayList *                    attrInfos;       
  AttrInfoSqlNode *                 attrInfo;
  Expression *                      expression;
  varArrayList *                    expressionList;  
  varArrayList *                    valueList; 
  varArrayList *                    insertValueList;        /* element type:varArrayList<element type: Value> */     
  varArrayList *                    conditionList;   
  varArrayList *                    relAttrList;    
  varArrayList *                    relationList;   
  InnerJoinSqlNode *                innerJoins; 
  varArrayList*                     innerJoinsList;
  OrderBySqlNode*                   orderbyUnit;
  varArrayList*                     orderbyUnitList;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              boolean;
  LimitSqlNode*                     limit;
  UpdateKV*                         updateKv;
  varArrayList*                     updateKvList;

#line 171 "yacc_sql.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sqlString, ParsedSqlResult * sqlResult, void * scanner);


#endif /* !YY_YY_YACC_SQL_H_INCLUDED  */
