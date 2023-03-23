#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Transaction, Banking){
        Account test_account0(0,1000), test_account1(1,500);
        Transaction test_transaction;
        ASSERT_EQ(test_transaction.fee(), 1);
        test_transaction.set_fee(100);
        ASSERT_EQ(test_transaction.fee(), 100);
        ASSERT_THROW(test_transaction.Make(test_account0, test_account0, 500), std::logic_error);
        ASSERT_THROW(test_transaction.Make(test_account0, test_account1, -500), std::invalid_argument);
        ASSERT_THROW(test_transaction.Make(test_account0, test_account1, 50), std::logic_error);
        if (test_transaction.fee()*2-1 >= 100)
                ASSERT_EQ(test_transaction.Make(test_account0, test_account1, test_transaction.fee()*2-1), false);
        test_account0.Lock();
        ASSERT_THROW(test_transaction.Make(test_account0, test_account1, 1000), std::runtime_error);
        test_account0.Unlock();
        ASSERT_EQ(test_transaction.Make(test_account0, test_account1, 500), true);
        ASSERT_EQ(test_account1.GetBalance(), 1000);
        ASSERT_EQ(test_account0.GetBalance(), 400);
        ASSERT_EQ(test_transaction.Make(test_account0, test_account1, 400), false);
        ASSERT_EQ(test_account1.GetBalance(), 1000);
        ASSERT_EQ(test_account0.GetBalance(), 400);
}

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
