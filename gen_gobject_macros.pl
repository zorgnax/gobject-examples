#!/usr/bin/perl

# A script to generate gobject boilerplate, give the name of the class 
# on the command line in camel case but you can use '_' to give hints to
# where it should separate words.
#
# e.g.
#     perl gen_gobject_macros.pl BankAccount
#     perl gen_gobject_macros.pl US_Currency
#     perl gen_gobject_macros.pl --interface Comparable
#

use Getopt::Long;

GetOptions(\my %args, "interface");

# args case: BankAccount, US_Currency
# (underscores are used as hints for where to break words up)
my ($ac) = @ARGV;

# camel case: BankAccount, USCurrency
my $cc = $ac;
$cc =~ s/_//g;

# lower case: bank_account, us_currency
my $lc = $ac;
$lc =~ s/([a-z])([A-Z])/$1_$2/g;
$lc = lc $lc;

# upper case: BANK_ACCOUNT, US_CURRENCY
my $uc = uc $lc;

if ($args{interface}) {
    print <<EOM;

typedef struct _${cc}      ${cc};
typedef struct _${cc}Iface ${cc}Iface;

struct _${cc}Iface {
    GTypeInterface parent;
};

#define TYPE_${uc}           (${lc}_get_type())
#define ${uc}(obj)           (G_TYPE_CHECK_INSTANCE_CAST    ((obj), TYPE_${uc}, ${cc}))
#define IS_${uc}(obj)        (G_TYPE_CHECK_INSTANCE_TYPE    ((obj), TYPE_${uc}))
#define ${uc}_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_${uc}, ${cc}Iface))

GType ${lc}_get_type (void);
EOM
}
else {
    print <<EOM;

typedef struct _${cc}      ${cc};
typedef struct _${cc}Class ${cc}Class;

struct _${cc} {
    GObject parent;
};

struct _${cc}Class {
    GObjectClass parent;
};

#define TYPE_${uc}           (${lc}_get_type())
#define ${uc}(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_${uc}, ${cc}))
#define ${uc}_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_${uc}, ${cc}Class))
#define IS_${uc}(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_${uc}))
#define IS_${uc}_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_${uc}))
#define ${uc}_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_${uc}, ${cc}Class))
#define ${lc}_new(...)       (g_object_new(TYPE_${uc}, ## __VA_ARGS__, NULL))

GType ${lc}_get_type (void);
EOM
}

