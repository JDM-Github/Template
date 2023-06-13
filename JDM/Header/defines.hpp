#pragma once
#ifndef JDM_DEFINES_HPP
#define JDM_DEFINES_HPP

#include "include.hpp"

#define JCONST                          const
#define JNEW                            new
#define JDELETE                         delete
#define JSTRUCT                         struct
#define JCLASS                          class
#define JENUM                           enum
#define JUNION                          union
#define JCONSTEXPR                      constexpr
#define JINLINE                         inline
#define JVIRTUAL                        virtual
#define JSTATIC                         static
#define JFRIEND                         friend
#define JNAMESPACE                      namespace
#define JTEMPLATE                       template
#define JNOEXCEPT                       noexcept
#define JAUTO                           auto
#define JEXTERN                         extern
#define JOVERRIDE                       override
#define JSTATICC                        static_cast
#define JDYNAMICC                       dynamic_cast
#define JREINTERPRETC                   reinterpret_cast
#define JGETTYPE                        decltype

#define JEMPTYSTRING                    ""
#define JNONE                           0
#define JTRUE                           1
#define JFALSE                          0
#define JNULL                           NULL
#define JNULLPTR                        nullptr
#define JTHIS                           this
#define JUSING                          using

#define JTYPENAME                       typename
#define JPUBLIC                         public
#define JPRIVATE                        private
#define JPROTECTED                      protected

#define JFOR                            for
#define JBREAK                          break
#define JCONTINUE                       continue
#define JRETURN                         return
#define JIF                             if
#define JELSE                           else
#define JWHILE                          while
#define JDO                             do
#define JSWITCH                         switch
#define JCASE                           case
#define JDEFAULT                        default

#define JEXIT                           std::exit
#define Random                          rand
#define SRand                           std::srand

#define JDM_UNDEFINED_POS               30
#define JDM_UNDEFINED_SIZE              100

const std::string JDMImage              = "C:/SDL/Template/JDM/DLL/Assets/Image/JDM.png";
const std::string DefaultImage          = "C:/SDL/Template/JDM/DLL/Assets/Image/default.png";
const std::string RoundedImage          = "C:/SDL/Template/JDM/DLL/Assets/Image/rounded_rectangle.png";
const std::string CircleImage           = "C:/SDL/Template/JDM/DLL/Assets/Image/circle.png";
template <class T> using JFUNCTION      = std::function<T>;
template <class T> using JVFUNCTION     = std::function<void(T)>;
using JFUNCCALL                         = std::function<void()>;

std::string typedef                     JSTR;
std::string_view typedef                JSTRVIEW;
std::wstring typedef                    JWSTR;
const std::string typedef               JCSTR;
const std::wstring typedef              JCWSTR;

void typedef                            JVOID;
const void typedef                      JCVOID;
bool typedef                            JBOOL;
short typedef                           JSHORT;
int typedef                             JINT;
long typedef                            JLONG;
long long typedef                       JLLONG;
float typedef                           JFLOAT;
double typedef                          JDOUBLE;
char typedef                            JCHAR;
wchar_t typedef                         JWCHAR;

unsigned short typedef                  JUSHORT;
unsigned int typedef                    JUINT;
unsigned long typedef                   JULONG;
unsigned long long typedef              JULLONG;
unsigned char typedef                   JUCHAR;
unsigned char typedef                   JUINT8;
unsigned short typedef                  JUINT16;
unsigned int typedef                    JUINT32;
unsigned long typedef                   JUINT64;

const bool typedef                      JCBOOL;
const short typedef                     JCSHORT;
const int typedef                       JCINT;
const long typedef                      JCLONG;
const long long typedef                 JCLLONG;
const float typedef                     JCFLOAT;
const double typedef                    JCDOUBLE;
const char typedef                      JCCHAR;
const wchar_t typedef                   JCWCHAR;

const unsigned short typedef            JCUSHORT;
const unsigned int typedef              JCUINT;
const unsigned long typedef             JCULONG;
const unsigned long long typedef        JCULLONG;
const unsigned char typedef             JCUCHAR;
const unsigned char typedef             JCUINT8;
const unsigned short typedef            JCUINT16;
const unsigned int typedef              JCUINT32;
const unsigned long typedef             JCUINT64;

using JCCHARP                           = const char *;

template <class T> JWSTR JTOWSTR(T Expression)  { return std::to_wstring(Expression); }
template <class T> JSTR  JTOSTR (T Expression)  { return std::to_string(Expression ); }

template <class T> using JUP            =   std::unique_ptr<T>;
template <class T, class S> using JPAIR =   std::pair<T, S>;
template <class T> using JSP            =   std::shared_ptr<T>;
#define JMP                                 std::make_unique
#define JMPAIR                              std::make_pair
#define JMS                                 std::make_shared

template <class T> using JVECTOR        =   std::vector<T>;
template <class T> using JSET           =   std::set<T>;
template <class T> using JSTACK         =   std::stack<T>;
template <class T> using JQUEUE         =   std::queue<T>;
template <class T> using JLIST          =   std::list<T>;
template <class T, class C> using JMAP  =   std::map<T, C>;
template <class T, class C> using JUMAP =   std::unordered_map<T, C>;

inline bool operator==(const std::string &str, const std::string &str2) { return !(str.compare(str2)); }
inline bool operator!=(const std::string &str, const std::string &str2) { return  (str.compare(str2)); }

#endif