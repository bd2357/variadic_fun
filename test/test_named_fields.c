#include "unity.h"
#include "named_fields.h"

#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}


#define F1_POS 0
#define F1_WTH 5
#define F2_POS 8
#define F2_WTH 3
#define F3_POS 16
#define F3_WTH 1
#define F4_POS 22
#define F4_WTH 6


void test_named_fields(void)
{

    uint32_t val = 0xAAAAAAAA;
    //Write_Fields(val, (F1, 2), (F2, 3),  (F3, 0));
    
    printf("%i\n", COUNT_VARARGS((F1, 2), (F2, 3),  (F3, 0) ));
    teststr((hello there));
    teststr((Build_Field(F3, 0x3)));
    
    
    teststr((_apply_x_and_or( Build_FieldMask, (F1,5),  (F2,6) )));
    teststr((_apply_x_and_or( Build_Field,     (F1,5),  (F2,6) )));
    teststr((_apply_x_and_or( Build_Field,     (F3,23), (F1,5), (F2,6) )));    
    teststr((_apply_x_and_or( Build_Field,     (F2,6)         )));    
    printf("0X%X\n", val);
    
    TEST_ASSERT_EQUAL(0x3,Build_Field(F1,3));
    Build_Fields((F1,3));
    val = 0;
    TEST_ASSERT_EQUAL(0x3,Build_Fields((F1,3),(F2,val)));    
    val = 3;
    TEST_ASSERT_EQUAL(0x303,Build_Fields((F1,3),(F2,val)));
    val = 0xff;
    TEST_ASSERT_EQUAL(0x703,Build_Fields((F1,3),(F2,val)));
    val = 0xff;
    TEST_ASSERT_EQUAL(0x10703,Build_Fields((F1,3),(F2,val),(F3,0xf)));

}

void test_overwrite(void)
{
    uint32_t val = 0xffffffff;
    val = Mutate_Fields(val,(F3,0));
    TEST_ASSERT_EQUAL(0xfffeffff, val);
    val = Mutate_Fields(val,(F1,8));
    TEST_ASSERT_EQUAL_HEX(0xfffeffe8, val);
    teststr(( Mutate_Fields(val,(F3,0),(F1,8))));
    val = Mutate_Fields(val,(F3,0),(F1,8));
    TEST_ASSERT_EQUAL_HEX(0xfffeffe8, val);
    
/*    
((val & 
  ~(((((_BaseReg_t)(1) << 1) - 1U) << 16) | ((((_BaseReg_t)(1) << 5) - 1U) << 0))
 ) | 
 ( (((0) << 16) & ((((_BaseReg_t)(1) << 1) - 1U) << 16)) | (((8) << 0) & ((((_BaseReg_t)(1) << 5) - 1U) << 0)))
) 
*/
    
    
    
}


// define at least 15 field positions
#define TF1_POS 0
#define TF1_WTH 2
#define TF2_POS 2
#define TF2_WTH 2
#define TF3_POS 4
#define TF3_WTH 2
#define TF4_POS 6
#define TF4_WTH 2
#define TF5_POS 8
#define TF5_WTH 2
#define TF6_POS 0xa
#define TF6_WTH 2
#define TF7_POS 0xc
#define TF7_WTH 2
#define TF8_POS 0xe
#define TF8_WTH 2
#define TF9_POS 0x10
#define TF9_WTH 2
#define TFA_POS 0x12
#define TFA_WTH 2
#define TFB_POS 0x14
#define TFB_WTH 2
#define TFC_POS 0x16
#define TFC_WTH 2
#define TFD_POS 0x18
#define TFD_WTH 2
#define TFE_POS 0x1a
#define TFE_WTH 2
#define TFF_POS 0x1c
#define TFF_WTH 2
#define TF10_POS 29
#define TF10_WTH 3

/*
Dump of assembler code for function test_build_15_fields:
113     {
   0x0000000000401a8b <+0>:     push   %rbp
   0x0000000000401a8c <+1>:     mov    %rsp,%rbp
   0x0000000000401a8f <+4>:     sub    $0x30,%rsp

114         TEST_ASSERT_EQUAL_HEX(0x15555555,
=> 0x0000000000401a93 <+8>:     movl   $0x44,0x20(%rsp)
   0x0000000000401a9b <+16>:    mov    $0x72,%r9d
   0x0000000000401aa1 <+22>:    mov    $0x0,%r8d
   0x0000000000401aa7 <+28>:    mov    $0x15555555,%edx
   0x0000000000401aac <+33>:    mov    $0x15555555,%ecx
   0x0000000000401ab1 <+38>:    callq  0x402771 <UnityAssertEqualNumber>

115         Build_Fields((TF1,1),(TF6,1),(TF7,1),(TFC,1),(TFD,1),
116                      (TF2,1),(TF5,1),(TF8,1),(TFB,1),(TFE,1),
117                      (TF3,1),(TF4,1),(TF9,1),(TFA,1),(TFF,1) ) );
118
119     }
   0x0000000000401ab6 <+43>:    nop
   0x0000000000401ab7 <+44>:    add    $0x30,%rsp
   0x0000000000401abb <+48>:    pop    %rbp
   0x0000000000401abc <+49>:    retq

End of assembler dump.
*/
void test_build_15_fields(void)
{
    TEST_ASSERT_EQUAL_HEX(0x15555555,
    Build_Fields((TF1,1),(TF6,1),(TF7,1),(TFC,1),(TFD,1),
                 (TF2,1),(TF5,1),(TF8,1),(TFB,1),(TFE,1),
                 (TF3,1),(TF4,1),(TF9,1),(TFA,1),(TFF,1) ) );
    
}

void test_build_1_field(void)
{
    TEST_ASSERT_EQUAL_HEX(0x10000000, Build_Fields( (TFF,1) ) );
    TEST_ASSERT_EQUAL_HEX(0x20000000, Build_Fields( (TF10,1) ) );
    TEST_ASSERT_EQUAL_HEX(0xE0000000, Build_Fields( (TF10,7) ) );
    TEST_ASSERT_EQUAL_HEX(0x00000000, Build_Fields( (TF1,0) ) );
    TEST_ASSERT_EQUAL_HEX(0x00000003, Build_Fields( (TF1,3) ) );
}


/*
Dump of assembler code for function test_mutate_15_fields:
122     {
   0x0000000000401abd <+0>:     push   %rbp
   0x0000000000401abe <+1>:     mov    %rsp,%rbp
   0x0000000000401ac1 <+4>:     sub    $0x40,%rsp

123         uint32_t val = 0xffffffff;
=> 0x0000000000401ac5 <+8>:     movl   $0xffffffff,-0x4(%rbp)

124         TEST_ASSERT_EQUAL_HEX(0xeaaaaaaa,
   0x0000000000401acc <+15>:    mov    -0x4(%rbp),%eax
   0x0000000000401acf <+18>:    and    $0xc0000000,%eax
   0x0000000000401ad4 <+23>:    or     $0x2aaaaaaa,%eax
   0x0000000000401ad9 <+28>:    cltq
   0x0000000000401adb <+30>:    movl   $0x44,0x20(%rsp)
   0x0000000000401ae3 <+38>:    mov    $0x7c,%r9d
   0x0000000000401ae9 <+44>:    mov    $0x0,%r8d
   0x0000000000401aef <+50>:    mov    %rax,%rdx
   0x0000000000401af2 <+53>:    mov    $0xffffffffeaaaaaaa,%rcx
   0x0000000000401af9 <+60>:    callq  0x402771 <UnityAssertEqualNumber>

125         Mutate_Fields(val, (TF1,2),(TF6,2),(TF7,2),(TFC,2),(TFD,2),
126                      (TF2,2),(TF5,2),(TF8,2),(TFB,2),(TFE,2),
127                      (TF3,2),(TF4,2),(TF9,2),(TFA,2),(TFF,2) ) );
128
129     }
   0x0000000000401afe <+65>:    nop
   0x0000000000401aff <+66>:    add    $0x40,%rsp
   0x0000000000401b03 <+70>:    pop    %rbp
   0x0000000000401b04 <+71>:    retq

End of assembler dump.
*/
void test_mutate_15_fields(void)
{
    uint32_t val = 0xffffffff;
    TEST_ASSERT_EQUAL_HEX(0xeaaaaaaa,
    Mutate_Fields(val, 
                 (TF1,2),(TF6,2),(TF7,2),(TFC,2),(TFD,2),
                 (TF2,2),(TF5,2),(TF8,2),(TFB,2),(TFE,2),
                 (TF3,2),(TF4,2),(TF9,2),(TFA,2),(TFF,2) ) );
    
}


void test_mutate_1_field(void)
{
    uint32_t val = 0xffffffff;
    TEST_ASSERT_EQUAL_HEX(0xDfffffff, Mutate_Fields(val, (TFF,1) ) );
    TEST_ASSERT_EQUAL_HEX(0x3fffffff, Mutate_Fields(val, (TF10,1) ) );
    TEST_ASSERT_EQUAL_HEX(0xffffffff, Mutate_Fields(val, (TF10,7) ) );
    TEST_ASSERT_EQUAL_HEX(0xfffffffC, Mutate_Fields(val, (TF1,0) ) );
    TEST_ASSERT_EQUAL_HEX(0xffffffff, Mutate_Fields(val, (TF1,3) ) );
}



/*
Verify it genrates the assemble we expect
Dump of assembler code for function mutate_with_vars:
218     {
   0x0000000000401e42 <+0>:     push   %rbp
   0x0000000000401e43 <+1>:     mov    %rsp,%rbp
   0x0000000000401e46 <+4>:     mov    %ecx,0x10(%rbp)
   0x0000000000401e49 <+7>:     mov    %edx,0x18(%rbp)
   0x0000000000401e4c <+10>:    mov    %r8d,0x20(%rbp)
   0x0000000000401e50 <+14>:    mov    %r9d,%eax
   0x0000000000401e53 <+17>:    mov    %al,0x28(%rbp)

219
220         return Mutate_Fields(start_val,
=> 0x0000000000401e56 <+20>:    mov    0x41b4(%rip),%eax        # 0x406010 <start_val>
   0x0000000000401e5c <+26>:    and    $0xc0000000,%eax
   0x0000000000401e61 <+31>:    mov    %eax,%edx
   0x0000000000401e63 <+33>:    mov    0x10(%rbp),%eax
   0x0000000000401e66 <+36>:    and    $0x3,%eax
   0x0000000000401e69 <+39>:    mov    %eax,%ecx
   0x0000000000401e6b <+41>:    mov    0x18(%rbp),%eax
   0x0000000000401e6e <+44>:    shl    $0xa,%eax
   0x0000000000401e71 <+47>:    and    $0xc00,%eax
   0x0000000000401e76 <+52>:    or     %eax,%ecx
   0x0000000000401e78 <+54>:    mov    0x20(%rbp),%eax
   0x0000000000401e7b <+57>:    shl    $0xc,%eax
   0x0000000000401e7e <+60>:    and    $0x3000,%eax
   0x0000000000401e83 <+65>:    or     %eax,%ecx
   0x0000000000401e85 <+67>:    movzbl 0x28(%rbp),%eax
   0x0000000000401e89 <+71>:    shl    $0x16,%eax
   0x0000000000401e8c <+74>:    and    $0xc00000,%eax
   0x0000000000401e91 <+79>:    or     %ecx,%eax
   0x0000000000401e93 <+81>:    or     %edx,%eax
   0x0000000000401e95 <+83>:    or     $0x2a2a82a8,%eax

221                      (TF1,v1),(TF6,v2),(TF7,v3),(TFC,v4),(TFD,2),
222                      (TF2,2),(TF5,2),(TF8,2),(TFB,2),(TFE,2),
223                      (TF3,2),(TF4,2),(TF9,2),(TFA,2),(TFF,2) ) ;
224
225     }
   0x0000000000401e9a <+88>:    pop    %rbp
   0x0000000000401e9b <+89>:    retq

End of assembler dump.

*/
uint32_t start_val = 0xffffffff;
uint32_t mutate_with_vars(int v1, int v2, uint32_t v3, uint8_t v4)
{

    return Mutate_Fields(start_val, 
                 (TF1,v1),(TF6,v2),(TF7,v3),(TFC,v4),(TFD,2),
                 (TF2,2),(TF5,2),(TF8,2),(TFB,2),(TFE,2),
                 (TF3,2),(TF4,2),(TF9,2),(TFA,2),(TFF,2) ) ;
    
}


void test_mutate_fields_with_variables(void)
{

    TEST_ASSERT_EQUAL_HEX(0xEA2ABAA9, mutate_with_vars(1,2,3,4) );


}

