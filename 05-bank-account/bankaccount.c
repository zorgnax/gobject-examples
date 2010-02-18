#include <glib-object.h>
#include "bankaccount.h"

enum {
    PROP_0,
    PROP_BALANCE
};

G_DEFINE_TYPE(BankAccount, bank_account, G_TYPE_OBJECT);

void bank_account_print (BankAccount *self) {
    BANK_ACCOUNT_GET_CLASS(self)->print(self);
}

static void bank_account_print_real (BankAccount *self) {
    g_print("account balance is $%.02f\n", self->balance);
}

void bank_account_withdraw (BankAccount *self, gdouble amount) {
    BANK_ACCOUNT_GET_CLASS(self)->withdraw(self, amount);
}

void bank_account_withdraw_real (BankAccount *self, gdouble amount) {
    if (self->balance < amount)
        g_error("Account overdrawn");
    self->balance -= amount;
}

static void bank_account_get_property (GObject    *obj,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec) {
    BankAccount *self = BANK_ACCOUNT(obj);
    
    switch (prop_id) {
    case PROP_BALANCE:
        g_value_set_double(value, self->balance);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void bank_account_set_property (GObject      *obj,
                                       guint         prop_id,
                                       const GValue *value,
                                       GParamSpec   *pspec) {
    BankAccount *self = BANK_ACCOUNT(obj);
    
    switch (prop_id) {
    case PROP_BALANCE:
        self->balance = g_value_get_double(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
        break;
    }
}

static void bank_account_class_init (BankAccountClass *cls) {
    GObjectClass *gobject_cls = G_OBJECT_CLASS(cls);

    gobject_cls->get_property = bank_account_get_property;
    gobject_cls->set_property = bank_account_set_property;
    cls->print = bank_account_print_real;
    cls->withdraw = bank_account_withdraw_real;
    
    g_object_class_install_property(
        gobject_cls,
        PROP_BALANCE,
        g_param_spec_double(
            "balance", "Balance", "Bank account balance",
            -G_MAXDOUBLE, /* => */ G_MAXDOUBLE, /* def => */ 0.0,
            G_PARAM_READWRITE));
}

static void bank_account_init (BankAccount *self) {
    /* nop  */
}

void bank_account_deposit (BankAccount *self, gdouble amount) {
    self->balance += amount;
}

