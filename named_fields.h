/**
 *  @file named_fields.h
 *  @brief Set of C Pre Processor Macros for manipulating fields within 
 *         an integer variable type. 
 *  @details For use when builtin bit_fields are undesirable. These macros 
 *  use a sub fields left shift offset and bit field width to do the correct
 *  mask and shift operations. Macro become more complex going down building 
 *  on previous macros to construct more complex behavior. 
 *  The final set of Macros define a Domain specific language to build or
 *  mutate an integer given a set of Field name, field value pairs enclosed
 *  in parentheses and separated by commas. The DSL assumes field name macros
 *  exist with root name and suffixes of _POS and _WTH. 
 *  For example, given two fields with system defined names STATUS and CONTROL,
 *  there should be defined 4 macros:
 *      STATUS_POS, STATUS_WTH, CONTROL_POS, CONTROL_WTH.
 *  The Macro Build_Fields would then be used as:
 *  uint32_t val = Build_Fields((STATUS, 0x3), (CONTROL, my_status));
 *  where the value portion of the pair can be a constant or a variable.
 *  When all constant values are use, the Macro deduces to a single integer 
 *  constant.
 *  In addition to Build_Fields there is a Mutate_Fields which applies the
 *  field pairs to an existing value to allow READ-MODIFY-WRITE operations
 *  on field values.
 *  
 */
#ifndef _NAMED_FIELDS_H
#define _NAMED_FIELDS_H

#include <stdint.h>
typedef volatile uint32_t _BaseReg_t;


// Accept any number of args >= N, but expand to just the Nth one. In this case,
// we have settled on 15 as N. 
#define _GET_Nof15_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, _F, N, ...) N
#define COUNT_VARARGS(...) _GET_Nof15_ARG(__VA_ARGS__,0xF,0xE, 0xD, 0xC, 0xB, 0xA,9,8,7,6,5,4,3,2,1)


// basic operation of building a field, 
// the base value is shifted into position then trimmed for size
#define _BuildField(val, pos, pos_mask) ((val << pos) & pos_mask)

// basic operation of extracting a field from a variable
// the base value is shifted out of position then trimmed to size
#define _TrimField(val, pos, base_mask) ((val >> pos) & base_mask)

// alternate operation of extracting a field from an UNSIGNED variable
// the base value is trimmed for size then shifted out of position
#define _TrimField2(val, pos, pos_mask) ((val & pos_mask) >> pos)

// make a base mask of desired width
//#define _MakeBaseMask(width) (((_BaseReg_t)(1) << width) - 1U)
#define _MakeBaseMask(width) ((1UL << width) - 1U)

// make a positional mask of desired width at position
#define _MakePosMask(width, pos) (_MakeBaseMask(width) << pos)


// assuming a field with a unique name FNAME there will be two macros defined
// FNAME_POS and FNAME_WTH defining the offset position and width of the field.
// we use these macros to create macros to set and get fields by name.

#define _make_pos(fname) fname ## _POS
#define _make_wth(fname) fname ## _WTH

#define _NameBaseMask(fname) _MakeBaseMask(_make_wth(fname))
#define _NamePosMask(fname)  _MakePosMask(_make_wth(fname), _make_pos(fname))

// macro to put a value into named field
#define Build_Field(fname, val) _BuildField((val), _make_pos( fname ), _NamePosMask( fname ))
// macro with same pattern as Build_Field that just builds the mask
#define Build_FieldMask(fname, val) _NamePosMask(fname)
// macro to extract a named field value from a variable
#define Trim_Field(var, fname) _TrimField(var, _make_pos(fname), _NameBaseMsk(fname))




// Macro Hacks to allow iteration over varadic macro lists

#define _or_0(_call, x, ...) _call x  
#define _or_1(_call, x, ...) _call x  | _or_0(_call, __VA_ARGS__)
#define _or_2(_call, x, ...) _call x  | _or_1(_call, __VA_ARGS__)
#define _or_3(_call, x, ...) _call x  | _or_2(_call, __VA_ARGS__)
#define _or_4(_call, x, ...) _call x  | _or_3(_call, __VA_ARGS__)
#define _or_5(_call, x, ...) _call x  | _or_4(_call, __VA_ARGS__)
#define _or_6(_call, x, ...) _call x  | _or_5(_call, __VA_ARGS__)
#define _or_7(_call, x, ...) _call x  | _or_6(_call, __VA_ARGS__)
#define _or_8(_call, x, ...) _call x  | _or_7(_call, __VA_ARGS__)
#define _or_9(_call, x, ...) _call x  | _or_8(_call, __VA_ARGS__)
#define _or_A(_call, x, ...) _call x  | _or_9(_call, __VA_ARGS__)
#define _or_B(_call, x, ...) _call x  | _or_A(_call, __VA_ARGS__)
#define _or_C(_call, x, ...) _call x  | _or_B(_call, __VA_ARGS__)
#define _or_D(_call, x, ...) _call x  | _or_C(_call, __VA_ARGS__)
#define _or_E(_call, x, ...) _call x  | _or_D(_call, __VA_ARGS__)

#define _apply_x_and_or(x, ...) \
    _GET_Nof15_ARG(__VA_ARGS__, \
    _or_E, _or_D, _or_C, _or_B, _or_A, \
    _or_9, _or_8, _or_7, _or_6, _or_5,\
    _or_4, _or_3, _or_2, _or_1, _or_0)(x, __VA_ARGS__)

// some debug macros
#define EVAL1(...) __VA_ARGS__
#define STR_IT(val) # val
#define teststr(...) printf("str is %s \n", EVAL1(STR_IT __VA_ARGS__))

// combine one or more (field,value) pairs to produce a register value, 
// unspecified fields set to zero 
// Looks like Build_Fields((name1, val1)[,(name2, val2),...(name_n, value_n)] )
// where the name,value pair MUST be in parentheses, even in addition to the
// macro's parentheses
#define Build_Fields(...) (_apply_x_and_or(Build_Field, __VA_ARGS__))

// mutate fields in an existing register with one or more (field,value) pairs
// result can be written back to register for true read-modify-write operation  
#define Mutate_Fields(start, ...) ((start & ~(_apply_x_and_or(Build_FieldMask, __VA_ARGS__))) | (_apply_x_and_or(Build_Field, __VA_ARGS__)))
// macro to take a set of (field, value) pairs and 
// apply them to a variable as a single read modify write
#define Reg_RMW(reg,  ...) reg = Mutate_Fields(reg, __VA_ARGS__)

#endif // _NAMED_FIELDS_H
