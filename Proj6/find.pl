#!/usr/bin/perl -w
use strict;

my $regex;
my $i;
if($ARGV[0] ne "-i"){
	$regex = $ARGV[0];
	$i = 1;
} else {
	$regex = $ARGV[1];
	$i = 2;
}

while($i <= $#ARGV){
	my@str = split /\//, $ARGV[$i];
	if($ARGV[0] ne "-i"){
		if($ARGV[$i] =~ /$regex/){
			print "$str[$#str]\n";
		} else {
			open(IN, "<", $ARGV[$i]) or die "could not open: $!\n";
			while(<IN>){
				if($_ =~ /$regex/){
					print "$str[$#str]: $_";
					last;
				}
			}
		}
	} else {
		my $file = $str[$#str];
		if($ARGV[$i] !~ /$regex/){
			open(IN, "<", $ARGV[$i]) or die "could not open: $!\n";
			while(<IN>){
				if($_ =~ /$regex/){
					$file = "";
				}
			}
			if($file){
				print "$file\n";
			}
		}
	}
	$i++;
}

close(IN);

