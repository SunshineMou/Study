#!/usr/bin/perl
use strict;
use warnings;

my @music = ('White Album,Beatles','Graceland,Paul Simon','A boy named Sue, Goo Goo Dolls');

foreach my $record (@music)
{
    my ($record_name , $artist) = split(/,/,$record);
}
my $numbers = join(',', (1..10)); 
    print $numbers."\n";
my @number = qw(12 23 25 26 28 35 66);
my @sorted = sort{ $a<=>$b ;} @number;
    print @sorted;

