#include "isp_type.h"
Word32u Cmult_uu(const Word16u x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, mult_uu_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = (Word32u)x * (Word32u)y;

	return(tmp);
}

Word32u Cmult_su(const Word16 x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, mult_su_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = (Word32)x * (Word32)y;

	return(tmp);
}

Word32u Cadd_uu(const Word16u x, const Word16u bx, const Word16u y, const Word16u by, const Word16u bz, add_uu_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = (Word32u)x + (Word32u)y;

	return(tmp);
}

Word32u Cadd_ss(const Word32 x, const Word16u bx, const Word32 y, const Word16u by, const Word16u bz, add_ss_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = x + y;

	return(tmp);
}

Word32u Cadd64_ss(const Word64 x, const Word16u bx, const Word64 y, const Word16u by, const Word16u bz, add_ss_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word64 tmp;
	tmp = x + y;

	return(tmp);
}

Word32u Cadd64_uu(const Word64u x, const Word16u bx, const Word64u y, const Word16u by, const Word16u bz, add_uu_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word64 tmp;
	tmp = x + y;

	return(tmp);
}

Word32u Cshift_u(const Word16u x, const Word16u bx, const Word16u shift, const Word16u bz, shift_u_cp* cp)
{
	(void)x;
	(void)bx;
	(void)shift;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = (0 <= shift) ? x << shift : x >> (-shift);

	return(tmp);
}
Word32u Cshift_s(const Word32 x, const Word16u bx, const Word16u shift, const Word16u bz, shift_s_cp* cp)
{
	(void)x;
	(void)bx;
	(void)shift;
	(void)bz;
	(void)cp;
	Word32u tmp;
	tmp = (0 <= shift) ? x << shift : x >> (-shift);

	return(tmp);
}

Word32u Cabs_s(const Word32 x, const Word16u bx, const Word16u bz, abs_s_cp* cp)
{
	(void)x;
	(void)bx;
	(void)bz;
	(void)cp;
	Word64 tmp;
	tmp = (0 > x) ? -x : x;

	return(tmp);
}

Word32u Cshift64_s(const Word64 x, const Word16u bx, const Word16u shift, const Word16u bz, shift64_s_cp* cp)
{
	(void)x;
	(void)bx;
	(void)shift;
	(void)bz;
	(void)cp;
	Word64 tmp;
	tmp = (0 <= shift) ? x << shift : x >> (-shift);

	return(tmp);
}
Word32u Cclamp_s(const Word32 x, const Word16u bx, const Word32 minn, const Word32 maxx, const Word16u bz, clamp_s_cp* cp)
{
	(void)x;
	(void)bx;
	(void)minn;
	(void)maxx;
	(void)bz;
	(void)cp;
	Word32 tmp;
	tmp = (maxx < x) ? maxx : ((minn > x) ? minn : x);

	return(tmp);
}

Word32u Cclamp64_s(const Word64 x, const Word16u bx, const Word64 minn, const Word64 maxx, const Word16u bz, clamp_s_cp* cp)
{
	(void)x;
	(void)bx;
	(void)minn;
	(void)maxx;
	(void)bz;
	(void)cp;
	Word32 tmp;
	tmp = (maxx < x) ? maxx : ((minn > x) ? minn : x);

	return(tmp);
}

Word32u Cclamp64_u(const Word64u x, const Word16u bx, const Word64u minn, const Word64u maxx, const Word16u bz, clamp_u_cp* cp)
{
	(void)x;
	(void)bx;
	(void)minn;
	(void)maxx;
	(void)bz;
	(void)cp;
	Word32 tmp;
	tmp = (maxx < x) ? maxx : ((minn > x) ? minn : x);

	return(tmp);
}

Word64 Cmult64_ss(const Word32 x, const Word16u bx, const Word32 y, const Word16u by, const Word16u bz, mult64_ss_cp* cp)
{
	(void)x;
	(void)bx;
	(void)y;
	(void)by;
	(void)bz;
	(void)cp;
	Word64 tmp;
	tmp = (Word64)x * (Word64)y;;

	return(tmp);
}