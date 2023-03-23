#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Transaction, Banking){
	const int num0 = 5000, num1 = 5000, num_fee = 100;
	Account user0(0,num0), user1(1,num1);
	Transaction test_transaction;
	ASSERT_EQ(test_transaction.fee(), 1);
	test_transaction.set_fee(num_fee);
	ASSERT_EQ(test_tran.fee(), base_fee);
	ASSERT_THROW(test_transaction.Make(user0, user0, 1000), std::logic_error);
	ASSERT_THROW(test_transaction.Make(user0, user1, -50), std::invalid_argument);
	ASSERT_THROW(test_transaction.Make(user0, user1, 50), std::logic_error);
	if (test_transaction.fee()*2-1 >= 100)
		ASSERT_EQ(test_transaction.Make(user0, user1, test_transaction.fee()*2-1), false);
	user0.Lock();
	ASSERT_THROW(test_transaction.Make(user0, user1, 1000), std::runtime_error);
	user0.Unlock();
	ASSERT_EQ(test_transaction.Make(user0, user1, 1000), true);
	ASSERT_EQ(user1.GetBalance(), num1+1000);	
	ASSERT_EQ(user0.GetBalance(), num0-1000-num_fee);
	ASSERT_EQ(test_transaction.Make(user0, user1, 3900), false);
	ASSERT_EQ(user1.GetBalance(), num1+1000);	
	ASSERT_EQ(user0.GetBalance(), num0-1000-num_fee);
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
