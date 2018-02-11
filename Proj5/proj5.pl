#!/usr/bin/perl -w
use strict;

open(IN, "<", "p5Customer.txt") or die "could not open: $!\n";

my @data;
my $i=0;
while(<IN>){
	chomp($_);
	my @line = split(',', $_);
	my @token = split ' ', $line[1];
	if($line[4] > $line[3]){
		$line[3] = $token[-1];
		$data[$i] = [@line];
		$i++;
	}
}

my $size = $i;
my @template;
$i=0;
while($i < $size){
	open(IN, "<", "template.txt") or die "could not open: $!\n";
	@template = <IN>;
	my $temp;
	foreach $temp(@template){
		$temp =~ s/EMAIL/$data[$i][0]/g;
		$temp =~ s/FULLNAME/$data[$i][1]/g;
		$temp =~ s/NAME/$data[$i][3]/g;
		$temp =~ s/TITLE/$data[$i][2]/g;
		$temp =~ s/AMOUNT/$data[$i][4]/g;
		$temp =~ s/DATE/$ARGV[0]/g;
	}
	open (OUT, ">", $data[$i][0]) or die "could not open: $!\n";
	print OUT @template;
	$i++;
}
close(IN);
close(OUT);


