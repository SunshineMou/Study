#!/usr/bin/perl -w

print "Please input the a string:\n";
while(<>)
{
	while(/(\w[\w-]*)/g)
	{
		$Words{$1}++;
	}
}
	
foreach(keys %Words)
{
	print"$_  $Words{$_}\n";
}

