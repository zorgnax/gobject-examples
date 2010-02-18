#include <glib-object.h>
#include "bankaccount.h"
#include "checkingaccount.h"

enum {
    PROP_0,
    PROP_OVERDRAFT_ACCOUNT
};

G_DEFINE_TYPE(CheckingAccount, checking_account, TYPE_BANK_ACCOUNT);

static void checking_account_print (BankAccount *self) {
    BANK_ACCOUNT_CLASS(checking_account_parent_class)->print(self);
    CheckingAccount *checking_account = CHECKING_ACCOUNT(self);
    if (checking_account->overdraft_account) {
        g_print("overdraft balance is $%.02f\n", checking_account->overdraft_account->balance);
    }
    else {
        g_print("no overdraft account\n");
    }
}

static void checking_account_withdraw (BankAccount *self, gdouble amount) {
    CheckingAccount *checking_account = CHECKING_ACCOUNT(self);
    gdouble overdraft_amount = amount - self->balance;
    if (checking_account->overdraft_account && overdraft_amount > 0.0) {
        bank_account_withdraw(checking_account->overdraft_account, overdraft_amount);
        bank_account_deposit(self, overdraft_amount);
    }
    BANK_ACCOUNT_CLASS(checking_account_parent_class)->withdraw(self, amount);
}

static void checking_account_get_property (GObject    *obj,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec) {
    CheckingAccount *self = CHECKING_ACCOUNT(obj);
    
    switch (prop_id) {
    case PROP_OVERDRAFT_ACCOUNT:
        g_value_set_object(value, self->overdraft_account);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void checking_account_set_property (GObject      *obj,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec) {
    CheckingAccount *self = CHECKING_ACCOUNT(obj);
    
    switch (prop_id) {
    case PROP_OVERDRAFT_ACCOUNT:
        self->overdraft_account = g_value_get_object(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void checking_account_class_init (CheckingAccountClass *cls) {
    GObjectClass *gobject_cls = G_OBJECT_CLASS(cls);
    BankAccountClass *bank_account_cls = BANK_ACCOUNT_CLASS(cls);

    gobject_cls->get_property = checking_account_get_property;
    gobject_cls->set_property = checking_account_set_property;
    bank_account_cls->print = checking_account_print;
    bank_account_cls->withdraw = checking_account_withdraw;
    
    g_object_class_install_property(
        gobject_cls,
        PROP_OVERDRAFT_ACCOUNT,
        g_param_spec_object(
            "overdraft-account", "Overdraft account",
            "The overdraft account allows the user to temporarily withdraw "
            "more than they have in their checking account",
            TYPE_BANK_ACCOUNT,
            G_PARAM_READWRITE));
}

static void checking_account_init (CheckingAccount *self) {
    /* nop  */
}

