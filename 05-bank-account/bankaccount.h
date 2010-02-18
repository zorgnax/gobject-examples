#ifndef __BANKACCOUNT_H__
#define __BANKACCOUNT_H__

#include <glib-object.h>

typedef struct _BankAccount      BankAccount;
typedef struct _BankAccountClass BankAccountClass;

struct _BankAccount {
    GObject parent;
    gdouble balance;
};

struct _BankAccountClass {
    GObjectClass parent;
    void (*print)    (BankAccount *self);
    void (*withdraw) (BankAccount *self, gdouble amount);
};

#define TYPE_BANK_ACCOUNT           (bank_account_get_type())
#define BANK_ACCOUNT(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BANK_ACCOUNT, BankAccount))
#define BANK_ACCOUNT_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_BANK_ACCOUNT, BankAccountClass))
#define IS_BANK_ACCOUNT(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BANK_ACCOUNT))
#define IS_BANK_ACCOUNT_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_BANK_ACCOUNT))
#define BANK_ACCOUNT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_BANK_ACCOUNT, BankAccountClass))
#define bank_account_new(...)       (g_object_new(TYPE_BANK_ACCOUNT, ## __VA_ARGS__, NULL))

GType bank_account_get_type (void);
void  bank_account_print    (BankAccount *self);
void  bank_account_withdraw (BankAccount *self, gdouble amount);
void  bank_account_deposit  (BankAccount *self, gdouble amount);

#endif

