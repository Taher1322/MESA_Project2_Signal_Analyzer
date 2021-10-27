#ifndef __DHRY_H__
#define __DHRY_H__

#include "stddef.h"

#define USEC_PER_SEC     1000000.0
/* Berkeley UNIX C returns process times in seconds/HZ */

#ifdef  NOSTRUCTASSIGN
#define structassign(d, s)      memcpy(&(d), &(s), sizeof(d))
#else
#define structassign(d, s)      d = s
#endif

#ifdef  NOENUM
#define Ident_1 0
#define Ident_2 1
#define Ident_3 2
#define Ident_4 3
#define Ident_5 4
typedef int dhry_e;
#else
typedef enum
{
    Ident_1, Ident_2, Ident_3, Ident_4, Ident_5
} dhry_e;
#endif
/* for boolean and enumeration types in Ada, Pascal */

/* General definitions: */

#define NULL 0
/* Value of a NULL pointer */
#define true  1
#define false 0

typedef int One_Thirty;
typedef int One_Fifty;
typedef char Capital_Letter;
typedef int Boolean;
typedef char Str_30[31];
typedef int Arr_1_Dim[50];
typedef int Arr_2_Dim[50][50];

typedef struct record
{
    struct record *Ptr_Comp;
    dhry_e Discr;
    union
    {
        struct
        {
            dhry_e Enum_Comp;
            int Int_Comp;
            char Str_Comp[31];
        } var_1;
        struct
        {
            dhry_e E_Comp_2;
            char Str_2_Comp[31];
        } var_2;
        struct
        {
            char Ch_1_Comp;
            char Ch_2_Comp;
        } var_3;
    } variant;
} Rec_Type, *Rec_Pointer;

/* Function Declarations */
void dhry_main(int Number_Of_Runs);
void Proc_1(Rec_Pointer Ptr_Val_Par);
void Proc_2(One_Fifty * Int_Par_Ref);
void Proc_3(Rec_Pointer * Ptr_Ref_Par);
void Proc_4(void);
void Proc_5(void);
void Proc_6(dhry_e Enum_Val_Par, dhry_e * Enum_Ref_Par);
void Proc_7(One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val, One_Fifty * Int_Par_Ref);
void Proc_8(Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref, int Int_1_Par_Val, int Int_2_Par_Val);
dhry_e Func_1(Capital_Letter Ch_1_Par_Val, Capital_Letter Ch_2_Par_Val);
Boolean Func_2(Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref);
Boolean Func_3(dhry_e Enum_Par_Val);

#endif
