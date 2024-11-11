#include "gtest.h"
#include "stack_queue.h"
#include <cassert>

static const int n = 100;

TEST(QueueSt, can_create_queuest)
{
    ASSERT_NO_THROW(QueueSt<int> q);
}

TEST(QueueSt, cant_create_queuest_with_negative_length)
{
    ASSERT_ANY_THROW(QueueSt<int> q(-1));
}

TEST(QueueSt, can_empty)
{
    QueueSt<int> q;
    EXPECT_EQ(1, q.IsEmpty());
}

TEST(QueueSt, can_size)
{
    QueueSt<int> q(7);
    for (int i = 0; i < 4; i++)
        q.push_back(i * i);
    EXPECT_EQ(4, q.size());
}

TEST(QueueSt, can_inc)
{
    QueueSt<int> q;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        q.IncQueue(i * i);
        v.push_back(i * i);
    }
    vector<int> check;
    size_t size = q.size();
    for (size_t i = 0; i < size; i++) {
        check.push_back(q.GetF());
        q.DeQueue();
    }
    EXPECT_EQ(check, v);
}

TEST(QueueSt, throw_pop)
{
    QueueSt<int> q;
    ASSERT_ANY_THROW(q.DeQueue());
}

TEST(QueueSt, can_de)
{
    QueueSt<int> st;
    for (int i = 0; i < n; i++)
        st.IncQueue(i * i);
    st.DeQueue();
    st.DeQueue();
    EXPECT_EQ(4, st.GetF());
}
