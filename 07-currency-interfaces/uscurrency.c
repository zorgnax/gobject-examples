#include <glib-object.h>
#include "uscurrency.h"
#include "printable.h"
#include "comparable.h"
#include "eq.h"

USCurrency *us_currency_new (gdouble amount) {
    USCurrency *self = g_object_new(TYPE_US_CURRENCY, NULL);
    self->amount = amount;
    return self;
}

static gchar *us_currency_to_string (Printable *obj) {
    USCurrency *self = US_CURRENCY(obj);
    return g_strdup_printf("$%0.2f USD", self->amount);
}

static gint us_currency_compare (Comparable *obj1, Comparable *obj2) {
    USCurrency *self = US_CURRENCY(obj1), *other = US_CURRENCY(obj2);
    /* amount of money is the same if there's less than 1 cent difference  */
    return ABS(self->amount - other->amount) < 0.01 ?  0
         : self->amount < other->amount             ? -1
         :                                             1
         ;
}

static void implement_printable (PrintableIface *iface) {
    iface->to_string = us_currency_to_string;
}

static void implement_comparable (ComparableIface *iface) {
    iface->compare = us_currency_compare;
}

static void us_currency_class_init (USCurrencyClass *cls) {}
static void us_currency_init       (USCurrency *cls)      {}

G_DEFINE_TYPE_WITH_CODE
(
    USCurrency,
    us_currency,
    G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE(TYPE_PRINTABLE,  implement_printable)
    G_IMPLEMENT_INTERFACE(TYPE_COMPARABLE, implement_comparable)
    G_IMPLEMENT_INTERFACE(TYPE_EQ,         NULL)
);

