#include "Postfix.h"

#include <gtest.h>

TEST(Postfix, can_create_postfix)
{
	ASSERT_NO_THROW(Postfix p);
}

TEST(Postfix, simple_get_infix)
{
	Postfix x("1+1");

	string ans = "1+1";
	ASSERT_EQ(ans, x.GetInfix());
}

TEST(Postfix, simple_get_postfix)
{
	Postfix x("1+1");

	string ans = "11+";
	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix)
{
	Postfix x("1+(1+1)");

	string ans = "111++";
	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix_with_MUL)
{
	Postfix x("1*(1+1)");

	string ans = "111+*";
	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix_with_MUL2)
{
	Postfix x("2+1*1");

	string ans = "211*+";
	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix_with_MUL3)
{
	Postfix x("2+1*1/2");

	string ans = "211*2/+";
	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix_with_MUL4)
{
	Postfix x("(2+1)*1/2");

	string ans = "21+1*2/";

	x.ToPostfix();
	ASSERT_EQ(ans, x.GetPostfix());
}

TEST(Postfix, get_postfix_with_all)
{
	Postfix x("1/(7-(1+1))*3-(2+(1+1))*1/(7-(2+1))*3-(2+(1+1))*(1/(7-(1+1))*3-(2+(1+1))+1/(7-(1+1))*3-(2+(1+1)))");

	x.ToPostfix();
	//cout « x.GetPostfix() « endl;
	double ans = x.Calculate();

	int a = (ans == 24.8);

	ASSERT_EQ(1, a);
}

TEST(Postfix, get_postfix_with_incorrect_parenthesis_sequence)
{
	ASSERT_ANY_THROW(Postfix x("1/(7-(1+1))*3-(2+(1+1))*1/(7-(2+1))*3-(2+(1+1))*(1/(7-(1+1))*3-(2+(1+1))+1/(7-(1+1))*3-(2+(1+1))))"));
}

TEST(Postfix, get_postfix_with_incorrect_parenthesis_sequence2)
{

	ASSERT_ANY_THROW(Postfix x("1/(7-(1+1))*3-(2+(1+1))*1/(7-(2+1))*3-(2+(1+1))*(1/(7-(1+1))*3-(2+(1+1))+1/(7-(1+1))*3-(2+(1+1))"));
}

TEST(Postfix, get_postfix_with_incorrect_placement_of_signs)
{

	ASSERT_ANY_THROW(Postfix x("1/(7-(1+1))*3-(2+(1+1))*1/(7-(2+1))*3-(2+(1+1))*(1/(7-(1+1))*3--(2+(1+1))+1/(7-(1+1))*3-(2+(1+1)))"));
}