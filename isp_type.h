#pragma once
#pragma once
typedef unsigned short int Word16u;
typedef short int Word16;
typedef unsigned long int Word32u;
typedef long int Word32;
typedef long long int Word64;
typedef long long unsigned int Word64u;
typedef unsigned short Word16_u;
typedef unsigned long Word32_u;
typedef char					Word8;
typedef unsigned char Word8u;

typedef Word32u counter_t;




typedef struct
{
	counter_t add_in_1_msb;
	counter_t add_in_2_msb;
	counter_t add_out_msb;
	counter_t counter;
} add_uu_cp;

typedef struct
{
	counter_t add_in_1_pos_msb;
	counter_t add_in_1_neg_msb;
	counter_t add_in_2_msb;
	counter_t add_out_pos_msb;
	counter_t add_out_neg_msb;
	counter_t counter;
} add_su_cp;

typedef struct
{
	counter_t add_in_1_pos_msb;
	counter_t add_in_1_neg_msb;
	counter_t add_in_2__pos_msb;
	counter_t add_in_2_neg_msb;
	counter_t add_out_pos_msb;
	counter_t add_out_neg_msb;
	counter_t counter;
} add_ss_cp;

typedef struct
{
	counter_t sub_in_1_msb;
	counter_t sub_in_2_msb;
	counter_t sub_out_pos_msb;
	counter_t sub_out_neg_msb;
	counter_t counter;
} sub_uu_cp;

typedef struct
{
	counter_t sub_in_1_pos_msb;
	counter_t sub_in_1_neg_msb;
	counter_t sub_in_2_msb;
	counter_t sub_out_pos_msb;
	counter_t sub_out_neg_msb;
	counter_t counter;
} sub_su_cp;

typedef struct
{
	counter_t sub_in_1_msb;
	counter_t sub_in_2_pos_msb;
	counter_t sub_in_2_neg_msb;
	counter_t sub_out_pos_msb;
	counter_t sub_out_neg_msb;
	counter_t counter;
} sub_us_cp;

typedef struct
{
	counter_t sub_in_1_pos_msb;
	counter_t sub_in_1_neg_msb;
	counter_t sub_in_2__pos_msb;
	counter_t sub_in_2_neg_msb;
	counter_t sub_out_pos_msb;
	counter_t sub_out_neg_msb;
	counter_t counter;
} sub_ss_cp;

typedef struct
{
	counter_t mul_in_1_msb;
	counter_t mul_in_2_msb;
	counter_t mul_out_msb;
	counter_t counter;
} mult_uu_cp;

typedef struct
{
	counter_t  mul_in_1_pos_msb;
	counter_t  mul_in_1_neg_msb;
	counter_t  mul_in_2_msb;
	counter_t  mul_out_pos_msb;
	counter_t  mul_out_neg_msb;
	counter_t counter;
} mult_su_cp;

typedef struct
{
	counter_t mul_in_1_pos_msb;
	counter_t mul_in_1_neg_msb;
	counter_t mul_in_2_pos_msb;
	counter_t mul_in_2_neg_msb;
	counter_t mul_out_pos_msb;
	counter_t mul_out_neg_msb;
	counter_t counter;
} mult_ss_cp;

typedef struct
{
	counter_t mul_in_1_msb;
	counter_t mul_in_2_msb;
	counter_t mul_out_msb;
	counter_t counter;
} mult64_uu_cp;

typedef struct
{
	counter_t  mul_in_1_pos_msb;
	counter_t  mul_in_1_neg_msb;
	counter_t  mul_in_2_msb;
	counter_t  mul_out_pos_msb;
	counter_t  mul_out_neg_msb;
	counter_t counter;
} mult64_su_cp;

typedef struct
{
	counter_t mul_in_1_pos_msb;
	counter_t mul_in_1_neg_msb;
	counter_t mul_in_2_pos_msb;
	counter_t mul_in_2_neg_msb;
	counter_t mul_out_pos_msb;
	counter_t mul_out_neg_msb;
	counter_t counter;
} mult64_ss_cp;

typedef struct
{
	counter_t abs_in_1_msb;
	counter_t abs_in_2_msb;
	counter_t abs_out_msb;
	counter_t counter;
} abs_s_cp;

typedef struct
{
	counter_t  shift_in_1_msb;
	counter_t  shift_out_msb;
	counter_t counter;
} shift_u_cp;

typedef struct
{
	counter_t shift_in_1_pos_msb;
	counter_t shift_in_1_neg_msb;
	counter_t shift_out_pos_msb;
	counter_t shift_out_neg_msb;
	counter_t counter;
} shift_s_cp;

typedef struct
{
	counter_t  shift_in_1_msb;
	counter_t  shift_out_msb;
	counter_t counter;
} shift64_u_cp;

typedef struct
{
	counter_t shift_in_1_pos_msb;
	counter_t shift_in_1_neg_msb;
	counter_t shift_out_pos_msb;
	counter_t shift_out_neg_msb;
	counter_t counter;
} shift64_s_cp;

typedef struct
{
	counter_t  sat_out_max;
	counter_t  sat_out_min;
	counter_t counter;
} clamp_u_cp;

typedef struct
{
	counter_t  sat_out_max;
	counter_t  sat_out_min;
	counter_t counter;
} clamp_s_cp;

typedef struct
{
	add_uu_cp* add_uu;
	Word32 num_add_uu;

	add_su_cp* add_su;
	Word32 num_add_su;

	add_ss_cp* add_ss;
	Word32 num_add_ss;

	sub_uu_cp* sub_uu;
	Word32 num_sub_uu;

	sub_su_cp* sub_su;
	Word32 num_sub_su;

	sub_ss_cp* sub_ss;
	Word32 num_sub_ss;

	mult_uu_cp* mult_uu;
	Word32 num_mult_uu;

	mult_su_cp* mult_su;
	Word32 num_mult_su;

	mult_ss_cp* mult_ss;
	Word32 num_mult_ss;

	mult64_uu_cp* mult64_uu;
	Word32 num_mult64_uu;

	mult64_su_cp* mult64_su;
	Word32 num_mult64_su;

	mult64_ss_cp* mult64_ss;
	Word32 num_mult64_ss;

	abs_s_cp* abs_s;
	Word32 num_abs_s;

	shift_u_cp* shift_u;
	Word32 num_shift_u;

	shift_s_cp* shift_s;
	Word32 num_shift_s;

	shift64_u_cp* shift64_u;
	Word32 num_shift64_u;

	shift64_s_cp* shift64_s;
	Word32 num_shift64_s;

	clamp_u_cp* clamp_u;
	Word32 num_clamp_u;

	clamp_s_cp* clamp_s;
	Word32 num_clamp_s;
} module_cp;

Word32u Cshift_u(const Word16u x, const Word16u bx, const Word16u shift, const Word16u bz, shift_u_cp* cp);
Word32u Cshift_s(const Word32 x, const Word16u bx, const Word16u shift, const Word16u bz, shift_s_cp* cp);
Word32u Cabs_s(const Word32 x, const Word16u bx, const Word16u bz, abs_s_cp* cp);
Word32u Cadd_uu(const Word16u x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, add_uu_cp* cp);
Word32u Cmult_uu(const Word16u x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, mult_uu_cp* cp);
Word32u Cmult_su(const Word16 x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, mult_su_cp* cp);
Word32u Cadd_ss(const Word32 x, const Word16u bx, const Word32 y, const Word16u by, const Word16u bz, add_ss_cp* cp);
Word32u Cclamp_s(const Word32 x, const Word16u bx, const Word32 minn, const Word32 maxx, const Word16u bz, clamp_s_cp* cp);
Word32u Cclamp64_s(const Word64 x, const Word16u bx, const Word64 minn, const Word64 maxx, const Word16u bz, clamp_s_cp* cp);
Word32u Cclamp64_u(const Word64u x, const Word16u bx, const Word64u minn, const Word64u maxx, const Word16u bz, clamp_u_cp* cp);
Word32u Cadd64_ss(const Word64 x, const Word16u bx, const Word64 y, const Word16u by, const Word16u bz, add_ss_cp* cp);
Word32u Cadd64_uu(const Word64u x, const Word16u bx, const Word64u y, const Word16u by, const Word16u bz, add_uu_cp* cp);
Word32u Cshift64_s(const Word64 x, const Word16u bx, const Word16u shift, const Word16u bz, shift64_s_cp* cp);
Word64 Cmult64_ss(const Word32 x, const Word16u bx, const Word32 y, const Word16u by, const Word16u bz, mult64_ss_cp* cp);

