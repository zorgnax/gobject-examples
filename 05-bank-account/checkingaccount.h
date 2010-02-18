#ifndef __CHECKINGACCOUNT_H__
#define __CHECKINGACCOUNT_H__

#include <glib-object.h>
#include "bankaccount.h"

typedef struct _CheckingAccount      CheckingAccount;
typedef struct _CheckingAccountClass CheckingAccountClass;

struct _CheckingAccount {
    BankAccount parent;
    BankAccount *overdraft_account;
};

struct _CheckingAccountClass {
    BankAccountClass parent;
};

#define TYPE_CHECKING_ACCOUNT           (checking_account_get_type())
#define CHECKING_ACCOUNT(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CHECKING_ACCOUNT, CheckingAccount))
#define CHECKING_ACCOUNT_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_CHECKING_ACCOUNT, CheckingAccountClass))
#define IS_CHECKING_ACCOUNT(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CHECKING_ACCOUNT))
#define IS_CHECKING_ACCOUNT_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_CHECKING_ACCOUNT))
#define CHECKING_ACCOUNT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_CHECKING_ACCOUNT, CheckingAccountClass))
#define checking_account_new(...)       (g_object_new(TYPE_CHECKING_ACCOUNT, ## __VA_ARGS__, NULL))

GType checking_account_get_type (void);

#endif

