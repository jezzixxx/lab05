#include <Account.h>
#include <gtest/gtest.h>

TEST(Account, Banking){
        Account test_account(0,0);
        ASSERT_EQ(test_account.GetBalance(), 0);
        ASSERT_THROW(test_account.ChangeBalance(1), std::runtime_error);
        test_account.Lock();
        ASSERT_NO_THROW(test_account.ChangeBalance(1));
        ASSERT_EQ(test_account.GetBalance(), 1);
        ASSERT_THROW(test_account.Lock(), std::runtime_error);
        test_account.Unlock();
        ASSERT_THROW(test_account.ChangeBalance(1), std::runtime_error);
}
