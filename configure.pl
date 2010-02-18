#!/usr/bin/perl

use File::Basename;

# Generates the makefile

my @progs;
my $rules;

for my $dir (grep -d, glob "*") {
    my @all_files = grep -f, glob "$dir/*.[ch]";
    my @c_files   = grep -f, glob "$dir/*.c";
    my $prog;
    for my $file (@c_files) {
        open my $fh, $file or die "Unable to open $file: $!";
        my $text = do {local $/; <$fh>};
        close $fh;
        # find the file with the main function
        next unless $text =~ /int \s+ main \s* \(/x;
        ($prog) = $file =~ m/ (.+) \. \w+ $/x;
        push @progs, $prog;
        last;
    }
    die "huh?! no prog" if !defined $prog;
    $rules .= "$prog: @all_files\n" .
              "\tgcc \${CFLAGS} -o \$\@ @c_files \${LDFLAGS}\n" .
              "\tcp -v $prog .\n\n";
}

my @bprogs = map basename($_), @progs;

open my $make, ">", "Makefile" or die "Unable to create Makefile: $!";

print $make <<EOF;
CFLAGS  = `pkg-config --cflags gobject-2.0` -g
LDFLAGS = `pkg-config --libs gobject-2.0` -ltap
PROGS   = @progs
BPROGS  = @bprogs

all: \${PROGS}

clean:
	rm -rvf \${PROGS} \${BPROGS}

$rules

EOF

close $make;

