/*
An example based on the bankaccount example in the Moose cookbook (which
itself was taken from an example in the book "Practical Common Lisp")
http://search.cpan.org/~drolsky/Moose-0.98/lib/Moose/Cookbook/Basics/Recipe2.pod

This is interesting because the checking account is derived from a bank
account and has a member variable of the bankaccount type.
*/

#include <glib-object.h>
#include "tap.h"
#include "bankaccount.h"
#include "checkingaccount.h"

int main () {
    g_type_init();

    plan(21);

    /* savings account  */
    BankAccount *savings_account = bank_account_new("balance", 250.0);
    ok (IS_BANK_ACCOUNT(savings_account), "isa BankAccount");

    bank_account_withdraw(savings_account, 50.0);
    ok (1, "withdrew from savings successfully");

    gdouble balance;
    g_object_get(savings_account, "balance", &balance, NULL);
    ok (balance == 200.0, "got the right savings balance after withdrawl");

    bank_account_deposit(savings_account, 150.0);
    g_object_get(savings_account, "balance", &balance, NULL);
    ok (balance == 350.0, "got the right savings balance after deposit");

    /* checking account with overdraft account  */
    CheckingAccount *checking_account
        = checking_account_new("balance", 100.0,
                               "overdraft-account", savings_account);
    ok (IS_CHECKING_ACCOUNT(checking_account), "isa CheckingAccount");
    ok (IS_BANK_ACCOUNT(checking_account), "isa BankAccount");

    BankAccount *overdraft_account;
    g_object_get(checking_account, "overdraft-account", &overdraft_account, NULL);
    ok (overdraft_account == savings_account, "got the right overdraft account");
    g_object_unref(overdraft_account);

    g_object_get(checking_account, "balance", &balance, NULL);
    ok (balance == 100.0, "got the right checking balance");

    bank_account_withdraw(BANK_ACCOUNT(checking_account), 50.0);
    ok (1, "withdrew from checking successfully");

    g_object_get(checking_account, "balance", &balance, NULL);
    ok (balance == 50.0, "got the right checking balance after withdrawl");

    g_object_get(savings_account, "balance", &balance, NULL);
    ok (balance == 350.0, "got the right savings balance after checking withdrawl (no overdraft)");

    bank_account_withdraw(BANK_ACCOUNT(checking_account), 200.0);
    ok (1, "withdraw from checking successfully");

    g_object_get(checking_account, "balance", &balance, NULL);
    ok (balance == 0.0, "got the right checkings balance after withdrawl");

    g_object_get(savings_account, "balance", &balance, NULL);
    ok (balance == 200.0, "got the right savings balance after overdraft withdrawl");

    g_object_unref(checking_account);
    g_object_unref(savings_account);

    /* checking account without overdraft account  */
    checking_account = checking_account_new("balance", 100.0);
    ok (IS_CHECKING_ACCOUNT(checking_account), "isa CheckingAccount");
    ok (IS_BANK_ACCOUNT(checking_account), "isa BankAccount");

    g_object_get(checking_account, "overdraft-account", &overdraft_account, NULL);
    ok (!overdraft_account, "no overdraft account");

    g_object_get(checking_account, "balance", &balance, NULL);
    ok (balance == 100.0, "got the right checking balance");

    bank_account_withdraw(BANK_ACCOUNT(checking_account), 50.0);
    ok (1, "withdrew from checking successfully");

    g_object_get(checking_account, "balance", &balance, NULL);
    ok (balance == 50.0, "got the right checking balance after withdrawl");

    dies_ok ({bank_account_withdraw(BANK_ACCOUNT(checking_account), 200.0);},
             "withdrawal failed due to attempted overdraft");

    return exit_status();
}

