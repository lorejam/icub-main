///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2009 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-06-05
// Updated : 2009-06-05
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_common.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

inline void _mm_add_ps(__m128 in1[4], __m128 in2[4], __m128 out[4])
{
	{
		out[0] = _mm_add_ps(in1[0], in2[0]);
		out[1] = _mm_add_ps(in1[1], in2[1]);
		out[2] = _mm_add_ps(in1[2], in2[2]);
		out[3] = _mm_add_ps(in1[3], in2[3]);
	}
}

inline void _mm_sub_ps(__m128 in1[4], __m128 in2[4], __m128 out[4])
{
	{
		out[0] = _mm_sub_ps(in1[0], in2[0]);
		out[1] = _mm_sub_ps(in1[1], in2[1]);
		out[2] = _mm_sub_ps(in1[2], in2[2]);
		out[3] = _mm_sub_ps(in1[3], in2[3]);
	}
}

inline __m128 _mm_mul_ps(__m128 m[4], __m128 v)
{
	__m128 v0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 v1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	__m128 v2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	__m128 v3 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));

	__m128 m0 = _mm_mul_ps(m[0], v0);
	__m128 m1 = _mm_mul_ps(m[1], v1);
	__m128 m2 = _mm_mul_ps(m[2], v2);
	__m128 m3 = _mm_mul_ps(m[3], v3);

	__m128 a0 = _mm_add_ps(m0, m1);
	__m128 a1 = _mm_add_ps(m2, m3);
	__m128 a2 = _mm_add_ps(a0, a1);

	return a2;
}

inline __m128 _mm_mul_ps(__m128 v, __m128 m[4])
{
	__m128 i0 = m[0];
	__m128 i1 = m[1];
	__m128 i2 = m[2];
	__m128 i3 = m[3];

	__m128 m0 = _mm_mul_ps(v, i0);
	__m128 m1 = _mm_mul_ps(v, i1);
	__m128 m2 = _mm_mul_ps(v, i2);
	__m128 m3 = _mm_mul_ps(v, i3);

	__m128 u0 = _mm_unpacklo_ps(m0, m1);
	__m128 u1 = _mm_unpackhi_ps(m0, m1);
	__m128 a0 = _mm_add_ps(u0, u1);

	__m128 u2 = _mm_unpacklo_ps(m2, m3);
	__m128 u3 = _mm_unpackhi_ps(m2, m3);
	__m128 a1 = _mm_add_ps(u2, u3);

	__m128 f0 = _mm_movelh_ps(a0, a1);
	__m128 f1 = _mm_movehl_ps(a1, a0);
	__m128 f2 = _mm_add_ps(f0, f1);

	return f2;
}

inline void _mm_mul_ps(__m128 in1[4], __m128 in2[4], __m128 out[4])
{
	{
		__m128 e0 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[0] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[1] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[2] = a2;
	}

	{
		//(__m128&)_mm_shuffle_epi32(__m128i&)in2[0], _MM_SHUFFLE(3, 3, 3, 3))
		__m128 e0 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[3] = a2;
	}
}

inline void _mm_transpose_ps(__m128 const in[4], __m128 out[4])
{
    __m128 tmp0 = _mm_shuffle_ps(in[0], in[1], 0x44);
    __m128 tmp2 = _mm_shuffle_ps(in[0], in[1], 0xEE);
    __m128 tmp1 = _mm_shuffle_ps(in[2], in[3], 0x44);
    __m128 tmp3 = _mm_shuffle_ps(in[2], in[3], 0xEE);

    out[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
    out[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
    out[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
    out[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
}

inline void _mm_inverse_ps(__m128 const in[4], __m128 out[4])
{
	__m128 Fac0;
	{
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		//	valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac0 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac1;
	{
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		//	valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac1 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}


	__m128 Fac2;
	{
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		//	valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac2 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac3;
	{
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		//	valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac3 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac4;
	{
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		//	valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac4 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac5;
	{
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		//	valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		__m128 Swp0a = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp0b = _mm_shuffle_ps(in[3], in[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(in[2], in[1], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac5 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
	__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);

	// m[1][0]
	// m[0][0]
	// m[0][0]
	// m[0][0]
	__m128 Temp0 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][1]
	// m[0][1]
	// m[0][1]
	// m[0][1]
	__m128 Temp1 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(1, 1, 1, 1));
	__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][2]
	// m[0][2]
	// m[0][2]
	// m[0][2]
	__m128 Temp2 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(2, 2, 2, 2));
	__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][3]
	// m[0][3]
	// m[0][3]
	// m[0][3]
	__m128 Temp3 = _mm_shuffle_ps(in[1], in[0], _MM_SHUFFLE(3, 3, 3, 3));
	__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));

	// col0
	// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
	// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
	// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
	// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
	__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
	__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
	__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
	__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
	__m128 Add00 = _mm_add_ps(Sub00, Mul02);
	__m128 Inv0 = _mm_mul_ps(SignB, Add00);

	// col1
	// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
	// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
	// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
	// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
	__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
	__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
	__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
	__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
	__m128 Add01 = _mm_add_ps(Sub01, Mul05);
	__m128 Inv1 = _mm_mul_ps(SignA, Add01);

	// col2
	// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
	// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
	// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
	// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
	__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
	__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
	__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
	__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
	__m128 Add02 = _mm_add_ps(Sub02, Mul08);
	__m128 Inv2 = _mm_mul_ps(SignB, Add02);

	// col3
	// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
	// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
	// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
	// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
	__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
	__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
	__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
	__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
	__m128 Add03 = _mm_add_ps(Sub03, Mul11);
	__m128 Inv3 = _mm_mul_ps(SignA, Add03);

	__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));

	//	valType Determinant = m[0][0] * Inverse[0][0] 
	//						+ m[0][1] * Inverse[1][0] 
	//						+ m[0][2] * Inverse[2][0] 
	//						+ m[0][3] * Inverse[3][0];
	__m128 Det0 = _mm_dot_ps(in[0], Row2);

	//	Inverse /= Determinant;
	out[0] = _mm_div_ps(Inv0, Det0);
	out[1] = _mm_div_ps(Inv1, Det0);
	out[2] = _mm_div_ps(Inv2, Det0);
	out[3] = _mm_div_ps(Inv3, Det0);
}
