#include "gtest.h"
#include "..\mp2-lab5-polinom\TPolinom.h"
#include <sstream>

static bool operator==(const TPolinom& thePolinom, const std::string& theExpected)
{
	std::stringstream aStrStream;
	aStrStream << thePolinom;
	std::string aResult;
	getline(aStrStream, aResult);
	return aResult == theExpected;
}

TEST(TPolinom, can_print_polinom)
{
	TPolinom aPolinom;
	aPolinom.AddMonom(TMonom(4, 5, 1, 9));
	aPolinom.AddMonom(TMonom(3, 3, 0, 2));
	aPolinom.AddMonom(TMonom(1, 2, 3, 4));

	std::string anExpected = "4*x^5*y^1*z^9+3*x^3*z^2+1*x^2*y^3*z^4";

	std::stringstream aStrStream;
	aStrStream << aPolinom;
	std::string anActual;
	aStrStream >> anActual;

	ASSERT_EQ(anExpected, anActual);
}

TEST(TPolinom, can_read_polinom)
{
	TPolinom aPolinom;
	std::string input = "2 1 2 3 4 5 6 7 8";
	std::string anExpected = "5*x^6*y^7*z^8+1*x^2*y^3*z^4";
	{
		std::stringstream aStrStream(input);
		aStrStream >> aPolinom;
	}
	std::string anActual;
	{
		std::stringstream aStrStream;
		aStrStream << aPolinom;
		aStrStream >> anActual;
	}
	ASSERT_EQ(anActual, anExpected);
}


TEST(TPolinom, can_create_polinom)
{
	ASSERT_EQ(TPolinom(), "0");
}

TEST(TPolinom, can_add_monom) 
{
	TPolinom aPolinom;;
	TMonom aMonom(1, 2, 3, 4);
	aPolinom.AddMonom(aMonom);
	ASSERT_EQ(aPolinom, "1*x^2*y^3*z^4");
}

TEST(TPolinom, can_copy_empty_polinom)
{
	TPolinom aPolinom;
	ASSERT_EQ(TPolinom(aPolinom), "0");
}

TEST(TPolinom, can_copy_polinom_with_one_monom)
{
	TPolinom aPolinom;
	TMonom aMonom(1, 2, 3, 4);
	aPolinom.AddMonom(aMonom);
	ASSERT_EQ(TPolinom(aPolinom), "1*x^2*y^3*z^4");
}

TEST(TPolinom, can_copy_polinom_with_several_monoms)
{
	TPolinom aPolinom;
	aPolinom.AddMonom(TMonom(1, 2, 3, 4));
	aPolinom.AddMonom(TMonom(4, 5, 0, 9));
	aPolinom.AddMonom(TMonom(-7, 3, 2, 7));
	ASSERT_EQ(TPolinom(aPolinom), "4*x^5*z^9-7*x^3*y^2*z^7+1*x^2*y^3*z^4");
}

TEST(TPolinom, can_sum_polinoms_with_one_monom_1)
{
	TPolinom aPolinom1, aPolinom2;
	aPolinom1.AddMonom(TMonom(1, 2, 3, 4));
	aPolinom2.AddMonom(TMonom(5, 6, 7, 8));
	TPolinom aPolinom3 = aPolinom1 + aPolinom2;
	ASSERT_EQ(aPolinom3, "5*x^6*y^7*z^8+1*x^2*y^3*z^4");
}

TEST(TPolinom, can_sum_polinoms_with_one_monom_2)
{
	TPolinom aPolinom1, aPolinom2;
	aPolinom1.AddMonom(TMonom(1, 2, 3, 4));
	aPolinom2.AddMonom(TMonom(-1, 2, 3, 4));
	TPolinom aPolinom3 = aPolinom1 + aPolinom2;
	ASSERT_EQ(aPolinom3, "0");
}

TEST(TPolinom, can_sum_polinoms_with_several_monoms)
{
	TPolinom aPolinom1, aPolinom2;
	aPolinom1.AddMonom(TMonom(4, 5, 1, 9));
	aPolinom1.AddMonom(TMonom(3, 3, 0, 2));
	aPolinom1.AddMonom(TMonom(1, 2, 3, 4));

	aPolinom2.AddMonom(TMonom(-7, 3, 2, 7));
	aPolinom2.AddMonom(TMonom(-8, 3, 0, 7));
	aPolinom2.AddMonom(TMonom(-1, 2, 3, 4));

	TPolinom aPolinom3 = aPolinom1 + aPolinom2;

	ASSERT_EQ(aPolinom3, "4*x^5*y^1*z^9-7*x^3*y^2*z^7-8*x^3*z^7+3*x^3*z^2");
}

TEST(TPolinom, can_sum_polinoms_with_several_monoms_2)
{
	TPolinom aPolinom1, aPolinom2;
	aPolinom1.AddMonom(TMonom(4, 5, 1, 9));
	aPolinom1.AddMonom(TMonom(3, 3, 0, 2));
	aPolinom1.AddMonom(TMonom(1, 2, 3, 4));

	aPolinom2.AddMonom(TMonom(-4, 5, 1, 9));
	aPolinom2.AddMonom(TMonom(-8, 3, 0, 7));
	aPolinom2.AddMonom(TMonom(1, 2, 3, 4));

	TPolinom aPolinom3 = aPolinom1 + aPolinom2;

	ASSERT_EQ(aPolinom3, "-8*x^3*z^7+3*x^3*z^2+2*x^2*y^3*z^4");
}

TEST(TPolinom, can_mul_by_num)
{
	TPolinom aPolinom;
	aPolinom.AddMonom(TMonom(1, 2, 3, 4));
	aPolinom.AddMonom(TMonom(-5, 6, 7, 8));
	aPolinom *= 5;
	ASSERT_EQ(aPolinom, "-25*x^6*y^7*z^8+5*x^2*y^3*z^4");
}

TEST(TPolinom, can_mul_by_monom)
{
	TPolinom aPolinom;
	aPolinom.AddMonom(TMonom(3, 1, 0, 0));
	aPolinom.AddMonom(TMonom(1, 2, 3, 4));
	aPolinom.AddMonom(TMonom(-5, 6, 7, 8));
	aPolinom *= TMonom(4, 1, 2, 3);
	ASSERT_EQ(aPolinom, "-20*x^7*y^9*z^11+4*x^3*y^5*z^7+12*x^2*y^2*z^3");
}
