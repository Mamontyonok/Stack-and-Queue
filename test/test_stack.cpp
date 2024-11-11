#include "gtest.h"
#include "stack_queue.h"
#include <cassert>

static const int n = 100;

TEST(Stack, can_create_stack)
{
    ASSERT_NO_THROW(Stack<int> st);
}

TEST(Stack, cant_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(Stack<int> st(-1));
}

TEST(Stack, can_push)
{
    Stack<int> st;
    vector <int> v;
    for (int i = 0; i < n; i++) {
        st.push(i - 3);
        v.push_back(i - 3);
    }
    bool f = true;
    for (int i = 0; i < n; i++) {
        if (st[i] != v[i]) {
            f = false;
            break;
        }
    }
    EXPECT_EQ(1, f);
}

TEST(Stack, can_pop)
{
    Stack<int> st;
    for (int i = 0; i < n; i++)
        st.push(i - 3);
    st.pop();
    EXPECT_EQ(n - 5, st[n - 2]);
}

TEST(Stack, can_get_size)
{
    Stack<int> st(5);
    st.push(3);
    st.push(-7);
    EXPECT_EQ(2, st.size());
}

TEST(Stack, can_top)
{
    Stack<int> st;
    for (int i = 0; i < n; i++)
        st.push(i - 3);
    EXPECT_EQ(n - 4, st.top());
}

