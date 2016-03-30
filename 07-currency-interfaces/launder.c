/*
An example based on the first roles recipe in the Moose cookbook
http://search.cpan.org/~drolsky/Moose-0.98/lib/Moose/Cookbook/Roles/Recipe1.pod

This one creates a USCurrency class that implements two roles, er,
interfaces. Printable and Comparable. Comparable implements an Eq interface
with g_type_interface_add_prerequisite() and shows that its possible for one
interface to involve another. Also it shows how one class can pass its
interface's requirements, e.g. to_string(), and the interface can use these
to implement other functions, e.g. print().
*/

#include <glib-object.h>
#include "tap.h"
#include "uscurrency.h"
#include "printable.h"
#include "comparable.h"
#include "eq.h"

int main () {
    g_type_init();

    plan(21);

    g_set_print_handler((GPrintFunc) diag);
    g_print("ready to launder money through a poor orphanage\n");

    USCurrency *cash  = us_currency_new(1.06);
    USCurrency *money = us_currency_new(1.05);
    USCurrency *green = us_currency_new(1.05);
    USCurrency *dough = us_currency_new(3.2E6);

    g_print("cash:  "); printable_print(PRINTABLE(cash));
    g_print("money: "); printable_print(PRINTABLE(money));
    g_print("green: "); printable_print(PRINTABLE(green));
    g_print("dough: "); printable_print(PRINTABLE(dough));

    gchar *cash_s  = printable_to_string(PRINTABLE(cash));
    gchar *money_s = printable_to_string(PRINTABLE(money));
    gchar *green_s = printable_to_string(PRINTABLE(green));
    gchar *dough_s = printable_to_string(PRINTABLE(dough));

    ok (comparable_compare(COMPARABLE(cash), COMPARABLE(money)) ==  1,
        "%s <=> %s == 1", cash_s, money_s);
    ok (comparable_compare(COMPARABLE(money), COMPARABLE(green)) ==  0,
        "%s <=> %s == 0", money_s, green_s);
    ok (comparable_compare(COMPARABLE(green), COMPARABLE(dough)) == -1,
        "%s <=> %s == -1", green_s, dough_s);

    ok (!comparable_less_than(COMPARABLE(cash), COMPARABLE(money)),
        "%s >= %s", cash_s, money_s);
    ok (!comparable_less_than(COMPARABLE(money), COMPARABLE(green)),
        "%s >= %s", money_s, green_s);
    ok (comparable_less_than(COMPARABLE(green), COMPARABLE(dough)),
        "%s < %s", green_s, dough_s);

    ok (comparable_greater_than(COMPARABLE(cash), COMPARABLE(money)),
        "%s > %s", cash_s, money_s);
    ok (!comparable_greater_than(COMPARABLE(money), COMPARABLE(green)),
        "%s <= %s", money_s, green_s);
    ok (!comparable_greater_than(COMPARABLE(green), COMPARABLE(dough)),
        "%s <= %s", green_s, dough_s);

    ok (!comparable_equal_to(COMPARABLE(cash), COMPARABLE(money)),
        "%s != %s", cash_s, money_s);
    ok (comparable_equal_to(COMPARABLE(money), COMPARABLE(green)),
        "%s == %s", money_s, green_s);
    ok (!comparable_equal_to(COMPARABLE(green), COMPARABLE(dough)),
        "%s != %s", green_s, dough_s);

    ok (!comparable_less_than_or_equal_to(COMPARABLE(cash), COMPARABLE(money)),
        "%s > %s", cash_s, money_s);
    ok (comparable_less_than_or_equal_to(COMPARABLE(money), COMPARABLE(green)),
        "%s <= %s", money_s, green_s);
    ok (comparable_less_than_or_equal_to(COMPARABLE(green), COMPARABLE(dough)),
        "%s <= %s", green_s, dough_s);

    ok (comparable_greater_than_or_equal_to(COMPARABLE(cash), COMPARABLE(money)),
        "%s >= %s", cash_s, money_s);
    ok (comparable_greater_than_or_equal_to(COMPARABLE(money), COMPARABLE(green)),
        "%s >= %s", money_s, green_s);
    ok (!comparable_greater_than_or_equal_to(COMPARABLE(green), COMPARABLE(dough)),
        "%s < %s", green_s, dough_s);

    ok (eq_equal_to(EQ(money), EQ(green)), "%s == %s", cash_s, money_s);
    ok (eq_not_equal_to(EQ(cash), EQ(money)), "%s != %s", money_s, green_s);
    ok (eq_not_equal_to(EQ(green), EQ(dough)), "%s != %s", green_s, dough_s);

    return exit_status();
}

