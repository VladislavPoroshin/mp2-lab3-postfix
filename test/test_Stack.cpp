#include "Stack.h"

#include <gtest.h>

TEST(Stack, cant_pop_when_stack_is_empty)
{
	Stack<int> A;
	int a;
	ASSERT_ANY_THROW(a = A.Pop());
}

TEST(Stack, cant_top_when_stack_is_empty)
{
	Stack<int> A;
	int a;
	ASSERT_ANY_THROW(a = A.Top());
}

TEST(Stack, can_push_when_stack_is_empty)
{
	Stack<int> A;
	int a = 0;
	ASSERT_NO_THROW(A.Push(a));
}

TEST(Stack, can_push_when_stack_isnt_empty)
{
	Stack<int> A;
	int a = 0;
	int b = 1;
	A.Push(a);
	ASSERT_NO_THROW(A.Push(b));
}

TEST(Stack, correct_work_IsEmpty)
{
	Stack<int> A;
	int a = 0;
	EXPECT_EQ(true, A.IsEmpty());
	A.Push(a);
	EXPECT_EQ(false, A.IsEmpty());
}

TEST(Stack, correct_work_IsFull)
{
	Stack<int> A;
	int a = 0;
	EXPECT_EQ(false, A.IsFull());
	A.Push(a);
	EXPECT_EQ(true, A.IsFull());
}

TEST(Stack, correct_work_Push_and_Top)
{
	Stack<int> A;
	int a = 0;
	A.Push(a);
	int b = A.Top();
	EXPECT_EQ(a, b);
	EXPECT_EQ(false, A.IsEmpty());
}

TEST(Stack, correct_work_Push_and_Pop)
{
	Stack<int> A;
	int a = 0;
	A.Push(a);
	int c = A.Pop();
	EXPECT_EQ(a, c);
	EXPECT_EQ(true, A.IsEmpty());
}

TEST(Stack, correct_work_Size)
{
	Stack<int> A(48);
	int a = A.Size();
	EXPECT_EQ(0, a);
	A.Push(a);
	a = A.Size();
	EXPECT_EQ(1, a);
	EXPECT_EQ(false, A.IsFull());
}

TEST(Stack, can_copy_stack)
{
	Stack<int> A(48);
	ASSERT_NO_THROW(Stack<int> B(A));
}

TEST(Stack, correct_work_operatorEQ_and_operatorASSIGN)
{
	Stack<int> A(48);
	Stack<int> B = A;
	EXPECT_EQ(A, B);
	B.Push(0);
	EXPECT_NE(A, B);
	Stack<int> C(40);
	EXPECT_NE(A, C);
}

TEST(Stack, cant_announce_stack_with_zero_or_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> A(0));
	ASSERT_ANY_THROW(Stack<int> A(-1));
}

