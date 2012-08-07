#!/usr/bin/perl -w

$_ = "Apple is red";
($fruit,$color) =  /(.*)\sis\s(.*)/;
print "The fruit is: $fruit\n";	
print "The color is: $color\n";

