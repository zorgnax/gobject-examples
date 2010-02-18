#ifndef __USCURRENCY_H__
#define __USCURRENCY_H__

#include <glib-object.h>

typedef struct _USCurrency      USCurrency;
typedef struct _USCurrencyClass USCurrencyClass;

struct _USCurrency {
    GObject parent;
    gdouble amount;
};

struct _USCurrencyClass {
    GObjectClass parent;
};

#define TYPE_US_CURRENCY           (us_currency_get_type())
#define US_CURRENCY(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_US_CURRENCY, USCurrency))
#define US_CURRENCY_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_US_CURRENCY, USCurrencyClass))
#define IS_US_CURRENCY(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_US_CURRENCY))
#define IS_US_CURRENCY_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_US_CURRENCY))
#define US_CURRENCY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_US_CURRENCY, USCurrencyClass))

GType       us_currency_get_type (void);
USCurrency *us_currency_new      (gdouble amount);

#endif

