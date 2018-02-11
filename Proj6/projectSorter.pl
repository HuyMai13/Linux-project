#!/usr/bin/perl -w
use strict;

my @files = glob("./$ARGV[0]/*");

foreach my $file(@files) {
	my @f = split /\//, $file;
	if ($f[$#f] =~ /^proj(.*)\./){
		`mkdir -p DataB/assignment$1`;
		`mv $file DataB/assignment$1/`;
	} elsif($f[$#f] !~ /^\.+$/ && not -d $file){
		`mkdir -p DataB/misc`;
		`mv $file DataB/misc/`;
	}
}