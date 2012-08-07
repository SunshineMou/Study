#!/usr/bin/perl -w

print "Please input the pattern:";
$pat = <STDIN>;
chomp $pat;

$_ = "The pharse that pays";
if(/$pat/)
{
	print "The source is: $_ . It contains the pattern $pat\n";	
}
else
{
	print "The source is: $_ . It does not contain the pattern $pat\n";
}
